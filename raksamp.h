

extern class DrifeitClient *g_DrifeitClient;

typedef unsigned int RakNetTime;
typedef long long RakNetTimeNS;

typedef struct _UNOCCUPIED_SYNC_DATA
{
#pragma pack ( 1 ) 
	USHORT VehicleID;
	USHORT byteSeatID;
	short cvecRoll[3];
	short cvecDirection[3];
	BYTE unk[13];
	float vecPos[3];
	float vecMoveSpeed[3];
	float vecTurnSpeed[3];
	float fHealth;

} UNOCCUPIED_SYNC_DATA;

typedef struct _ONFOOT_SYNC_DATA
{
#pragma pack ( 1 )
	WORD lrAnalog;
	WORD udAnalog;
	WORD wKeys;
	float vecPos[3];
	float fQuaternion[4];
	BYTE byteHealth;
	BYTE byteArmour;
	BYTE byteCurrentWeapon;
	BYTE byteSpecialAction;	
	float vecMoveSpeed[3];
	float vecSurfOffsets[3];
	WORD wSurfInfo;
	int	iCurrentAnimationID;
} ONFOOT_SYNC_DATA;

typedef struct _INCAR_SYNC_DATA
{
#pragma pack ( 1 )
	USHORT VehicleID;
	WORD lrAnalog;
	WORD udAnalog;
	WORD wKeys;
	float fQuaternion[4];
	float vecPos[3];
	float vecMoveSpeed[3];
	float fCarHealth;
	BYTE bytePlayerHealth;
	BYTE bytePlayerArmour;
	BYTE byteCurrentWeapon;
	BYTE byteSirenOn;
	BYTE byteLandingGearState;
	WORD TrailerID_or_ThrustAngle;
	FLOAT fTrainSpeed;
} INCAR_SYNC_DATA;

typedef struct _PASSENGER_SYNC_DATA
{
#pragma pack ( 1 )
	USHORT VehicleID;
	BYTE byteSeatFlags : 7;
	BYTE byteDriveBy : 1;
	BYTE byteCurrentWeapon;
	BYTE bytePlayerHealth;
	BYTE bytePlayerArmour;
	WORD lrAnalog;
	WORD udAnalog;
	WORD wKeys;
	float vecPos[3];
} PASSENGER_SYNC_DATA;

typedef struct _AIM_SYNC_DATA
{
#pragma pack ( 1 )
	BYTE byteCamMode;
	float vecAimf1[3];
	float vecAimPos[3];
	float fAimZ;
	BYTE byteCamExtZoom : 6;	// 0-63 normalized
	BYTE byteWeaponState : 2;	// see eWeaponState
	BYTE bUnk;
} AIM_SYNC_DATA;



void SendWastedNotification(BYTE byteDeathReason, SHORT WhoWasResponsible);
void SendFakeUnoccupiedSyncData(USHORT VehicleID, float fPos[3]);
void SendFakeDriverSyncData(USHORT VehicleID, float fPos[3], float HealthCar, float Speed[3], WORD key);
void SendFakeOnfootSyncData1(float fPos[3], float Health, int byteCurrentWeapon, float speed[3]);
void SendFakeOnfootSyncData13(float fPos[3], float Health, int byteCurrentWeapon, int byteSpecialAction, float speed[3]);
void  SendFakeDriverSyncData1(USHORT VehicleID, float coord[3], float HealthCar, float speed[3], float fQuaternion[4], WORD key);
#define MAX_RCON_LEN 512
void DamageVehicle(USHORT VehicleID, bool vehPanelStatus, bool vehDoorStatus, int vehLightStatus, int vehTireStatus, int vehTireTest, int vehTireTests) ;
void DamageVehicle11() ;
void  SendSCMEventP( int vehicleID, int eventId, int param1, int param2 );
void SendFakeCarDeath(USHORT VehicleID);
void SendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, char *szInputResp);
void UpdatePlayerScoresAndPings(int iWait, int iMS);

