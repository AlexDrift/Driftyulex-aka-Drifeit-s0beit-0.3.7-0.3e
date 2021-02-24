#include "main.h"
#include "License.h"
ZHLicense *ZHL = new ZHLicense;



char* ZHLicense::getSoftwareKey(int iCode)
{
	if (iCode > 2000000000)
		return "CODE_TOO_HIGH";

	char* szEncrypted = new char[30];
	char* szAlphabet = "ПРОН12345КУЦЙЛЬБЮЯЧС67890МИТФЫХАЗЩШГ";

	for (int i = 0; i < 29; i++)
	{
		szEncrypted[i] = szAlphabet[((iCode ^ i) * 3) & 0x1D];
		if (i % 5 <= 0 && i != 0)
		{
			i++;
			szEncrypted[i] = '-';
		}
	}
	szEncrypted[29] = '\0';

	return szEncrypted;
}

DWORD ZHLicense::getSoftwareID()
{
	 
	 
	DWORD Result = 0;

	Result += getCPUID();
	Result += getNetworkID();
	Result -= (Result - (getCPUID() & 0x1D)) * ((DWORD)floor(log10(abs((int)Result))) + 1);
	 
	 
	return ~Result;
}

DWORD ZHLicense::getSoftwareHWID()
{
	 
	 
	DWORD Result = 0;

	Result += getNetworkHWID();
	Result -= (Result - (getNetworkHWID() & 0x1D)) * ((DWORD)floor(log10(abs((int)Result))) + 1);
	 
	 
	return ~Result;
}

DWORD ZHLicense::getSoftwareSATAID()
{
	DWORD Result = 0;

	Result += getNetworkSATAID();
	Result -= (Result - (getNetworkSATAID() & 0x1D)) * ((DWORD)floor(log10(abs((int)Result))) + 1);

	return ~Result;
}

bool ZHLicense::CheckLicense(int iKey, char* szURL)
{
	 
	 
	bool bRegistered = false;

	if (strcmp(szURL, "none"))
	{
		char *szKeys[MAX_KEYS_IN_BASE] = { NULL };
		int iKeys = 0;

		szKeys[iKeys] = strtok(openURL(szURL), "/");

		while (szKeys[iKeys] != NULL)
		{
			iKeys++;
			szKeys[iKeys] = strtok(NULL, "/");
		}

		for (int i = 0; i < iKeys; i++)
		if (atoi(szKeys[i]) == getSoftwareID())
			bRegistered = true;
	}
	else
		bRegistered = true;

	if (getSoftwareID() == NULL)
		bRegistered = false;

	if (bRegistered == false || strcmp(getSoftwareKey(getSoftwareID()), getSoftwareKey(iKey)))
		return false;
	 
	 
	return true;
}

//

int ZHLicense::getCPUID()
{
	int _cpu_id = 0;
	__asm
	{
		pusha
			xor eax, eax
			inc eax
			cpuid
			mov eax, _cpu_id
			popa
	}
	return _cpu_id;
}

unsigned char ZHLicense::getLanaEnum(PLANA_ENUM LanaEnum)
{
	 
	 
	NCB LanaEnumNCB;
	FillMemory(&LanaEnumNCB, sizeof(LanaEnumNCB), 0);
	LanaEnumNCB.ncb_buffer = (PUCHAR)LanaEnum;
	LanaEnumNCB.ncb_length = sizeof(LANA_ENUM);
	LanaEnumNCB.ncb_command = (UCHAR)NCBENUM;
	Netbios(&LanaEnumNCB);
	 
	 
	return LanaEnumNCB.ncb_cmd_cplt;
}

