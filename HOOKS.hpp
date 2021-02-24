#include "main.h"
#include <string>
#include <map>
using namespace std;

typedef enum TypeHOOK TypeHOOK;
typedef unsigned int   size_t;
enum TypeHOOK
{
	Jump = 0,
	Call,
	Call_s
};
class CHOOKS
{
	struct VirtFunc{
		DWORD addr = 0;
		DWORD len = 0;
		bool rehook = false;
		bool Call_s = false;
	};
	struct ByteInfo{
		byte *bytes;
		size_t len;
		VirtFunc virt;
	};
	map<DWORD, ByteInfo> HOOKaddr;
	void *memcpy_safe(void *_dest, const void *_src, size_t stLen)
	{
		if (_dest == nullptr || _src == nullptr || stLen == 0)
			return nullptr;

		MEMORY_BASIC_INFORMATION	mbi;
		VirtualQuery(_dest, &mbi, sizeof(mbi));
		VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);

		void	*pvRetn = memcpy(_dest, _src, stLen);
		VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);
		FlushInstructionCache(GetCurrentProcess(), _dest, stLen);
		return pvRetn;
	}
	int memset_safe(void *_dest, int c, DWORD len)
	{
		byte *dest = (byte *)_dest;
		byte buf[4096];
		memset(buf, c, (len > 4096) ? 4096 : len);
		for (;;)
		{
			if (len > 4096)
			{
				if (!memcpy_safe(dest, buf, 4096))
					return 0;
				dest += 4096;
				len -= 4096;
			}
			else
			{
				if (!memcpy_safe(dest, buf, len))
					return 0;
				break;
			}
		}
		return 1;
	}
	bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)
				return false;

		return (*szMask) == NULL;
	}