void SendFakeAimSyncData(float vecAimPos[3], float vecAimf1[3], float fAimZ, BYTE byteCamMode, BYTE byteCamExtZoom, BYTE byteWeaponState, BYTE bUnk);
void SendPlayerDamage(uint16_t playerid, float amountdam, int weaponid, bool takedam);
void  SendFakeDriverSyncData12(USHORT VehicleID, float coord[3], float HealthCar, float speed[3], float fQuaternion[4], WORD key);
void SendFakeOnfootSyncData22(float fPos[3], float fSpeed[3],float Health,float Armor , int AnimationID , float Quaternion[4]);
void SendDamageVehicle(WORD vehicleID, DWORD panel, DWORD door, BYTE lights, BYTE tires);
void SendFakePassengerSyncData(WORD vehicleid, float fPos[3], float HealthCar, uint8_t WeaponID, int SeatID, WORD key);
void SendFakeSpecData(float fPos[3]);
void SendFakeDriverFullSyncData(INCAR_SYNC_DATA *picSync, int iUseCarPos);
//void SendFakeUnnocupiedFullSyncData(stUnoccupiedData *picSync, int iUseCarPos);
void SendFakeUnoccupiedSyncData(uint16_t VehicleID, uint8_t SeatID, float Pos[3], float Speed[3], float Health, float spin[3], float roll[3]);


enum RPCEnumeration
{
	RPC_ServerJoin = 10,
	RPC_ServerQuit = 11,
	RPC_InitGame = 12,
	RPC_ClientJoin = 81,
	RPC_NPCJoin = 152,
	RPC_Death = 151,
	RPC_RequestClass = 101,
	RPC_RequestSpawn = 102,
	RPC_SetInteriorId = 7,
	RPC_Spawn = 11,
	RPC_Chat = 138,
	RPC_EnterVehicle = 103,
	RPC_ExitVehicle = 104,
	RPC_DamageVehicle = 131,
	RPC_MenuSelect = 143,
	RPC_MenuQuit = 144,
	RPC_ScmEvent = 140,
	RPC_AdminMapTeleport = 255,
	RPC_WorldPlayerAdd = 69, //by PovarGek(Golub) - 0.3e    
	RPC_WorldPlayerDeath = 130, //by PovarGek(Golub) - 0.3e    
	RPC_WorldPlayerRemove = 127, //by PovarGek(Golub) - 0.3e    
	RPC_WorldVehicleAdd = 128,//by PovarGek(Golub) - 0.3e    
	RPC_WorldVehicleRemove = 129,//by PovarGek(Golub) - 0.3e    
	RPC_SetCheckpoint = 130,
	RPC_DisableCheckpoint = 255,
	RPC_SetRaceCheckpoint = 255,
	RPC_DisableRaceCheckpoint = 255,
	RPC_UpdateScoresPingsIPs = 105,
	RPC_SvrStats = 255,
	RPC_GameModeRestart = 42,
	RPC_ConnectionRejected = 13,
	RPC_ClientMessage = 14,
	RPC_WorldTime = 255,
	RPC_Pickup = 255,
	RPC_DestroyPickup = 255,
	RPC_DestroyWeaponPickup = 255,
	RPC_Weather = 19,
	RPC_SetTimeEx = 255,
	RPC_ToggleClock = 255,
	RPC_ServerCommand = 6,
	RPC_PickedUpPickup = 142,
	RPC_PickedUpWeapon = 255,
	RPC_VehicleDestroyed = 9,
	RPC_SpawnPlayer = 150,// by povargek
	RPC_DialogResponse = 78,
	RPC_PlayAudioStream = 45,
	RPC_ClickPlayer = 79,
	RPC_MapMaker = 8,
	RPC_PlayerClickTextDraw = 58,
	RPC_PlayerGiveDamage = 60, //(short, 	, 	, 	)
	RPC_ExitedMenu = 144,
	RPC_SelectedMenuRow = 143,
};