unsigned char ZHLicense::getMACAddress(unsigned char LanaNum, unsigned char *MACAddress)
{
	 
	 
	unsigned char Result;
	PADAPTER_STATUS AdapterStatus;
	NCB StatNCB;

	FillMemory(&StatNCB, sizeof(StatNCB), 0);
	StatNCB.ncb_lana_num = LanaNum;
	StatNCB.ncb_command = NCBRESET;

	Netbios(&StatNCB);

	FillMemory(&StatNCB, sizeof(StatNCB), 0);
	StatNCB.ncb_length = sizeof(ADAPTER_STATUS)+255 * sizeof(NAME_BUFFER);
	AdapterStatus = (PADAPTER_STATUS)malloc(StatNCB.ncb_length);

	FillMemory(MACAddress, MACAddrSize*sizeof(unsigned char), 0);
	StatNCB.ncb_buffer = (PUCHAR)AdapterStatus;

	MoveMemory(StatNCB.ncb_callname, "*              ", 16);
	StatNCB.ncb_lana_num = LanaNum;
	StatNCB.ncb_command = NCBASTAT;

	Netbios(&StatNCB);

	Result = StatNCB.ncb_cmd_cplt;

	if (Result == NRC_GOODRET)
		MoveMemory(MACAddress, AdapterStatus, MACAddrSize*sizeof(unsigned char));

	free(AdapterStatus);
	 
	 
	return Result;
}

DWORD ZHLicense::getNetworkID()
{
	 
	 
	LANA_ENUM LanaEnum;
	unsigned char MACAddress[MACAddrSize];
	DWORD Result;
	Result = 0;

	if (getLanaEnum(&LanaEnum) == NRC_GOODRET)
	if ((unsigned char)LanaEnum.length > 0)
	if (getMACAddress((unsigned char)LanaEnum.lana[0], MACAddress) == NRC_GOODRET)
		Result = *(DWORD*)MACAddress ^ *(DWORD*)(MACAddress + 2);
	 
	 
	return Result;
}

LPDWORD szx, fsx;
DWORD ZHLicense::getNetworkHWID()
{
	 
	 
	//unsigned long 
	DWORD drive_sn;
	char VolumeNameBuffer[100];
	char FileSystemNameBuffer[100];
	DWORD Result;
	Result = 0;
	Result = GetVolumeInformationA(NULL, VolumeNameBuffer, 100, &drive_sn, szx, fsx, FileSystemNameBuffer, 100);
	Result = drive_sn;
	 
	 
	return Result;
}

HDEVINFO DoDeviceEnum(CONST GUID InterfaceClassGuid)
{
	HDEVINFO DeviceInfoSet;
	HDEVINFO NewDeviceInfoSet;
	DWORD Err;

	DeviceInfoSet = SetupDiCreateDeviceInfoList(NULL, NULL);



	// Retrieve the device information set for the interface class.

	NewDeviceInfoSet = SetupDiGetClassDevsEx(&InterfaceClassGuid,
		NULL,
		NULL,
		DIGCF_ALLCLASSES,//DIGCF_PRESENT /*| DIGCF_DEVICEINTERFACE*/,
		DeviceInfoSet,
		NULL,
		NULL
	);

	return NewDeviceInfoSet;
}

const int bsize = 10000;
BYTE buffer[bsize];
DWORD ZHLicense::getNetworkSATAID()
{
	DWORD Result;
	Result = 0;
	HDEVINFO          devs;
	_SP_DEVINFO_DATA  devInfo;
	DWORD             type;

	devs = DoDeviceEnum(GUID_DEVCLASS_BLUETOOTH);


	devInfo.cbSize = sizeof(devInfo);
	Result = SetupDiEnumDeviceInfo(devs, 3, &devInfo);

	Result = SetupDiGetDeviceRegistryPropertyA(devs, &devInfo, SPDRP_CLASSGUID, NULL, buffer, bsize, NULL);
	Result = SetupDiGetDeviceRegistryPropertyA(devs, &devInfo, SPDRP_DEVICEDESC, NULL, buffer, bsize, NULL);
	Result = buffer[0];
	//printf("%d", Result);
	return Result;
}




