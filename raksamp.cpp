#include "main.h"



DrifeitClient *g_DrifeitClient = NULL;

DrifeitClient::DrifeitClient(void *pDrifeitClientInterface)
{
	pDrifeitClient = (RakClientInterface *)pDrifeitClientInterface;
}

bool DrifeitClient::RPC(int rpcId,  BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (!pDrifeitClient)
		return false;
	
	return pDrifeitClient->RPC(&rpcId, bitStream, priority, reliability, orderingChannel, shiftTimestamp);
}

bool DrifeitClient::Send( BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	if (!pDrifeitClient)
		return false;

	return pDrifeitClient->Send(bitStream, priority, reliability, orderingChannel);
}



bool ValidPlayerx(int PlayerID)
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

bool ValidVehiclex(int VehicleID)
{
	if ( g_Vehicles->iIsListed[VehicleID] != 1 )
		return 0;

	if ( g_Vehicles->pSAMP_Vehicle[VehicleID] == NULL )
		return 0;

	if ( g_Vehicles->pSAMP_Vehicle[VehicleID]->pGTA_Vehicle == NULL )
		return 0;

	return 1;
}


void UpdatePlayerScoresAndPings(int iWait, int iMS)
{
	static DWORD dwLastUpdateTick = 0;

	if(iWait)
	{
		if ((GetTickCount() - dwLastUpdateTick) > (DWORD)iMS)
		{
			dwLastUpdateTick = GetTickCount();
			 BitStream bsParams;
			g_DrifeitClient->RPC(RPC_UpdateScoresPingsIPs, &bsParams, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
		}
	}
	else
	{
		 BitStream bsParams;
		g_DrifeitClient->RPC(RPC_UpdateScoresPingsIPs, &bsParams, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
	}
}





void DrifeitClient::SendFakeUnoccupiedSyncData1(int carhnd, float fpos[3], float HealthCar, float speed[3])
{
	vehicle_info *tar = vehicle_info_get(carhnd, VEHICLE_ALIVE);

	stUnoccupiedData unSync;
	ZeroMemory(&unSync, sizeof(stUnoccupiedData));
	unSync.sVehicleID = getSAMPVehicleIDFromGTAVehicle(tar);
	unSync.fPosition[0] = fpos[0];
	unSync.fPosition[1] = fpos[1];
	unSync.fPosition[2] = fpos[2];
	unSync.fHealth = HealthCar;
	unSync.fMoveSpeed[0] = speed[0];
	unSync.fMoveSpeed[1] = speed[1];
	unSync.fMoveSpeed[2] = speed[2];
	unSync.fRoll[0] = 1;//if something dont work change it to 1
	unSync.fRoll[1] = 0;
	unSync.fRoll[2] = 0;
	unSync.byteSeatID = 1;
	unSync.fDirection[0] = 0;
	unSync.fDirection[1] = 1; //if something dont work change it to 1
	unSync.fDirection[2] = 0;
	unSync.fTurnSpeed[0] = speed[0];
	unSync.fTurnSpeed[1] = speed[1];
	unSync.fTurnSpeed[2] = speed[2];
	BitStream bsUnoccupiedSync;
	bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
	g_DrifeitClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}



void DrifeitClient::SendFakeDriverSyncDataWithQuaternion(USHORT VehicleID, float fPos[3], float fQuaternion[4], float HealthCar, float Speed[3], WORD key)
{
	struct actor_info *self = actor_info_get(ACTOR_SELF, NULL);
	stInCarData picSync;
	memset(&picSync, 0, sizeof(stInCarData));
	BitStream bsVehicleSync;
	picSync.sVehicleID = VehicleID;
	picSync.fQuaternion[0] = fQuaternion[0];
	picSync.fQuaternion[1] = fQuaternion[1];
	picSync.fQuaternion[2] = fQuaternion[2];
	picSync.fQuaternion[3] = fQuaternion[3];
	picSync.fPosition[0] = fPos[0];
	picSync.fPosition[1] = fPos[1];
	picSync.fPosition[2] = fPos[2];
	picSync.fVehicleHealth = HealthCar;
	picSync.fMoveSpeed[0] = Speed[0];
	picSync.fMoveSpeed[1] = Speed[1];
	picSync.fMoveSpeed[2] = Speed[2];
	picSync.sKeys = key;
	picSync.byteArmor = static_cast<uint8_t>(self->armor);
	picSync.bytePlayerHealth = static_cast<uint8_t>(self->hitpoints);
	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)&picSync, sizeof(stInCarData));
	g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void SendWastedNotification(BYTE byteDeathReason, SHORT WhoWasResponsible)
{
	if (g_SAMP == NULL) return;

	 BitStream bsPlayerDeath;

	bsPlayerDeath.Write(byteDeathReason);
	bsPlayerDeath.Write(WhoWasResponsible);
	g_DrifeitClient->RPC(RPC_Death, &bsPlayerDeath, SYSTEM_PRIORITY, UNRELIABLE, 0, 0);
}

void SendFakeUnoccupiedSyncData(USHORT VehicleID, float fPos[3])
{
	if ( g_SAMP == NULL ) return;
	
	 BitStream bs;
	UNOCCUPIED_SYNC_DATA sync;
	ZeroMemory(&sync, sizeof(sync));
	sync.vecTurnSpeed[0] = 9999999.99f;
	sync.vecTurnSpeed[1] = 9999999.99f;
	sync.vecTurnSpeed[2] = 9999999.99f;
	sync.fHealth = 1000.0f;
	memcpy(sync.vecPos, fPos, sizeof(sync.vecPos));
	sync.VehicleID = VehicleID;
	bs.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bs.Write((PCHAR)&sync, sizeof(UNOCCUPIED_SYNC_DATA));

	for ( int i = 0; i < 3; i++ )
		g_DrifeitClient->Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}



void SendFakeDriverSyncData(USHORT VehicleID, float fPos[3], float HealthCar, float Speed[3], WORD key)
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );	
	INCAR_SYNC_DATA picSync;
	
 memset(&picSync, 0, sizeof(INCAR_SYNC_DATA));
  BitStream bsVehicleSync;
 picSync.VehicleID = VehicleID;
   picSync.vecPos[0] = fPos[0];
  picSync.vecPos[1] = fPos[1];
  picSync.vecPos[2] = fPos[2];
 picSync.fCarHealth = HealthCar;
 picSync.vecMoveSpeed[0] = Speed[0];
  picSync.vecMoveSpeed[1] = Speed[1];
   picSync.vecMoveSpeed[2] = Speed[2];
   picSync.wKeys = key;
 picSync.bytePlayerHealth = self->hitpoints;
 picSync.bytePlayerArmour = self->armor;
 bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
 bsVehicleSync.Write((PCHAR)&picSync,sizeof(INCAR_SYNC_DATA));
 g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
 

} 