enum ScriptRPCEnumeration
{
	RPC_ScrSetSpawnInfo = 125, //by PovarGek(Golub) - 0.3e 
	RPC_ScrSetPlayerTeam = 126, //by PovarGek(Golub) - 0.3e 
	RPC_ScrSetPlayerSkin = 20, //by PovarGek(Golub) - 0.3e (      PlayerID,       SkinID) 
	RPC_ScrSetPlayerName = 21, //by PovarGek(Golub) - 0.3e 
	RPC_ScrSetPlayerPos = 22, //by PovarGek(Golub) - 0.3e 
	RPC_ScrSetPlayerPosFindZ = 23, //by PovarGek(Golub) - 0.3e 
	RPC_ScrSetPlayerHealth = 24, //by PovarGek(Golub) - 0.3e (float HP) 
	RPC_ScrPutPlayerInVehicle = 25, //by PovarGek(Golub) - 0.3e 
	RPC_ScrRemovePlayerFromVehicle = 26, //by PovarGek(Golub) - 0.3e 
	RPC_ScrSetPlayerColor = 27, //by PovarGek(Golub) - 0.3e 
	RPC_ScrDisplayGameText = 28, //03e 
	RPC_ScrSetInterior = 255,
	RPC_ScrSetCameraPos = 107,
	RPC_ScrSetCameraLookAt = 108,
	RPC_ScrSetVehiclePos = 109,
	RPC_ScrSetVehicleZAngle = 255,
	RPC_ScrVehicleParams = 80,
	RPC_ScrSetCameraBehindPlayer = 112,
	RPC_ScrTogglePlayerControllable = 113,
	RPC_ScrPlaySound = 114,
	RPC_ScrSetWorldBounds = 155,
	RPC_ScrHaveSomeMoney = 255,
	RPC_ScrSetPlayerFacingAngle = 117,
	RPC_ScrResetMoney = 118,
	RPC_ScrResetPlayerWeapons = 119,
	RPC_ScrGivePlayerWeapon = 120, //by PovarGek(Golub) - 0.3e (      WeaponID,       Ammo) 
	RPC_ScrRespawnVehicle = 129, //by PovarGek(Golub) - 0.3e 
	RPC_ScrLinkVehicle = 255,
	RPC_ScrSetPlayerArmour = 123,
	RPC_ScrDeathMessage = 153,
	RPC_ScrSetMapIcon = 154,
	RPC_ScrDisableMapIcon = 155,
	RPC_ScrSetWeaponAmmo = 255,
	RPC_ScrSetGravity = 255,
	RPC_ScrSetVehicleHealth = 158,
	RPC_ScrAttachTrailerToVehicle = 255,
	RPC_ScrDetachTrailerFromVehicle = 255,
	RPC_ScrCreateObject = 48, //by PovarGek(Golub) - 0.3e 
	RPC_ScrSetObjectPos = 49,
	RPC_ScrSetObjectRotation = 50,
	RPC_ScrDestroyObject = 51,
	RPC_ScrCreateExplosion = 54, //by PovarGek(Golub) - 0.3e 
	RPC_ScrShowNameTag = 255,
	RPC_ScrMoveObject = 255,
	RPC_ScrStopObject = 255,
	RPC_ScrNumberPlate = 255,
	RPC_ScrTogglePlayerSpectating = 97,
	RPC_ScrSetPlayerSpectating = 98,
	RPC_ScrPlayerSpectatePlayer = 99,
	RPC_ScrPlayerSpectateVehicle = 100,
	RPC_ScrRemoveComponent = 140,
	RPC_ScrForceSpawnSelection = 29,
	RPC_ScrAttachObjectToPlayer = 61, 
	RPC_ScrAttachObjectToPlayer1 = 44,
	RPC_ScrInitMenu = 31, //by PovarGek(Golub) - 0.3e 
	RPC_ScrShowMenu = 32, //by PovarGek(Golub) - 0.3e 
	RPC_ScrHideMenu = 33,
	RPC_ScrSetPlayerWantedLevel = 34,
	RPC_ScrShowTextDraw = 35,
	RPC_ScrHideTextDraw = 36,
	RPC_ScrEditTextDraw = 38,
	RPC_ScrAddGangZone = 39,
	RPC_ScrRemoveGangZone = 82,
	RPC_ScrFlashGangZone = 83,
	RPC_ScrStopFlashGangZone = 84,
	RPC_ScrApplyAnimation = 87,
	RPC_ScrClearAnimations = 255,
	RPC_ScrSetSpecialAction = 87,
	RPC_ScrEnableStuntBonus = 37,
	RPC_ScrSetFightingStyle = 88,
	RPC_ScrSetPlayerVelocity = 89,
	RPC_ScrSetVehicleVelocity = 255,
	RPC_ScrToggleWidescreen = 255,
	RPC_ScrSetVehicleTireStatus = 255,
	RPC_ScrSetPlayerDrunkVisuals = 255,
	RPC_ScrSetPlayerDrunkHandling = 72,
	RPC_ScrDialogBox = 77, //03e
	RPC_ScrSelectObject = 63, //by PovarGek(Golub) - 0.3e 
    RPC_ScrEditObject = 62, //by PovarGek(Golub) - 0.3e
	RPC_SetWorldTime = 15,
	RPC_SetPlayerWeather = 19,
	RPC_SetPlayerPosFindZ = 23,
	RPC_RemovePlayerFromVehicle = 26,
	RPC_AttachObjectToPlayer = 30,
	RPC_StopAudioStreamForPlayer = 46,
	RPC_RemoveBuildingForPlayer = 47,
	RPC_AttachCameraToObject = 56,
	RPC_CancelEdit = 64,
	RPC_ConnectionPong = 65,
	RPC_SetPlayerTime = 66,
	RPC_TogglePlayerClock = 67,
	RPC_SetPlayerSkillLevel = 71,
	RPC_ShowDialog = 77,
	RPC_SetVehicleVelocity = 90,
	RPC_MoveObject = 94,
	RPC_StopObject = 95,
};



