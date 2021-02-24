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
struct gta_cheat 
{
	uint8_t		*addr;
	const char	*name;
};

USHORT VehicleID;

struct stPlayerInfo
{
	int iIsConnected;
	int iIsStreamedIn;
	int iGotMarkersPos;
	char szPlayerName[20];
	int iScore;
	DWORD dwPing;
	int iAreWeInAVehicle;
	unsigned int uiChallenge;

	// STORED INFO
	//ONFOOT_SYNC_DATA onfootData;
	//INCAR_SYNC_DATA incarData;
	//PASSENGER_SYNC_DATA passengerData;
	//AIM_SYNC_DATA aimData;
	//UNOCCUPIED_SYNC_DATA unocData;
};


int		cheat_panic ( void );
void	cheat_prevent_freeze ( void );
void	cheat_teleport ( const float pos[3], int interior_id );
void	cheat_teleport_nearest_car ( void );
void	cheat_handle_misc ( void );
void	cheat_handle_debug ( HWND wnd );
void	cheat_handle_spoof_weapon ( void );
void	cheat_handle_weapon_disable ( void );
void	cheat_handle_freeze_vehicles ( struct vehicle_info *vehicle_info, struct actor_info *actor_info );
void	cheat_handle_unlock ( void );
void	cheat_handle_hp ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff );
void	cheat_handle_stick ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff );
void	cheat_handle_money ( void );
void	cheat_handle_weapon ( void );
void	cheat_handle_teleport ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff );
void	cheat_handle_checkpoint ( void );
void	cheat_handle_unfreeze ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff );
void	cheat_handle_emo ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff );
void	cheat_handle_exit_vehicle ( struct vehicle_info *vehicle_info, struct actor_info *actor_info );
// samp only
void	cheat_handle_antiHijack ( actor_info *ainfo, vehicle_info *veh, float time_diff );
void SendFakeOnfootSyncData ( float coord[3], float speed[3] );
void cheat_handle_carspam ();
void cheat_handle_pulsedweapon ();
void cheat_handle_crasher ();
void cheat_handle_fake ();
void cheat_handle_skin_changer ();
void cheat_handle_respavner ();
void cheat_handle_pic ();
void cheat_handle_rcon () ;
void cheat_handle_ddos (); 
void cheat_handle_pulsedisk ();
void cheat_handle_qqqq ();
void cheat_handle_jos ();
void cheat_handle_dri ();
void cheat_handle_crh ();
void cheat_handle_lag ();
void cheat_handle_lags ();
void cheat_handle_cccc ();
void cheat_handle_gggg ();
void    cheat_handle_surfer ();
void cheat_handle_grt ();
void cheat_handle_ssss ();
void cheat_handle_ffff ();
void SendFakeDriverSyncData( float coord[3] );
void SendEnterVehicleNotifications(USHORT VehicleID);
void SendFakeUnoccupiedSyncData(USHORT VehicleID, float fPos[3]);
void cheat_handle_pickmaasssssswqzzq141aaazzzv();
void cheat_handle_pickmaasssssswqzzq141aaazzzvg();
void cheat_handle_pickmaasssssswqzzq141aaazzzvg1();
void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmmm();
void cheat_handle_vehcomponent_crasher32();
void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmm();
void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmmmm();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasEWWEaswewedffdll1212WEWEWE();
void cheat_handle_grtdfdfdsds();
void cheat_handle_pickmaasssssswqzzq141aa1112111qbb();
void cheat_handle_pickmaasssssswqzzq141aa1112111qb();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasdsaswewell();
void cheat_handle_pickmaasssssswqzzq141aa1112111qbbb();
void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzggfg();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewe4554();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewe();
void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzggfgdfdff();
void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzffffvvv();
void cheat_handle_grtdfdf();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll1212();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewell();
void cheat_handle_picdddkmaasssssswqzzq141aa11121kk1czzzfm11();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll1212WEWEWE();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll121reer2();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewell1212();
void cheat_handle_pickmaasssssswqzzq141aa1112111qasas();
void SendFakeTrailerData(vehicle_info *vehicle, float fpos[3], float HealthCar, float Speed[3]);
void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfm();
void cheat_handle_bike_crasher();
void cheat_handle_pAAAsSA1gjhjhg();
void cheat_handle_picdddkmaasssssswqzzq141aa11121kk1czzzfm();
void cheat_handle_pickmaggfasssssswqzzq141aa1112111qasas();
void cheat_handle_deathb();
void cheat_handle_pAAAsSA1gjhjhgjjjj();
void cheat_handle_pickmaa();
 void cheat_handle_crh1 () ;
	  void cheat_handle_crh2 () ;
