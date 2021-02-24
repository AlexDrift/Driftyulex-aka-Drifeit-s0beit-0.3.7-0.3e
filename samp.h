/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux

	mod_sa is available from http://code.google.com/p/m0d-s0beit-sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/
#define samp_base									pCRMP->getBase()

#define SAMP_PLAYER_MAX				1002
#define SAMP_VEHICLE_MAX			2000
#define SAMP_PICKUP_MAX				4096
#define SAMP_OBJECTS_MAX			1000
#define SAMP_GANGZONE_MAX			1024
#define MAX_3DTEXT					2048
#define MAX_TEXTDRAW				2048
#define MAX_GANGZONES				1024
#define MAX_PLAYER_NAME				24
#define ALLOWED_PLAYER_NAME_LENGTH	20
#define MAX_CLIENTCMDS				144
#define SAMP_MENUS_MAX				128

#define SAMP_CHAT_INFO_OFFSET			0x20DFD8
#define SAMP_CHAT_INPUT_INFO_OFFSET		0x20DFDC
#define SAMP_KILL_INFO_OFFSET			0x20DFE0
#define SAMP_INFO_OFFSET				0x20DFEC

#define SAMP_FUNC_SETTEXT 0x7BA30
#define SAMP_FUNC_CLOSE_DIALOG 0x66C50
#define SAMP_DIALOG_INFO_OFFSET 0x20DFAC

#define SAMP_COLOR_OFFSET				0x20AE78
#define VALUE_DRAWING_DISTANCE			0xC9CA8

// used in proxyIDirect3DDevice9.cpp
#define SAMP_SCOREBOARD_INFO			0x20DFA8
#define SAMP_GAMEPROCESSHOOK			0x9783A
#define SAMP_FUNCUPDATESCOREBOARDDATA	0x76C0
#define SAMP_PATCH_NOCARCOLORRESETTING	0xA67B0
#define SAMP_DRAWTEXTLABELS				0x6BF37

#define GAMESTATE_AWAIT_JOIN			30
#define GAMESTATE_RESTARTING			33
#define GAMESTATE_WAIT_CONNECT			26
#define GAMESTATE_CONNECTING			28
#define GAMESTATE_CONNECTED				29

#define PLAYER_STATE_NONE				0
#define PLAYER_STATE_ONFOOT				65
#define PLAYER_STATE_DRIVER				67
#define PLAYER_STATE_PASSENGER			66
#define PLAYER_STATE_WASTED				144
#define PLAYER_STATE_SPAWNED			145

#define PLAYER_MARKERS_MODE_OFF			0
#define PLAYER_MARKERS_MODE_GLOBAL		1
#define PLAYER_MARKERS_MODE_STREAMED	2

#define SPECIAL_ACTION_NONE				0
#define SPECIAL_ACTION_DUCK				1
#define SPECIAL_ACTION_USEJETPACK		2
#define SPECIAL_ACTION_ENTER_VEHICLE	3
#define SPECIAL_ACTION_EXIT_VEHICLE		4
#define SPECIAL_ACTION_DANCE1			5
#define SPECIAL_ACTION_DANCE2			6
#define SPECIAL_ACTION_DANCE3			7
#define SPECIAL_ACTION_DANCE4			8
#define SPECIAL_ACTION_HANDSUP			10
#define SPECIAL_ACTION_USECELLPHONE		11
#define SPECIAL_ACTION_SITTING			12
#define SPECIAL_ACTION_STOPUSECELLPHONE 13
#define SPECIAL_ACTION_DRINK_BEER		20
#define SPECIAL_ACTION_SMOKE_CIGGY		21
#define SPECIAL_ACTION_DRINK_WINE		22
#define SPECIAL_ACTION_DRINK_SPRUNK		23


//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// SAMP STRUCTURES ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



struct stDrifeitPacket //31 итого
{
	BYTE byteCamMode; //1 байт
	float vecAimf1[3]; //12 байт
	float shit[2];
	float DrifeitCheck; //4
	float DrifeitVer; //4 байта
	BYTE DrifeitProtectState; //1
	BYTE DrifeitDesyncCarState; //
};


typedef struct _SPECTATOR_SYNC_DATA
{
	#pragma pack(1)
	WORD lrAnalog;
	WORD udAnalog;
	WORD wKeys;
	float vecPos[3];
} SPECTATOR_SYNC_DATA;