enum NetPatchType
{
	INCOMING_RPC,
	OUTCOMING_RPC,
	INCOMING_PACKET,
	OUTCOMING_PACKET,
};

struct stNetPatch
{
	const char *name;
	int hotkey;
	bool enabled;
	byte id;
	NetPatchType type;
};



enum PacketEnumeration
{
	ID_INTERNAL_PING = 4,
	ID_PING,
	ID_PING_OPEN_CONNECTIONS,
	ID_CONNECTED_PONG,
	ID_PAD1,
	ID_PAD11,
	ID_PAD12,
	ID_REQUEST_STATIC_DATA,
	ID_CONNECTION_REQUEST,
	ID_PAD2,
	ID_SECURED_CONNECTION_RESPONSE,
	ID_SECURED_CONNECTION_CONFIRMATION,
	ID_RPC_MAPPING,
	ID_PAD3,
	ID_PAD5,
	ID_PAD6,
	ID_DETECT_LOST_CONNECTIONS,
	ID_OPEN_CONNECTION_REQUEST,
	ID_OPEN_CONNECTION_REPLY,
	ID_PAD4,
	ID_RPC,
	ID_RPC_REPLY,
	ID_BROADCAST_PINGS,
	ID_SET_RANDOM_NUMBER_SEED,
	ID_CONNECTION_REQUEST_ACCEPTED,
	ID_CONNECTION_ATTEMPT_FAILED,
	ID_NEW_INCOMING_CONNECTION,
	ID_NO_FREE_INCOMING_CONNECTIONS,
	ID_DISCONNECTION_NOTIFICATION,
	ID_CONNECTION_LOST,
	ID_RSA_PUBLIC_KEY_MISMATCH,
	ID_CONNECTION_BANNED,
	ID_INVALID_PASSWORD,
	ID_MODIFIED_PACKET,
	ID_TIMESTAMP,
	ID_PONG,
	ID_RECEIVED_STATIC_DATA,
	ID_REMOTE_DISCONNECTION_NOTIFICATION,
	ID_REMOTE_CONNECTION_LOST,
	ID_REMOTE_NEW_INCOMING_CONNECTION,
	ID_REMOTE_EXISTING_CONNECTION,
	ID_REMOTE_STATIC_DATA,
	// ...
	ID_ADVERTISE_SYSTEM = 51,