void SendFakeOnfootSyncData1(float fPos[3], float Health, int byteCurrentWeapon, float speed[3])
{
 stOnFootData picSync;
 memset(&picSync, 0, sizeof(stOnFootData));
  BitStream bsOnfootSync;
 picSync.byteHealth = Health;
 picSync.byteCurrentWeapon = byteCurrentWeapon;
 picSync.fPosition[0] = fPos[0];
 picSync.fPosition[1] = fPos[1];
 picSync.fPosition[2] = fPos[2];
 picSync.fMoveSpeed[0] = speed[0];
 picSync.fMoveSpeed[1] = speed[1];
 picSync.fMoveSpeed[2] = speed[2];
 bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
 bsOnfootSync.Write((PCHAR)&picSync,sizeof(stOnFootData));
 g_DrifeitClient->Send(&bsOnfootSync, SYSTEM_PRIORITY, UNRELIABLE, 0);

}



void SendFakeOnfootSyncData13(float fPos[3], float Health, int byteCurrentWeapon, int byteSpecialAction, float speed[3])
{
 stOnFootData picSync;
 memset(&picSync, 0, sizeof(stOnFootData));
  BitStream bsOnfootSync;
 picSync.byteHealth = Health;
 picSync.byteCurrentWeapon = byteCurrentWeapon;
 picSync.byteSpecialAction = byteSpecialAction;
 picSync.fPosition[0] = fPos[0];
 picSync.fPosition[1] = fPos[1];
 picSync.fPosition[2] = fPos[2];
 picSync.fMoveSpeed[0] = speed[0];
 picSync.fMoveSpeed[1] = speed[1];
 picSync.fMoveSpeed[2] = speed[2];
 bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
 bsOnfootSync.Write((PCHAR)&picSync,sizeof(stOnFootData));
 g_DrifeitClient->Send(&bsOnfootSync, SYSTEM_PRIORITY, UNRELIABLE, 0);

}


void  SendFakeDriverSyncData1(USHORT VehicleID, float coord[3], float HealthCar, float speed[3], float fQuaternion[4], WORD key)
{
struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
INCAR_SYNC_DATA sync;  

memset(&sync, 0, sizeof(INCAR_SYNC_DATA));
sync.fCarHealth = 1000; 
sync.VehicleID = VehicleID;
sync.fCarHealth = HealthCar;
sync.wKeys = key;
vect3_copy(coord, sync.vecPos); 
vect3_copy(speed, sync.vecMoveSpeed); 
vect3_copy(fQuaternion, sync.fQuaternion); 

 BitStream bs;

bs.Write((BYTE)ID_VEHICLE_SYNC); 
bs.Write((PCHAR)&sync, sizeof(INCAR_SYNC_DATA)); 
g_DrifeitClient->Send(&bs, SYSTEM_PRIORITY, UNRELIABLE, 0);

}