struct stSAMPPools
{
	struct stGangzonePool	*pPool_Gangzone;
	struct stPlayerPool		*pPool_Player;
	struct stVehiclePool	*pPool_Vehicle;
	void					*pPool_PlayerLabels;
	struct stTextdrawPool	*pPool_Textdraw;
	struct stObjectPool		*pPool_Object;
	struct stTextLabelPool	*pPool_Text3D;
	struct stPickupPool		*pPool_Pickup;
};

enum eSampWeaponState
{
	WS_NO_BULLETS = 0,
	WS_LAST_BULLET = 1,
	WS_MORE_BULLETS = 2,
	WS_RELOADING = 3,
};

struct stSAMP
{
	uint32_t				ulMapIcons[108];
	int						iLanMode; // not tested
	uint32_t				ulPort;
	char					szIP[257];
	char					szHostname[257];
	int						iGameState;
	uint32_t				*ulConnectTick; // not tested
	void					*pDrifeitClientInterface;
	struct stSampSettings	*pSettings;
	struct stSAMPPools		 pPools;
};



struct stSampSettings
{
	uint8_t unk_0[5];
	uint8_t	byteNoNametagsBehindWalls;
	uint8_t bytePlayerMarkersMode;
	int		iSpawnsAvailable;	
	uint8_t	unk_11[3];
	uint8_t byteShowNameTags;
	uint8_t unk_16;
	uint8_t byteCJWalk;
	int		iUnk_18;
	float	fWorldBoundaries[4];
	uint8_t unk_35;
	float	fGravity;
	uint8_t unk_40;
	int		iUnk_41;
	float	fNameTagsDistance;
	uint8_t byteShowZoneNames; // not tested
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
};

struct stNewVehicleInfo
{
    uint16_t  VehicleId;
	int		  iVehicleType;
	float	  vecPos[3];
	float	  fRotation;
	BYTE	  aColor1;
	BYTE	  aColor2;
	float	  fHealth;
	BYTE	  byteInterior;
	DWORD	  dwDoorDamageStatus;
	DWORD	  dwPanelDamageStatus;
	BYTE	  byteLightDamageStatus;
	BYTE	  byteTireDamageStatus;
	BYTE      byteModSlots[14];
	BYTE	  bytePaintjob;
	DWORD	  cColor1;
	DWORD	  cColor2;
	
};

struct stNewPlayerInfo
{
	BYTE byteFightingStyle;
	BYTE byteTeam;
	int iSkin;
	float vecPos[3];
	float fRotation;
	DWORD dwColor;

};



struct stTextdraw
{
	char szText[1024];
	uint8_t unk_1025;
	char szString[2048];
	uint8_t unk_3073[2];  // always = 00 00  (?)
	float fLetterWidth;
	float fLetterHeight;
	DWORD dwLetterColor;
	uint8_t byte_unk; // always = 01 (?)
	BYTE byteCenter;
	BYTE byteBox;
	float fBoxSizeX;
	float fBoxSizeY;
	DWORD dwBoxColor;
	BYTE byteProportional;
	DWORD dwShadowColor;
	BYTE byteShadowSize;
	BYTE byteOutline;
	BYTE byteLeft;
	BYTE byteRight;
	BYTE byteStyle; // font style/texture
	uint8_t unk[3]; // 00 00 00
	float fX;
	float fY;
};

struct stTextdrawPool
{
	int					iIsListed[MAX_TEXTDRAW];
	uint8_t				unk[1024];
	struct stTextdraw	*textdraw[MAX_TEXTDRAW];
};

struct stPickup
{
	int		iModelID;
	int		iType;
	float	fPosition[3];
};

struct stPickupPool
{
	int					iTimePickup[SAMP_PICKUP_MAX];
	uint8_t				unk[SAMP_PICKUP_MAX * 3];
	struct stPickup		pickup[SAMP_PICKUP_MAX];
	uint32_t			ul_GTA_PickupID[SAMP_PICKUP_MAX];
	int					iPickupID[SAMP_PICKUP_MAX];
};