	ID_UNOCCUPIED_SYNC = 110,

	ID_PASSENGER_SYNC = 115,
	ID_PLAYER_SYNC = 116,
	ID_AIM_SYNC = 117,
	ID_VEHICLE_SYNC = 118,
	ID_RCON_COMMAND = 119,
	ID_RCON_RESPONCE = 120,
	ID_STATS_UPDATE = 121,
	ID_WEAPONS_UPDATE = 112,
	ID_MARKERS_SYNC,
	ID_SPECTATOR_SYNC = 113,
	ID_TRAILER_SYNC = 114
};

/// These enumerations are used to describe when packets are delivered.
enum PacketPriority
{
	SYSTEM_PRIORITY,   /// \internal Used by RakNet to send above-high priority messages.
	HIGH_PRIORITY,   /// High priority messages are send before medium priority messages.
	MEDIUM_PRIORITY,   /// Medium priority messages are send before low priority messages.
	LOW_PRIORITY,   /// Low priority messages are only sent when no other messages are waiting.
	NUMBER_OF_PRIORITIES
};

/// These enumerations are used to describe how packets are delivered.
/// \note  Note to self: I write this with 3 bits in the stream.  If I add more remember to change that
enum PacketReliability
{
	UNRELIABLE,   /// Same as regular UDP, except that it will also discard duplicate datagrams.  RakNet adds (6 to 17) + 21 bits of overhead, 16 of which is used to detect duplicate packets and 6 to 17 of which is used for message length.
	UNRELIABLE_SEQUENCED,  /// Regular UDP with a sequence counter.  Out of order messages will be discarded.  This adds an additional 13 bits on top what is used for UNRELIABLE.
	RELIABLE,   /// The message is sent reliably, but not necessarily in any order.  Same overhead as UNRELIABLE.
	RELIABLE_ORDERED,   /// This message is reliable and will arrive in the order you sent it.  Messages will be delayed while waiting for out of order messages.  Same overhead as UNRELIABLE_SEQUENCED.
	RELIABLE_SEQUENCED /// This message is reliable and will arrive in the sequence you sent it.  Out or order messages will be dropped.  Same overhead as UNRELIABLE_SEQUENCED.
};

typedef unsigned short PlayerIndex;
#pragma pack(push, 1)
struct PlayerID
{
	///The peer address from inet_addr.
	unsigned int binaryAddress;
	///The port number
	unsigned short port;

	PlayerID& operator = (const PlayerID& input)
	{
		binaryAddress = input.binaryAddress;
		port = input.port;
		return *this;
	}

	bool operator==(const PlayerID& right) const;
	bool operator!=(const PlayerID& right) const;
	bool operator > (const PlayerID& right) const;
	bool operator < (const PlayerID& right) const;
};

/// This represents a user message from another system.
struct Packet
{
	/// Server only - this is the index into the player array that this playerId maps to
	PlayerIndex playerIndex;

	/// The system that send this packet.
	PlayerID playerId;

	/// The length of the data in bytes
	/// \deprecated You should use bitSize.
	unsigned int length;

	/// The length of the data in bits
	unsigned int bitSize;

