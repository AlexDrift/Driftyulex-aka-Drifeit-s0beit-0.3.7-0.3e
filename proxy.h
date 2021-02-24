
namespace SOCKS5
{
#pragma pack( push, 1 )

	struct AuthRequestHeader
	{
		byte	byteVersion;
		byte	byteAuthMethodsCount;
		byte	byteMethods[1];
	};

	struct AuthRespondHeader
	{
		byte	byteVersion;
		byte	byteAuthMethod;
	};

	struct ConnectRequestHeader
	{
		byte	byteVersion;
		byte	byteCommand;
		byte	byteReserved;
		byte	byteAddressType;
		ULONG	ulAddressIPv4;
		USHORT	usPort;
	};

	struct ConnectRespondHeader
	{
		byte	byteVersion;
		byte	byteResult;
		byte	byteReserved;
		byte	byteAddressType;
		ULONG	ulAddressIPv4;
		USHORT	usPort;
	};

	struct UDPDatagramHeader
	{
		USHORT	usReserved;
		byte	byteFragment;
		byte	byteAddressType;
		ULONG	ulAddressIPv4;
		USHORT	usPort;
	};

#pragma pack( pop )
};

class Proxy
{
public:
	Proxy() : m_sockTCP(INVALID_SOCKET), m_bStarted(false) {};

	bool Start(ULONG proxyIP, USHORT proxyPort);
	int SendTo(SOCKET socket, char *data, int dataLength, int flags, sockaddr_in *to, int tolen);
	int RecvFrom(SOCKET socket, char *buffer, int bufferLength, int flags, sockaddr_in *from, int *fromlen);
	bool IsStarted(void) { return m_bStarted; };
	void Restart(void);
private:
	SOCKET m_sockTCP;
	sockaddr_in m_proxyServerAddr;
	ULONG m_proxyIP;
	USHORT m_proxyPort;
	bool m_bStarted;
};

extern Proxy *proxy;