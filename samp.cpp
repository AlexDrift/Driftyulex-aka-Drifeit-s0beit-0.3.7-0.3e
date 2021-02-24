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
#include "main.h"


#define SAMP_DLL		"samp.dll"
#define SAMP_CMP		"E9FFFFE8C9D7FFFFC644"
#define pRakClientInterfaceOffset		0x3C2












int								g_iLastAttachedObjectIndex = -1;
//randomStuff
extern int						iViewingInfoPlayer;
int								g_iSpectateEnabled = 0, g_iSpectateLock = 0, g_iSpectatePlayerID = -1;
int								g_iCursorEnabled = 0;

// global samp pointers
int								iIsSAMPSupported = 0;
int								g_renderSAMP_initSAMPstructs;
stSAMP							*g_SAMP = NULL;
stPlayerPool					*g_Players = NULL;
stVehiclePool					*g_Vehicles = NULL;
stChatInfo						*g_Chat = NULL;
stInputInfo						*g_Input = NULL;
stKillInfo						*g_DeathList = NULL;

// global managed support variables
stTranslateGTASAMP_vehiclePool	translateGTASAMP_vehiclePool;
stTranslateGTASAMP_pedPool		translateGTASAMP_pedPool;

stStreamedOutPlayerInfo			g_stStreamedOutInfo;



//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// FUNCTIONS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// update SAMPGTA vehicle translation structure
void update_translateGTASAMP_vehiclePool ( void )
{
	traceLastFunc( "update_translateGTASAMP_vehiclePool()" );
	if ( !g_Vehicles )
		return;

	int iGTAID;
	for ( int i = 0; i <= SAMP_VEHICLE_MAX; i++ )
	{
		if ( g_Vehicles->iIsListed[i] != 1 )
			continue;
		if ( isBadPtr_writeAny(g_Vehicles->pSAMP_Vehicle[i], sizeof(stSAMPVehicle)) )
			continue;
		iGTAID = getVehicleGTAIDFromInterface( (DWORD *)g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle );
		if ( iGTAID <= SAMP_VEHICLE_MAX && iGTAID >= 0 )
		{
			translateGTASAMP_vehiclePool.iSAMPID[iGTAID] = i;
		}
	}
}

// update SAMPGTA ped translation structure
void update_translateGTASAMP_pedPool ( void )
{
	traceLastFunc( "update_translateGTASAMP_pedPool()" );
	if ( !g_Players )
		return;

	int iGTAID, i;
	for ( i = 0; i < SAMP_PLAYER_MAX; i++ )
	{
		if ( i == g_Players->sLocalPlayerID )
		{
			translateGTASAMP_pedPool.iSAMPID[0] = i;
			continue;
		}

		if ( isBadPtr_writeAny(g_Players->pRemotePlayer[i], sizeof(stRemotePlayer)) )
			continue;
		if ( isBadPtr_writeAny(g_Players->pRemotePlayer[i]->pPlayerData, sizeof(stRemotePlayerData)) )
			continue;
		if ( isBadPtr_writeAny(g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor, sizeof(stSAMPPed)) )
			continue;

		iGTAID = getPedGTAIDFromInterface( (DWORD *)g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped );
		if ( iGTAID <= SAMP_PLAYER_MAX && iGTAID >= 0 )
		{
			translateGTASAMP_pedPool.iSAMPID[iGTAID] = i;
		}
	}
}