struct stPlayerPool
{
	struct stLocalPlayer	*pLocalPlayer;
	void					*pVTBL_txtHandler;
	union
	{
		char	szLocalPlayerName[16];
		char	*pszLocalPlayerName;
	};
	int						iStrlen_LocalPlayerName;
	int						iScoreboard_something;
	struct stRemotePlayer	*pRemotePlayer[SAMP_PLAYER_MAX];
	int						iIsListed[SAMP_PLAYER_MAX];
	int						iLocalPlayerScore;
	int						iLocalPlayerPing;
	uint16_t				sLocalPlayerID;
};

struct stSAMPKeys
{
	uint8_t keys_primaryFire : 1;
	uint8_t keys_horn__crouch : 1;
	uint8_t keys_secondaryFire__shoot : 1;
	uint8_t keys_accel__zoomOut : 1;
	uint8_t keys_enterExitCar : 1;
	uint8_t keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t keys_circleRight : 1;
	uint8_t keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t keys_circleLeft : 1;
	uint8_t keys_landingGear__lookback : 1;
	uint8_t keys_unknown__walkSlow : 1;
	uint8_t keys_specialCtrlUp : 1;
	uint8_t keys_specialCtrlDown : 1;
	uint8_t keys_specialCtrlLeft : 1;
	uint8_t keys_specialCtrlRight : 1;
	uint8_t keys__unused : 1;
};

struct stSpectatorData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float	fPosition[3];
};

#pragma pack(1)
struct stOnFootData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fPosition[3];
	float		fQuaternion[4];
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSpecialAction;
	float		fMoveSpeed[3];
	float		fSurfingOffsets[3];
	uint16_t	sSurfingVehicleID;
	uint16_t	iCurrentAnimationID;
	uint16_t	sAnimFlags;
};

struct stInCarData
{
	uint16_t	sVehicleID;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fQuaternion[4];
	float		fPosition[3];
	float		fMoveSpeed[3];
	float		fVehicleHealth;
	uint8_t		bytePlayerHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSiren;
	uint8_t		byteLandingGearState;
	uint16_t	sTrailerID;
	union
	{
		uint16_t	HydraThrustAngle[2];	//nearly same value
		float		fTrainSpeed;
	};
};

struct stAimData  /// original code
{
#pragma pack( 1 )
	BYTE	byteCamMode; // uncurrect // 0
	float	vecAimf1[3]; //  // + 1
	float	vecAimPos[3]; // + 13
	float	fAimZ; //+ 25
	BYTE	byteCamExtZoom : 6;		// 0-63 normalized
	BYTE	byteWeaponState : 2;	// see eWeaponState
	BYTE	bUnk;
};

struct stTrailerData
{
	uint16_t	sTrailerID;
	float		fDirection[3];
	float		fRoll[3];
	float		fPosition[3];
	float		fSpeed[3];
	uint32_t	pad; // fix alignment
};

struct stPassengerData
{
	uint16_t	sVehicleID;
	uint8_t		byteSeatID;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float	fPosition[3];
};

struct stDamageData
{
	uint16_t	sVehicleID_lastDamageProcessed;
	int			iBumperDamage;
	int			iDoorDamage;
	uint8_t		byteLightDamage;
	uint8_t		byteWheelDamage;
};