public:
	DWORD CreateHOOK(DWORD dwAddress, DWORD dwFunc, TypeHOOK type = Jump, size_t len = 5)
	{
		if (len < 5)
			return 0;

		DWORD data = type == Jump ? 0xE9 : 0xE8;

		bool rehook = false;
		if (*(byte*)dwAddress == 0xE9 || *(byte*)dwAddress == 0xE8)
		{
			len = 5;
			DWORD new_addr = (DWORD)VirtualAlloc(NULL, 15, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			memset((void*)new_addr, 0x90, 10);
			DWORD oldAddr = *(DWORD*)(dwAddress + 1);
			DWORD olddwFunc = oldAddr + (dwAddress + 5);
			
			*(byte*)(new_addr + 5) = *(byte*)dwAddress;
			*(DWORD*)(new_addr + 6) = olddwFunc - (new_addr + 10);

			if (*(byte*)dwAddress == 0xE8)
			{
				*(byte*)(new_addr + 10) = 0xE9;
				*(DWORD*)(new_addr + 11) = dwAddress - (new_addr + 15);
			}

			DWORD new_data = 0xE9;
			memcpy_safe((void*)dwAddress, &new_data, 1);
			new_data = new_addr - (dwAddress + 5);
			memcpy_safe((void*)(dwAddress + 1), &new_data, 4);

			HOOKaddr[new_addr].virt.addr = dwAddress;
			HOOKaddr[new_addr].virt.len = 15;
			HOOKaddr[new_addr].virt.rehook = true;
			HOOKaddr[new_addr].virt.Call_s = false;
			dwAddress = new_addr;
			rehook = true;
		}

		byte *OrigData = new byte[len];
		memcpy_safe(OrigData, (void*)dwAddress, len);

		if (!rehook && type == Call_s)
		{
			DWORD new_addr = (DWORD)VirtualAlloc(NULL, len + 10, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			*(byte*)new_addr = 0xE8; //call
			*(DWORD*)(new_addr + 1) = dwFunc - (new_addr + 5);

			memcpy_safe((void*)new_addr, OrigData, len + 5);
			*(byte*)(new_addr + len + 10) = 0xE9; //jmp
			*(DWORD*)(new_addr + len + 11) = dwAddress - (new_addr + len + 15);

			data = 0xE9; //jmp
			dwFunc = new_addr;
			HOOKaddr[dwAddress].virt.addr = new_addr;
			HOOKaddr[new_addr].virt.len = len + 10;
			HOOKaddr[new_addr].virt.rehook = false;
			HOOKaddr[new_addr].virt.Call_s = true;
		}

		memcpy_safe((void*)dwAddress, &data, 1);

		data = dwFunc - (dwAddress + 5);
		dwAddress++;
		memcpy_safe((void*)dwAddress, &data, 4);

		dwAddress += 4;
		len -= 5;
		if (len > 0)
			memset_safe((void*)dwAddress, 0x90, len);

		if (!rehook && type == Jump)
		{
			DWORD new_addr = (DWORD)VirtualAlloc(NULL, len + 10, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			memcpy_safe((void*)new_addr, OrigData, len + 5);
			*(byte*)(new_addr + len + 5) = 0xE9; //jmp
			*(DWORD*)(new_addr + len + 6) = dwAddress - (new_addr + len + 10);

			HOOKaddr[new_addr].virt.addr = dwAddress;
			HOOKaddr[new_addr].virt.len = len + 10;
			HOOKaddr[new_addr].virt.rehook = false;
			HOOKaddr[new_addr].virt.Call_s = false;
			dwAddress = new_addr;
		}

		HOOKaddr[dwAddress].len = len + 5;
		HOOKaddr[dwAddress].bytes = OrigData;
		return dwAddress;
	}
	bool RemoveHOOK(DWORD dwAddress) //returned address from function CreateHOOK
	{
		if (!HOOKaddr[dwAddress].len)
			return false;

		memcpy_safe((void*)dwAddress, HOOKaddr[dwAddress].bytes, HOOKaddr[dwAddress].len);

		if (HOOKaddr[dwAddress].virt.addr != 0)
		{
			if (!HOOKaddr[dwAddress].virt.rehook)
			{
				if (HOOKaddr[dwAddress].virt.Call_s)
					VirtualFree((void*)HOOKaddr[dwAddress].virt.addr, HOOKaddr[dwAddress].virt.len, MEM_RELEASE);
				else VirtualFree((void*)dwAddress, HOOKaddr[dwAddress].virt.len, MEM_RELEASE);
			}
			else
			{
				DWORD type = *(DWORD*)(dwAddress + 5);
				DWORD oldAddr = *(DWORD*)(dwAddress + 6);
				DWORD olddwFunc = oldAddr + (dwAddress + 10);

				memcpy_safe((void*)HOOKaddr[dwAddress].virt.addr, &type, 1);
				DWORD new_data = olddwFunc - (HOOKaddr[dwAddress].virt.addr + 5);
				memcpy_safe((void*)(HOOKaddr[dwAddress].virt.addr + 1), &new_data, 4);

				VirtualFree((void*)dwAddress, HOOKaddr[dwAddress].virt.len, MEM_RELEASE);
			}
		}

		HOOKaddr[dwAddress].len = 0;
		delete HOOKaddr[dwAddress].bytes;

		return true;
	}
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
	{
		for (DWORD i = 0; i < dwLen; i++)
			if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
				return (DWORD)(dwAddress + i);

		return 0;
	}

	~CHOOKS()
	{
		for (auto itr = HOOKaddr.rbegin(); itr != HOOKaddr.rend(); ++itr)
			RemoveHOOK(itr->first);
	}
}; 

/*Поиск участка кода, по его части.
Использование:

DWORD ret = FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)

где dsAddress - начальный аддрес поиска.Например GetModuleHandle(samp.dll), для поиска функций в samp.dll
dwLen - размер адресного пространство(как далеко искать).Например для поиска статичных функций в samp.dll, можно указать ее размер.
bMask - часть кода искомой функции
szMask - маска кода(x - байт должен быть такой же как в bMask, ? -байт может быть любой)
ret - адрес искомого участка кода


Создает хук.
Использование:

DWORD ret = CreateHOOK(DWORD dwAddress, DWORD dwFunc, TypeHOOK type, size_t len)

где dwAddress - адрес кода, на который необходимо поставить хук.
dwFunc - функция на которую будет ссылаться хук
type - тип хука
Jump - обычный переход, оригинальный код будет вызываться после выхода из вашей функции
Call - вызов вашей функции, оригинальный код не будет вызываться после выхода из вашей функции
Call_s - вызов вашей функции, оригинальный код будет вызываться после выхода из вашей функции
len - количество заменяемых байт(не меньше 5)
ret - адрес выхода из функции, у Jump хуков в конце должен быть переход на этот адрес, для вызова оригинального кода, этот же адрес используется для удаления хука(сделано это в связи с тем, что на 1 адрес можно нацепить несколько хуков)

Удаляет хук.
Использование:

bool ret = RemoveHOOK(DWORD dsAddress)

где dwAddress - адрес который вернула функция создания хука
ret - результат операции :
false - хук не существует, удален ранее, или создан не через данный класс
true - хук успешно удален
При вызове деструктора все хуки удаляются.

Весь сок в том, что хуки можно ставить друг на друга, пока не кончится память.

Копиригхт :
	функция memcpy_safe и memset_safe взяты из соба
	функция поиска участка кода была давно найдена где - то в интернетах, кажется на unkowncheats.me*/