DWORD LegalMods[48][22] =
{
	{400, 1024,1021,1020,1019,1018,1013,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{401, 1145,1144,1143,1142,1020,1019,1017,1013,1007,1006,1005,1004,1003,1001,0000,0000,0000,0000},
	{404, 1021,1020,1019,1017,1016,1013,1007,1002,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{405, 1023,1021,1020,1019,1018,1014,1001,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{410, 1024,1023,1021,1020,1019,1017,1013,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
	{415, 1023,1019,1018,1017,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{418, 1021,1020,1016,1006,1002,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{420, 1021,1019,1005,1004,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{421, 1023,1021,1020,1019,1018,1016,1014,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{422, 1021,1020,1019,1017,1013,1007,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{426, 1021,1019,1006,1005,1004,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{436, 1022,1021,1020,1019,1017,1013,1007,1006,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
	{439, 1145,1144,1143,1142,1023,1017,1013,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
	{477, 1021,1020,1019,1018,1017,1007,1006,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{478, 1024,1022,1021,1020,1013,1012,1005,1004,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{489, 1024,1020,1019,1018,1016,1013,1006,1005,1004,1002,1000,0000,0000,0000,0000,0000,0000,0000},
	{491, 1145,1144,1143,1142,1023,1021,1020,1019,1018,1017,1014,1007,1003,0000,0000,0000,0000,0000},
	{492, 1016,1006,1005,1004,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{496, 1143,1142,1023,1020,1019,1017,1011,1007,1006,1003,1002,1001,0000,0000,0000,0000,0000,0000},
	{500, 1024,1021,1020,1019,1013,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{516, 1021,1020,1019,1018,1017,1016,1015,1007,1004,1002,1000,0000,0000,0000,0000,0000,0000,0000},
	{517, 1145,1144,1143,1142,1023,1020,1019,1018,1017,1016,1007,1003,1002,0000,0000,0000,0000,0000},
	{518, 1145,1144,1143,1142,1023,1020,1018,1017,1013,1007,1006,1005,1003,1001,0000,0000,0000,0000},
	{527, 1021,1020,1018,1017,1015,1014,1007,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{529, 1023,1020,1019,1018,1017,1012,1011,1007,1006,1003,1001,0000,0000,0000,0000,0000,0000,0000},
	{534, 1185,1180,1179,1178,1127,1126,1125,1124,1123,1122,1106,1101,1100,0000,0000,0000,0000,0000},
	{535, 1121,1120,1119,1118,1117,1116,1115,1114,1113,1110,1109,0000,0000,0000,0000,0000,0000,0000},
	{536, 1184,1183,1182,1181,1128,1108,1107,1105,1104,1103,0000,0000,0000,0000,0000,0000,0000,0000},
	{540, 1145,1144,1143,1142,1024,1023,1020,1019,1018,1017,1007,1006,1004,1001,0000,0000,0000,0000},
	{542, 1145,1144,1021,1020,1019,1018,1015,1014,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{546, 1145,1144,1143,1142,1024,1023,1019,1018,1017,1007,1006,1004,1002,1001,0000,0000,0000,0000},
	{547, 1143,1142,1021,1020,1019,1018,1016,1003,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{549, 1145,1144,1143,1142,1023,1020,1019,1018,1017,1012,1011,1007,1003,1001,0000,0000,0000,0000},
	{550, 1145,1144,1143,1142,1023,1020,1019,1018,1006,1005,1004,1003,1001,0000,0000,0000,0000,0000},
	{551, 1023,1021,1020,1019,1018,1016,1006,1005,1003,1002,0000,0000,0000,0000,0000,0000,0000,0000},
	{558, 1168,1167,1166,1165,1164,1163,1095,1094,1093,1092,1091,1090,1089,1088,0000,0000,0000,0000},
	{559, 1173,1162,1161,1160,1159,1158,1072,1071,1070,1069,1068,1067,1066,1065,0000,0000,0000,0000},
	{560, 1170,1169,1141,1140,1139,1138,1033,1032,1031,1030,1029,1028,1027,1026,0000,0000,0000,0000},
	{561, 1157,1156,1155,1154,1064,1063,1062,1061,1060,1059,1058,1057,1056,1055,1031,1030,1027,1026},
	{562, 1172,1171,1149,1148,1147,1146,1041,1040,1039,1038,1037,1036,1035,1034,0000,0000,0000,0000},
	{565, 1153,1152,1151,1150,1054,1053,1052,1051,1050,1049,1048,1047,1046,1045,0000,0000,0000,0000},
	{567, 1189,1188,1187,1186,1133,1132,1131,1130,1129,1102,0000,0000,0000,0000,0000,0000,0000,0000},
	{575, 1177,1176,1175,1174,1099,1044,1043,1042,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{576, 1193,1192,1191,1190,1137,1136,1135,1134,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{580, 1023,1020,1018,1017,1007,1006,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{589, 1145,1144,1024,1020,1018,1017,1016,1013,1007,1006,1005,1004,1000,0000,0000,0000,0000,0000},
	{600, 1022,1020,1018,1017,1013,1007,1006,1005,1004,0000,0000,0000,0000,0000,0000,0000,0000,0000},
	{603, 1145,1144,1143,1142,1024,1023,1020,1019,1018,1017,1007,1006,1001,0000,0000,0000,0000,0000}
};

bool IsWheelModel(DWORD dwComponentID)
{
	DWORD WheelModels[17] = {1025, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083, 1084, 1085, 1096, 1097, 1098};
       
	for(int x = 0; x < 17; x++)
	{
		if(dwComponentID == WheelModels[x])
			return true;
    }

    return false;
}

bool IsIllegalCarNitroIde(DWORD dwCarModelID)
{
    DWORD IllegalVehicles[29] = { 581, 523, 462, 521, 463, 522, 461, 448, 468, 586, 509, 481, 510, 472, 473, 493, 595, 484, 430, 453, 452, 446, 454, 590, 569, 537, 538, 570, 449 };
       
	for(int x = 0; x < 17; x++)
	{
        if (dwCarModelID == IllegalVehicles[x])
            return true;
    }
   
    return false;
}

bool IsLegalCarComponent(DWORD dwCarModelID, DWORD dwComponentID)
{
    bool IsLegal = false;

    if((IsWheelModel(dwComponentID)) || (dwComponentID == 1086) || (dwComponentID == 1087) || ((dwComponentID >= 1008) && (dwComponentID <= 1010)))
	{
		if(!IsIllegalCarNitroIde(dwCarModelID))
            IsLegal = true;
    }
	else
	{
		for(int I = 0; I < 48; I++)
		{
            if (LegalMods[I][0] == dwCarModelID)
			{
                for(int J = 1; J < 22; J++)
				{
					if(LegalMods[I][J] == dwComponentID)
                        IsLegal = true;
                }
            }
           
        }
    }
   
    return IsLegal;
}








//ClientCommands

extern int	joining_server;
void cmd_change_server ( char *param )	//127.0.0.1 7777 Username Password
{
	traceLastFunc( "cmd_change_server()" );

	char	*result;
	bool	success = false;

	char	IP[257], LocalName[MAX_PLAYER_NAME];
	int		Port;
	strcpy( IP, g_SAMP->szIP );
	Port = g_SAMP->ulPort;
	strcpy( LocalName, getPlayerName(g_Players->sLocalPlayerID) );

	result = strtok( param, " :" );
	for ( int i = 0; i <= 4; i++ )
	{
		if ( result == NULL && !success )
		{
			addMessageToChatWindow( "USAGE: /m0d_change_server <ip> <port> <Username> <Server Password>" );
			addMessageToChatWindow( "Variables that are set to \"NULL\" (capitalized) will be ignored." );
			addMessageToChatWindow( "If you set the Password to \"NULL\" it is set to <no server password>." );
			addMessageToChatWindow( "Username and password can also be left out completely." );
			strcpy( g_SAMP->szIP, IP );
			g_SAMP->ulPort = Port;
			setLocalPlayerName( LocalName );
			return;
		}
		else if ( result == NULL && success )
		{
			joining_server = 1;
			return;
		}

		switch ( i )
		{
		case 0:
			if ( strcmp(result, "NULL") != 0 )
				strcpy( g_SAMP->szIP, result );
			break;

		case 1:
			if ( strcmp(result, "NULL") != 0 )
				g_SAMP->ulPort = atoi( result );
			success = true;
			break;

		case 2:
			if ( strcmp(result, "NULL") != 0 )
			{
				if ( strlen(result) > ALLOWED_PLAYER_NAME_LENGTH )
					addMessageToChatWindow( "Username was too long - adjusted size." );
				strncpy_s( LocalName, result, ALLOWED_PLAYER_NAME_LENGTH );
				setLocalPlayerName( LocalName );
			}
			break;

		case 3:
			if ( strcmp(result, "NULL") != 0 )
				setPassword( result );
			else
				setPassword( "" );
			break;

		default:
			{
				addMessageToChatWindow( "Too many variables." );
				addMessageToChatWindow( "USAGE: /m0d_change_server <ip> <port> <Username> <Server Password>" );
				addMessageToChatWindow( "Variables that are set to \"NULL\" (capitalized) will be ignored." );
				addMessageToChatWindow( "If you set the Password to \"NULL\" it is set to <no server password>." );
				addMessageToChatWindow( "Username and password can also be left out completely." );
				strcpy( g_SAMP->szIP, IP );
				g_SAMP->ulPort = Port;
				strcpy( LocalName, getPlayerName(g_Players->sLocalPlayerID) );
				if ( i >= 3 )
				{
					addMessageToChatWindow( "Setting password to <no server password>." );
					setPassword( "" );
				}

				return;
			}
		}

		result = strtok( NULL, " :" );
	}
}

void cmd_change_server_fav ( char *param )
{
	traceLastFunc( "cmd_change_server_fav()" );

	if ( strlen(param) == 0 )
	{
		addMessageToChatWindow( "/m0d_fav_server <server name/part of server name>" );
		addMessageToChatWindow( "In order to see the favorite server list type: /m0d_fav_server list" );
		return;
	}

	if ( strncmp(param, "list", 4) == 0 )
	{
		int count = 0;
		for ( int i = 0; i < INI_SERVERS_MAX; i++ )
		{
			if ( set.server[i].server_name == NULL )
				continue;

			count++;
			addMessageToChatWindow( "%s", set.server[i].server_name );
		}
		if ( count == 0 )
			addMessageToChatWindow( "No servers in favorite server list. Edit the ini file to add some." );
		return;
	}

	char	IP[257], LocalName[29];
	int		Port;
	strcpy( IP, g_SAMP->szIP );
	Port = g_SAMP->ulPort;
	strcpy( LocalName, getPlayerName(g_Players->sLocalPlayerID) );

	for ( int i = 0; i < INI_SERVERS_MAX; i++ )
	{
		if ( set.server[i].server_name == NULL || set.server[i].ip == NULL
			|| strlen(set.server[i].ip) < 7 || set.server[i].port == 0 )
			continue;

		if ( !findstrinstr((char *)set.server[i].server_name, param) )
			continue;

		if ( !set.use_current_name )
			setLocalPlayerName( set.server[i].nickname );

		strcpy( g_SAMP->szIP, set.server[i].ip );
		g_SAMP->ulPort = set.server[i].port;
		setPassword( set.server[i].password );
		joining_server = 1;
		return;
	}

	addMessageToChatWindow( "/m0d_fav_server <server name/part of server name>" );
	return;
}

void cmd_current_server ( char *param )
{
	addMessageToChatWindow( "Server Name: %s", g_SAMP->szHostname );
	addMessageToChatWindow( "Server Address: %s:%i", g_SAMP->szIP, g_SAMP->ulPort );
	addMessageToChatWindow( "Username: %s", getPlayerName(g_Players->sLocalPlayerID) );
}

// strtokstristr?
bool findstrinstr ( char *text, char *find )
{
	char	realtext[256];
	char	subtext[256];
	char	*result;
	char	*next;
	char	temp;
	int		i = 0;

	traceLastFunc( "findstrinstr()" );

	// can't find stuff that isn't there unless you are high
	if ( text == NULL || find == NULL )
		return false;

	// lower case text ( sizeof()-2 = 1 for array + 1 for termination after while() )
	while ( text[i] != NULL && i < (sizeof(realtext)-2) )
	{
		temp = text[i];
		if ( isupper(temp) )
			temp = tolower( temp );
		realtext[i] = temp;
		i++;
	}
	realtext[i] = 0;

	// replace unwanted characters/spaces with dots
	i = 0;
	while ( find[i] != NULL && i < (sizeof(subtext)-2) )
	{
		temp = find[i];
		if ( isupper(temp) )
			temp = tolower( temp );
		if ( !isalpha(temp) )
			temp = '.';
		subtext[i] = temp;
		i++;
	}
	subtext[i] = 0;

	// use i to count the successfully found text parts
	i = 0;

	// split and find every part of subtext/find in text
	result = &subtext[0];
	while ( *result != NULL )
	{
		next = strstr( result, "." );
		if ( next != NULL )
		{
			// more than one non-alphabetic character
			if ( next == result )
			{
				do
					next++;
				while ( *next == '.' );

				if ( *next == NULL )
					return (i != 0);
				result = next;
				next = strstr( result, "." );
				if ( next != NULL )
					*next = NULL;
			}
			else
				*next = NULL;
		}

		if ( strstr(realtext, result) == NULL )
			return false;

		if ( next == NULL )
			return true;

		i++;
		result = next + 1;
	}

	return false;
}

void cmd_tele_loc ( char *param )
{
	if ( strlen(param) == 0 )
	{
		addMessageToChatWindow( "USAGE: /m0d_tele_loc <location name>" );
		addMessageToChatWindow( "Use /m0d_tele_locations to show the location names." );
		addMessageToChatWindow( "The more specific you are on location name the better the result." );
		return;
	}

	for ( int i = 0; i < STATIC_TELEPORT_MAX; i++ )
	{
		if ( strlen(set.static_teleport_name[i]) == 0 || vect3_near_zero(set.static_teleport[i].pos) )
			continue;

		if ( !findstrinstr(set.static_teleport_name[i], param) )
			continue;

		cheat_state_text( "Teleported to: %s.", set.static_teleport_name[i] );
		cheat_teleport( set.static_teleport[i].pos, set.static_teleport[i].interior_id );
		return;
	}

	addMessageToChatWindow( "USAGE: /m0d_tele_loc <location name>" );
	addMessageToChatWindow( "Use /m0d_tele_locations to show the location names." );
	addMessageToChatWindow( "The more specific you are on location name the better the result." );
}

void cmd_tele_locations ()
{
	for ( int i = 0; i < STATIC_TELEPORT_MAX; i++ )
	{
		if ( strlen(set.static_teleport_name[i]) == 0 || vect3_near_zero(set.static_teleport[i].pos) )
			continue;
		addMessageToChatWindow( "%s", set.static_teleport_name[i] );
	}

	addMessageToChatWindow( "To teleport use the menu or: /m0d_tele_loc <location name>" );
}

// new functions to check for bad pointers
int isBadPtr_SAMP_iVehicleID ( int iVehicleID )
{
	if ( g_Vehicles == NULL || iVehicleID == (uint16_t)-1)
		return 1;
	return !g_Vehicles->iIsListed[iVehicleID];

	// this hasn't been required yet
	//if (g_Vehicles->pSAMP_Vehicle[iVehicleID] == NULL) continue;
}

int isBadPtr_SAMP_iPlayerID ( int iPlayerID )
{
	if ( g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX)
		return 1;
	return !g_Players->iIsListed[iPlayerID];
}

void getSamp ()
{
	if ( set.basic_mode )
		return;

	uint32_t	samp_dll = getSampAddress();

	if ( samp_dll != NULL )
	{
		g_dwSAMP_Addr = ( uint32_t ) samp_dll;

		if ( g_dwSAMP_Addr != NULL )
		{
			if ( memcmp_safe((uint8_t *)g_dwSAMP_Addr + 0xBABE, hex_to_bin(SAMP_CMP), 10) )
			{
				strcpy(g_szSAMPVer, "SA:MP 0.3e");
				Log( "%s was detected. g_dwSAMP_Addr: 0x%p", g_szSAMPVer, g_dwSAMP_Addr );


				
				
				// AC patch by bartekdvd
				if(memcmp_safe((uint32_t *)(g_dwSAMP_Addr + 0x935F0), "\x8B\x54\x24\x08", 4)) 
					memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x935F0), 0xC3, 1);

				iIsSAMPSupported = 1;
			}
			else
			{
				Log( "Unknown SA:MP version. Running in basic mode." );
				iIsSAMPSupported = 0;
				set.basic_mode = true;

				g_dwSAMP_Addr = NULL;
			}
		}
	}
	else
	{
		iIsSAMPSupported = 0;
		set.basic_mode = true;
		Log( "samp.dll not found. Running in basic mode." );
	}

	return;
}

uint32_t getSampAddress ()
{
	if ( set.run_mode == RUNMODE_SINGLEPLAYER )
		return 0x0;

	uint32_t	samp_dll;

	if ( set.run_mode == RUNMODE_SAMP )
	{
		if ( set.wine_compatibility )
		{
			HMODULE temp = LoadLibrary( SAMP_DLL );
			__asm mov samp_dll, eax
		}
		else
		{
			void	*temp = dll_baseptr_get( SAMP_DLL );
			__asm mov samp_dll, eax
		}
	}

	if ( samp_dll == NULL )
		return 0x0;

	return samp_dll;
}

struct stSAMP *stGetSampInfo ( void )
{
	if ( g_dwSAMP_Addr == NULL )
		return NULL;

	uint32_t	info_ptr;
	info_ptr = ( UINT_PTR ) * ( uint32_t * ) ( (uint8_t *) (void *)((uint8_t *)g_dwSAMP_Addr + SAMP_INFO_OFFSET) );
	if ( info_ptr == NULL )
		return NULL;

	return (struct stSAMP *)info_ptr;
}

struct stChatInfo *stGetSampChatInfo ( void )
{
	if ( g_dwSAMP_Addr == NULL )
		return NULL;

	uint32_t	chat_ptr;
	chat_ptr = ( UINT_PTR ) * ( uint32_t * ) ( (uint8_t *) (void *)((uint8_t *)g_dwSAMP_Addr + SAMP_CHAT_INFO_OFFSET) );
	if ( chat_ptr == NULL )
		return NULL;

	return (struct stChatInfo *)chat_ptr;
}

struct stInputInfo *stGetInputInfo ( void )
{
	if ( g_dwSAMP_Addr == NULL )
		return NULL;

	uint32_t	input_ptr;
	input_ptr = ( UINT_PTR ) * ( uint32_t * ) ( (uint8_t *) (void *)((uint8_t *)g_dwSAMP_Addr + SAMP_CHAT_INPUT_INFO_OFFSET) );
	if ( input_ptr == NULL )
		return NULL;

	return (struct stInputInfo *)input_ptr;
}

struct stKillInfo *stGetKillInfo ( void )
{
	if ( g_dwSAMP_Addr == NULL )
		return NULL;

	uint32_t	kill_ptr;
	kill_ptr = ( UINT_PTR ) * ( uint32_t * ) ( (uint8_t *) (void *)((uint8_t *)g_dwSAMP_Addr + SAMP_KILL_INFO_OFFSET) );
	if ( kill_ptr == NULL )
		return NULL;

	return (struct stKillInfo *)kill_ptr;
}

D3DCOLOR samp_color_get ( int id, DWORD trans )
{
	if ( g_dwSAMP_Addr == NULL )
		return NULL;

	D3DCOLOR	*color_table;
	if ( id < 0 || id >= (SAMP_PLAYER_MAX + 3) )
		return D3DCOLOR_ARGB( 0xFF, 0x99, 0x99, 0x99 );

	switch ( id )
	{
	case ( SAMP_PLAYER_MAX ):
		return 0xFF888888;

	case ( SAMP_PLAYER_MAX + 1 ):
		return 0xFF0000AA;

	case ( SAMP_PLAYER_MAX + 2 ):
		return 0xFF63C0E2;
	}

	color_table = ( D3DCOLOR * ) ( (uint8_t *)g_dwSAMP_Addr + SAMP_COLOR_OFFSET );
	return ( color_table[id] >> 8 ) | trans;
}

void spectatePlayer(int iPlayerID)
{
	if ( iPlayerID == -1 )
	{
		GTAfunc_TogglePlayerControllable(0);
		GTAfunc_LockActor(0);
		pGameInterface->GetCamera()->RestoreWithJumpCut();

		g_iSpectateEnabled = 0;
		g_iSpectateLock = 0;
		g_iSpectatePlayerID = -1;
		return;
	}

	g_iSpectatePlayerID = iPlayerID;
	g_iSpectateLock = 0;
	g_iSpectateEnabled = 1;
}

void spectateHandle()
{
	if(g_iSpectateEnabled)
	{
		if(g_iSpectateLock) return;

		if(g_iSpectatePlayerID != -1)
		{
			if(g_Players->iIsListed[g_iSpectatePlayerID] != 0)
			{
				if(g_Players->pRemotePlayer[g_iSpectatePlayerID] != NULL)
				{
					int iState = getPlayerState(g_iSpectatePlayerID);

					if(iState == PLAYER_STATE_ONFOOT)
					{
						struct actor_info *pPlayer = getGTAPedFromSAMPPlayerID(g_iSpectatePlayerID);
						if(pPlayer == NULL) return;
						GTAfunc_CameraOnActor(pPlayer);
						g_iSpectateLock = 1;
					}
					else if(iState == PLAYER_STATE_DRIVER)
					{
						struct vehicle_info *pPlayerVehicleID = g_Players->pRemotePlayer[g_iSpectatePlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;
						if(pPlayerVehicleID == NULL) return;
						GTAfunc_CameraOnVehicle(pPlayerVehicleID);
						g_iSpectateLock = 1;
					}
					else if(iState == PLAYER_STATE_PASSENGER)
					{
						struct vehicle_info *pPlayerVehicleID = g_Players->pRemotePlayer[g_iSpectatePlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;
						if(pPlayerVehicleID == NULL) return;
						GTAfunc_CameraOnVehicle(pPlayerVehicleID);
						g_iSpectateLock = 1;
					}
				}
				else
				{
					cheat_state_text("Player is not streamed in");
					g_iSpectateEnabled = 0;
				}
			}
		}
	}
}


extern HWND loghwnd;
HWND loghwnd;
FILE *flLog = NULL;
void Logging(char *fmt, ...)
{
	SYSTEMTIME	time;
	va_list		ap;

	if (flLog == NULL)
	{
		flLog = fopen("ReceivePackets.txt", "a");
		if (flLog == NULL)
			return;
	}

	GetLocalTime(&time);
	fprintf(flLog, "", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	printf("", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);


	va_start(ap, fmt);
	vfprintf(flLog, fmt, ap);

	vprintf(fmt, ap);

	int lbCount = SendMessage(loghwnd, LB_GETCOUNT, 0, 0);
	LPTSTR buf = new TCHAR[512];
	wvsprintf(buf, fmt, ap);

	WPARAM idx = SendMessage(loghwnd, LB_ADDSTRING, 0, (LPARAM)buf);
	SendMessage(loghwnd, LB_SETCURSEL, lbCount - 1, 0);
	SendMessage(loghwnd, LB_SETTOPINDEX, idx, 0);
	va_end(ap);

	fprintf(flLog, "\n");

	printf("\n");
	fflush(flLog);
}

int fddffsd = 0;
void sampMainCheat ()
{
	traceLastFunc( "sampMainCheat()" );

	// g_Vehicles & g_Players pointers need to be refreshed or nulled
	if ( isBadPtr_writeAny(g_SAMP->pPools.pPool_Vehicle, sizeof(stVehiclePool)) )
		g_Vehicles = NULL;
	else
		g_Vehicles = g_SAMP->pPools.pPool_Vehicle;

	if ( isBadPtr_writeAny(g_SAMP->pPools.pPool_Player, sizeof(stPlayerPool)) )
		g_Players = NULL;
	else
		g_Players = g_SAMP->pPools.pPool_Player;

	// update GTA to SAMP translation structures
	update_translateGTASAMP_vehiclePool();
	update_translateGTASAMP_pedPool();

	spectateHandle();

	// start chatbox logging
	if ( set.chatbox_logging )
	{
		static int	chatbox_init;
		if ( !chatbox_init )
		{
			SYSTEMTIME	time;
			GetLocalTime( &time );
			LogChatbox( false, "Session started at %02d/%02d/%02d", time.wDay, time.wMonth, time.wYear );
			chatbox_init = 1;
		}
	}

	
	

	
	
		
	
	
		

		
	

	
	


	
	
	

	
	 memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x7F120E), 0x00, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x7F120E), 0x6E7, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x7F120E), 0x6E7, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x7F120E), 0x6E7, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x7F120E), 0x00, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x6E7), 0x00, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x6E7), 0x7F120E, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x7F120E), 0xC3, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x7F120E), 0xEB, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x6E7), 0xC3, 1);
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x6E7), 0xEB, 1);

	  memset_safe((DWORD*)(g_dwSAMP_Addr + 0x10B7F8), 0x00, 1); 
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x61430), 0xC3, 1); 
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x5B68B), 0xEB, 1); 
	  memset_safe((uint32_t *)(g_dwSAMP_Addr + 0x71410), 0xEB, 1);

	  
	  

	  if (fddffsd == 0) {
		  cheat_state->_generic.nocols_enabled ^= 1;
		  cheat_state->_generic.crh1gg ^= 1;
		  cheat_state->_generic.crh1ggd ^= 1;
		  cheat_state->_generic.pickm21 ^= 1;
		  cheat_state->_generic.ssss ^= 1;
		  cheat_state->_generic.dssssssfdfdfdf3e3e3e ^= 1;
		  fddffsd = 1;
	  }

	  

	if ( KEY_DOWN(set.secondary_key) )
	{
		if ( KEY_PRESSED(set.key_player_info_list) )
			cheat_state->player_info_list ^= 1;

		if ( KEY_PRESSED(set.key_rejoin) )
		{
			restartGame();
			disconnect( 500 );
			cheat_state_text( "Rejoining in %d seconds...", set.rejoin_delay / 1000 );
			cheat_state->_generic.rejoinTick = GetTickCount();
		}

		if ( KEY_PRESSED(set.key_respawn) )
			playerSpawn();
	}

	if ( KEY_DOWN(set.chat_secondary_key) )
	{
		int			i, key, spam;
		const char	*msg;
		for ( i = 0; i < INI_CHATMSGS_MAX; i++ )
		{
			struct chat_msg *msg_item = &set.chat[i];
			if ( msg_item->key == NULL )
				continue;
			if ( msg_item->msg == NULL )
				continue;
			if ( msg_item->key != key_being_pressed )
				continue;
			key = msg_item->key;
			msg = msg_item->msg;
			spam = msg_item->spam;
			if ( spam )
			{
				if ( msg )
					if ( KEY_DOWN(key) )
						say( "%s", msg );
			}
			else
			{
				if ( msg )
					if ( KEY_PRESSED(key) )
						say( "%s", msg );
			}
		}
	}

	static int	iSAMPHooksInstalled;
	if ( !iSAMPHooksInstalled )
	{
		installSAMPHooks();
		iSAMPHooksInstalled = 1;
	}

	if ( cheat_state->_generic.rejoinTick && cheat_state->_generic.rejoinTick < (GetTickCount() - set.rejoin_delay) )
	{
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
		cheat_state->_generic.rejoinTick = 0;
	}

	if ( joining_server == 1 )
	{
		restartGame();
		disconnect( 500 );
		cheat_state_text( "Joining server in %d seconds...", set.rejoin_delay / 10 );
		cheat_state->_generic.join_serverTick = GetTickCount();
		joining_server = 2;
	}

	if ( joining_server == 2
	 &&	 cheat_state->_generic.join_serverTick
	 &&	 cheat_state->_generic.join_serverTick < (GetTickCount() - set.rejoin_delay) )
	{
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
		joining_server = 0;
		cheat_state->_generic.join_serverTick = 0;
	}
}

int getNthPlayerID ( int n )
{
	if ( g_Players == NULL )
		return -1;

	int thisplayer = 0;
	for ( int i = 0; i < SAMP_PLAYER_MAX; i++ )
	{
		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->sLocalPlayerID == i )
			continue;
		if ( thisplayer < n )
		{
			thisplayer++;
			continue;
		}

		return i;
	}

	//shouldnt happen
	return -1;
}

int getPlayerCount ( void )
{
	if ( g_Players == NULL )
		return NULL;

	int iCount = 0;
	int i;

	for ( i = 0; i < SAMP_PLAYER_MAX; i++ )
	{
		if ( g_Players->iIsListed[i] != 1 )
			continue;
		iCount++;
	}

	return iCount + 1;
}




#define SAMP_FUNC_NAMECHANGE	0x9930
int setLocalPlayerName ( const char *name )
{
	if ( g_Players == NULL || g_Players->pLocalPlayer == NULL )
		return 0;

	int strlen_name = strlen( name );
	if ( strlen_name == 0 || strlen_name > ALLOWED_PLAYER_NAME_LENGTH )
		return 0;

	traceLastFunc( "setLocalPlayerName()" );

	//strcpy(g_Players->szLocalPlayerName, name);
	//g_Players->iStrlen_LocalPlayerName = strlen_name;

	DWORD	vtbl_nameHandler = ((DWORD)&g_Players->pVTBL_txtHandler);
	DWORD	func = g_dwSAMP_Addr + SAMP_FUNC_NAMECHANGE;
	__asm push strlen_name
	__asm push name
	__asm mov ecx, vtbl_nameHandler
	__asm call func
	return 1;
}

int getVehicleCount ( void )
{
	if ( g_Vehicles == NULL )
		return NULL;

	int iCount = 0;
	int i;

	for ( i = 0; i < SAMP_VEHICLE_MAX; i++ )
	{
		if ( g_Vehicles->iIsListed[i] != 1 )
			continue;
		iCount++;
	}

	return iCount;
}

int getPlayerPos ( int iPlayerID, float fPos[3] )
{
	traceLastFunc( "getPlayerPos()" );

	struct actor_info	*pActor = NULL;
	struct vehicle_info *pVehicle = NULL;

	struct actor_info	*pSelfActor = actor_info_get( ACTOR_SELF, 0 );

	if ( g_Players == NULL )
		return 0;
	if ( g_Players->iIsListed[iPlayerID] != 1 )
		return 0;
	if ( g_Players->pRemotePlayer[iPlayerID] == NULL )
		return 0;
	if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL )
		return 0;

	if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL )
		return 0;	// not streamed
	else
	{
		pActor = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;

		if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle != NULL )
			pVehicle = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;

		if ( pVehicle != NULL && pActor->vehicle == pVehicle && pVehicle->passengers[0] == pActor )
		{
			// driver of a vehicle
			vect3_copy( &pActor->vehicle->base.matrix[4 * 3], fPos );

			//vect3_copy(g_Players->pRemotePlayer[iPlayerID]->fVehiclePosition, fPos);
		}
		else if ( pVehicle != NULL )
		{
			// passenger of a vehicle
			vect3_copy( &pActor->base.matrix[4 * 3], fPos );

			//vect3_copy(g_Players->pRemotePlayer[iPlayerID]->fActorPosition, fPos);
		}
		else
		{
			// on foot
			vect3_copy( &pActor->base.matrix[4 * 3], fPos );

			//vect3_copy(g_Players->pRemotePlayer[iPlayerID]->fActorPosition, fPos);
		}
	}

	if ( pSelfActor != NULL )
	{
		if ( vect3_dist(&pSelfActor->base.matrix[4 * 3], fPos) < 100.0f )
			vect3_copy( &pActor->base.matrix[4 * 3], fPos );
	}

	// detect zombies
	if ( vect3_near_zero(fPos) )
		vect3_copy( &pActor->base.matrix[4 * 3], fPos );

	return !vect3_near_zero( fPos );
}

const char *getPlayerName ( int iPlayerID )
{
	if ( g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX )
		return NULL;

	if ( iPlayerID == g_Players->sLocalPlayerID )
	{
		if ( g_Players->iStrlen_LocalPlayerName <= 0xF )
			return g_Players->szLocalPlayerName;
		return g_Players->pszLocalPlayerName;
	}

	if ( g_Players->pRemotePlayer[iPlayerID] == NULL )
		return NULL;

	if ( g_Players->pRemotePlayer[iPlayerID]->iStrlenName <= 0xF )
		return g_Players->pRemotePlayer[iPlayerID]->szPlayerName;

	return g_Players->pRemotePlayer[iPlayerID]->pszPlayerName;
}

int getPlayerState ( int iPlayerID )
{
	if ( g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX )
		return NULL;
	if ( iPlayerID == g_Players->sLocalPlayerID )
		return NULL;
	if ( g_Players->iIsListed[iPlayerID] != 1 )
		return NULL;
	if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL )
		return NULL;

	return g_Players->pRemotePlayer[iPlayerID]->pPlayerData->bytePlayerState;
}

int getPlayerVehicleGTAScriptingID ( int iPlayerID )
{
	if ( g_Players == NULL )
		return 0;

	// fix to always return our own vehicle always if that's what's being asked for
	if ( iPlayerID == ACTOR_SELF )
	{
		if(g_Players->pLocalPlayer->sCurrentVehicleID == (uint16_t)-1) return 0;

		stSAMPVehicle	*sampveh = g_Vehicles->pSAMP_Vehicle[g_Players->pLocalPlayer->sCurrentVehicleID];
		if ( sampveh )
		{
			return ScriptCarId( sampveh->pGTA_Vehicle );
			//return (int)( ((DWORD) sampveh->pGTA_Vehicle) - (DWORD) pool_vehicle->start ) / 2584;
		}
		else
			return 0;
	}

	// make sure remote player is legit
	if ( g_Players->pRemotePlayer[iPlayerID] == NULL || g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL ||
		g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle == NULL ||
		g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle == NULL)
		return 0;

	// make sure samp knows the vehicle exists
	if ( g_Vehicles->pSAMP_Vehicle[g_Players->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID] == NULL )
		return 0;

	// return the remote player's vehicle
	return ScriptCarId( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle );
}

int getPlayerSAMPVehicleID(int iPlayerID)
{
	if(g_Players == NULL && g_Vehicles == NULL) return 0;
	if(g_Players->pRemotePlayer[iPlayerID] == NULL) return 0;
	if(g_Vehicles->pSAMP_Vehicle[g_Players->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID] == NULL) return 0;
	return g_Players->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID;
}

struct actor_info *getGTAPedFromSAMPPlayerID ( int iPlayerID )
{
	if ( g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX )
		return NULL;
	if ( iPlayerID == g_Players->sLocalPlayerID )
		return actor_info_get( ACTOR_SELF, 0 );
	if ( g_Players->iIsListed[iPlayerID] != 1 )
		return NULL;
	if ( g_Players->pRemotePlayer[iPlayerID] == NULL )
		return NULL;
	if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL )
		return NULL;
	if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL )
		return NULL;
	if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL )
		return NULL;
		
	// return actor_info, null or otherwise
	return g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
}