void  SendFakeDriverSyncData12(USHORT VehicleID, float coord[3], float HealthCar, float speed[3], float fQuaternion[4], WORD key)
{
struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
stInCarData sync;  

memset(&sync, 0, sizeof(stInCarData)); 
sync.sVehicleID = VehicleID;
sync.fVehicleHealth = HealthCar;
sync.sKeys = key;
vect3_copy(coord, sync.fPosition); 
vect3_copy(speed, sync.fMoveSpeed); 
vect3_copy(fQuaternion, sync.fQuaternion); 

 BitStream bs;

bs.Write((BYTE)ID_VEHICLE_SYNC); 
bs.Write((PCHAR)&sync, sizeof(stInCarData)); 
g_DrifeitClient->Send(&bs, SYSTEM_PRIORITY, UNRELIABLE, 0);

}

void SendFakeDriverFullSyncData(INCAR_SYNC_DATA *picSync, int iUseCarPos)
{
	if (picSync == NULL)
		return;
	
	 BitStream bsVehicleSync;
	
	if(iUseCarPos)
	{
		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[picSync->VehicleID]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info *vinfo = vehicle_info_get( car_id, 0 );

		if(!vinfo)
			return;

		float fPos[3];
		vect3_copy( &vinfo->base.matrix[4 * 3], fPos );

		picSync->vecPos[0] = fPos[0];
		picSync->vecPos[1] = fPos[1];
		picSync->vecPos[2] = fPos[2];
	}

	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)picSync, sizeof(stInCarData));

	g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void crashRCON()
{
	char szRcon[MAX_RCON_LEN + 1] = "login ";
	static int ooo = 1;
	for ( int i = 0; i < ooo; i++)
		szRcon[i + 6] = 33 + rand()%95;

	ooo++;
	
	if ( ooo > MAX_RCON_LEN - 6 ) ooo = 1;

	 BitStream ls;
	unsigned long len = strlen(szRcon);
	ls.Write((BYTE)ID_RCON_COMMAND);
	ls.Write(MAX_RCON_LEN);
	ls.Write(szRcon, len);
	g_DrifeitClient->Send(&ls, PacketPriority(rand()%3+1), RELIABLE, 0);
}

void DamageVehicle(USHORT VehicleID, bool vehPanelStatus, bool vehDoorStatus, int vehLightStatus, int vehTireStatus, int vehTireTest, int vehTireTests) 
{ 
	 BitStream bStream;
	bStream.Write(VehicleID);
	bStream.Write(vehPanelStatus);
	bStream.Write(vehDoorStatus);
	bStream.Write(vehLightStatus);
    bStream.Write(vehTireStatus);
	g_DrifeitClient->RPC(RPC_DamageVehicle, &bStream, SYSTEM_PRIORITY, UNRELIABLE, 0, 0);
}