	/// The data from the sender
	unsigned char* data;

	/// @internal
	/// Indicates whether to delete the data, or to simply delete the packet.
	bool deleteData;
};

/// All RPC functions have the same parameter list - this structure.
struct RPCParameters
{
	/// The data from the remote system
	unsigned char *input;

	/// How many bits long \a input is
	unsigned int numberOfBitsOfData;

	/// Which system called this RPC
	PlayerID sender;

	/// Which instance of RakPeer (or a derived RakServer or RakClient) got this call
	void *recipient;

	/// You can return values from RPC calls by writing them to this BitStream.
	/// This is only sent back if the RPC call originally passed a BitStream to receive the reply.
	/// If you do so and your send is reliable, it will block until you get a reply or you get disconnected from the system you are sending to, whichever is first.
	/// If your send is not reliable, it will block for triple the ping time, or until you are disconnected, or you get a reply, whichever is first.
	 BitStream *replyToSender;
};

/// Store Statistics information related to network usage 
struct RakNetStatisticsStruct
{
	///  Number of Messages in the send Buffer (high, medium, low priority)
	unsigned messageSendBuffer[NUMBER_OF_PRIORITIES];
	///  Number of messages sent (high, medium, low priority)
	unsigned messagesSent[NUMBER_OF_PRIORITIES];
	///  Number of data bits used for user messages
	unsigned messageDataBitsSent[NUMBER_OF_PRIORITIES];
	///  Number of total bits used for user messages, including headers
	unsigned messageTotalBitsSent[NUMBER_OF_PRIORITIES];

	///  Number of packets sent containing only acknowledgements
	unsigned packetsContainingOnlyAcknowlegements;
	///  Number of acknowledgements sent
	unsigned acknowlegementsSent;
	///  Number of acknowledgements waiting to be sent
	unsigned acknowlegementsPending;
	///  Number of acknowledgements bits sent
	unsigned acknowlegementBitsSent;

	///  Number of packets containing only acknowledgements and resends
	unsigned packetsContainingOnlyAcknowlegementsAndResends;

	///  Number of messages resent
	unsigned messageResends;
	///  Number of bits resent of actual data
	unsigned messageDataBitsResent;
	///  Total number of bits resent, including headers
	unsigned messagesTotalBitsResent;
	///  Number of messages waiting for ack (// TODO - rename this)
	unsigned messagesOnResendQueue;

	///  Number of messages not split for sending
	unsigned numberOfUnsplitMessages;
	///  Number of messages split for sending
	unsigned numberOfSplitMessages;
	///  Total number of splits done for sending
	unsigned totalSplits;

	///  Total packets sent
	unsigned packetsSent;

	///  Number of bits added by encryption
	unsigned encryptionBitsSent;
	///  total bits sent
	unsigned totalBitsSent;

	///  Number of sequenced messages arrived out of order
	unsigned sequencedMessagesOutOfOrder;
	///  Number of sequenced messages arrived in order
	unsigned sequencedMessagesInOrder;

	///  Number of ordered messages arrived out of order
	unsigned orderedMessagesOutOfOrder;
	///  Number of ordered messages arrived in order
	unsigned orderedMessagesInOrder;

	///  Packets with a good CRC received
	unsigned packetsReceived;
	///  Packets with a bad CRC received
	unsigned packetsWithBadCRCReceived;
	///  Bits with a good CRC received
	unsigned bitsReceived;
	///  Bits with a bad CRC received
	unsigned bitsWithBadCRCReceived;
	///  Number of acknowledgement messages received for packets we are resending
	unsigned acknowlegementsReceived;
	///  Number of acknowledgement messages received for packets we are not resending
	unsigned duplicateAcknowlegementsReceived;
	///  Number of data messages (anything other than an ack) received that are valid and not duplicate
	unsigned messagesReceived;
	///  Number of data messages (anything other than an ack) received that are invalid
	unsigned invalidMessagesReceived;
	///  Number of data messages (anything other than an ack) received that are duplicate
	unsigned duplicateMessagesReceived;
	///  Number of messages waiting for reassembly
	unsigned messagesWaitingForReassembly;
	///  Number of messages in reliability output queue
	unsigned internalOutputQueueSize;
	///  Current bits per second
	double bitsPerSecond;
	///  connection start time
	RakNetTime connectionStartTime;
};
 