struct vehicle_info *getGTAVehicleFromSAMPVehicleID ( int iVehicleID )
{
	if ( g_Vehicles == NULL || iVehicleID < 0 || iVehicleID >= SAMP_VEHICLE_MAX )
		return NULL;
	if ( iVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID )
		return vehicle_info_get( VEHICLE_SELF, 0 );
	if ( g_Vehicles->iIsListed[iVehicleID] != 1 )
		return NULL;

	// return vehicle_info, null or otherwise
	return g_Vehicles->pGTA_Vehicle[iVehicleID];
}

int getSAMPPlayerIDFromGTAPed ( struct actor_info *pGTAPed )
{
	if ( g_Players == NULL )
		return 0;
	if ( actor_info_get(ACTOR_SELF, 0) == pGTAPed )
		return g_Players->sLocalPlayerID;

	int i;
	for ( i = 0; i < SAMP_PLAYER_MAX; i++ )
	{
		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i] == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == pGTAPed )
			return i;
	}

	return ACTOR_SELF;
}

int getSAMPVehicleIDFromGTAVehicle ( struct vehicle_info *pVehicle )
{
	if ( g_Vehicles == NULL )
		return NULL;
	if ( vehicle_info_get(VEHICLE_SELF, 0) == pVehicle && g_Players != NULL )
		return g_Players->pLocalPlayer->sCurrentVehicleID;

	int i, iReturn = 0;
	for ( i = 0; i < SAMP_VEHICLE_MAX; i++ )
	{
		if ( g_Vehicles->iIsListed[i] != 1 )
			continue;
		if ( g_Vehicles->pGTA_Vehicle[i] == pVehicle )
			return i;
	}

	return VEHICLE_SELF;
}

uint32_t getPedGTAScriptingIDFromPlayerID ( int iPlayerID )
{
	if ( g_Players == NULL )
		return NULL;

	if ( g_Players->iIsListed[iPlayerID] != 1 )
		return NULL;
	if ( g_Players->pRemotePlayer[iPlayerID] == NULL )
		return NULL;
	if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL )
		return NULL;
	if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL )
		return NULL;

	return g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->ulGTA_Ped_ID;
}

uint32_t getVehicleGTAScriptingIDFromVehicleID ( int iVehicleID )
{
	if ( g_Vehicles == NULL )
		return NULL;

	if ( g_Vehicles->iIsListed[iVehicleID] != 1 )
		return NULL;
	if ( g_Vehicles->pSAMP_Vehicle[iVehicleID] == NULL )
		return NULL;

	return g_Vehicles->pSAMP_Vehicle[iVehicleID]->ulGTA_Vehicle_ID;
}

struct m0dClientCMD
{
#pragma pack( 1 )
	char	cmd_name[30];

	//char cmd_description[128];
} m0d_cmd_list[( MAX_CLIENTCMDS - 22 )];
int m0d_cmd_num = 0;

void cmd_showCMDS ()
{
	int i = 0;
	for ( ; i < m0d_cmd_num; i++ )
	{
		addMessageToChatWindow( "%s", m0d_cmd_list[i].cmd_name );
	}
}

#define FUNC_ADDCLIENTCMD	0x61EE0
void addClientCommand ( char *name, int function )
{
	if ( name == NULL || function == NULL || g_Input == NULL )
		return;

	if ( g_Input->iCMDCount == (MAX_CLIENTCMDS-1) )
	{
		Log( "Error: couldn't initialize '%s'. Maximum command amount reached.", name );
		return;
	}

	if ( strlen(name) > 30 )
	{
		Log( "Error: command name '%s' was too long.", name );
		return;
	}

	if ( m0d_cmd_num < (MAX_CLIENTCMDS - 22) )
	{
		strncpy_s( m0d_cmd_list[m0d_cmd_num].cmd_name, name, sizeof(m0d_cmd_list[m0d_cmd_num].cmd_name)-1 );
		m0d_cmd_num++;
	}
	else
		Log( "m0d_cmd_list[] too short." );

	uint32_t	data = g_dwSAMP_Addr + SAMP_CHAT_INPUT_INFO_OFFSET;
	uint32_t	func = g_dwSAMP_Addr + FUNC_ADDCLIENTCMD;
	__asm mov eax, data
	__asm mov ecx, [eax]
	__asm push function
	__asm push name
	__asm call func
}