void crashRCON();
void onlinegraph();
void cheat_handle_pickm2();
void cheat_handle_pickm21();
void cheat_handle_aaaaa();
void DamageVehicle(USHORT VehicleID, bool vehPanelStatus, bool vehDoorStatus, int vehLightStatus, int vehTireStatus, int vehTireTest, int vehTireTests) ;
void cheat_handle_spawner();
void cheat_handle_pickm();
void cheat_handle_vehcomponent_crasher ();
void cheat_handle_vehcomponent_crasher1 ();
void cheat_handle_vehcomponent_crasher2 ();
void cheat_handle_pickm1();
void cheat_handle_pickm13() ;
void cheat_handle_vehcomponent_crasher21 ();
void cheat_handle_pickm216()  ;
void cheat_handle_pickm2161() ;
void gen_random(char *s, const int len);
void cheat_handle_pickmaaaa();
 void cheat_handle_pickmaaaas();
 void cheat_handle_pAAA() ;
 void cheat_handle_crh25a () ;
 void SendSpectatorData(float fPos[3]);
 void cheat_handle_crh25ass () ;
 void cheat_iTroll();
 void cheat_handle_itroll_targetfinder ();
 void cheat_iTrollc();
 void cheat_handle_itroll_targetfinderc ();
 void cheat_iTrolls();
 void cheat_handle_itroll_targetfinders ();
 #pragma once

extern void cheat_handle_aim(actor_info* info);
void							CalcScreenCoors ( D3DXVECTOR3 *vecWorld, D3DXVECTOR3 *vecScreen );
void							CalcWorldCoors ( D3DXVECTOR3 *vecScreen, D3DXVECTOR3 *vecWorld );
void renderVehicleTags ( void );
void RenderPickupTexts ( void );
void RenderObjectTexts ( void );
 void cheat_handle_pickm21ss();
 void cheat_handle_pAAAs() ;
 void cheat_handle_pAAAsee();
 void cheat_handle_pAAAsSA();
void cheat_handle_pAAAsSA1();
void cheat_handle_pickmaasssssswq();
void cheat_handle_pickmaasssssswqzz();  
 void cheat_handle_pickmaasssssswqzzq();
  void cheat_handle_pickmaasssssswqzzq1();
  void cheat_handle_pickmaasssssswqzzq14();  
   void cheat_handle_pickmaasssssswqzzq141();  
    void cheat_handle_pickmaasssssswqzzq1411();
	void cheat_handle_pickmaasssssswqzzq141a(); 
	 void cheat_handle_pickmaasssssswqzzq141aa();
	  void cheat_handle_pickmaasssssswqzzq141aaa();
	 void  cheat_handle_pickmaasssssswqzzq141aa11();
	 void cheat_handle_pickmaasssssswqzzq141aa1112();
	 void cheat_handle_pickmaasssssswqzzq141aa11121();
	 void cheat_handle_pickmaasssssswqzzq141aa111211();
	 void cheat_handle_pickmaasssssswqzzq141aa1112111();
	 void cheat_handle_pickmaasssssswqzzq141aa11121111();
	 void cheat_handle_pickmaasssssswqzzq141aa111211111();
	 void cheat_handle_pickmaasssssswqzzq141aa1112111q();
	 void cheat_handle_pickmaasssssswqzzq141aa111211x();  
	 void cheat_handle_pickmaasssssswqzzq141aa111211x1();
	 void cheat_handle_pickmaasssssswqzzq141aa111211vvc();  
	 void cheat_handle_pickmaasssssswqzzq141aa111211xx();  
	 void cheat_handle_pickmaasssssswqzzq141aa111211xx1();
	 void cheat_handle_pickmaasssssswqzzq141aa11121kk1(); 
	 void cheat_handle_pickmaasssssswqzzq141aa11121kk1c();  
	 void cheat_handle_pickmaasssssswqzzq141aa11121kk1cz();
	 void cheat_handle_pickmaasssssswqzzq141aa11121kk1czz(); 
	void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzz();
	void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzf();
	void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzff(); 
	void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfff();
	void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzffff(); 
	 void sendServerCommand(char *szCommand);
	 void cheat_handle_pickmaasssssswqzzq141aaazzz();  
	  void cheat_handle_pickmaasssssswqzzq141aaazzz4343();  
	  void cheat_handle_pickmaasssssswqzzq141aaazzz2323();
	  void cheat_handle_pickmaasssssswqzzq141aaazzz2323rere();
	   void cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasae();
	   void cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaebb();
		   void cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaebb1();
		   void cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqw();
		   void cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwe();
		   void cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwer();
		   void cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaejj();
		   void cheat_handle_pickmaasssssswqzzq141aa11m(); 
			    void cheat_handle_pickmaasssssswqzzq141aa11mm() ;
				void cheat_handle_pickmaasssssswqzzq141aa11mq();
				 void cheat_handle_pickmaasssssswqzzq14l();
				 void cheat_handle_pickmaasssssswqzzq14l1();
				 void cheat_handle_pickmaasssssswqzzq14l2();
				 void cheat_handle_pickmaasssssswqzzq14l2d();
				 void cheat_handle_pAAAsSA1d();
				 void cheat_handle_pickmaasssssswqzzq141aa1112111qasas5656ytty();
				 void cheat_handle_pickmaasssssswqzzq141aa1112111qasas5656ytty3434();
				 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwerdfdf();








				 
 class tVector
{
public:

	float X, Y, Z;

	tVector()	{ this->X = 0.0f; this->Y = 0.0f; this->Z = 0.0f; };
	tVector ( float a_float_X, float a_float_Y, float a_float_Z )	{ this->X = a_float_X; this->Y = a_float_Y; this->Z = a_float_Z; };

	tVector& operator= ( const tVector& a_Vector ) { this->X = a_Vector.X; this->Y = a_Vector.Y; this->Z = a_Vector.Z; return *this; }

	tVector operator+ ( const tVector& a_Vector ) const { return tVector ( this->X + a_Vector.X, this->Y + a_Vector.Y, this->Z + a_Vector.Z ); }
	tVector& operator+= ( const tVector& a_Vector ) { this->X += a_Vector.X; this->Y += a_Vector.Y; this->Z+= a_Vector.Z; return *this; };

	tVector operator- ( const tVector& a_Vector ) const { return tVector ( this->X - a_Vector.X, this->Y - a_Vector.Y, this->Z - a_Vector.Z ); }
	tVector& operator-= ( const tVector& a_Vector ) { this->X -= a_Vector.X; this->Y -= a_Vector.Y; this->Z -= a_Vector.Z; return *this; };

	tVector operator* ( const tVector& a_Vector ) const { return tVector ( this->X * a_Vector.X, this->Y * a_Vector.Y, this->Z * a_Vector.Z ); }
	tVector& operator*= ( const tVector& a_Vector ) { this->X *= a_Vector.X; this->Y *= a_Vector.Y; this->Z *= a_Vector.Z; return *this; };

	tVector operator/ ( const tVector& a_Vector ) const { return tVector ( this->X / a_Vector.X, this->Y / a_Vector.Y, this->Z / a_Vector.Z ); }
	tVector& operator/= ( const tVector& a_Vector ) { this->X /= a_Vector.X; this->Y /= a_Vector.Y; this->Z /= a_Vector.Z; return *this; };

	tVector operator/ ( const float a_Value ) const { return tVector ( this->X / a_Value, this->Y / a_Value, this->Z / a_Value ); }
	tVector& operator/= ( const float a_Value ) { this->X /= a_Value; this->Y /= a_Value; this->Z /= a_Value; return *this; };

	float GetLength ( void )
	{
		return sqrt ( X * X + Y * Y + Z * Z );
	};
		
	float GetDistanceFrom ( tVector* a_Vector )
	{
		return tVector ( X - a_Vector->X, Y - a_Vector->Y, Z - a_Vector->Z ).GetLength();
	}
};

typedef struct QuaternionVector_t
{
	float W, X, Y, Z;
} tQuaternionVector;

void QuaternionToMatrix( float &quaterW, float &quaterX, float &quaterY, float &quaterZ, tVector* right, tVector* up, tVector* at );
void MatrixToQuaternion( tVector* right, tVector* up, tVector* at, float &quaterW, float &quaterX, float &quaterY, float &quaterZ );