struct stSurfData
{
	int			iIsSurfing;
	float		fSurfPosition[3];
	int			iUnknown;
	uint16_t	sSurfingVehicleID;
	uint32_t	ulSurfTick;
	int			iunknown_[2];
	int			iSurfMode;	//0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};

struct stHeadSync
{
	float	fHeadSync[3];
	int		iHeadSyncUpdateTick;
	int		iHeadSyncLookTick;
};

struct stUnoccupiedData
{
	int16_t sVehicleID;
	uint8_t byteSeatID;
	float	fRoll[3];
	float	fDirection[3];
	float	fPosition[3];
	float	fMoveSpeed[3];
	float	fTurnSpeed[3];
	float	fHealth;
};

struct stDialogInfo
{
	int  unk1; // +0x0
	int  iTextOffsetX; // +0x4
	int  iTextOffsetY; // +0x8
	int  unk2[2]; // +0x10
	int  iButtonOffsetX; // +0x14
	int  iButtonOffsetY; // +0x18
	void *pDialogBox; // +0x1C
	void *pListBox; // +0x20
	void *pEditBox; // +0x24
	int  iDialogShowed; // +0x28
	int  iDialogType; // +0x2C
	int  iDialogID; // +0x30
	int  unk3[3]; // +0x34
	char szDialogHeader[65]; // +0x40
	int  iSendResponse; // +0x81
};

struct stLocalPlayer
{
	struct stSAMPPed		*pSAMP_Actor;
	uint16_t				sCurrentVehicleID;
	uint16_t				sLastVehicleID;
	int						iIsActive;
	int						iIsWasted;
	int						iCurrentAnimID;
	int						iUnk;
	uint8_t					byteTeamID;
	int						iSpawnSkin;
	uint8_t					unknown_1D;
	float					fSpawnPos[3];
	float					fSpawnRot;
	int						iSpawnWeapon[3];
	int						iSpawnAmmo[3];
	int						iIsActorAlive;
	int						iSpawnClassLoaded;
	uint32_t				ulSpawnSelectionTick;
	uint32_t				ulSpawnSelectionStart;
	int						iIsSpectating;
	uint8_t					byteTeamID2; // wtf?!
	uint8_t					byteUnknown_5B[22];
	uint16_t				sAimingAtPid; // player id we are aiming at
	uint8_t					byteCurrentWeapon;
	uint8_t					byteWeaponInventory[13];
	int						iWeaponAmmo[13];
	struct stHeadSync		headSyncData;
	struct stSurfData		surfData;
	int						iPassengerDriveBy;
	uint8_t					byteCurrentInterior;
	int						iIsInRCVehicle;
	uint8_t					byteUnk[256];
	
	struct stPassengerData	passengerData;
	struct stAimData		aimData;
	struct stTrailerData	trailerData;
	struct stOnFootData		onFootData;
	struct stInCarData		inCarData;

	uint8_t					byteSpectatingUnk; // 15[?],14[?],(3-Veh/4-Player [follow])
	uint8_t					byteSpectatingWHAT; // 2 = Veh, 1 = Player // not tested
	int						iSpectateID;
	int						iInitiatedSpectating;
	struct stDamageData		vehicleDamageData;
	uint8_t					byteUnk_2F2[4];
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;

	// not placed correctly
	uint32_t				ulSendTick;
	uint32_t				ulSpectateTick;
	uint32_t				ulAimTick;
	uint32_t				ulStatsUpdateTick;
	uint32_t				ulWeapUpdateTick;
	uint32_t				ulUnknownTick;
	uint32_t				ulZoneNameTick;
	uint32_t				ulUnoccupiedTick;
};

struct stRemotePlayerData
{
	int						iUnk1;
	uint16_t				sPlayerID;
	uint16_t				sVehicleID;
	uint8_t					byteSeatID; // not tested
	int						iPassengerDriveBy;
	uint8_t					byteTeamID;
	uint8_t					bytePlayerState;


	struct stPassengerData	passengerData;
	struct stAimData		aimData;
	struct stTrailerData	trailerData;
	struct stInCarData		inCarData;
	struct stOnFootData		onFootData;

	uint8_t					unk[109];
	uint8_t					byteSpecialAction;
	int						iShowNameTag;
	int						iHasJetPack;
	uint32_t				dwTick;
	uint32_t				dwLastStreamedInTick; // is 0 when currently streamed in
	float					fActorHealth;
	float					fActorArmor;
	int						iUnk2;
	struct stSAMPPed		*pSAMP_Actor;
	struct stSAMPVehicle	*pSAMP_Vehicle;
	uint8_t					unk2[12];
	struct stHeadSync		headSyncData;
	uint8_t					unk3[16];
	float					fOnFootPos[3]; // lag comp copies of original onfoot/incar vars
	float					fOnFootMoveSpeed[3];
	float					fVehiclePosition[3];
	float					fVehicleMoveSpeed[3];
	float					fVehicleRoll[4];
	uint8_t					unk4[24];
	