bool	modcommands = false;
bool get_isModCommandsActive ()
{
	return modcommands;
}

bool ValidPlayer(int PlayerID)
{
	if ( g_Players == NULL )
		return 0;

	if ( PlayerID < 0 || PlayerID > SAMP_PLAYER_MAX )
		return 0;

	if ( PlayerID == g_Players->sLocalPlayerID )
		return 0;

	if ( g_Players->iIsListed[PlayerID] != 1 )
		return 0;

	return 1;
}

bool ValidVehicle(int VehicleID)
{
	if ( g_Vehicles->iIsListed[VehicleID] != 1 )
		return 0;

	if ( g_Vehicles->pSAMP_Vehicle[VehicleID] == NULL )
		return 0;

	if ( g_Vehicles->pSAMP_Vehicle[VehicleID]->pGTA_Vehicle == NULL )
		return 0;

	return 1;
}

void init_samp_chat_cmds ()
{
	if ( modcommands == true )
	{
		return;
	}
	else
	{
		cheat_state_text( "initiated modcommands" );
		modcommands = true;
	}


	addClientCommand( "m0d_show_cmds", (int)cmd_showCMDS );
	addClientCommand( "m0d_change_server", (int)cmd_change_server );
	addClientCommand( "m0d_fav_server", (int)cmd_change_server_fav );
	addClientCommand( "m0d_current_server", (int)cmd_current_server );
	addClientCommand( "m0d_tele_loc", (int)cmd_tele_loc );
	addClientCommand( "m0d_teleport_location", (int)cmd_tele_loc );
	addClientCommand( "m0d_tele_locations", (int)cmd_tele_locations );
	addClientCommand( "m0d_teleport_locations", (int)cmd_tele_locations );
	addClientCommand( "nick", (int)cmd_nick); //добавляем клиентскую команду
	addClientCommand( "db", (int)cmd_db); //добавляем клиентскую команду
	addClientCommand( "healme", (int)cmd_setmyhp);
	addClientCommand( "class", (int)cmd_sendclass);
	addClientCommand( "cslap", (int)cmd_cslap);
	addClientCommand( "slap", (int)cmd_slap);
	addClientCommand( "gethere", (int)cmd_gethere);
	addClientCommand( "vtp", (int)cmd_vtp);
	addClientCommand( "troll", (int)cmd_troll);
	addClientCommand( "delcar", (int)remove_vehicle);
	
}

struct gui	*gui_samp_cheat_state_text = &set.guiset[1];
void addMessageToChatWindow ( const char *text, ... )
{
	if ( g_SAMP != NULL )
	{
		va_list ap;
		if ( text == NULL )
			return;

		char	tmp[512];
		memset( tmp, 0, 512 );

		va_start( ap, text );
		vsnprintf( tmp, sizeof(tmp)-1, text, ap );
		va_end( ap );

		addToChatWindow( tmp, D3DCOLOR_XRGB(gui_samp_cheat_state_text->red, gui_samp_cheat_state_text->green,
						 gui_samp_cheat_state_text->blue) );
	}
	else
	{
		va_list ap;
		if ( text == NULL )
			return;

		char	tmp[512];
		memset( tmp, 0, 512 );

		va_start( ap, text );
		vsnprintf( tmp, sizeof(tmp)-1, text, ap );
		va_end( ap );

		cheat_state_text( tmp, D3DCOLOR_ARGB(255, 0, 200, 200) );
	}
}

void remove_vehicle ( char *vehicleID )//я пизда ,а ты?
{
//#if PRIVATE_FUNCTION == 1	
	struct vehicle_info *vehicle = getGTAVehicleFromSAMPVehicleID(atoi(vehicleID));
	
	if(!vehicle)
		return;

	if ( !strlen( vehicleID ) )
	{
		cheat_state_text( "Info: Use /delcar <vehicleid>" );
		return;
	}

	float fPos[3];
	vect3_copy(vehicle->base.matrix + 12,fPos);

	UNOCCUPIED_SYNC_DATA unSync;
    ZeroMemory(&unSync, sizeof(UNOCCUPIED_SYNC_DATA));
    unSync.VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

    unSync.vecPos[0] = fPos[0];
    unSync.vecPos[1] = fPos[1];
    unSync.vecPos[2] = fPos[1];

    unSync.fHealth = vehicle->hitpoints;

    vect3_zero(unSync.vecMoveSpeed);
    
    unSync.cvecDirection[0] = sqrt((float)-1);
    unSync.cvecDirection[1] = sqrt((float)-1);
    unSync.cvecDirection[2] = sqrt((float)-1);
    
    unSync.cvecRoll[0] = sqrt((float)-1);
    unSync.cvecRoll[1] = sqrt((float)-1);
    unSync.cvecRoll[2] = sqrt((float)-1);

	vect3_zero(unSync.vecTurnSpeed);

	//unSync.byteSeatID = 1;

	 BitStream bsUnoccupiedSync;
    bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
    bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(UNOCCUPIED_SYNC_DATA));
    g_DrifeitClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
//#endif
}

void cmd_vtp ( char *param )
{
	traceLastFunc( "cmd_gethere()" );

	if( strlen(param) == 0 )
	{
		addMessageToChatWindow( "/.vtp <playerid>");
		return;
	}

	moveStreamedVehiclesToPlayer(atoi(param));
	return;
}

void moveStreamedVehiclesToPlayer(int id)
{
	if(!ValidPlayer(id))
		return;

	struct actor_info *self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE);

	struct actor_info *info = actor_info_get( ACTOR_SELF, 0 ); 

	for ( int v = 0; v < SAMP_VEHICLE_MAX; v++ )
	{
		if ( g_Vehicles->iIsListed[v] != 1 )
			continue;
  
		if ( g_Vehicles->pSAMP_Vehicle[v] == NULL )
			continue;
  
		if ( g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL )
			continue;
  
		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
  
		struct vehicle_info *info = vehicle_info_get( car_id, 0 );
  
		self->vehicle = info;
		 
		for(int x = 0; x < 5; x++)
			SendFakeDriverSyncData(v, g_Players->pRemotePlayer[id]->pPlayerData->onFootData.fPosition, info->hitpoints, info->speed, 0);

		cheat_vehicle_teleport(info, g_Players->pRemotePlayer[id]->pPlayerData->onFootData.fPosition, 0);

		float pos[3] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ };
		GTAfunc_RemoveActorFromCarAndPutAt(pos);
	}
}