struct HuffmanEncodingTreeNode
{
	unsigned char value;
	unsigned weight;
	HuffmanEncodingTreeNode *left;
	HuffmanEncodingTreeNode *right;
	HuffmanEncodingTreeNode *parent;
};

class HuffmanEncodingTree
{

public:
	HuffmanEncodingTree();
	~HuffmanEncodingTree();

	/// Pass an array of bytes to array and a preallocated BitStream to receive the output
	/// \param [in] input Array of bytes to encode
	/// \param [in] sizeInBytes size of \a input
	/// \param [out] output The bitstream to write to
	//void EncodeArray(unsigned char *input, unsigned sizeInBytes, BitStream * output);

	// Decodes an array encoded by EncodeArray()
	//unsigned DecodeArray(BitStream * input, unsigned sizeInBits, unsigned maxCharsToWrite, unsigned char *output);
	void HuffmanEncodingTree::DecodeArray(unsigned char *input, unsigned sizeInBits, BitStream * output);
	unsigned HuffmanEncodingTree::DecompressAndAllocate(BitStream * input, unsigned char **output);
	//void HuffmanEncodingTree::InsertNodeIntoSortedList(HuffmanEncodingTreeNode * node, DataStructures::LinkedList<HuffmanEncodingTreeNode *> *huffmanEncodingTreeNodeList);
	/// Given a frequency table of 256 elements, all with a frequency of 1 or more, generate the tree
	//void GenerateFromFrequencyTable(unsigned int frequencyTable[256]);

	/// Free the memory used by the tree
	//void FreeMemory(void);

private:

	/// The root node of the tree 

	HuffmanEncodingTreeNode *root;

	/// Used to hold bit encoding for one character


	struct CharacterEncoding
	{
		unsigned char* encoding;
		unsigned short bitLength;
	};

	CharacterEncoding encodingTable[256];

};