	// not placed correctly (but also currently not used):
	int						iGlobalMarkerLoaded;
	int						iGlobalMarkerLocation[3];
	uint32_t				ulGlobalMarker_GTAID;
};

struct stRemotePlayer
{
	void				*pVTBL_txtHandler;
	union
	{
		char	szPlayerName[16];
		char	*pszPlayerName;
	};
	int					iStrlenName__; // ?
	int					iStrlenName; // iStrlenNameMax, numByteReserved?
	int					iSmth;
	stRemotePlayerData	*pPlayerData;
	int					iScore;
	int					iIsNPC;
	int					iPing;
};

struct stSAMPPed
{
	void				*pVTBL_sampPed;
	uint8_t				byteUnknown_4[60];
	struct actor_info	*pGTA_Ped_;
	uint32_t			ulGTA_Ped_ID;
	int					usingCellPhone;
	struct actor_info	*pGTA_Ped;
	uint8_t				byteUnknown_80[8];
	uint8_t				byteKeysId;
	uint8_t				pad[624];
	int					DrinkingOrSmoking;
	int					object_in_hand;
	int					drunkLevel;
	int					isUrinating;
	uint32_t			ulGTA_UrinateParticle_ID;
	uint8_t				byteUnknown_3[5];
	int					isDancing;
	int					danceStyle;
	int					danceMove;
};

struct stVehiclePool
{
	BYTE					bUnknown[0xBCAC];
	struct vehicle_info		*pGTA_Vehicle[SAMP_VEHICLE_MAX];
	struct stSAMPVehicle	*pSAMP_Vehicle[SAMP_VEHICLE_MAX];
	int						iIsListed[SAMP_VEHICLE_MAX];
	float					fSpawnPos[SAMP_VEHICLE_MAX][3];
	int						iInitiated; // not tested
};

struct stSAMPVehicle
{
	void				*pVTBL_Vehicle;
	struct vehicle_info *pGTA_Vehicle_;
	uint8_t				byteUnknown_8[60];
	uint32_t			ulGTA_Vehicle_ID;
	struct vehicle_info *pGTA_Vehicle;
	int					iIsMotorOn;
	int					iIsLightsOn;	
	int					iIsLocked;
	uint8_t				byteUnknown_88[8];
	uint8_t				byteIsObjective;
	int					iObjectiveBlipCreated;
	uint8_t				byteUnknown_101[24];
	uint8_t				byteColor[2];
	int					iColorSync;
	int					iColor_something;	
};

struct stObject
{
	void				*pVTBL_Object;
	uint8_t				pad[60];
	struct object_info	*pGTAObject;
	uint32_t			ulGTA_Object_ID;
};

struct stObjectPool
{
	int				iIsListed[SAMP_OBJECTS_MAX];
	struct stObject *object[SAMP_OBJECTS_MAX];
};

struct stGangzone
{
	float	fPosition[4];
	DWORD	dwColor;
	DWORD	dwAltColor;
};

struct stGangzonePool
{
	struct stGangzone	*pGangzone[SAMP_GANGZONE_MAX];
	int					iIsListed[SAMP_GANGZONE_MAX];
};

struct stTextLabel
{
	char		*pText;
	DWORD		color;
	float		fPosition[3];
	float		fMaxViewDistance;
	uint8_t		byteShowBehindWalls;
	uint16_t	sAttachedToPlayerID;
	uint16_t	sAttachedToVehicleID;
};

struct stTextLabelPool
{
	struct stTextLabel	textLabel[MAX_3DTEXT];
	int					iIsListed[MAX_3DTEXT];
};

struct stChatEntry
{
#pragma pack( 1 )
	
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 10 - text + prefix, 11 - text (server msg), 12 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
	uint32_t	SystemTime;
};

struct stAttachedObject
{
#pragma pack( 1 )
	int	iModelID;
	int	iBoneID;
	float vecPos[3];
	float vecRot[3];
	float vecScale[3];
	DWORD dwMaterialColor1;
	DWORD dwMaterialColor2;
};

struct stChatInfo
{
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				dwChatboxOffset;
	int					iChatWindowMode;			// 2 - normal, 1 - light, 0 - disabled
	uint8_t				bTimestamps;
	int					unk1;
	char				logFilePathChatLog[MAX_PATH+1];
	int					pagesize;
	uint8_t				unk[20];
	struct stChatEntry	chatEntry[100];
	