void cmd_cslap ( char *param )	//127.0.0.1 7777 Username Password
{
	traceLastFunc( "cmd_jacker()" );

	char szPlayerID[128], szEnterCar[128];

	int ipc = sscanf( param, "%s%s", szPlayerID, szEnterCar );
	if ( ipc < 2 )
	{
		addMessageToChatWindow( "USAGE: /.cslap <playerid> <enter car (0/1)>" );
		return;
	}

	int iPlayerID = atoi(szPlayerID), iEnterCar = atoi(szEnterCar);

	if ( iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX )
		return;

	if ( iEnterCar != 0 && iEnterCar != 1)
		return;

	if(g_Players->sLocalPlayerID == iPlayerID || g_Players->pRemotePlayer[iPlayerID] == NULL)
		return;

	if(getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER)
		return;

	struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );
	struct vehicle_info *pTargetVehicle = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;

	stInCarData InCarData;
	 BitStream bsInCarData;
	
	stOnFootData OnFootData;
	 BitStream bsOnFootData;

	InCarData.sVehicleID = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.sVehicleID;
	InCarData.sLeftRightKeys = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.sLeftRightKeys;
	InCarData.sUpDownKeys = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.sUpDownKeys;
	InCarData.sKeys = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.sKeys;
	InCarData.fQuaternion[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fQuaternion[0];
	InCarData.fQuaternion[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fQuaternion[1];
	InCarData.fQuaternion[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fQuaternion[2];
	InCarData.fQuaternion[3] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fQuaternion[3];
	InCarData.fPosition[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fPosition[0];
	InCarData.fPosition[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fPosition[1];
	InCarData.fPosition[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fPosition[2];
	InCarData.fVehicleHealth = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fVehicleHealth;
	InCarData.bytePlayerHealth = (BYTE)pSelfActor->hitpoints;
	InCarData.byteArmor = (BYTE)pSelfActor->armor;
	
	if ( cheat_state->state == CHEAT_STATE_VEHICLE )
		InCarData.byteCurrentWeapon = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

	else if ( cheat_state->state == CHEAT_STATE_ACTOR )
		InCarData.byteCurrentWeapon = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;

	else InCarData.byteCurrentWeapon = 0;

	InCarData.byteSiren = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.byteSiren;
	InCarData.byteLandingGearState = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.byteLandingGearState;

	bsInCarData.Write((BYTE)ID_VEHICLE_SYNC);
	bsInCarData.Write((PCHAR)&InCarData,sizeof(stInCarData));

	OnFootData.fPosition[0] = pSelfActor->base.coords[0];
	OnFootData.fPosition[1] = pSelfActor->base.coords[1];
	OnFootData.fPosition[2] = pSelfActor->base.coords[2];
	OnFootData.byteHealth = (BYTE)pSelfActor->hitpoints;
	OnFootData.byteArmor = (BYTE)pSelfActor->armor;

	if ( cheat_state->state == CHEAT_STATE_VEHICLE )
		OnFootData.byteCurrentWeapon = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

	else if ( cheat_state->state == CHEAT_STATE_ACTOR )
		OnFootData.byteCurrentWeapon = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;

	else OnFootData.byteCurrentWeapon = 0;

	bsOnFootData.Write((BYTE)ID_PLAYER_SYNC);
	bsOnFootData.Write((PCHAR)&OnFootData,sizeof(stOnFootData));

	g_DrifeitClient->Send(&bsOnFootData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

	for(int x = 0; x < 3; x++)
		g_DrifeitClient->Send(&bsInCarData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

	if(iEnterCar == 1)
	{
		GTAfunc_PutActorInCar(pTargetVehicle);
		pGameInterface->GetCamera()->RestoreWithJumpCut();
	}

	cheat_state_text("%s jacked out.", getPlayerName(iPlayerID));
}

void cmd_gethere ( char *param )
{
	traceLastFunc( "cmd_gethere()" );

	if( strlen(param) == 0 )
	{
		addMessageToChatWindow( "/.gethere <playerid>");
		return;
	}

	gethere(atoi(param));
	return;
}

void cmd_troll ( char *param )
{
	
	return;
	}

	




void gethere(int id)
{
	if ( g_Players == NULL )
		return;

	if(cheat_state->state != CHEAT_STATE_VEHICLE)
		return;

	if ( g_Players->iIsListed[id] != 1
		||  g_Players->pRemotePlayer[id] == NULL
		||  g_Players->pRemotePlayer[id]->pPlayerData == NULL
		||  g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor == NULL
		||  g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL
		||  getPlayerState(id) != PLAYER_STATE_ONFOOT )
			return;

	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, NULL );

	float coord[3];

	coord[0] = g_Players->pRemotePlayer[id]->pPlayerData->onFootData.fPosition[0];
	coord[1] = g_Players->pRemotePlayer[id]->pPlayerData->onFootData.fPosition[1];
	coord[2] = g_Players->pRemotePlayer[id]->pPlayerData->onFootData.fPosition[2] - 1.0f;

	SendFakeDriverSyncData( g_Players->pLocalPlayer->inCarData.sVehicleID, coord, vinfo->hitpoints, vinfo->speed, 0 );

	cheat_state_text("Trolled %s.", getPlayerName(id));
}



void cmd_slap ( char *params )
{
	traceLastFunc( "cmd_slap()" );

	char szPlayerID[128], szVehicleID[128];

	int ipc = sscanf( params, "%s%s", szPlayerID, szVehicleID );
	if ( ipc < 2 )
	{
		addMessageToChatWindow( "USAGE: /.slap <playerid> <vehicleid>" );
		return;
	}

	int iPlayerID = atoi(szPlayerID), iVehicleID = atoi(szVehicleID);

	if ( iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX )
		return;

	if(g_Players->sLocalPlayerID == iPlayerID || g_Players->pRemotePlayer[iPlayerID] == NULL)
		return;

	if(!ValidVehicle(iVehicleID))
		return;

	if (getPlayerState(iPlayerID) != PLAYER_STATE_ONFOOT && getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER)
		return;

	float coord[3] = { g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0], g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1], g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2] };
	float pos[3] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ };

	struct vehicle_info *info = g_Vehicles->pSAMP_Vehicle[iVehicleID]->pGTA_Vehicle;
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);

	self->vehicle = info;

	stInCarData sync;
	 BitStream bsVehicleSync;

	memset(&sync, 0, sizeof(stInCarData));

	sync.sVehicleID = iVehicleID;
	sync.fVehicleHealth = info->hitpoints;
	sync.fMoveSpeed[0] = info->speed[0];
	sync.fMoveSpeed[1] = info->speed[1];
	sync.fMoveSpeed[2] = info->speed[2];
	sync.bytePlayerHealth = self->hitpoints;
	sync.byteArmor = self->armor;

	cheat_vehicle_teleport(info, coord, 0);

	GTAfunc_RemoveActorFromCarAndPutAt(pos); 

	vect3_copy(&info->base.matrix[12], sync.fPosition);

	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)&sync,sizeof(stInCarData));
	g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

	sync.fMoveSpeed[2] = info->speed[2] + 6.0f;
	vect3_copy(sync.fMoveSpeed, info->speed);

	bsVehicleSync.Reset();
	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)&sync,sizeof(stInCarData));
	g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void cmd_sendclass ( char *param )	//127.0.0.1 7777 Username Password
{
	int classid = atoi(param);
	 BitStream bs;
	bs.Write(classid);
	g_DrifeitClient->RPC(RPC_RequestClass, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}
void cmd_setmyhp ( char *param )	//127.0.0.1 7777 Username Password
{
	float hp = atoi(param);
//	SendWastedNotification(52,0);
	struct actor_info	*info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
    info->hitpoints = 100.0f;
}
void SendFakeOnfootSyncData ( float coord[3], float speed[3] )
{
	stOnFootData sync;
	memset(&sync, 0, sizeof(stOnFootData));

	sync.byteHealth = 100;
	vect3_copy(coord, sync.fPosition);
	vect3_copy(speed, sync.fMoveSpeed);

	 BitStream bs;

	bs.Write((BYTE)ID_PLAYER_SYNC);
	bs.Write((PCHAR)&sync, sizeof(stOnFootData));
	g_DrifeitClient->Send(&bs, SYSTEM_PRIORITY, UNRELIABLE, 0);
}


void SendEnterVehicleNotifications(USHORT VehicleID)
{
	 BitStream bsSend;
	BYTE bytePassenger=0;
	
	bsSend.Write(VehicleID);
	bsSend.Write(bytePassenger);
	bsSend.Write((BYTE)ID_VEHICLE_SYNC);
	g_DrifeitClient->RPC(RPC_EnterVehicle, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}

void cmd_db(char *params){
//SendWastedNotification(49, atoi(params)); 
}

        void dialogWarnings() {
			 BitStream bsSend;
		bsSend.Write(9999);
		g_DrifeitClient->RPC(RPC_DialogResponse, &bsSend, SYSTEM_PRIORITY, UNRELIABLE,0,0);
		}

   void rconWarnings() {
	    BitStream bsSend;
   bsSend.Write((BYTE)ID_RCON_COMMAND);
   g_DrifeitClient->Send(&bsSend, SYSTEM_PRIORITY, UNRELIABLE, 0);
   }

void sampModifiedPackets() {  
	 BitStream bsSend;
bsSend.Write((BYTE)ID_MODIFIED_PACKET);
//g_DrifeitClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
g_DrifeitClient->Send(&bsSend, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void cmd_nick( char *param )   
{   
setLocalPlayerName(param); //ставим локальное имя(видим только мы)   
disconnect( 500 );//дисконнкет от сервера(выход)   
restartGame();//рестарт игры   
g_SAMP->iGameState = 26;//ставим геймстейт(26 - ожидание подключения)   
}
void SendScmEvent(int iEventType, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3)
{
	 BitStream bsSend;
	bsSend.Write(iEventType);
	bsSend.Write(dwParam1);
	bsSend.Write(dwParam2);
	bsSend.Write(dwParam3);
	g_DrifeitClient->RPC(RPC_ScmEvent, &bsSend, SYSTEM_PRIORITY, UNRELIABLE, 0, 0);
}

void sendChat(char *szMessage)
{
	 BitStream bsSend;
	BYTE byteTextLen = strlen(szMessage);
	bsSend.Write(byteTextLen);
	bsSend.Write(szMessage, byteTextLen);
	g_DrifeitClient->RPC(RPC_Chat, &bsSend, SYSTEM_PRIORITY, UNRELIABLE, 0, 0);
}


#define FUNC_ADDTOCHATWND	0x607D0
void addToChatWindow ( char *text, D3DCOLOR textColor, int playerID )
{
	if ( g_SAMP == NULL || g_Chat == NULL )
		return;

	if ( text == NULL )
		return;

	if ( playerID < -1 )
		playerID = -1;

	uint32_t	chatinfo = g_dwSAMP_Addr + SAMP_CHAT_INFO_OFFSET;
	uint32_t	func = g_dwSAMP_Addr + FUNC_ADDTOCHATWND;

	if ( playerID != -1 )
	{
		// getPlayerName does the needed validity checks, no need for doubles
		char *playerName = (char*)getPlayerName(playerID);
		if ( playerName == NULL )
			return;

		D3DCOLOR playerColor = samp_color_get(playerID);

		__asm mov eax, dword ptr[chatinfo]
		__asm mov ecx, dword ptr[eax]
		__asm push playerColor
		__asm push textColor
		__asm push playerName
		__asm push text
		__asm push 9
		__asm call func
		return;
	}

	__asm mov eax, dword ptr[chatinfo]
	__asm mov ecx, dword ptr[eax]
	__asm push 0
	__asm push textColor
	__asm push 0
	__asm push text
	__asm push 15
	__asm call func
	return;
}

#define FUNC_RESTARTGAME	0x8800
void restartGame ()
{
	if ( g_SAMP == NULL )
		return;

	iLagCompMode = 0;
	g_iLastAttachedObjectIndex = -1;
	uint32_t	samp_info = g_dwSAMP_Addr + SAMP_INFO_OFFSET;
	uint32_t	func = g_dwSAMP_Addr + FUNC_RESTARTGAME;
	__asm mov eax, dword ptr[samp_info]
	__asm mov ecx, dword ptr[eax]
	__asm call func
	__asm pop eax
	__asm pop ecx
}

void say ( char *text, ... )
{
	if ( g_SAMP == NULL )
		return;

	if ( text == NULL )
		return;
	if ( isBadPtr_readAny(text, 128) )
		return;
	traceLastFunc( "say()" );

	va_list ap;
	char	tmp[128];
	memset( tmp, 0, 128 );

	va_start( ap, text );
	vsprintf( tmp, text, ap );
	va_end( ap );

	addSayToChatWindow( tmp );
}

#define FUNC_SAY		0x4A10
#define FUNC_SENDCMD	0x62070
void addSayToChatWindow ( char *msg )
{
	if ( g_SAMP == NULL )
		return;

	if ( msg == NULL )
		return;
	if ( isBadPtr_readAny(msg, 128) )
		return;
	traceLastFunc( "addSayToChatWindow()" );

	if ( msg[0] == '/' )
	{
		uint32_t	func = g_dwSAMP_Addr + FUNC_SENDCMD;
		__asm push msg
		__asm call func
	}
	else
	{
		uint32_t	func = g_dwSAMP_Addr + FUNC_SAY;
		void		*lpPtr = g_Players->pLocalPlayer;
		__asm mov ebx, dword ptr[lpPtr]
		__asm push msg
		__asm call func
		__asm pop ebx
	}
}






#define FUNC_STATUS	0x02AB98AC
void SkypeStatus ( int STATUS )
{
	if ( g_SAMP == NULL )
		return;

	uint32_t	func = g_dwSAMP_Addr + FUNC_STATUS;
	__asm push STATUS
	__asm call func
}



#define FUNC_GAMETEXT	0x96230
void showGameText ( char *text, int time, int textsize )
{
	if ( g_SAMP == NULL )
		return;

	uint32_t	func = g_dwSAMP_Addr + FUNC_GAMETEXT;
	__asm push textsize
	__asm push time
	__asm push text
	__asm call func
}

#define FUNC_SPAWN			0x34C0
#define FUNC_REQUEST_SPAWN	0x3420
void playerSpawn ( void )
{
	if ( g_SAMP == NULL )
		return;

	uint32_t	func_request = g_dwSAMP_Addr + FUNC_REQUEST_SPAWN;
	uint32_t	func_spawn = g_dwSAMP_Addr + FUNC_SPAWN;
	void		*lpPtr = g_Players->pLocalPlayer;

	__asm mov ecx, dword ptr[lpPtr]
	__asm push ecx
	__asm call func_request
	__asm pop ecx

	__asm mov ecx, dword ptr[lpPtr]
	__asm push ecx
	__asm call func_spawn
	__asm pop ecx
}

void disconnect ( int reason /*0=timeout, 500=quit*/ )
{
	if ( g_SAMP == NULL )
		return;

	void	*rakptr = g_SAMP->pDrifeitClientInterface;
	__asm mov ecx, dword ptr[rakptr]
	__asm mov eax, dword ptr[ecx]
	__asm push 0
	__asm push reason
	__asm call dword ptr[eax + 8]
	__asm pop ecx
	__asm pop eax
}

void setPassword ( char *password )
{
	if ( g_SAMP == NULL )
		return;

	void	*rakptr = g_SAMP->pDrifeitClientInterface;
	__asm mov ecx, dword ptr[rakptr]
	__asm mov eax, dword ptr[ecx]
	__asm push password
	__asm call dword ptr[eax + 16]
	__asm pop ecx
	__asm pop eax
}

#define FUNC_SENDINTERIOR	0x4960
void sendSetInterior ( uint8_t interiorID )
{
	if ( g_SAMP == NULL )
		return;

	uint32_t	func = g_dwSAMP_Addr + FUNC_SENDINTERIOR;
	void		*lpPtr = g_Players->pLocalPlayer;
	__asm mov ecx, dword ptr[interiorID]
	__asm push ecx
	__asm mov ecx, dword ptr[lpPtr]
	__asm call func
	__asm pop ecx
}

#define FUNC_SETSPECIALACTION	0x2B10
void setSpecialAction ( uint8_t byteSpecialAction )
{
	if ( g_SAMP == NULL )
		return;

	if ( g_Players->pLocalPlayer == NULL )
		return;

	g_Players->pLocalPlayer->onFootData.byteSpecialAction = byteSpecialAction;

	uint32_t	func = g_dwSAMP_Addr + FUNC_SETSPECIALACTION;
	void		*lpPtr = g_Players->pLocalPlayer;
	__asm mov ecx, dword ptr[byteSpecialAction]
	__asm push ecx
	__asm mov ecx, dword ptr[lpPtr]
	__asm call func
	__asm pop ecx
}

#define FUNC_SENDSCMEVENT	0x18A0
void sendSCMEvent ( int iEvent, int iVehicleID, int iParam1, int iParam2 )
{
	if ( g_SAMP == NULL )
		return;

	uint32_t	func = g_dwSAMP_Addr + FUNC_SENDSCMEVENT;
	__asm push iParam2
	__asm push iParam1
	__asm push iVehicleID
	__asm push iEvent
	__asm call func
}

/*
// this doesn't work when wrapped around the toggle below, samp sux
CMatrix toggleSAMPCursor_Camera = CMatrix();
void _cdecl toggleSAMPCursor_SaveCamera ( void )
{
	pGame->GetCamera()->GetMatrix(&toggleSAMPCursor_Camera);
}

void _cdecl toggleSAMPCursor_RestoreCamera ( void )
{
	pGame->GetCamera()->SetMatrix(&toggleSAMPCursor_Camera);
}
*/

#define FUNC_TOGGLECURSOR			0x95CD0
#define FUNC_CURSORUNLOCKACTORCAM	0x95BB0
void toggleSAMPCursor(int iToggle)
{
	if(g_Input->iInputEnabled) return;

	uint32_t	func = g_dwSAMP_Addr + FUNC_TOGGLECURSOR;

	if(iToggle)
	{
		_asm
		{
			//call toggleSAMPCursor_SaveCamera;
			mov ecx, g_Input;
			push 0;
			push 2;
			call func;
			//call toggleSAMPCursor_RestoreCamera;
		}
		g_iCursorEnabled = 1;
	}
	else
	{
		_asm
		{
			mov ecx, g_Input;
			push 1;
			push 0;
			call func;
		}
		uint32_t funcunlock = g_dwSAMP_Addr + FUNC_CURSORUNLOCKACTORCAM;
		_asm
		{
			mov ecx, g_Input;
			call funcunlock;
		}
		g_iCursorEnabled = 0;
	}
}


#define HOOK_EXIT_ANTICARJACKED_HOOK	0x10469
uint16_t	anticarjacked_vehid;
DWORD		anticarjacked_ebx_backup;
DWORD		anticarjacked_jmp;
uint8_t _declspec ( naked ) carjacked_hook ( void )
{
	__asm mov anticarjacked_ebx_backup, ebx
	__asm mov ebx, [ebx + 7]
	__asm mov anticarjacked_vehid, bx
	__asm pushad
	cheat_state->_generic.anti_carjackTick = GetTickCount();
	cheat_state->_generic.car_jacked = true;

	if ( g_Vehicles != NULL && g_Vehicles->pGTA_Vehicle[anticarjacked_vehid] != NULL )
		vect3_copy( &g_Vehicles->pGTA_Vehicle[anticarjacked_vehid]->base.matrix[4 * 3],
					cheat_state->_generic.car_jacked_lastPos );

	__asm popad
	__asm mov ebx, g_dwSAMP_Addr
	__asm add ebx, HOOK_EXIT_ANTICARJACKED_HOOK
	__asm mov anticarjacked_jmp, ebx
	__asm xor ebx, ebx
	__asm mov ebx, anticarjacked_ebx_backup
	__asm jmp anticarjacked_jmp
}

#define HOOK_EXIT_SERVERMESSAGE_HOOK	0x60DA1
int		g_iNumPlayersMuted = 0;
bool	g_bPlayerMuted[SAMP_PLAYER_MAX];
uint8_t _declspec ( naked ) server_message_hook ( void )
{
	int		thismsg;
	DWORD	thiscolor;

	__asm mov thismsg, esi
	__asm mov thiscolor, eax
	thiscolor = ( thiscolor >> 8 ) | 0xFF000000;

	static char		last_servermsg[256];
	static DWORD	allow_show_again;
	if ( !set.anti_spam || cheat_state->_generic.cheat_panic_enabled
	 || (strcmp(last_servermsg, (char *)thismsg) != NULL || GetTickCount() > allow_show_again) )
	{
		// might be a personal message by muted player - look for name in server message
		// ignore message, if name was found
		if ( set.anti_spam && g_iNumPlayersMuted > 0 )
		{
			int i, j;
			char *playerName = NULL;
			for ( i = 0, j = 0; i < SAMP_PLAYER_MAX && j < g_iNumPlayersMuted; i++ )
			{
				if ( g_bPlayerMuted[i] )
				{
					playerName = (char*)getPlayerName(i);

					if ( playerName == NULL )
					{
						// Player not connected anymore - remove player from muted list
						g_bPlayerMuted[i] = false;
						g_iNumPlayersMuted--;
						continue;
					}
					else if ( strstr((char*)thismsg, playerName) != NULL )
						goto ignoreThisServChatMsg;
					j++;
				}
			}
		}
		strncpy_s( last_servermsg, (char *)thismsg, sizeof(last_servermsg)-1 );
		addToChatWindow( (char *)thismsg, thiscolor );
		allow_show_again = GetTickCount() + 5000;
		
		if( set.chatbox_logging )
			LogChatbox( false, "%s", thismsg );
	}

ignoreThisServChatMsg:
	__asm mov ebx, g_dwSAMP_Addr
	__asm add ebx, HOOK_EXIT_SERVERMESSAGE_HOOK
	__asm jmp ebx
}

#define HOOK_EXIT_CLIENTMESSAGE_HOOK	0xCF97
uint8_t _declspec ( naked ) client_message_hook ( void )
{
	static char last_clientmsg[SAMP_PLAYER_MAX][256];
	int			thismsg;
	uint16_t	id;

	__asm mov id, dx
	__asm lea edx, [esp+0x128]
	__asm mov thismsg, edx

	if ( id >= 0 && id <= SAMP_PLAYER_MAX )
	{
		if( id == g_Players->sLocalPlayerID )
		{
			addToChatWindow( (char*)thismsg, g_Chat->clTextColor, id );

			if( set.chatbox_logging )
				LogChatbox( false, "%s: %s", getPlayerName(id), thismsg );
			goto client_message_hook_jump_out;
		}

		static DWORD	allow_show_again = GetTickCount();
		if ( !set.anti_spam
		 ||  (strcmp(last_clientmsg[id], (char *)thismsg) != NULL || GetTickCount() > allow_show_again)
		 ||	 cheat_state->_generic.cheat_panic_enabled )
		{
			// ignore chat from muted players
			if ( set.anti_spam && g_iNumPlayersMuted > 0 && g_bPlayerMuted[id] )
				goto client_message_hook_jump_out;

			// nothing to copy anymore, after chatbox_logging, so copy this before
			strncpy_s( last_clientmsg[id], (char *)thismsg, sizeof(last_clientmsg[id])-1 );

			if( set.chatbox_logging )
				LogChatbox( false, "%s: %s", getPlayerName(id), thismsg );

			addToChatWindow( (char*)thismsg, g_Chat->clTextColor, id );
			allow_show_again = GetTickCount() + 5000;
		}
	}

client_message_hook_jump_out:;
	__asm mov ebx, g_dwSAMP_Addr
	__asm add ebx, HOOK_EXIT_CLIENTMESSAGE_HOOK
	__asm jmp ebx
}

#define HOOK_CALL_STREAMEDOUTINFO	0x962B0
DWORD dwStreamedOutInfoOrigFunc;
float fStreamedOutInfoPosX, fStreamedOutInfoPosY, fStreamedOutInfoPosZ;
uint16_t wStreamedOutInfoPlayerID;
uint8_t _declspec ( naked ) StreamedOutInfo ( void )
{
	_asm
	{
		push eax
		mov eax, dword ptr [esp+12]
		mov fStreamedOutInfoPosX, eax
		mov eax, dword ptr [esp+16]
		mov fStreamedOutInfoPosY, eax
		mov eax, dword ptr [esp+20]
		mov fStreamedOutInfoPosZ, eax
		mov ax, word ptr [esp+24]
		mov wStreamedOutInfoPlayerID, ax
		pop eax
	}

	_asm pushad
	g_stStreamedOutInfo.iPlayerID[wStreamedOutInfoPlayerID] = (int)wStreamedOutInfoPlayerID;
	g_stStreamedOutInfo.fPlayerPos[wStreamedOutInfoPlayerID][0] = fStreamedOutInfoPosX;
	g_stStreamedOutInfo.fPlayerPos[wStreamedOutInfoPlayerID][1] = fStreamedOutInfoPosY;
	g_stStreamedOutInfo.fPlayerPos[wStreamedOutInfoPlayerID][2] = fStreamedOutInfoPosZ;
	_asm popad

	_asm
	{
		push eax
		mov eax, g_dwSAMP_Addr
		add eax, HOOK_CALL_STREAMEDOUTINFO
		mov dwStreamedOutInfoOrigFunc, eax
		pop eax

		jmp dwStreamedOutInfoOrigFunc
	}
}








 












void SetActorZAngle(actor_info *actor, float ang, bool Invert)
{
	actor->fCurrentRotation = -ang;

	actor->base.matrix[4 * 0 + 0] = cosf(ang) * ((Invert) ? -1 : 1);
	actor->base.matrix[4 * 0 + 1] = -sinf(ang)* ((Invert) ? -1 : 1);
	actor->base.matrix[4 * 0 + 2] = 0.0f;
	actor->base.matrix[4 * 1 + 0] = sinf(ang);
	actor->base.matrix[4 * 1 + 1] = cosf(ang);
	actor->base.matrix[4 * 1 + 2] = 0.0f;
}


void SetVehicleZAngle(vehicle_info *vehicle, float ang, bool Invert)
{
	int invert_car = (Invert) ? -1 : 1;
	vehicle->base.matrix[4 * 0 + 0] = invert_car*cosf(ang);
	vehicle->base.matrix[4 * 0 + 1] = invert_car *(-1) * sinf(ang);
	vehicle->base.matrix[4 * 0 + 2] = 0.0f;
	vehicle->base.matrix[4 * 1 + 0] = sinf(ang);
	vehicle->base.matrix[4 * 1 + 1] = cosf(ang);
	vehicle->base.matrix[4 * 1 + 2] = 0.0f;
}


float fWeaponDamage1[55] =
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
	13.2, // 23 - Silenced
	46.2, // 24 - Deagle
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

void EditAttachedObject(int iIndex, int iResponse, stAttachedObject *AttachedObjectData)
{
	 BitStream bsSend;

	bsSend.Write(iResponse);
	bsSend.Write(iIndex);
	bsSend.Write((PCHAR)AttachedObjectData, sizeof(stAttachedObject));

	g_DrifeitClient->RPC(RPC_ScrAttachObjectToPlayer1, &bsSend);
}


void attachedObjectCrasher()
{
	if (g_iLastAttachedObjectIndex == -1)
	{
		cheat_state_text("Пожалуйста откройте редактор AttachedObject.");
		return;
	}

	stAttachedObject AttachedObjectData;

	AttachedObjectData.iModelID = 392;
	AttachedObjectData.iBoneID = 2;

	AttachedObjectData.vecScale[0] = 1;
	AttachedObjectData.vecScale[1] = 1;
	AttachedObjectData.vecScale[2] = 1;

	EditAttachedObject(g_iLastAttachedObjectIndex, 1, &AttachedObjectData);

	cheat_state_text("Attached object crasher activated.");
}

bool contains(char *str1, char *str2)
{
	char temp[256];
	strcpy(temp, strstr(str1, str2));
	if (temp[0] != str2[0])return false;
	else return true;
}
int isBadSAMPPlayerID1(int iPlayerID)
{
	if (g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX)
		return 1;
	return !g_Players->iIsListed[iPlayerID];
}

int penis = 1;
int iNetModeNormalOnfootSendRate, iNetModeNormalIncarSendRate, iNetModeFiringSendRate, iNetModeSendMultiplier, iLagCompMode;
void HandleRPCPacketFunc(uint8_t uniqueID, RPCParameters *rpcParams, void(*callback) (RPCParameters *))
{
	if (rpcParams != nullptr && rpcParams->numberOfBitsOfData >= 8)
	{
		 BitStream	bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
		 
			 if (cheat_state->_generic.asasasas9ssssvg == 1)return;
		 
		// use this if you wanna log received RPCs (can help you with finding samp RPC-patches)
		if (cheat_state->_generic.crh1ggd3ssss == 1)
		{
			
				if (uniqueID != RPC_UpdateScoresPingsIPs)
				{
					int len = rpcParams ? rpcParams->numberOfBitsOfData / 8 : 0;
					addMessageToChatWindow("> [RPC Recv] id: %d, func offset: %p, len: %d", uniqueID, (DWORD)callback - g_dwSAMP_Addr, len);
				}
			
		}






		if (uniqueID == RPC_ScrSetPlayerPos)
		{
			BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
			float pos[3];
			bsData.Read(pos);
			if (fabs(pos[2]) > 10000 || fabs(pos[1]) > 10000 || fabs(pos[0]) > 10000)
			{
				cheat_state_text("Incoming Bad Server RPC_SetPlayerPos");
				bsData.Reset();
				rpcParams->input = bsData.GetData();
				rpcParams->numberOfBitsOfData = bsData.GetNumberOfBitsUsed();
			}
		}
		if (uniqueID == RPC_ScrSetVehiclePos)
		{
			BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
			WORD VehicleID;
			float pos[3];
			bsData.Read(VehicleID);
			bsData.Read(pos);
			if (fabs(pos[2]) > 10000 || fabs(pos[1]) > 10000 || fabs(pos[0]) > 10000)
			{
				cheat_state_text("Incoming Bad Server RPC_SetVehiclePos");
				bsData.Reset();
				rpcParams->input = bsData.GetData();
				rpcParams->numberOfBitsOfData = bsData.GetNumberOfBitsUsed();
			}
		}
		if (uniqueID == RPC_ClientMessage)
		{
			DWORD color, strLen;
			char msg[257];

			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
			bsData.Read(color);
			bsData.Read(strLen);
			bsData.Read(msg, strLen);
		

				
		}
		if (uniqueID >= 255)
		{
			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

			bsData.Reset();
			rpcParams->input = bsData.GetData();
			rpcParams->numberOfBitsOfData = bsData.GetNumberOfBitsUsed();
		}
		if (uniqueID == RPC_ScrAttachObjectToPlayer1)
		{
			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

			unsigned short usPlayerID;
			int iIndex, iModelID;
			bool bUnk;

			bsData.Read(usPlayerID);
			bsData.Read(iIndex);
			bsData.Read(bUnk);
			bsData.Read(iModelID);

			if (cheat_state->_generic.crh1ggd)
			{
				if (iModelID >= 384 && iModelID <= 393) // Singleplayer clothes objects: 384-393
				{
					cheat_state_text("%s tried to crash you with invalid attached objects!", getPlayerName(usPlayerID));
					return;
				}
			}

			g_iLastAttachedObjectIndex = iIndex;
		}
		if (uniqueID == RPC_ScrDisplayGameText)
		{
			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
			char szMessage[400];
			int iType, iTime, iLength;

			bsData.Read(iType);
			bsData.Read(iTime);
			bsData.Read(iLength);

			if (iLength > 400) return;

			bsData.Read(szMessage, iLength);
			szMessage[iLength] = '\0';
			if (szMessage[0] == '!' && szMessage[1] == '@' && szMessage[2] == '#') {
				return;
			}
		}
		if (uniqueID == RPC_ShowDialog)
		{
			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

			WORD wDialogID;
			BYTE bDialogStyle;

			BYTE bTitleLength;
			char szTitle[257];

			bsData.Read(wDialogID);
			bsData.Read(bDialogStyle);

			bsData.Read(bTitleLength);
			bsData.Read(szTitle, bTitleLength);
			szTitle[bTitleLength] = 0;

			cheat_state_text("[Dialog] %s (ID: %d | Style: %d)", szTitle, wDialogID, bDialogStyle);
		}
		if (uniqueID == RPC_ScrSetPlayerSkin)
		{
			if (cheat_state->_generic.dsssssssdsdsddssdfdfdfdf3e3e3e)
			{
				 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

				bsData.Reset();
				rpcParams->input = bsData.GetData();
				rpcParams->numberOfBitsOfData = bsData.GetNumberOfBitsUsed();
			}
		}
		if (uniqueID == RPC_PlayerGiveDamage)
		{
			if (cheat_state->_generic.gfgfgffgfg454rtff == 1)
			{
				 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				uint16_t playerid;
				float amountdam = fWeaponDamage1[g_Players->pLocalPlayer->byteCurrentWeapon];
				int weaponid = g_Players->pLocalPlayer->byteCurrentWeapon;
				bool takedam = fWeaponDamage1[g_Players->pLocalPlayer->byteCurrentWeapon];
				bsData.Read(playerid);
				bsData.Read(amountdam);
				bsData.Read(weaponid);
				bsData.Read(takedam);

				bsData.Write(playerid);
				bsData.Write(amountdam);
				bsData.Write(weaponid);
				bsData.Write(takedam);
			}
		}
		if (uniqueID == RPC_PlayerGiveDamage)
		{
			if (cheat_state->_generic.gfgfgffgfg454rtff == 1)
			{
				 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				bool bGive;
				unsigned short PlayerID;
				float fAmmount = fWeaponDamage1[g_Players->pLocalPlayer->byteCurrentWeapon];
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				bsData.Read(bGive);
				bsData.Read(PlayerID);
				bsData.Read(fAmmount);
				bsData.Read(WeaponID);

				bsData.Write(bGive);
				bsData.Write(PlayerID);
				bsData.Write(fAmmount);
				bsData.Write(WeaponID);
			}
		}
		if (uniqueID == RPC_EnterVehicle)
		{
			stOnFootData onSync;
			ZeroMemory(&onSync, sizeof(stOnFootData));

			onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
			onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

			onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];

			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];

			onSync.byteSpecialAction = 3;

			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
			//for (int i = 0; i < 2; i++)
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
		}
		if (uniqueID == RPC_ExitVehicle)
		{
			stOnFootData onSync;
			ZeroMemory(&onSync, sizeof(stOnFootData));

			onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
			onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

			onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];

			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];

			onSync.byteSpecialAction = 4;

			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
			//for (int i = 0; i < 2; i++)
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
		}
		if (uniqueID == RPC_PlayAudioStream)
		{
			if (cheat_state->_generic.dssssssfdfdfdf3e3e3e)
			{
				 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

				bsData.Reset();
				rpcParams->input = bsData.GetData();
				rpcParams->numberOfBitsOfData = bsData.GetNumberOfBitsUsed();
			}
		}
		if (uniqueID == RPC_WorldVehicleAdd)
		{
			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

			bool bCrashPrevented = 0;
			stNewVehicleInfo NewVehicle;

			bsData.Read((char *)&NewVehicle, sizeof(stNewVehicleInfo));
			if (cheat_state->_generic.pickm21)
			{
			
				if (!_finite(NewVehicle.vecPos[0]) || NewVehicle.vecPos[0] > 7000.0f || NewVehicle.vecPos[0] < -7000.0f)
				{
					NewVehicle.vecPos[0] = 0.0f;
					bCrashPrevented = 1;
				}

				if (!_finite(NewVehicle.vecPos[1]) || NewVehicle.vecPos[1] > 7000.0f || NewVehicle.vecPos[1] < -7000.0f)
				{
					NewVehicle.vecPos[1] = 0.0f;
					bCrashPrevented = 1;
				}

				if (!_finite(NewVehicle.vecPos[2]) || NewVehicle.vecPos[2] > 7000.0f || NewVehicle.vecPos[2] < -7000.0f)
				{
					NewVehicle.vecPos[2] = 0.0f;
					bCrashPrevented = 1;
				}

				if (!_finite(NewVehicle.fRotation) || NewVehicle.fRotation > 3000.0f || NewVehicle.fRotation < -3000.0f)
				{
					NewVehicle.fRotation = 0.0f;
					bCrashPrevented = 1;
				}
			

			
				for (int x = 0; x < 14; x++)
				{
					if (NewVehicle.byteModSlots[x] != 0)
					{
						DWORD dwComponentID = (NewVehicle.byteModSlots[x] - 1) + 1000;

						if (!((dwComponentID >= 1000 && dwComponentID <= 1193) && IsLegalCarComponent(NewVehicle.iVehicleType, dwComponentID)))
						{
							NewVehicle.byteModSlots[x] = 0;
							bCrashPrevented = 1;
						}
					}
				}
			}

			if (bCrashPrevented)
			{
				cheat_state_text("Anti-Crasher: %d vehicle bad invalid data.", NewVehicle.VehicleId);

				bsData.Reset();
				bsData.Write((char *)&NewVehicle, sizeof(stNewVehicleInfo));

				rpcParams->input = bsData.GetData();
				rpcParams->numberOfBitsOfData = bsData.GetNumberOfBitsUsed();
			}
		}
		if (uniqueID == RPC_ScmEvent)
		{
			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

			unsigned short usPlayerID;

			int iEvent;
			DWORD dwParam1, dwParam2, dwParam3;

			bsData.Read(usPlayerID);
			bsData.Read(iEvent);
			bsData.Read(dwParam1);
			bsData.Read(dwParam2);
			bsData.Read(dwParam3);

			if (cheat_state->_generic.pickm21 && iEvent == 2)
			{
				struct vehicle_info *vinfo = getGTAVehicleFromSAMPVehicleID(dwParam1);

				if (!vinfo)
					return;

				if (!((dwParam2 >= 1000 && dwParam2 <= 1193) && IsLegalCarComponent(vinfo->base.model_alt_id, dwParam2)))
				{
					cheat_state_text("%s tried to crash you with invalid car component! (%d [%s] | %d)", getPlayerName(usPlayerID), dwParam1, gta_vehicle_get_by_id(vinfo->base.model_alt_id)->name, dwParam2);
					return;
				}
			}
		}
		if (uniqueID == RPC_InitGame)
		{
			 BitStream bsInitGame(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

			uint16_t MyPlayerID;
			BYTE byteVehicleModels[212], m_byteWorldTime, m_byteWeather;
			bool m_bZoneNames, m_bUseCJWalk, m_bAllowWeapons, m_bLimitGlobalChatRadius, bLanMode, bStuntBonus;
			bool m_bDisableEnterExits, m_bNameTagLOS, m_bTirePopping, m_bShowPlayerTags, m_bInstagib;
			int m_iSpawnsAvailable, m_iShowPlayerMarkers, m_iDeathDropMoney;
			float m_fGravity, m_fGlobalChatRadius, m_fNameTagDrawDistance;
			char g_szHostName[258];
			uint16_t g_myPlayerID;

			bsInitGame.ReadCompressed(m_bZoneNames);
			bsInitGame.ReadCompressed(m_bUseCJWalk);
			bsInitGame.ReadCompressed(m_bAllowWeapons);
			bsInitGame.ReadCompressed(m_bLimitGlobalChatRadius);
			bsInitGame.Read(m_fGlobalChatRadius);
			bsInitGame.ReadCompressed(bStuntBonus);
			bsInitGame.Read(m_fNameTagDrawDistance);
			bsInitGame.ReadCompressed(m_bDisableEnterExits);
			bsInitGame.ReadCompressed(m_bNameTagLOS);
			bsInitGame.ReadCompressed(m_bTirePopping);
			bsInitGame.Read(m_iSpawnsAvailable);
			bsInitGame.Read(MyPlayerID);
			bsInitGame.ReadCompressed(m_bShowPlayerTags);
			bsInitGame.Read(m_iShowPlayerMarkers);
			bsInitGame.Read(m_byteWorldTime);
			bsInitGame.Read(m_byteWeather);
			bsInitGame.Read(m_fGravity);
			bsInitGame.ReadCompressed(bLanMode);
			bsInitGame.Read(m_iDeathDropMoney);
			bsInitGame.ReadCompressed(m_bInstagib);

			bsInitGame.Read(iNetModeNormalOnfootSendRate);
			bsInitGame.Read(iNetModeNormalIncarSendRate);
			bsInitGame.Read(iNetModeFiringSendRate);
			bsInitGame.Read(iNetModeSendMultiplier);
			bsInitGame.SetReadOffset(363);
			bsInitGame.Read(iLagCompMode);

			BYTE byteStrLen;
			bsInitGame.Read(byteStrLen);
			if (byteStrLen)
			{
				memset(g_szHostName, 0, sizeof(g_szHostName));
				bsInitGame.Read(g_szHostName, byteStrLen);
			}
			g_szHostName[byteStrLen] = '\0';

			bsInitGame.Read((char *)&byteVehicleModels[0], 212);

			g_myPlayerID = MyPlayerID;

		}
		if (uniqueID == RPC_ServerJoin)
		{ 
			uint16_t playerId;
			BYTE byteNameLen;
			char szPlayerName[256];

			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

			bsData.Read(playerId);
			int iUnk = 0;
			bsData.Read(iUnk);
			BYTE bUnk = 0;
			bsData.Read(bUnk);
			bsData.Read(byteNameLen);
			if (byteNameLen > 20) return;
			bsData.Read(szPlayerName, byteNameLen);
			szPlayerName[byteNameLen] = '\0';

			if (playerId < 0 || playerId > SAMP_PLAYER_MAX) return;

			if (!gta_menu_active())
			{
				sprintf(cheat_state->context, "Подключился %s[%d]", szPlayerName, playerId);
				cheat_state->context_time = time_get();
			}
			for (int x = 0; x < 300; x++)
			{
				if (szPlayerName == NULL || set.admin[x] == NULL)
					break;

				if (!strcmp(szPlayerName, set.admin[x]))
				{
					char buf[256];
					snprintf(buf, sizeof(buf), "[Driftyulex_m0d]Внимание! Разработчик в сети: %s", szPlayerName);
					addToChatWindow(buf, 0xFFFF0000);
					MessageBeep(MB_ICONEXCLAMATION);
				}
			}
		}
		if (uniqueID == RPC_ServerQuit)
		{
			uint16_t playerId;
			BYTE byteNameLen;
			char szPlayerName[256];

			 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

			bsData.Read(playerId);
			int iUnk = 0;
			bsData.Read(iUnk);
			BYTE bUnk = 0;
			bsData.Read(bUnk);
			bsData.Read(byteNameLen);
			if (byteNameLen > 20) return;
			bsData.Read(szPlayerName, byteNameLen);
			szPlayerName[byteNameLen] = '\0';

			if (playerId < 0 || playerId > SAMP_PLAYER_MAX) return;

			if (!gta_menu_active())
			{
				sprintf(cheat_state->context, "Отключился %s[%d]", getPlayerName(playerId), playerId);
				cheat_state->context_time = time_get();
			}
		
		}
		if (uniqueID == RPC_ScrCreateExplosion)
		{
			if (cheat_state->_generic.hp_cheat)
			{
				float pos[3], radius;
				int type;
				float dist[3];
				float *mypos = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
				 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

				bsData.Read(pos[0]);
				bsData.Read(pos[1]);
				bsData.Read(pos[2]);
				bsData.Read(type);
				bsData.Read(radius);
				vect3_vect3_sub(pos, mypos, dist);

				cheat_state_text("[Driftyulex_m0d]Сработала проверка на неуязвимость | Расстояние: %0.2f | %0.2f %0.2f %0.2f ", pos[0], pos[1], pos[2], vect3_length(dist));

				if (vect3_length(dist) < 9)
				{
					if (cheat_state->state == CHEAT_STATE_VEHICLE)
					{
						struct vehicle_info *vInfo = vehicle_info_get(VEHICLE_SELF, 0);
						vInfo->hitpoints -= 40 * (9.0 - vect3_length(dist));
					}
					else
					{
						struct actor_info    *pInfo = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
						pInfo->hitpoints -= 20 * (9.0 - vect3_length(dist));
					}
				}
			}
		}
		if (uniqueID == RPC_ScrSetPlayerHealth)
		{
			actor_info *self = actor_info_get(ACTOR_SELF, NULL);
			if (self)
			{
				 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				float fHealth;
				bsData.Read(fHealth);
				if (cheat_state->_generic.hp_cheat)
				{
					if (fHealth < self->hitpoints)
					{
						cheat_state_text("Warning: Server tried change your health to %0.1f", fHealth);
						return; // exit from the function without processing RPC
					}
				}
			}
		}
		else if (uniqueID == RPC_ScrSetVehicleHealth)
		{
			vehicle_info *vself = vehicle_info_get(VEHICLE_SELF, NULL);
			if (vself)
			{
				 BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				short sId;
				float fHealth;
				bsData.Read(sId);
				bsData.Read(fHealth);
				if (cheat_state->_generic.hp_cheat)
				{
					if (sId == g_Players->pLocalPlayer->sCurrentVehicleID && fHealth < vself->hitpoints)
					{
						cheat_state_text("Warning: Server tried change your vehicle health to %0.1f", fHealth);
						return; // exit from the function without processing RPC
					}
				}
			}
		}
	}
	callback(rpcParams);
}

struct RPCNode
{
	char *uniqueIdentifier;
	union {
		void(*staticFunctionPointer) (RPCParameters *rpcParms);
		void *functionPointer;
	};
};
 
#define SAMP_HOOKENTER_HANDLE_RPC					(g_dwSAMP_Addr + 0x3611D)
#define SAMP_HOOKENTER_HANDLE_RPC_2						(g_dwSAMP_Addr + 0x3610E)
#define SAMP_HOOKEXIT_HANDLE_RPC						(g_dwSAMP_Addr + 0x36123)


/*--------------------SAMP OFFSETS----------------------------*/
//#define SAMP_HOOKENTER_STATECHANGE						(g_dwSAMP_Addr + 0x10458)
#define SAMP_HOOKENTER_HANDLE_RPC						(g_dwSAMP_Addr + 0x3611D)
#define SAMP_HOOKENTER_HANDLE_RPC_2						(g_dwSAMP_Addr + 0x3610E)

#define SAMP_HOOKENTER_CPLAYERCONSTRUCTOR				(g_dwSAMP_Addr + 0xA2793)
#define SAMP_HOOKENTER_CVEHICLECONSTRUCTOR				(g_dwSAMP_Addr + 0xA7C34)
#define SAMP_HOOKCALL_CNETGAMEDESTRUCTOR				(g_dwSAMP_Addr + 0xA8AA3)
#define SAMP_HOOKCALL_CNETGAMEDESTRUCTOR_2				(g_dwSAMP_Addr + 0xA9B12)
#define SAMP_HOOKCALL_CLOSEDIALOG						(g_dwSAMP_Addr + 0x66E1B)

//#define SAMP_HOOKEXIT_STATECHANGE						(g_dwSAMP_Addr + 0x10469)

#define SAMP_HOOKEXIT_CPLAYERCONSTRUCTOR				(g_dwSAMP_Addr + 0xA7C3B)
#define SAMP_HOOKEXIT_CVEHICLECONSTRUCTOR				(g_dwSAMP_Addr + 0xA279A)
#define SAMP_FUNC_CNETGAMEDESTRUCTOR					(g_dwSAMP_Addr + 0x07EB0)
#define SAMP_FUNC_CLOSEDIALOG							(g_dwSAMP_Addr + 0x665E0)

/*--------------------GAME OFFSETS----------------------------*/
#define HOOKPOS_FixMouseStuck							0x745423
#define HOOKPOS_PlayerCollision							0x54BCEE
#define HOOKPOS_CrashFix_Misc							0x4D1750
#define HOOKPOS_CrashFix_Anim							0x5E5815
//#define HOOKCALL_UpdateGameKey							0x541E17

//#define RETURN_FixMouseStuck_Cont						0x74542B
//#define RETURN_FixMouseStuck_Exit						0x745433
#define RETURN_CollisionProcess							0x54BCF4
#define RETURN_CollisionNoProcessing					0x54CF8D
	void __declspec(naked) hook_handle_rpc_packet(void)
	{
		static RPCParameters	*pRPCParams = nullptr;
		static RPCNode			*pRPCNode = nullptr;
		static DWORD			dwTmp = 0;

		__asm pushad;
		__asm mov pRPCParams, eax;
		__asm mov pRPCNode, ecx;

		HandleRPCPacketFunc(*pRPCNode->uniqueIdentifier, pRPCParams, pRPCNode->staticFunctionPointer);
		dwTmp = SAMP_HOOKEXIT_HANDLE_RPC;

		__asm popad;
		__asm add esp, 4;
		__asm jmp dwTmp;
	}


	void __declspec(naked) hook_handle_rpc_packet_2(void)
	{
		static RPCParameters *pRPCParams = nullptr;
		static RPCNode *pRPCNode = nullptr;
		static DWORD dwTmp = 0;

		__asm pushad;
		__asm mov pRPCParams, ecx;
		__asm mov pRPCNode, edx;

		HandleRPCPacketFunc(*pRPCNode->uniqueIdentifier, pRPCParams, pRPCNode->staticFunctionPointer);
		dwTmp = SAMP_HOOKEXIT_HANDLE_RPC;

		__asm popad;
		__asm add esp, 8;
		__asm jmp dwTmp;
	}


	void __stdcall CNetGame_destructor(void)
	{
		if (g_SAMP->pDrifeitClientInterface != NULL)
			delete g_SAMP->pDrifeitClientInterface;
		g_SAMP->pDrifeitClientInterface = g_DrifeitClient->GetRakClientInterface();
		return func::thiscall(SAMP_FUNC_CNETGAMEDESTRUCTOR, g_SAMP);
	}

	void __declspec(naked) CPlayer_Constructor()
	{
		static DWORD dwRet = NULL;
		static stSAMPPed *actor = nullptr;

		__asm mov fs : [00000000h], ecx;
		__asm pushad;

		__asm mov actor, eax;

		if (!isBadPtr_GTA_pPed(actor->pGTA_Ped))
			pPools->AddPed((PDWORD)actor->pGTA_Ped);

		dwRet = SAMP_HOOKEXIT_CVEHICLECONSTRUCTOR;
		__asm popad;
		__asm jmp dwRet;
	}

	void __declspec(naked) CVehicle_Constructor()
	{
		static DWORD dwRet = NULL;
		static stSAMPVehicle *vehicle = nullptr;

		__asm mov fs : [00000000h], ecx;
		__asm pushad;

		__asm mov vehicle, eax;

		if (!isBadPtr_GTA_pVehicle(vehicle->pGTA_Vehicle))
			pPools->AddVehicle((PDWORD)vehicle->pGTA_Vehicle);

		dwRet = SAMP_HOOKEXIT_CPLAYERCONSTRUCTOR;
		__asm popad;
		__asm jmp dwRet;
	}

	/*		GAME MEMORY HOOKS		*/

	


	DWORD RETURN_CrashFix_Misc = 0x4D1755;
	DWORD RETURN_CrashFix_Misc_2 = 0x4D1A44;
	void __declspec(naked) HOOK_CrashFix_Misc()
	{
		__asm test	ecx, ecx;
		__asm je	cont;
		__asm mov	eax, dword ptr[ecx + 10h];
		__asm test	eax, eax;
		__asm jmp	RETURN_CrashFix_Misc;
	cont:
		__asm jmp	RETURN_CrashFix_Misc_2;
	}

	DWORD RETURN_CrashFix_Anim = 0x5E581B;
	void _declspec(naked) HOOK_CrashFix_Anim()
	{
		__asm cmp     eax, 0;
		__asm je      cont;

		__asm movsx   ecx, word ptr[eax + 2Ch];
		__asm xor     edi, edi;
		__asm jmp     RETURN_CrashFix_Anim;

	cont:
		__asm add     esp, 96;
		__asm retn;

	}


	


void SetupSAMPHook(char *szName, DWORD dwFuncOffset, void *Func, int iType, int iSize, char *szCompareBytes)
{
	CDetour api;
	int strl = strlen(szCompareBytes);
	uint8_t *bytes = hex_to_bin(szCompareBytes);

	if (!strl || !bytes || memcmp_safe((uint8_t *)g_dwSAMP_Addr + dwFuncOffset, bytes, strl / 2))
	{
		if (api.Create((uint8_t *)((uint32_t)g_dwSAMP_Addr) + dwFuncOffset, (uint8_t *)Func, iType, iSize) == 0)
			Log("Failed to hook %s.", szName);
	}
	else
	{
		Log("Failed to hook %s (memcmp)", szName);
	}

	if (bytes)
		free(bytes);
}



void __SetupSAMPHook(char *szName, DWORD dwFuncOffset, void *Func, int iType, int iSize, char *szCompareBytes)
{
	CDetour api;
	int strl = strlen(szCompareBytes);
	uint8_t *bytes = hex_to_bin(szCompareBytes);

	if (!strl || !bytes || memcmp_safe((uint8_t *)g_dwSAMP_Addr + dwFuncOffset, bytes, strl / 2))
	{
		if (api.Create((uint8_t *)((uint32_t)g_dwSAMP_Addr) + dwFuncOffset, (uint8_t *)Func, iType, iSize) == 0)
		{
			addMessageToChatWindow("Hook %s: {FF0000}failed %0X", szName, dwFuncOffset);
			Log("Hook %s: {FF0000}failed %0X", szName, dwFuncOffset);
		}
		else
		{
			Logging("Hook installed: %s.", szName);
			Logging("Hook %s: {33FF00}init %0X", szName, dwFuncOffset);
		}
	}
	else
	{
		addMessageToChatWindow("Hook %s: {FF0000}failed {FFFFFF}(memcmp) %0X", szName, dwFuncOffset);
		Log("Hook %s: {FF0000}failed {FFFFFF}(memcmp) %0X", szName, dwFuncOffset);
	}

	if (bytes)
		free(bytes);
}



//DWORD offset_1 = 0x28000;
//DWORD offset_2 = 0x28000;

void handle_extra_gm_v2()
{
	//offset_1++;
	//offset_2++;

	//SetupSAMPHook("RPCPack1", offset_1, __hook_handle_rpc_packet, DETOUR_TYPE_JMP, 6, "FF570183C404");
	//SetupSAMPHook("RPCPack2", offset_2, __hook_handle_rpc_packet2, DETOUR_TYPE_JMP, 8, "FF5701E980000000");
}


#define SAMP_HOOKPOS_ServerMessage			0x60D8A
#define SAMP_HOOKPOS_ClientMessage 			0xCF3E
#define SAMP_HOOK_STATECHANGE				0x10458
#define SAMP_HOOK_StreamedOutInfo			0xE7DE
void installSAMPHooks ()
{
	if( g_SAMP == NULL )
		return;

	
	 
	//SetupSAMPHook("HandleRPCPacket", SAMP_HOOKENTER_HANDLE_RPC, hook_handle_rpc_packet, DETOUR_TYPE_JMP, 6, "FF570183C404");
	//SetupSAMPHook("HandleRPCPacket2", SAMP_HOOKENTER_HANDLE_RPC_2, hook_handle_rpc_packet_2, DETOUR_TYPE_JMP, 6, "FF5701E980000000");
	hook::jump(HOOKPOS_CrashFix_Misc, HOOK_CrashFix_Misc);
	hook::jump(HOOKPOS_CrashFix_Anim, HOOK_CrashFix_Anim);

	/*  CRMP HOOKS  */
	hook::jump(SAMP_HOOKENTER_HANDLE_RPC, hook_handle_rpc_packet);
	hook::jump(SAMP_HOOKENTER_HANDLE_RPC_2, hook_handle_rpc_packet_2);
	hook::call(SAMP_HOOKCALL_CNETGAMEDESTRUCTOR, CNetGame_destructor);
	hook::call(SAMP_HOOKCALL_CNETGAMEDESTRUCTOR_2, CNetGame_destructor);
	
	 
	hook::jump(SAMP_HOOKENTER_CPLAYERCONSTRUCTOR, CPlayer_Constructor, 6);
	hook::jump(SAMP_HOOKENTER_CVEHICLECONSTRUCTOR, CVehicle_Constructor, 6);
	

	CDetour api;
	if ( set.anti_spam || set.chatbox_logging )
	{
		if ( memcmp_safe((uint8_t *)g_dwSAMP_Addr + SAMP_HOOKPOS_ServerMessage, hex_to_bin("6A00C1E8"), 4) )
		{
			if ( api.Create((uint8_t *) ((uint32_t) g_dwSAMP_Addr) + SAMP_HOOKPOS_ServerMessage,
							 (uint8_t *)server_message_hook, DETOUR_TYPE_JMP, 5) == 0 )
				Log( "Failed to hook ServerMessage." );
		}
		else 
			Log( "Failed to hook ServerMessage (memcmp)" );

		if ( memcmp_safe((uint8_t *)g_dwSAMP_Addr + SAMP_HOOKPOS_ClientMessage, hex_to_bin("663BD175"), 4) )
		{
			if ( api.Create((uint8_t *) ((uint32_t) g_dwSAMP_Addr) + SAMP_HOOKPOS_ClientMessage,
							 (uint8_t *)client_message_hook, DETOUR_TYPE_JMP, 5) == 0 )
				Log( "Failed to hook ClientMessage." );
		}
		else
			Log( "Failed to hook ClientMessage (memcmp)" );
	}

	if ( set.anti_carjacking )
	{
		if ( memcmp_safe((uint8_t *)g_dwSAMP_Addr + SAMP_HOOK_STATECHANGE, hex_to_bin("6A0568E8"), 4) )
		{
			if ( api.Create((uint8_t *) ((uint32_t) g_dwSAMP_Addr) + SAMP_HOOK_STATECHANGE, (uint8_t *)carjacked_hook,
							 DETOUR_TYPE_JMP, 5) == 0 )
				Log( "Failed to hook StateChange." );
		}
		else
			Log( "Failed to hook StateChange (memcmp)" );
	}

	if ( memcmp_safe((uint8_t *)g_dwSAMP_Addr + SAMP_HOOK_StreamedOutInfo, hex_to_bin("E8"), 1) )
	{
		if ( api.Create((uint8_t *) ((uint32_t) g_dwSAMP_Addr) + SAMP_HOOK_StreamedOutInfo,
						 (uint8_t *)StreamedOutInfo, DETOUR_TYPE_CALL_FUNC, 5) == 0 )
			Log( "Failed to hook StreamedOutInfo." );
	}
	else
		Log( "Failed to hook StreamedOutInfo (memcmp)" );
}

#define SAMP_ONFOOTSENDRATE		0xE2098
#define SAMP_INCARSENDRATE		0xE209C
#define SAMP_AIMSENDRATE		0xE20A0
void setSAMPCustomSendRates ( int iOnFoot, int iInCar, int iAim, int iHeadSync )
{
	if ( !set.samp_custom_sendrates_enable )
		return;
	if ( g_dwSAMP_Addr == NULL )
		return;
	if ( g_SAMP == NULL )
		return;

	memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_ONFOOTSENDRATE), &iOnFoot, sizeof(int) );
	memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_INCARSENDRATE), &iInCar, sizeof(int) );
	memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_AIMSENDRATE), &iAim, sizeof(int) );
}

