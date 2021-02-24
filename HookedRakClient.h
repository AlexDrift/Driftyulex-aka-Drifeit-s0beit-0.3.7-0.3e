

class HookedRakClientInterface/* : public OrigRakClientInterface*/ 
{
public:
	virtual ~HookedRakClientInterface() { };
	virtual bool Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer );
	virtual void Disconnect( unsigned int blockDuration, unsigned char orderingChannel=0 );
	virtual void InitializeSecurity( const char *privKeyP, const char *privKeyQ );
	virtual void SetPassword( const char *_password );
	virtual bool HasPassword( void ) const;
	virtual bool Send( const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel );
	virtual bool Send( BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel );
	virtual Packet* Receive( void );
	virtual void DeallocatePacket( Packet *packet );
	virtual void PingServer( void );
	virtual void PingServer( const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections );
	virtual int GetAveragePing( void );
	virtual int GetLastPing( void ) const;
	virtual int GetLowestPing( void ) const;
	virtual int GetPlayerPing( const PlayerID playerId );
	virtual void StartOccasionalPing( void );
	virtual void StopOccasionalPing( void );
	virtual bool IsConnected( void ) const;
	virtual unsigned int GetSynchronizedRandomInteger( void ) const;
	virtual bool GenerateCompressionLayer( unsigned int inputFrequencyTable[ 256 ], bool inputLayer );
	virtual bool DeleteCompressionLayer( bool inputLayer );
	virtual void RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms));
	virtual void RegisterClassMemberRPC( int* uniqueID, void *functionPointer );
	virtual void UnregisterAsRemoteProcedureCall( int* uniqueID );
	virtual bool RPC( int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp );
	virtual bool RPC( int* uniqueID,  BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp );
	virtual void Pad( void );
	virtual void SetTrackFrequencyTable( bool b );
	virtual bool GetSendFrequencyTable( unsigned int outputFrequencyTable[ 256 ] );
	virtual float GetCompressionRatio( void ) const;
	virtual float GetDecompressionRatio( void ) const;
	virtual void AttachPlugin(void *messageHandler);
	virtual void DetachPlugin(void *messageHandler);
	virtual  BitStream * GetStaticServerData( void );
	virtual void SetStaticServerData( const char *data, const int length );
	virtual  BitStream * GetStaticClientData( const PlayerID playerId );
	virtual void SetStaticClientData( const PlayerID playerId, const char *data, const int length );
	virtual void SendStaticClientDataToServer( void );
	virtual PlayerID GetServerID( void ) const;
	virtual PlayerID GetPlayerID( void ) const;
	virtual PlayerID GetInternalID( void ) const;
	virtual const char* PlayerIDToDottedIP( const PlayerID playerId ) const;
	virtual void PushBackPacket( Packet *packet, bool pushAtHead );
	virtual void SetRouterInterface(void *routerInterface);
	virtual void RemoveRouterInterface(void *routerInterface);
	virtual void SetTimeoutTime(RakNetTime timeMS);
	virtual bool SetMTUSize( int size );
	virtual int GetMTUSize( void ) const;	
	virtual void AllowConnectionResponseIPMigration( bool allow );
	virtual void AdvertiseSystem( const char *host, unsigned short remotePort, const char *data, int dataLength );
	virtual RakNetStatisticsStruct * const GetStatistics( void );
	virtual void ApplyNetworkSimulator( double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance);
	virtual bool IsNetworkSimulatorActive( void );
	virtual PlayerIndex GetPlayerIndex( void );
	uint8_t GetPacketID1(Packet *p);
};
BYTE GetPacketID(Packet *p);



extern class cDebugTracer DebugThread;


enum eDebugThread
{
	DEBUG_THREAD_RENDER,
	DEBUG_THREAD_BEMOD,
	DEBUG_THREAD_CHAT_LOGIN,
	DEBUG_THREAD_CHAT_UPDATE,
	DEBUG_THREAD_RAKNET,
	DEBUG_THREAD_MAIN_GAME,
	DEBUG_THREAD_DRONE,
	DEBUG_THREAD_ALL,
};


class cDebugTracer
{


	struct stDebugTrace
	{
		std::string trace_name;
		DWORD tick;
	};

	typedef std::vector<stDebugTrace> thread_trace;

	static const int trace_vect_len = 8;

	thread_trace trace_vect[trace_vect_len];

public:


	void push_trace_func(eDebugThread thread, std::string name);
	void clear_tracing(eDebugThread thread);
	void LogDebug();

};

