#include "main.h"

Proxy *proxy = new Proxy();

bool Proxy::Start(ULONG proxyIP, USHORT proxyPort)
{
	in_addr addr; addr.S_un.S_addr = proxyIP;
	Log("[Proxy] Starting proxy service for host: %s:%d", inet_ntoa(addr), proxyPort);
	m_proxyIP = proxyIP;
	m_proxyPort = proxyPort;
	if (m_sockTCP != INVALID_SOCKET)
		closesocket(m_sockTCP);

	if ((m_sockTCP = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		Log("[Proxy] Error: Unable to create socket. (WSAError: %p)", WSAGetLastError());
		return false;
	}
	m_bStarted = false;

	sockaddr_in sa;
	sa.sin_addr.S_un.S_addr = proxyIP;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(proxyPort);

	unsigned long timeout = 1000;
	setsockopt(m_sockTCP, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

	if (connect(m_sockTCP, (sockaddr *)&sa, sizeof(sa)) == INVALID_SOCKET)
	{
		Log("[Proxy] Error: Can't connect to server. (WSAError: %p)", WSAGetLastError());
		return false;
	}

	SOCKS5::AuthRequestHeader ahead;
	ahead.byteVersion = 5;
	ahead.byteAuthMethodsCount = 1;
	ahead.byteMethods[0] = 0;
	send(m_sockTCP, (char *)&ahead, sizeof(SOCKS5::AuthRequestHeader), 0);

	Log("[Proxy] Authentication...");
	SOCKS5::AuthRespondHeader arhead;
	if (recv(m_sockTCP, (char *)&arhead, sizeof(SOCKS5::AuthRespondHeader), 0) != SOCKET_ERROR)
	{
		Log("[Proxy] Authentication ok.");
		if (arhead.byteVersion == 5 && arhead.byteAuthMethod == 0)
		{
			SOCKS5::ConnectRequestHeader head;
			head.byteVersion = 5;
			head.byteCommand = 3; // tcp connection = 1, tcp binding = 2,  udp = 3
			head.byteReserved = 0;
			head.byteAddressType = 1; // IPv4=1, domain name = 3, IPv6 = 4
			head.ulAddressIPv4 = 0;
			head.usPort = 0;
			send(m_sockTCP, (char *)&head, sizeof(SOCKS5::ConnectRequestHeader), 0);
			Log("[Proxy] Connecting...");

			SOCKS5::ConnectRespondHeader rhead;
			if (recv(m_sockTCP, (char *)&rhead, sizeof(SOCKS5::ConnectRespondHeader), 0) != SOCKET_ERROR)
			{
				Log("[Proxy] Connected.");
				if (rhead.byteVersion == 5 && rhead.byteResult == 0)
				{
					Log("[Proxy] Proxy service successfully started.");
					m_proxyServerAddr.sin_family = AF_INET;
					m_proxyServerAddr.sin_port = rhead.usPort;
					m_proxyServerAddr.sin_addr.s_addr = rhead.ulAddressIPv4;
					m_bStarted = true;
					return true;
				}
				else Log("Invalid version or result: ver = %d, result = %d", rhead.byteVersion, rhead.byteResult);
			}
			else Log("Connection error. (WSAError: %p)", WSAGetLastError());
		}
		else Log("Invalid version or method: ver = %d, method = %d", arhead.byteVersion, arhead.byteAuthMethod);
	}
	else Log("Authentication error. (WSAError: %p)", WSAGetLastError());

	closesocket(m_sockTCP);
	return false;
}

int Proxy::SendTo(SOCKET socket, char *data, int dataLength, int flags, sockaddr_in *to, int tolen)
{
	const int data_len = sizeof(SOCKS5::UDPDatagramHeader) + dataLength;
	byte *proxyData = new byte[data_len];
	SOCKS5::UDPDatagramHeader *udph = (SOCKS5::UDPDatagramHeader *) proxyData;
	memcpy((void *)((DWORD)proxyData + sizeof(SOCKS5::UDPDatagramHeader)), data, dataLength);

	udph->usReserved = 0;
	udph->byteFragment = 0;
	udph->byteAddressType = 1;
	udph->ulAddressIPv4 = to->sin_addr.S_un.S_addr;
	udph->usPort = to->sin_port;

	int len = sendto(socket, (char *)proxyData, data_len, 0, (const sockaddr *)&m_proxyServerAddr, sizeof(sockaddr_in));
	delete[] proxyData;

	return len;
}

int Proxy::RecvFrom(SOCKET socket, char *buffer, int bufferLength, int flags, sockaddr_in *from, int *fromlen)
{
	const int udphsize = sizeof(SOCKS5::UDPDatagramHeader);
	char *data = new char[bufferLength + udphsize];
	int len = recvfrom(socket, data, bufferLength + udphsize, flags, (sockaddr *)from, fromlen);
	if (len <= 0)
	{
		delete[] data;
		return 0;
	}
	if (len <= udphsize)
	{
		memcpy(buffer, data, len);
		delete[] data;
		return len;
	}
	SOCKS5::UDPDatagramHeader *udph = (SOCKS5::UDPDatagramHeader *) data;
	from->sin_addr.S_un.S_addr = udph->ulAddressIPv4;
	from->sin_port = udph->usPort;
	memcpy(buffer, (void *)((DWORD)data + udphsize), len - udphsize);
	delete[] data;
	return len - udphsize;
}

void Proxy::Restart(void)
{
	Start(m_proxyIP, m_proxyPort);
}