void DamageVehicle11() 
{ 
	static int time = 0;
if (GetTickCount() - 8000 > time)

{
	 BitStream bsPlayerDeath;
			//bsPlayerDeath.Write(1);
			g_DrifeitClient->RPC(RPC_UpdateScoresPingsIPs, &bsPlayerDeath, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
			time = GetTickCount();
}
}

void SendFakeSpecData(float fPos[3])
{
	 SPECTATOR_SYNC_DATA specData;
     ZeroMemory(&specData, sizeof(SPECTATOR_SYNC_DATA));
     specData.vecPos[0] = fPos[0];
	 specData.vecPos[1] = fPos[1];
     specData.vecPos[2] = fPos[2];
	  BitStream bsSpec;
     bsSpec.Write((BYTE)ID_SPECTATOR_SYNC);
     bsSpec.Write((PCHAR)&specData, sizeof(SPECTATOR_SYNC_DATA));
     g_DrifeitClient->Send(&bsSpec, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void  SendSCMEventP( int vehicleID, int eventId, int param1, int param2 )
{
	 BitStream bsScmEvent;

	bsScmEvent.Write ( vehicleID );
	bsScmEvent.Write ( param1 );
	bsScmEvent.Write ( param2 );
	bsScmEvent.Write ( eventId );
	g_DrifeitClient->RPC(RPC_ScmEvent, &bsScmEvent, SYSTEM_PRIORITY, UNRELIABLE, 0, 0);
}
	
void SendFakeCarDeath(USHORT VehicleID)
{
	 BitStream VehicleBoom;
	VehicleBoom.Write(VehicleID);
	g_DrifeitClient->RPC(RPC_VehicleDestroyed, &VehicleBoom, SYSTEM_PRIORITY, UNRELIABLE, 0, 0);
}

void SendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, char *szInputResp)
{
	BYTE respLen = (BYTE)strlen(szInputResp);
	 BitStream bsSend;
	bsSend.Write(wDialogID);
	bsSend.Write(bButtonID);
	bsSend.Write(wListBoxItem);
	bsSend.Write(respLen);
	bsSend.Write(szInputResp, respLen);
	g_DrifeitClient->RPC(RPC_DialogResponse, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);

	
}

void DrifeitClient::SendWeaponUpdateSync(BYTE weaponslot, BYTE weaponid, WORD ammo)
{
	stWeaponUpdate picSync;
	memset(&picSync, 0, sizeof(stWeaponUpdate)); 
	 BitStream bsWeaponSync;
	picSync.slot = weaponslot;
	picSync.weaponid = weaponid;
	picSync.ammo = ammo;
	bsWeaponSync.Write((BYTE)ID_WEAPONS_UPDATE);
	bsWeaponSync.Write((PCHAR)&picSync, sizeof(stWeaponUpdate));
	g_DrifeitClient->Send(&bsWeaponSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void SendFakeAimSyncData(float vecAimPos[3], float vecAimf1[3], float fAimZ, BYTE byteCamMode, BYTE byteCamExtZoom, BYTE byteWeaponState, BYTE bUnk)
{
	stAimData aimSync;
	memset(&aimSync, 0, sizeof(stAimData)); 
	 BitStream bsAimSync;
	aimSync.fAimZ = fAimZ;
	aimSync.vecAimf1[0] = vecAimf1[0];
	aimSync.vecAimf1[1] = vecAimf1[1];
	aimSync.vecAimf1[2] = vecAimf1[2];
	aimSync.vecAimPos[0] = vecAimPos[0];
	aimSync.vecAimPos[1] = vecAimPos[1];
	aimSync.vecAimPos[2] = vecAimPos[2];
	aimSync.byteCamMode = byteCamMode;
	aimSync.byteCamExtZoom = byteCamExtZoom;
	aimSync.byteWeaponState = byteWeaponState;
	aimSync.bUnk = bUnk;
	bsAimSync.Write((BYTE)ID_AIM_SYNC);
	bsAimSync.Write((PCHAR)&aimSync, sizeof(stAimData));
	g_DrifeitClient->Send(&bsAimSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void SendPlayerDamage(uint16_t playerid, float amountdam, int weaponid, bool takedam)
{
	 BitStream damage;
	damage.Write(takedam);
	damage.Write(playerid);
	damage.Write(amountdam);
	damage.Write(weaponid);
	g_DrifeitClient->RPC(RPC_PlayerGiveDamage, &damage, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}

void SendSpectatorData(float fPos[3])
{
	SPECTATOR_SYNC_DATA pSpecData;
	memset(&pSpecData, 0, sizeof(SPECTATOR_SYNC_DATA));
	 BitStream bsSpecSync;

	pSpecData.vecPos[0] = fPos[0];
	pSpecData.vecPos[1] = fPos[1];
	pSpecData.vecPos[2] = fPos[2];
	bsSpecSync.Write((BYTE)ID_SPECTATOR_SYNC);
	bsSpecSync.Write((PCHAR)&pSpecData, sizeof(SPECTATOR_SYNC_DATA));
	g_DrifeitClient->Send(&bsSpecSync,HIGH_PRIORITY,UNRELIABLE_SEQUENCED,0);
}

void SendFakeOnfootSyncData22(float fPos[3], float fSpeed[3],float Health,float Armor , int AnimationID , float Quaternion[4])
{
	stOnFootData onSync;
	ZeroMemory(&onSync, sizeof(stOnFootData)); 

    onSync.byteHealth = Health; 
	onSync.byteArmor = Armor;

    onSync.fPosition[0] = fPos[0];
    onSync.fPosition[1] = fPos[1];
    onSync.fPosition[2] = fPos[2];

    onSync.fMoveSpeed[0] = fSpeed[0];
    onSync.fMoveSpeed[1] = fSpeed[1];
    onSync.fMoveSpeed[2] = fSpeed[2];

	onSync.fQuaternion[0] = Quaternion[0];
	onSync.fQuaternion[1] = Quaternion[1];
	onSync.fQuaternion[2] = Quaternion[2];
	onSync.fQuaternion[3] = Quaternion[3];

	onSync.iCurrentAnimationID = AnimationID;

	 BitStream bsData;
    bsData.Write((BYTE)ID_PLAYER_SYNC);
    bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));
    g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void SendDamageVehicle(WORD vehicleID, DWORD panel, DWORD door, BYTE lights, BYTE tires)
{
	 BitStream bsDamageVehicle;
	bsDamageVehicle.Write(vehicleID);
	bsDamageVehicle.Write(panel);//(panel);  //<3
	bsDamageVehicle.Write(door);//(door);
	bsDamageVehicle.Write(lights);//(lights);
	bsDamageVehicle.Write(tires);//tires
	g_DrifeitClient->RPC(RPC_DamageVehicle, &bsDamageVehicle, SYSTEM_PRIORITY, UNRELIABLE, 0, 0);
}

void SendFakePassengerSyncData(WORD vehicleid, float fPos[3], float HealthCar, uint8_t WeaponID, int SeatID, WORD key)
{
	struct actor_info *self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE ); 
	stPassengerData PassData = g_Players->pLocalPlayer->passengerData;
   	ZeroMemory(&PassData, sizeof(stPassengerData));
	 BitStream bsVehicleSync;
    PassData.sVehicleID = vehicleid;

    PassData.fPosition[0] = fPos[0];
    PassData.fPosition[1] = fPos[1];
    PassData.fPosition[2] = fPos[2];
    PassData.byteCurrentWeapon = WeaponID;
	PassData.sKeys = key;
	PassData.byteSeatID = SeatID;
    PassData.byteHealth = self->hitpoints;
    PassData.byteArmor = self->armor;
    bsVehicleSync.Write((BYTE)ID_PASSENGER_SYNC);
    bsVehicleSync.Write((PCHAR)&PassData,sizeof(stPassengerData));
    g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}


void SendFakeTrailerData(vehicle_info *vehicle, float fpos[3], float HealthCar, float Speed[3])
{

	if (!vehicle_info_get(VEHICLE_SELF, NULL))
		return;

	stInCarData incar;
	memcpy(&incar, &g_Players->pLocalPlayer->inCarData, sizeof(stInCarData));
	incar.sTrailerID = getSAMPVehicleIDFromGTAVehicle(vehicle);

	 BitStream bsPacket;
	bsPacket.Write((BYTE)ID_VEHICLE_SYNC);
	bsPacket.Write((PCHAR)(&incar), sizeof(incar));
	g_DrifeitClient->Send(&bsPacket);


	stTrailerData trailer_sync;
	memcpy(trailer_sync.fPosition, fpos, sizeof(float) * 4);
	memcpy(trailer_sync.fSpeed, Speed, sizeof(float) * 4);
	//memcpy(trailer_sync.fDirection, fpos, sizeof(float)* 4);
	//memcpy(trailer_sync.fRoll, Speed, sizeof(float)* 4);
	trailer_sync.sTrailerID = getSAMPVehicleIDFromGTAVehicle(vehicle);

	 BitStream bsPackettrailer;
	bsPackettrailer.Write((BYTE)ID_TRAILER_SYNC);
	bsPackettrailer.Write((PCHAR)(&trailer_sync), sizeof(trailer_sync));
	g_DrifeitClient->Send(&bsPackettrailer);
}

void  DrifeitClient::SendMutantDriverSyncData(uint16_t VehicleID, float fPos[3], float fSpeed[3], float fQuaternion[4])
{
	//static DWORD time = GetTickCount();
	//if (GetTickCount() - 1500 > time)
	//{
	 
		struct actor_info	*self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		
		
		stUnoccupiedData stUnoDop1;
		memset(&stUnoDop1, 0, sizeof(stUnoccupiedData));
		stUnoDop1.byteSeatID = 0;
		stUnoDop1.fPosition[0] = fPos[0];
		stUnoDop1.fPosition[1] = fPos[1];
		stUnoDop1.fPosition[2] = fPos[2];
		stUnoDop1.sVehicleID = VehicleID;
		stUnoDop1.fDirection[0] = fPos[0];
		stUnoDop1.fDirection[1] = fPos[1];
		stUnoDop1.fDirection[2] = fPos[2];
		stUnoDop1.fRoll[0] = fPos[0];
		stUnoDop1.fRoll[1] = fPos[1];
		stUnoDop1.fRoll[2] = fPos[2];
		stUnoDop1.fTurnSpeed[0] = fSpeed[0];
		stUnoDop1.fTurnSpeed[1] = fSpeed[1];
		stUnoDop1.fTurnSpeed[2] = fSpeed[2];

		stUnoccupiedData stUno;
		memset(&stUno, 0, sizeof(stUnoccupiedData));
		stUno.byteSeatID = 0;
		stUno.fPosition[0] = fPos[0];
		stUno.fPosition[1] = fPos[1];
		stUno.fPosition[2] = fPos[2];
		stUno.sVehicleID = VehicleID;
		stUno.fDirection[0] = fPos[0];
		stUno.fDirection[1] = fPos[1];
		stUno.fDirection[2] = fPos[2];
		stUno.fRoll[0] = fPos[0];
		stUno.fRoll[1] = fPos[1];
		stUno.fRoll[2] = fPos[2];
		stUno.fTurnSpeed[0] = fSpeed[0];
		stUno.fTurnSpeed[1] = fSpeed[1];
		stUno.fTurnSpeed[2] = fSpeed[2];

		stInCarData onSync;
		memset(&onSync, 0, sizeof(stUnoccupiedData));
		onSync.sVehicleID = VehicleID;
		onSync.byteArmor = self->armor;
		onSync.bytePlayerHealth = self->hitpoints;
		onSync.fVehicleHealth = 1000;
		onSync.fPosition[0] = fPos[0];
		onSync.fPosition[1] = fPos[1];
		onSync.fPosition[2] = fPos[2];
		onSync.fMoveSpeed[0] = fSpeed[0];
		onSync.fMoveSpeed[1] = fSpeed[1];
		onSync.fMoveSpeed[2] = fSpeed[2];
		onSync.fQuaternion[0] = fQuaternion[0];
		onSync.fQuaternion[1] = fQuaternion[1];
		onSync.fQuaternion[2] = fQuaternion[2];
		onSync.fQuaternion[2] = fQuaternion[3];

		stUnoccupiedData stUnoDop;
		memset(&stUnoDop, 0, sizeof(stUnoccupiedData));
		stUnoDop.byteSeatID = 0;
		stUnoDop.fPosition[0] = fPos[0];
		stUnoDop.fPosition[1] = fPos[1];
		stUnoDop.fPosition[2] = fPos[2];
		stUnoDop.sVehicleID = VehicleID;
		stUnoDop.fDirection[0] = fPos[0];
		stUnoDop.fDirection[1] = fPos[1];
		stUnoDop.fDirection[2] = fPos[2];
		stUnoDop.fRoll[0] = fPos[0];
		stUnoDop.fRoll[1] = fPos[1];
		stUnoDop.fRoll[2] = fPos[2];
		stUnoDop.fTurnSpeed[0] = fSpeed[0];
		stUnoDop.fTurnSpeed[1] = fSpeed[1];
		stUnoDop.fTurnSpeed[2] = fSpeed[2];

		stUnoccupiedData stUnoDop2;
		memset(&stUnoDop2, 0, sizeof(stUnoccupiedData));
		stUnoDop2.byteSeatID = 0;
		stUnoDop2.fPosition[0] = fPos[0];
		stUnoDop2.fPosition[1] = fPos[1];
		stUnoDop2.fPosition[2] = fPos[2];
		stUnoDop2.sVehicleID = VehicleID;
		stUnoDop2.fDirection[0] = fPos[0];
		stUnoDop2.fDirection[1] = fPos[1];
		stUnoDop2.fDirection[2] = fPos[2];
		stUnoDop2.fRoll[0] = fPos[0];
		stUnoDop2.fRoll[1] = fPos[1];
		stUnoDop2.fRoll[2] = fPos[2];
		stUnoDop2.fTurnSpeed[0] = fSpeed[0];
		stUnoDop2.fTurnSpeed[1] = fSpeed[1];
		stUnoDop2.fTurnSpeed[2] = fSpeed[2];

		stUnoccupiedData stUnoDop3;
		memset(&stUnoDop3, 0, sizeof(stUnoccupiedData));
		stUnoDop3.byteSeatID = 0;
		stUnoDop3.fPosition[0] = fPos[0];
		stUnoDop3.fPosition[1] = fPos[1];
		stUnoDop3.fPosition[2] = fPos[2];
		stUnoDop3.sVehicleID = VehicleID;
		stUnoDop3.fDirection[0] = fPos[0];
		stUnoDop3.fDirection[1] = fPos[1];
		stUnoDop3.fDirection[2] = fPos[2];
		stUnoDop3.fRoll[0] = fPos[0];
		stUnoDop3.fRoll[1] = fPos[1];
		stUnoDop3.fRoll[2] = fPos[2];
		stUnoDop3.fTurnSpeed[0] = fSpeed[0];
		stUnoDop3.fTurnSpeed[1] = fSpeed[1];
		stUnoDop3.fTurnSpeed[2] = fSpeed[2];

		 BitStream vehExit1;
		vehExit1.Write(VehicleID);
		g_DrifeitClient->RPC(RPC_ExitVehicle, &vehExit1, SYSTEM_PRIORITY, RELIABLE_SEQUENCED, 0, 0);
		 BitStream bsUnoDop1;
		bsUnoDop1.Write((BYTE)ID_UNOCCUPIED_SYNC);
		bsUnoDop1.Write((PCHAR)&stUnoDop1, sizeof(stUnoccupiedData));
		g_DrifeitClient->Send(&bsUnoDop1, SYSTEM_PRIORITY, RELIABLE_SEQUENCED, 0);
		 BitStream bsUnoDop;
		bsUnoDop.Write((BYTE)ID_UNOCCUPIED_SYNC);
		bsUnoDop.Write((PCHAR)&stUnoDop, sizeof(stUnoccupiedData));
		g_DrifeitClient->Send(&bsUnoDop, SYSTEM_PRIORITY, RELIABLE_SEQUENCED, 0);
		 BitStream vehExit2;
		vehExit2.Write(VehicleID);
		g_DrifeitClient->RPC(RPC_ExitVehicle, &vehExit2, SYSTEM_PRIORITY, RELIABLE_SEQUENCED, 0, 0);
		 BitStream bs;
		bs.Write((BYTE)ID_VEHICLE_SYNC);
		bs.Write((PCHAR)&onSync, sizeof(stUnoccupiedData));
		delete &onSync;
		delete &bs;
		g_DrifeitClient->Send(&bs, LOW_PRIORITY, UNRELIABLE, 0);
		delete &onSync;
		delete &bs;
		 BitStream bsUno;
		bsUno.Write((BYTE)ID_UNOCCUPIED_SYNC);
		bsUno.Write((PCHAR)&stUno, sizeof(stUnoccupiedData));
		g_DrifeitClient->Send(&bsUno, SYSTEM_PRIORITY, RELIABLE_SEQUENCED, 0);
		 BitStream bsUnof;
		bsUnof.Write((BYTE)ID_UNOCCUPIED_SYNC);
		bsUnof.Write((PCHAR)&stUnoDop2, sizeof(stUnoccupiedData));
		g_DrifeitClient->Send(&bsUnof, SYSTEM_PRIORITY, RELIABLE_SEQUENCED, 0);
		 BitStream bsUnofg;
		bsUnofg.Write((BYTE)ID_UNOCCUPIED_SYNC);
		bsUnofg.Write((PCHAR)&stUnoDop3, sizeof(stUnoccupiedData));
		g_DrifeitClient->Send(&bsUnofg, SYSTEM_PRIORITY, RELIABLE_SEQUENCED, 0);
		 BitStream vehExit;
		vehExit.Write(VehicleID);
		g_DrifeitClient->RPC(RPC_ExitVehicle, &vehExit, SYSTEM_PRIORITY, RELIABLE_SEQUENCED, 0, 0);
		//time = GetTickCount();
	//}
}

void DrifeitClient::SendFakeUnnocupiedFullSyncData(stUnoccupiedData *picSync, int iUseCarPos)
{
	if (picSync == NULL)
		return;

	
	 BitStream bsVehicleSync;
	if (iUseCarPos)
	{
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[picSync->sVehicleID]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

		if (!vinfo)
			return;

		float fPos[3];
		vect3_copy(&vinfo->base.matrix[4 * 3], fPos);

		picSync->fPosition[0] = fPos[0];
		picSync->fPosition[1] = fPos[1];
		picSync->fPosition[2] = fPos[2];
	}

	bsVehicleSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsVehicleSync.Write((PCHAR)picSync, sizeof(stUnoccupiedData));

	g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void SendFakeUnoccupiedSyncData(uint16_t VehicleID, uint8_t SeatID, float Pos[3], float Speed[3], float Health, float spin[3], float roll[3])
{
	stUnoccupiedData picSync;
	memset(&picSync, 0, sizeof(stUnoccupiedData));
	 BitStream bsUnoccupiedSync;
	picSync.sVehicleID = VehicleID;
	picSync.byteSeatID = SeatID;
	struct vehicle_info *vinfo = getGTAVehicleFromSAMPVehicleID(VehicleID);
	picSync.fDirection[0] = vinfo->base.matrix[4 * 1 + 0];
	picSync.fDirection[1] = vinfo->base.matrix[4 * 1 + 1];
	picSync.fDirection[2] = vinfo->base.matrix[4 * 1 + 2];
	picSync.fRoll[0] = roll[0];
	picSync.fRoll[1] = roll[1];
	picSync.fRoll[2] = roll[2];
	picSync.fPosition[0] = Pos[0];
	picSync.fPosition[1] = Pos[1];
	picSync.fPosition[2] = Pos[2];
	picSync.fMoveSpeed[0] = Speed[0];
	picSync.fMoveSpeed[1] = Speed[1];
	picSync.fMoveSpeed[2] = Speed[2];
	picSync.fTurnSpeed[0] = spin[0];
	picSync.fTurnSpeed[1] = spin[1];
	picSync.fTurnSpeed[2] = spin[2];
	picSync.fHealth = Health;
	bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsUnoccupiedSync.Write((PCHAR)&picSync, sizeof(stUnoccupiedData));
	g_DrifeitClient->Send(&bsUnoccupiedSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void DrifeitClient::SendFakeDriverSyncData44(USHORT VehicleID, float fPos[3], float HealthCar, float Speed[3], WORD key)
{
	struct actor_info *self = actor_info_get(ACTOR_SELF, NULL);
	stInCarData picSync;
	memset(&picSync, 0, sizeof(stInCarData));
	BitStream bsVehicleSync;
	picSync.sVehicleID = VehicleID;
	picSync.fPosition[0] = fPos[0];
	picSync.fPosition[1] = fPos[1];
	picSync.fPosition[2] = fPos[2];
	picSync.fVehicleHealth = HealthCar;
	picSync.fMoveSpeed[0] = Speed[0];
	picSync.fMoveSpeed[1] = Speed[1];
	picSync.fMoveSpeed[2] = Speed[2];
	picSync.sKeys = key;
	picSync.byteArmor = static_cast<uint8_t>(self->armor);
	picSync.bytePlayerHealth = static_cast<uint8_t>(self->hitpoints);
	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)&picSync, sizeof(stInCarData));
	g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}


void DrifeitClient::SendEnterVehicle(int vehID, int as)  //as = 0 as driver, as = 1 as passenger
{
	BitStream bsSpecSync;
	bsSpecSync.Write((BYTE)RPC_EnterVehicle);
	bsSpecSync.Write((uint16_t)vehID);
	bsSpecSync.Write((uint8_t)as);
	g_DrifeitClient->Send(&bsSpecSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void DrifeitClient::SendExitVehicle(int vehID)  //as = 0 as driver, as = 1 as passenger
{
	BitStream bsSpecSync;
	bsSpecSync.Write((BYTE)RPC_ExitVehicle);
	bsSpecSync.Write((uint16_t)vehID);
	g_DrifeitClient->Send(&bsSpecSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
//as = 0 as driver, as = 1 as passenger

void DrifeitClient::SendDamageVehicle(WORD vehicleID, DWORD panel, DWORD door, BYTE lights, BYTE tires)
{
	BitStream bsDamageVehicle;

	bsDamageVehicle.Write(vehicleID);
	bsDamageVehicle.Write(panel);
	bsDamageVehicle.Write(door);
	bsDamageVehicle.Write(lights);
	bsDamageVehicle.Write(tires);
	g_DrifeitClient->RPC(RPC_DamageVehicle, &bsDamageVehicle, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE);
}


HuffmanEncodingTree::HuffmanEncodingTree()
{
	root = 0;
}

HuffmanEncodingTree::~HuffmanEncodingTree()
{
	//FreeMemory();
}



void HuffmanEncodingTree::DecodeArray(unsigned char *input, unsigned sizeInBits, BitStream * output)
{
	HuffmanEncodingTreeNode * currentNode;

	if (sizeInBits <= 0)
		return;

	BitStream bitStream(input, BITS_TO_BYTES(sizeInBits), false);

	currentNode = root;

	// For each bit, go left if it is a 0 and right if it is a 1.  When we reach a leaf, that gives us the desired value and we restart from the root
	for (unsigned counter = 0; counter < sizeInBits; counter++)
	{
		if (bitStream.ReadBit() == false)   // left!
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;

		if (currentNode->left == 0 && currentNode->right == 0)   // Leaf
		{
			output->WriteBits(&(currentNode->value), sizeof(char) * 8, true); // Use WriteBits instead of Write(char) because we want to avoid TYPE_CHECKING
			currentNode = root;
		}
	}
}
unsigned HuffmanEncodingTree::DecompressAndAllocate(BitStream * input, unsigned char **output)
{

	unsigned int bitsUsed, destinationSizeInBytes, decompressedBytes;
	unsigned int frequencyTable[256];
	unsigned i;

	input->ReadCompressed(destinationSizeInBytes);
	for (i = 0; i < 256; i++)
		input->ReadCompressed(frequencyTable[i]);
	input->AlignReadToByteBoundary();
	if (input->Read(bitsUsed) == false)
	{
		return 0;
	}
	*output = new unsigned char[destinationSizeInBytes];
	return destinationSizeInBytes;
}