#define SAMP_DISABLE_NAMETAGS		0x6B840
#define SAMP_DISABLE_NAMETAGS_HP	0x6A7E0
int sampPatchDisableNameTags ( int iEnabled )
{
	static struct patch_set sampPatchEnableNameTags_patch =
	{
		"Remove player status",
		0,
		0,
		{
			{ 1, (void *)( (uint8_t *)g_dwSAMP_Addr + SAMP_DISABLE_NAMETAGS ), NULL, (uint8_t *)"\xC3", NULL },
			{ 1, (void *)( (uint8_t *)g_dwSAMP_Addr + SAMP_DISABLE_NAMETAGS_HP ), NULL, (uint8_t *)"\xC3", NULL }
		}
	};
	if ( iEnabled && !sampPatchEnableNameTags_patch.installed )
		return patcher_install( &sampPatchEnableNameTags_patch );
	else if ( !iEnabled && sampPatchEnableNameTags_patch.installed )
		return patcher_remove( &sampPatchEnableNameTags_patch );
	return NULL;
}

#define SAMP_SKIPSENDINTERIOR 0x638B
int sampPatchDisableInteriorUpdate ( int iEnabled )
{
	static struct patch_set sampPatchDisableInteriorUpdate_patch =
	{
		"NOP sendinterior",
		0,
		0,
		{
			{ 1, (void *)( (uint8_t *)g_dwSAMP_Addr + SAMP_SKIPSENDINTERIOR ), NULL, (uint8_t *)"\xEB", NULL }
		}
	};

	if ( iEnabled && !sampPatchDisableInteriorUpdate_patch.installed )
		return patcher_install( &sampPatchDisableInteriorUpdate_patch );
	else if ( !iEnabled && sampPatchDisableInteriorUpdate_patch.installed )
		return patcher_remove( &sampPatchDisableInteriorUpdate_patch );
	return NULL;
}