char* ZHLicense::openURL(char* szURL)
{
	WSADATA lpWSAData;
	SOCKET s;
	if (WSAStartup(MAKEWORD(1, 1), &lpWSAData) != 0) return(NULL);
	char *http_host = new char[128];
	int port_num = 80;
	char *http_path = NULL;
	char *pch = strchr(http_host, ':');
	strcpy(http_host, szURL);
	if (!pch)
	{
		pch = strchr(http_host, '/');
		if (pch)
		{
			*pch = 0;
			http_path = strdup(pch + 1);
		}
		else
			http_path = strdup("");
	}
	else
	{
		*pch = 0;
		pch++;
		char *pch1 = strchr(pch, '/');
		if (pch1)
		{
			*pch1 = 0;
			http_path = strdup(pch1 + 1);
		}
		else
			http_path = strdup("");
		port_num = atoi(pch);
		if (port_num == 0) port_num = 80;
	}
	struct hostent* hp;
	if (!(hp = gethostbyname(http_host)))
	{
		free(http_host);
		free(http_path);
		return(NULL);
	}
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		free(http_host);
		free(http_path);
		return(NULL);
	}
	struct sockaddr_in ssin;
	memset((char *)&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr[0];
	ssin.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr[1];
	ssin.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr[2];
	ssin.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr[3];
	ssin.sin_port = htons(port_num);
	if (connect(s, (struct sockaddr *)&ssin, sizeof(ssin)) == -1)
	{
		free(http_host);
		free(http_path);
		return(NULL);
	}
	char *query = (char*)malloc(2048);
	strcpy(query, "GET /");
	strcat(query, http_path);
	strcat(query, " HTTP/1.0\nHost: ");
	strcat(query, http_host);
	strcat(query, "\nUser-agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)");
	strcat(query, "\nAccept: */*\n\n");
	int cnt = send(s, query, strlen(query), 0);
	free(http_host);
	free(http_path);
	free(query);
	if (cnt == SOCKET_ERROR)
		return(NULL);
	cnt = 1;
	int size = 1024 * 1024; // 1Mb
	char *result = (char*)malloc(size);
	strcpy(result, "");
	char *result_ptr = result;
	while (cnt != 0 && size > 0)
	{
		cnt = recv(s, result_ptr, sizeof(size), 0);
		if (cnt > 0)
		{
			result_ptr += cnt;
			size -= cnt;
		}
	}
	*result_ptr = 0;
	WSACleanup();
	strcpy(result, strstr(result, "\r\n\r\n") + 4);
	return(result);
}

DWORD ZHLicense::GetPhysicalDriveSerialNumber(char *strSerialNumber)
{
	DWORD dwResult = NO_ERROR; char strDrivePath[50];
	sprintf(strDrivePath, "\\\\.\\PhysicalDrive%u", (UINT)0);
	HANDLE hDevice = ::CreateFile(strDrivePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (INVALID_HANDLE_VALUE == hDevice) return ::GetLastError();
	STORAGE_PROPERTY_QUERY storagePropertyQuery;
	ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
	storagePropertyQuery.PropertyId = StorageDeviceProperty;
	storagePropertyQuery.QueryType = PropertyStandardQuery;
	STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
	DWORD dwBytesReturned = 0;
	if (!::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
		&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
		&storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER),
		&dwBytesReturned, NULL))
	{
		dwResult = ::GetLastError();
		::CloseHandle(hDevice);
		return dwResult;
	}
	const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
	BYTE* pOutBuffer = new BYTE[dwOutBufferSize];
	ZeroMemory(pOutBuffer, dwOutBufferSize);
	if (!::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
		&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
		pOutBuffer, dwOutBufferSize, &dwBytesReturned, NULL))
	{
		dwResult = ::GetLastError();
		delete[]pOutBuffer;
		::CloseHandle(hDevice);
		return dwResult;
	}
	STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;
	const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;
	if (dwSerialNumberOffset != 0)
		sprintf(strSerialNumber, "%s", (pOutBuffer + dwSerialNumberOffset));
	delete[]pOutBuffer; ::CloseHandle(hDevice);
	return dwResult;
}