	// not placed correctly
	DWORD				dwChatLinesHeight;
	DWORD				dwDistanceTextToTimestamp;
};

struct stInputBox
{
	void	*pUnknown;
	uint8_t	bIsChatboxOpen;
	uint8_t	bIsMouseInChatbox;
	uint8_t	bMouseClick_related;
	uint8_t	unk;
	DWORD	dwPosChatInput[2];
	uint8_t	unk2[263];
	int		iCursorPosition;
	uint8_t	unk3;
	int		iMarkedText_startPos; // Highlighted text between this and iCursorPosition
	uint8_t	unk4[20];
	int		iMouseLeftButton;
};

struct stWeaponUpdate
{
	BYTE	slot;
	BYTE	weaponid;
	WORD	ammo;
};

typedef void ( __cdecl *CMDPROC ) ( PCHAR );
struct stInputInfo
{
	void		*pD3DDevice;
	void		*pDXUTDialog;
	stInputBox	*pDXUTEditBox;
	CMDPROC 	pszCMDs[MAX_CLIENTCMDS];
	char		szCMDNames[MAX_CLIENTCMDS][33];
	int			iCMDCount;
	int			iInputEnabled;
	char		szInputBuffer[129];
	char		szRecallBufffer[10][129];
	char		szCurrentBuffer[129];
	int			iCurrentRecall;
	int			iTotalRecalls;
	CMDPROC 	pszDefaultCMD;
};

struct stKillEntry
{
	char		szKiller[25];
	char		szVictim[25];
	D3DCOLOR	clKillerColor;
	D3DCOLOR	clVictimColor;
	uint8_t		byteType;
};

struct stKillInfo
{
#pragma pack( 1 )
	int					iEnabled;
	struct stKillEntry	killEntry[5];
};

struct stChatPlayer
{
	int			iCreated;
	char		probablyTheText[256]; // text max length = 144
	DWORD		dwTickCreated;
	DWORD		dwLiveLength;
	DWORD		dwColor;
	float		fDrawDistance;
	DWORD		dwUnknown;
};

struct stChatBubbleInfo
{
	struct stChatPlayer	chatBubble[SAMP_PLAYER_MAX];
};

struct stStreamedOutPlayerInfo
{
	int		iPlayerID[SAMP_PLAYER_MAX];
	float	fPlayerPos[SAMP_PLAYER_MAX][3];
};

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// SUPPORT VARIABLES //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
struct stTranslateGTASAMP_vehiclePool
{
	// the index is the position in the vehicle pool
	//
	// translation data
	int iSAMPID[SAMP_VEHICLE_MAX];
};

struct stTranslateGTASAMP_pedPool
{
	// the index is the position in the ped pool
	//
	// translation data
	int iSAMPID[SAMP_PLAYER_MAX];
};

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// FUNCTIONS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void											update_translateGTASAMP_vehiclePool ( void );
void											update_translateGTASAMP_pedPool ( void );

bool											findstrinstr ( char *text, char *find );

int												isBadPtr_SAMP_iVehicleID ( int iVehicleID );
int												isBadPtr_SAMP_iPlayerID ( int iPlayerID );

void											getSamp ();
uint32_t										getSampAddress ();

struct stSAMP									*stGetSampInfo ( void );
struct stChatInfo								*stGetSampChatInfo ( void );
struct stInputInfo								*stGetInputInfo ( void );
struct stKillInfo								*stGetKillInfo ( void );
D3DCOLOR										samp_color_get ( int id, DWORD trans = 0xFF000000 );

void											sampMainCheat ();

int												getNthPlayerID ( int n );
int												getPlayerCount ( void );
int												getVehicleCount ( void );

int												setLocalPlayerName ( const char *name );
int												getPlayerPos ( int iPlayerID, float fPos[3] );
const char										*getPlayerName ( int iPlayerID );
int												getPlayerState ( int iPlayerID );
int												getPlayerVehicleGTAScriptingID ( int iPlayerID );
int												getPlayerSAMPVehicleID ( int iPlayerID );
void											spectatePlayer(int iPlayerID);
void											spectateHandle();
void cmd_nick( char *param );
void SendFakeOnfootSyncData ( float coord[3], float speed[3] );
void cmd_lagger();
void cmd_db(char *params);
void cmd_randv ( char *param );
void sendChat(char *szMessage);
void SetActorZAngle(actor_info *actor, float ang, bool Invert);
void SetVehicleZAngle(vehicle_info *vehicle, float ang, bool Invert);

struct actor_info								*getGTAPedFromSAMPPlayerID ( int iPlayerID );
struct vehicle_info								*getGTAVehicleFromSAMPVehicleID ( int iPlayerID );
int												getSAMPPlayerIDFromGTAPed ( struct actor_info *info );
int												getSAMPVehicleIDFromGTAVehicle ( struct vehicle_info *pVehicle );
uint32_t										getPedGTAScriptingIDFromPlayerID ( int iPlayerID );
uint32_t										getVehicleGTAScriptingIDFromVehicleID ( int iVehicleID );

int												samp_vehicle_find_nearest ( int flags );

bool											get_isModCommandsActive ();
void											init_samp_chat_cmds ();
void											addClientCommand ( char *text, int function );
void											addToChatWindow ( char *text, D3DCOLOR textColor, int playerID = -1 );
void											addMessageToChatWindow ( const char *text, ... );
void											addMessageToChatWindowSS ( const char *text, ... );
void											restartGame ();
void											addSayToChatWindow ( char *msg );
void											say ( char *text, ... );
void											showGameText ( char *text, int time, int textsize );
void											playerSpawn ( void );
void											disconnect ( int reason );
void											setPassword ( char *password );
void											sendSetInterior ( uint8_t interiorID );
void											setSpecialAction ( uint8_t byteSpecialAction );
void											sendSCMEvent ( int iEvent, int iVehicleID, int iParam1, int iParam2 );
void											toggleSAMPCursor(int iToggle);
void SkypeStatus ( int STATUS );
void handle_extra_gm_v2();
void											installSAMPHooks ();
void											setSAMPCustomSendRates ( int iOnFoot, int iInCar, int iAim, int iHeadSync );
int												sampPatchDisableNameTags ( int iEnabled );
int												sampPatchDisableInteriorUpdate ( int iEnabled );
int												sampPatchDisableScoreboardToggleOn ( int iEnabled );
int												sampPatchDisableChatInputAdjust ( int iEnabled );
void SendScmEvent(int iEventType, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);
void sampModifiedPackets();
void rconWarnings();
void dialogWarnings();
void cmd_sendclass ( char *param );
void cmd_setmyhp ( char *param );
void cmd_cslap( char *param );
void cmd_gethere( char *param );
void gethere(int id);
void cmd_slap ( char *params );
void cmd_vtp ( char *param );
void cmd_randv (int param );
void cmd_troll ( char *param );
void Troller(int id);
void moveStreamedVehiclesToPlayer(int id);
void SendEnterVehicleNotifications(USHORT VehicleID);
void remove_vehicle ( char *vehicleID );
void Logging(char *fmt, ...);
void sampDialogClose(BYTE bButtonID, DWORD wListBoxItem, char *szInputResp);
void attachedObjectCrasher();

// global pointer externals
extern int										iIsSAMPSupported;
extern int										g_renderSAMP_initSAMPstructs;
extern struct stSAMP							*g_SAMP;
extern struct stPlayerPool						*g_Players;
extern struct stVehiclePool						*g_Vehicles;
extern struct stChatInfo						*g_Chat;
extern struct stInputInfo						*g_Input;
extern struct stKillInfo						*g_DeathList;
extern struct stStreamedOutPlayerInfo			g_stStreamedOutInfo;

// global support variables externals
extern struct stTranslateGTASAMP_vehiclePool	translateGTASAMP_vehiclePool;
extern struct stTranslateGTASAMP_pedPool		translateGTASAMP_pedPool;

extern int										g_iSpectateEnabled;
extern int										g_iCursorEnabled;
extern int										g_iNumPlayersMuted;
extern bool										g_bPlayerMuted[SAMP_PLAYER_MAX];
//void HandleRPCPacketFunc(unsigned char byteRPCID, RPCParameters *rpcParams, void(*functionPointer) (RPCParameters *));
void SetupSAMPHook(char *szName, DWORD dwFuncOffset, void *Func, int iType, int iSize, char *szCompareBytes);
extern int										iNetModeNormalOnfootSendRate;
extern int										iNetModeNormalIncarSendRate;
extern int										iNetModeFiringSendRate;
extern int										iNetModeSendMultiplier;
extern int										iLagCompMode;