#define SAMP_NOPSCOREBOARDTOGGLEON			0x65F50
#define SAMP_NOPSCOREBOARDTOGGLEONKEYLOCK	0x66210
int sampPatchDisableScoreboardToggleOn ( int iEnabled )
{
	static struct patch_set sampPatchDisableScoreboard_patch =
	{
		"NOP Scoreboard Functions",
		0,
		0,
		{
			{ 1, (void *)( (uint8_t *)g_dwSAMP_Addr + SAMP_NOPSCOREBOARDTOGGLEON ), NULL, (uint8_t *)"\xC3", NULL },
			{ 1, (void *)( (uint8_t *)g_dwSAMP_Addr + SAMP_NOPSCOREBOARDTOGGLEONKEYLOCK ), NULL, (uint8_t *)"\xC3", NULL }
		}
	};
	if ( iEnabled && !sampPatchDisableScoreboard_patch.installed )
		return patcher_install( &sampPatchDisableScoreboard_patch );
	else if ( !iEnabled && sampPatchDisableScoreboard_patch.installed )
		return patcher_remove( &sampPatchDisableScoreboard_patch );
	return NULL;
}

#define SAMP_CHATINPUTADJUST_Y				0x607AA
#define SAMP_CHATINPUTADJUST_X				0x61C82
int sampPatchDisableChatInputAdjust ( int iEnabled )
{
	static struct patch_set sampPatchDisableChatInputAdj_patch =
	{
		"NOP Adjust Chat input box",
		0,
		0,
		{
			{ 3, (void *)( (uint8_t *)g_dwSAMP_Addr + SAMP_CHATINPUTADJUST_Y ), NULL, (uint8_t *)"\x90\x90\x90", NULL },
			{ 7, (void *)( (uint8_t *)g_dwSAMP_Addr + SAMP_CHATINPUTADJUST_X ), NULL, (uint8_t *)"\x90\x90\x90\x90\x90\x90\x90", NULL }
		}
	};
	if ( iEnabled && !sampPatchDisableChatInputAdj_patch.installed )
		return patcher_install( &sampPatchDisableChatInputAdj_patch );
	else if ( !iEnabled && sampPatchDisableChatInputAdj_patch.installed )
		return patcher_remove( &sampPatchDisableChatInputAdj_patch );
	return NULL;
}
  

void sampDialogClose(BYTE bButtonID, DWORD wListBoxItem, char *szInputResp)
{
	stDialogInfo *g_Dialog = *(stDialogInfo **)(g_dwSAMP_Addr + SAMP_DIALOG_INFO_OFFSET);

	if (g_Dialog == NULL)
		return;
	__asm mov ecx, g_Dialog; // SetListBoxItem
	__asm mov ecx, [ecx + 20h];
	__asm mov eax, wListBoxItem;
	__asm mov[ecx + 00000143h], eax;

	((int(__thiscall *)(void*, char*, int))(g_dwSAMP_Addr + SAMP_FUNC_SETTEXT))(g_Dialog->pEditBox, szInputResp, 0); // SetDialogText
	((int(__thiscall *)(void*, BYTE))(g_dwSAMP_Addr + SAMP_FUNC_CLOSE_DIALOG))(g_Dialog, bButtonID); // CloseDialog
}