class RakClientInterface
{
public:
	virtual ~RakClientInterface() { };
	virtual bool Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer);
	virtual void Disconnect(unsigned int blockDuration, unsigned char orderingChannel ) ;
	virtual void InitializeSecurity(const char *privKeyP, const char *privKeyQ) ;
	virtual void SetPassword(const char *_password) ;
	virtual bool HasPassword(void) const ;
	virtual bool Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel) ;
	virtual bool Send( BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel) ;
	virtual Packet* Receive(void) ;
	virtual void DeallocatePacket(Packet *packet) ;
	virtual void PingServer(void) ;
	virtual void PingServer(const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections) ;
	virtual int GetAveragePing(void) ;
	virtual int GetLastPing(void) const ;
	virtual int GetLowestPing(void) const ;
	virtual int GetPlayerPing(const PlayerID playerId) ;
	virtual void StartOccasionalPing(void) ;
	virtual void StopOccasionalPing(void) ;
	virtual bool IsConnected(void) const ;
	virtual unsigned int GetSynchronizedRandomInteger(void) const ;
	virtual bool GenerateCompressionLayer(unsigned int inputFrequencyTable[256], bool inputLayer) ;
	virtual bool DeleteCompressionLayer(bool inputLayer) ;
	virtual void RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms)) ;
	virtual void RegisterClassMemberRPC(int* uniqueID, void *functionPointer) ;
	virtual void UnregisterAsRemoteProcedureCall(int* uniqueID) ;
	virtual bool RPC(int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp) ;
	virtual bool RPC(int* uniqueID,  BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp) ;
	virtual void Pad(void) ; // XXX: Fix it.
	virtual void SetTrackFrequencyTable(bool b) ;
	virtual bool GetSendFrequencyTable(unsigned int outputFrequencyTable[256]) ;
	virtual float GetCompressionRatio(void) const ;
	virtual float GetDecompressionRatio(void) const ;
	virtual void AttachPlugin(void *messageHandler) ;
	virtual void DetachPlugin(void *messageHandler) ;
	virtual  BitStream * GetStaticServerData(void) ;
	virtual void SetStaticServerData(const char *data, const int length) ;
	virtual  BitStream * GetStaticClientData(const PlayerID playerId) ;
	virtual void SetStaticClientData(const PlayerID playerId, const char *data, const int length) ;
	virtual void SendStaticClientDataToServer(void) ;
	virtual PlayerID GetServerID(void) const ;
	virtual PlayerID GetPlayerID(void) const ;
	virtual PlayerID GetInternalID(void) const ;
	virtual const char* PlayerIDToDottedIP(const PlayerID playerId) const ;
	virtual void PushBackPacket(Packet *packet, bool pushAtHead) ;
	virtual void SetRouterInterface(void *routerInterface) ;
	virtual void RemoveRouterInterface(void *routerInterface) ;
	virtual void SetTimeoutTime(RakNetTime timeMS) ;
	virtual bool SetMTUSize(int size) ;
	virtual int GetMTUSize(void) const ;
	virtual void AllowConnectionResponseIPMigration(bool allow) ;
	virtual void AdvertiseSystem(const char *host, unsigned short remotePort, const char *data, int dataLength) ;
	virtual RakNetStatisticsStruct * const GetStatistics(void) ;
	virtual void ApplyNetworkSimulator(double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance) ;
	virtual bool IsNetworkSimulatorActive(void) ;
	virtual PlayerIndex GetPlayerIndex(void) ;
};







class DrifeitClient
{
public:
	DrifeitClient(void *pDrifeitClientInterface);
	bool RPC(int rpcId,  BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, char orderingChannel = 0, bool shiftTimestamp = false);
	bool Send( BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = UNRELIABLE_SEQUENCED, char orderingChannel = 0);
	void   DrifeitClient::SendMutantDriverSyncData(uint16_t VehicleID, float fPos[3], float fSpeed[3], float fQuaternion[4]);
	RakClientInterface *GetRakClientInterface(void) { return pDrifeitClient; };
	void DrifeitClient::SendFakeDriverSyncDataWithQuaternion(USHORT VehicleID, float fPos[3], float fQuaternion[4], float HealthCar, float Speed[3], WORD key);
	void DrifeitClient::DecodeArray(unsigned char *input, unsigned sizeInBits, BitStream * output);
	unsigned DrifeitClient::DecompressAndAllocate(BitStream * input, unsigned char **output);
	void DrifeitClient::SendEnterVehicle(int vehID, int as);
	void DrifeitClient::SendDamageVehicle(WORD vehicleID, DWORD panel, DWORD door, BYTE lights, BYTE tires);
	void DrifeitClient::SendExitVehicle(int vehID);
	void DrifeitClient::SendFakeDriverSyncData44(USHORT VehicleID, float fPos[3], float HealthCar, float Speed[3], WORD key);
	void DrifeitClient::SendFakeUnnocupiedFullSyncData(stUnoccupiedData *picSync, int iUseCarPos);
	void DrifeitClient::SendFakeUnoccupiedSyncData1(int carhnd, float fpos[3], float HealthCar, float speed[3]);
	void DrifeitClient::SendWeaponUpdateSync(BYTE weaponslot, BYTE weaponid, WORD ammo);




	//DrifeitRakClientInterface *GetInterface(void) { return pDrifeitClient; };
private:
	RakClientInterface *pDrifeitClient;
}; 
 