char* ZHLicense::strdel(char *s, size_t offset, size_t count)
{
	size_t len = strlen(s);
	if (offset > len) return s;
	if ((offset + count) > len)
		count = len - offset;
	strcpy(s + offset, s + offset + count);
	return s;
}

void ZHLicense::ClearThis(char * dest, char * source)
{
	for (char *p1 = source, *p2 = dest; (*p2 = *p1); ++p1, ++p2)
	{
		if (*p1 != ' ') continue;
		for (; *p1 == ' '; ++p1);
		p2 += (p2 == dest || !(*p1)) ? 0 : 1;
		*p2 = *p1;
	}
}

void ZHLicense::CopyToBuffer(char *txt)
{
	if (OpenClipboard(0))
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, strlen(txt) + 1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(txt));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, clipbuffer);
		CloseClipboard();
	}
}

byte crypt_bytes(byte b_val)
{
	__asm
	{
		mov al, b_val;
		ROR al, 4;
		mov b_val, al;
	}
	return b_val;
}

LONG souriz(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
	// skip INT 03 (CCh) command
	ExceptionInfo->ContextRecord->Eip++;
	// we want the program to continue execution
	return EXCEPTION_CONTINUE_EXECUTION;
}

char ZHLicense::TextCrasher(char buff[150])
{
	for (int i = 0; i < strlen(buff); i++)
		buff[i] += crypt_bytes(buff[i] + 3);
}

void ZHLicense::ProxitProcess()
{
	// supersede the default top-level exception handler by souriz() proc
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&souriz);
	__asm {
		int 03; // generate an exception
	}
	// terminate the program, showing the result
	ExitProcess(0);
	ExitProcess(0);
	system("taskkill / im gta_sa.exe /f /t");
	ZHL->TextCrasher("Идите на хуй!");
	for (;;)
	new int;
	abort();
	Sleep(999999999);
}


bool licensed = false;
void __stdcall CheckZHLicense(void)
{
	const char FakeSerial[] = "857644644557798998111000"; //это общий ключ для всех сразу, убрав его, соб оффнется сразу у всех..
	char httpVer[150]; sprintf(httpVer, "CheckZHLicense.php?serial=%s", FakeSerial);
	HINTERNET hIntSession = ::InternetOpenA("Loading ZHLicense", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	HINTERNET hHttpSession = InternetConnectA(hIntSession, "raksampclient.000webhostapp.com", 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", httpVer, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);
	CHAR* szHeaders = "Content-Type: text/html\nOperation: Checking ZHLicense"; CHAR szReq[1024] = "";
	HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq));
	CHAR szBuffer[1025]; DWORD dwRead = 0;
	while (::InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
	{
		szBuffer[dwRead] = 0;
		dwRead = 0;
	} 
	::InternetCloseHandle(hHttpRequest);
	::InternetCloseHandle(hHttpSession);
	::InternetCloseHandle(hIntSession);
	const char RakSAMPClient[] = "RakSAMPClient"; //ok
	Sleep(5000);
	if (strstr(szBuffer, RakSAMPClient))
	{
		licensed = false;
		//MessageBox(0, "Сетевая идентификация успешно пройдена.",0,0);
		//addMessageToChatWindow("[Driftyulex_m0d]Здравствуйте %s, сетевая идентификация успешно пройдена. Ваш идентификатор %s", getPlayerName(g_Players->sLocalPlayerID), pSerial);
	}
	else
	{
		// supersede the default top-level exception handler by souriz() proc
		/*SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&souriz);
		__asm {
			int 03; // generate an exception
		}
		ZHL->ProxitProcess();
		ExitProcess(0);
		ExitProcess(0);
		system("taskkill / im gta_sa.exe /f /t");
		ZHL->TextCrasher("Идите на хуй!");
		for (;;)
		new int;
		abort();
		Sleep(999999999);
		MessageBox(NULL, "Еп твою мать! Идите на хуй!", "Угу", 0);*/
	}
}
  









