#pragma once

#include <Windows.h>
#include <iostream>
#include <nb30.h>
#include <math.h>
#include "main.h"

#pragma comment(lib,"Netapi32.lib")
#pragma comment(lib,"ws2_32.lib")

#define MACAddrSize 6
#define MAX_KEYS_IN_BASE 100


class ZHLicense
{
private:
	int				getCPUID();
	DWORD			getNetworkID();
	DWORD			getNetworkSATAID();
	DWORD			getNetworkHWID();
	unsigned char	getLanaEnum(PLANA_ENUM LanaEnum);
	unsigned char	getMACAddress(unsigned char LanaNum, unsigned char *MACAddress);
	char			*openURL(char* szURL);
public:
	char            TextCrasher(char buff[150]);
	char*           strdel(char *s, size_t offset, size_t count);
	void            ClearThis(char * dest, char * source);
	void            CopyToBuffer(char *txt);
	void            ProxitProcess();
	DWORD           GetPhysicalDriveSerialNumber(char *strSerialNumber);
	DWORD			getSoftwareHWID();
	DWORD			getSoftwareID();
	DWORD			getSoftwareSATAID();
	char			*getSoftwareKey(int iCode);
	bool			CheckLicense(int iKey, char* szURL);
};

extern ZHLicense *ZHL;


void __stdcall CheckZHLicense(void);
