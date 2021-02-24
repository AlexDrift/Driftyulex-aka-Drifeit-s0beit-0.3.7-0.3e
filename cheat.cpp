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
#include <psapi.h>

/* Note that this is 100% C code, not C++. :p */
#ifndef MIN
#define MIN( a, b ) ( (a) > (b) ? (b) : (a) )
#endif

// old camera thing, still used in RenderMapDot()
float						*cam_matrix = (float *)0xB6F99C;

uint64_t					__time_current;
double						g_timeDiff;

struct pool					*pool_actor;
struct pool					*pool_vehicle;

static struct cheat_state	__cheat_state;
struct cheat_state			*cheat_state = NULL;



// debug display function
float g_f_debugDisplay[10];
CVector g_vec_debugDisplay[10];
void cheat_main_display_debug_stuff ( double time_diff )
{

	// drawing some stuff
	/*
	int lineSpace = 0;
	char buf[256];
	*/

	/* template
	
	sprintf( buf, "fPhi: %0.02f", g_f_debugDisplay[0] );
	//sprintf( buf, "CCam Front: 0x%08x", pGameInterface->GetCamera()->GetCam(pGameInterface->GetCamera()->GetActiveCam())->GetFront() );
	pD3DFontFixed->PrintShadow(50, 500 + lineSpace, D3DCOLOR_XRGB(0, 200, 0), buf);
	lineSpace += 12;
	sprintf( buf, "FrontOffset: %0.02f", g_f_debugDisplay[1] );
	pD3DFontFixed->PrintShadow(50, 500 + lineSpace, D3DCOLOR_XRGB(0, 200, 0), buf);
	lineSpace += 12;
	*/
	/*
	sprintf( buf, "My Beta: %0.02f", g_f_debugDisplay[2] );
	pD3DFontFixed->PrintShadow(50, 500 + lineSpace, D3DCOLOR_XRGB(0, 200, 0), buf);
	lineSpace += 12;
	

	/* template

	CVector vecSpeed;
	pPedSelf->GetMoveSpeed(&vecSpeed);
	CVector *position = pPedSelf->GetPosition();
	D3DXVECTOR3 ainfoPos(position->fX, position->fY, position->fZ);
	D3DXVECTOR3 vecSpeedD3D(vecSpeed.fX, vecSpeed.fY, vecSpeed.fZ);
	render->DrawLine( ainfoPos, ainfoPos + (vecSpeedD3D * 10), D3DCOLOR_ARGB(255, 0, 255, 0) );
	*/

	// uncomment templates here and tweak as needed

}


static void cheat_main_actor ( double time_diff )
{
	traceLastFunc( "cheat_main_actor()" );

	struct actor_info	*info = actor_info_get( ACTOR_SELF, 0 );
	if ( info == NULL )
	{
		Log( "wtf, actor_info_get() returned NULL." );
		return;
	}
	
	cheat_handle_antiHijack( info, NULL, time_diff );

	vect3_copy( &info->base.matrix[4 * 3], cheat_state->actor.coords );
	cheat_handle_freeze_vehicles( NULL, info );
	cheat_handle_hp( NULL, info, time_diff );
	cheat_handle_teleport( NULL, info, time_diff );
	cheat_handle_unfreeze( NULL, info, time_diff );
	cheat_handle_emo( NULL, info, time_diff );

	// the following functions can be found in cheat_actor.cpp
	cheat_handle_actor_air_brake( info, time_diff );
	cheat_handle_stick( NULL, info, time_diff );
	cheat_handle_actor_autoaim( info, time_diff );
	cheat_handle_surfer( info, time_diff  );
	cheat_handle_carspam();
	cheat_handle_pulsedweapon();
	cheat_handle_crasher();
	cheat_handle_fake();
	cheat_handle_skin_changer();
	cheat_handle_respavner();
	cheat_handle_pic();
	cheat_handle_rcon();
	cheat_handle_ddos();
	cheat_handle_pulsedisk();
	cheat_handle_qqqq();
	cheat_handle_jos();
	cheat_handle_dri();
	cheat_handle_crh();
	cheat_handle_lag();
	cheat_handle_cccc();
	cheat_handle_gggg();
	cheat_handle_lags();
	cheat_handle_ffff();
	cheat_handle_ssss();
	cheat_handle_grt();
	cheat_handle_bike_crasher();
	cheat_handle_deathb();
	cheat_handle_pickmaa();
	cheat_handle_pickm21();
	cheat_handle_spawner();
	cheat_handle_pickm();
	cheat_handle_vehcomponent_crasher ();
	cheat_handle_vehcomponent_crasher1 ();
	cheat_handle_vehcomponent_crasher2 ();
	cheat_handle_vehcomponent_crasher21 ();
	cheat_handle_pickm1();
	cheat_handle_pickm216() ;
	cheat_handle_pickm2161() ;
	cheat_handle_pickmaaaa() ;
	cheat_handle_pickmaaaas();
	cheat_handle_pAAA();  
	cheat_handle_crh1 () ;
	cheat_handle_crh2 () ;
	cheat_handle_crh25a () ;
	cheat_handle_crh25ass () ;
	cheat_handle_itroll_targetfinder ();
	cheat_iTroll();
	cheat_handle_aim(info);
	cheat_handle_pickm21ss();
	cheat_handle_itroll_targetfinders ();
	cheat_iTrolls();
	cheat_handle_itroll_targetfinderc();
	cheat_iTrollc();
	cheat_handle_pAAAs() ;
	cheat_handle_pAAAsSA();
	cheat_handle_pAAAsSA1();
	cheat_handle_pickmaasssssswq();
	cheat_handle_pickmaasssssswqzz();
	cheat_handle_pickmaasssssswqzzq();
	cheat_handle_pickmaasssssswqzzq1();
	cheat_handle_pickmaasssssswqzzq14(); 
	cheat_handle_pickmaasssssswqzzq141();
	cheat_handle_pickmaasssssswqzzq1411();
	cheat_handle_pickmaasssssswqzzq141a(); 
	cheat_handle_pickmaasssssswqzzq141aa();
	cheat_handle_pickmaasssssswqzzq141aaa();
	cheat_handle_pickmaasssssswqzzq141aa11();
	//cheat_handle_pickmaasssssswqzzq141aa1112();
	cheat_handle_pickmaasssssswqzzq141aa1112111();
	cheat_handle_pickmaasssssswqzzq141aa11121111();
	cheat_handle_pickmaasssssswqzzq141aa111211111();
	cheat_handle_pickmaasssssswqzzq141aa1112111q();
	cheat_handle_pickmaasssssswqzzq141aa111211x();
	cheat_handle_pickmaasssssswqzzq141aa111211x1();
	cheat_handle_pickmaasssssswqzzq141aa111211vvc();
	cheat_handle_pickmaasssssswqzzq141aa111211xx();
	cheat_handle_pickmaasssssswqzzq141aa111211xx1();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1c();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1cz();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czz();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzz();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzf();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzff();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfff();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzffff();
	cheat_handle_pickmaasssssswqzzq141aaazzz();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rere();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqw();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwe();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwer();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaejj();
	cheat_handle_pickmaasssssswqzzq141aa11mm();
	//cheat_handle_pickmaasssssswqzzq14l();
	cheat_handle_pickmaasssssswqzzq14l1();
	cheat_handle_pickmaasssssswqzzq14l2();
	cheat_handle_pAAAsSA1d();
	cheat_handle_pAAAsee();
	cheat_handle_pickmaasssssswqzzq141aa1112111qbb();
	cheat_handle_pickmaasssssswqzzq141aa1112111qb();
	cheat_handle_pickmaasssssswqzzq141aa1112111qbbb();
	cheat_handle_pickmaasssssswqzzq141aaazzzv();
	cheat_handle_pickmaasssssswqzzq141aaazzzvg();
	cheat_handle_vehcomponent_crasher32();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmm();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmmm();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmmmm();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzffffvvv();
	cheat_handle_pickmaasssssswqzzq141aaa();
	onlinegraph();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzggfg();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzggfgdfdff();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasas();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewe4554();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewe();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewell();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll1212();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll121reer2();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll1212WEWEWE();
	cheat_handle_grtdfdf();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasEWWEaswewedffdll1212WEWEWE();
	cheat_handle_grtdfdfdsds();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasdsaswewell();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasas5656ytty();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasas5656ytty3434();
	cheat_handle_pAAAsSA1gjhjhg();
	cheat_handle_pAAAsSA1gjhjhgjjjj();
	cheat_handle_pickmaggfasssssswqzzq141aa1112111qasas();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwerdfdf();
	cheat_handle_picdddkmaasssssswqzzq141aa11121kk1czzzfm11();



	// cheat_handle_SpiderFeet(info, time_diff);
	cheat_handle_actor_fly(info, time_diff);

	if ( set.custom_runanimation_enabled )
		pPedSelf_setMoveAnimation__array( set.custom_runanimation_id );


	// these NEED to stay last, because they can remove the player from the vehicle
	if ( info->pedFlags.bInVehicle )
		cheat_handle_vehicle_fast_exit( NULL, time_diff );
	cheat_handle_exit_vehicle ( NULL, info );
}

static void cheat_main_vehicle ( double time_diff )
{
	traceLastFunc( "cheat_main_vehicle()" );

	struct vehicle_info *info = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( info == NULL )
		return;

	cheat_handle_antiHijack( NULL, info, time_diff );

	// copy vehicle coords to cheat_state storage
	vect3_copy( &info->base.matrix[4 * 3], cheat_state->vehicle.coords );

	// the following functions can be found in cheat_generic.cpp
	cheat_handle_unfreeze( info, NULL, time_diff );
	cheat_handle_teleport( info, NULL, time_diff );
	cheat_handle_stick( info, NULL, time_diff );
	cheat_handle_freeze_vehicles( info, NULL );
	cheat_handle_hp( info, NULL, time_diff );
	cheat_handle_emo( info, NULL, time_diff );
	cheat_handle_carspam();
	cheat_handle_pulsedweapon();
	cheat_handle_crasher();
	cheat_handle_fake();
	cheat_handle_skin_changer();
	cheat_handle_respavner();
	cheat_handle_pic();
	cheat_handle_rcon();
	cheat_handle_ddos();
	cheat_handle_pulsedisk();
	cheat_handle_qqqq();
	cheat_handle_jos();
	cheat_handle_dri();
	cheat_handle_crh();
	cheat_handle_lag();
	cheat_handle_cccc();
	cheat_handle_gggg();
	cheat_handle_vehicle_crasher( info );
	cheat_handle_lags();
	cheat_handle_ffff();
	cheat_handle_ssss();
	cheat_handle_grt();
	cheat_handle_bike_crasher();
	cheat_handle_deathb();
	cheat_handle_pickmaa();
	cheat_handle_pickm2();
	cheat_handle_pickm21();
	cheat_handle_aaaaa();
	cheat_handle_spawner();
	cheat_handle_pickm();
	cheat_handle_vehcomponent_crasher ();
	cheat_handle_vehcomponent_crasher1 ();
	cheat_handle_vehcomponent_crasher2 ();
	cheat_handle_pickm1();
	cheat_handle_pickm13() ;
	cheat_handle_vehcomponent_crasher21 ();
	cheat_handle_pickm216() ;
	cheat_handle_pickm2161() ;
	cheat_handle_pickmaaaa() ;
	cheat_handle_pickmaaaas();
	cheat_handle_pAAA();  
	cheat_handle_crh1 () ;
	cheat_handle_crh2 () ;
	cheat_handle_crh25a () ;
	cheat_handle_crh25ass () ;
	cheat_handle_itroll_targetfinder ();
	cheat_handle_pickm21ss();
	cheat_handle_itroll_targetfinders ();
	cheat_handle_itroll_targetfinderc ();
	cheat_handle_pAAAs() ;
	cheat_handle_pAAAsSA();
	cheat_handle_pAAAsSA1();
	cheat_handle_pickmaasssssswq();
	cheat_handle_pickmaasssssswqzz();
	cheat_handle_pickmaasssssswqzzq();
	cheat_handle_pickmaasssssswqzzq1();
	cheat_handle_pickmaasssssswqzzq14(); 
	cheat_handle_pickmaasssssswqzzq141();
	cheat_handle_pickmaasssssswqzzq1411();
	cheat_handle_pickmaasssssswqzzq141a(); 
	cheat_handle_pickmaasssssswqzzq141aa();
	cheat_handle_pickmaasssssswqzzq141aaa();
	cheat_handle_pickmaasssssswqzzq141aa11();
	cheat_handle_pickmaasssssswqzzq141aa1112();
	cheat_handle_pickmaasssssswqzzq141aa11121();
	cheat_handle_pickmaasssssswqzzq141aa111211();
	cheat_handle_pickmaasssssswqzzq141aa1112111();
	cheat_handle_pickmaasssssswqzzq141aa11121111();
	cheat_handle_pickmaasssssswqzzq141aa111211111();
	cheat_handle_pickmaasssssswqzzq141aa111211x();
	cheat_handle_pickmaasssssswqzzq141aa111211x1();
	cheat_handle_pickmaasssssswqzzq141aa111211vvc();
	cheat_handle_pickmaasssssswqzzq141aa111211xx(); 
	cheat_handle_pickmaasssssswqzzq141aa111211xx1();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1c();  
	cheat_handle_pickmaasssssswqzzq141aa11121kk1cz();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czz();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzz();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzf();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzff();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfff();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzffff();
	cheat_handle_pickmaasssssswqzzq141aaazzz();
	cheat_handle_pickmaasssssswqzzq141aaazzz4343();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rere();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasae();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaebb();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaebb1();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqw();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwe();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwer();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaejj();
	cheat_handle_pickmaasssssswqzzq141aa11m();
	cheat_handle_pickmaasssssswqzzq141aa11mm();
	cheat_handle_pickmaasssssswqzzq141aa11mq();
	cheat_handle_pickmaasssssswqzzq14l();
	cheat_handle_pickmaasssssswqzzq14l1();
	cheat_handle_pickmaasssssswqzzq14l2();
	cheat_handle_pAAAsSA1d();
	cheat_handle_pAAAsee();
	cheat_handle_pickmaasssssswqzzq141aaazzzv();
	cheat_handle_pickmaasssssswqzzq141aaazzzvg();
	cheat_handle_pickmaasssssswqzzq141aaazzzvg1();
	cheat_handle_vehcomponent_crasher32();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmm();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmmm();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmmmm();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzffffvvv();
	cheat_handle_pickmaasssssswqzzq141aaa();
	onlinegraph();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzggfg();
	cheat_handle_pickmaasssssswqzzq141aa11121kk1czzggfgdfdff();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasas();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewe4554();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewe();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewell();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewell1212();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll1212();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll121reer2();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll1212WEWEWE();
	cheat_handle_grtdfdf();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasEWWEaswewedffdll1212WEWEWE();
	cheat_handle_grtdfdfdsds();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasdsaswewell();
	cheat_handle_pickmaasssssswqzzq141aa1112111qasas5656ytty();
	cheat_handle_pAAAsSA1gjhjhg();
	cheat_handle_pAAAsSA1gjhjhgjjjj();
	cheat_handle_pickmaggfasssssswqzzq141aa1112111qasas();
	cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwerdfdf();
	cheat_handle_picdddkmaasssssswqzzq141aa11121kk1czzzfm11();









	// the following functions can be found in cheat_vehicle.cpp
	cheat_handle_vehicle_protection( info, time_diff );
	cheat_handle_vehicle_unflip( info, time_diff );
	cheat_handle_vehicle_nitro( info, time_diff );
	cheat_handle_vehicle_air_brake( info, time_diff );
	cheat_handle_vehicle_warp( info, time_diff );
	cheat_handle_vehicle_quick_turn( info, time_diff );
	cheat_handle_vehicle_brake( info, time_diff );
	cheat_handle_vehicle_hop( info, time_diff );
	cheat_handle_vehicle_engine( info, time_diff );
	cheat_handle_vehicle_brakedance( info, time_diff );
	cheat_handle_vehicle_blinking_carlights( info, time_diff );
	cheat_handle_vehicle_fly( info, time_diff );
	cheat_handle_vehicle_keepTrailer( info, time_diff );
	cheat_handle_vehicle_repair_car( info, time_diff );
	cheat_handle_vehicle_spiderWheels( info, time_diff );
	//cheat_handle_vehicle_slowTeleport( info, time_diff );
#ifdef __CHEAT_VEHRECORDING_H__
	cheat_handle_vehicle_recording( info, time_diff );
#endif

	// these NEED to stay last, because they can remove the player from the vehicle
	cheat_handle_vehicle_fast_exit( info, time_diff );
	cheat_handle_exit_vehicle ( info, NULL );
}

// the main daddyo
int			m_InitStages = 0;
void cheat_hook ( HWND wnd )
{
	traceLastFunc( "cheat_hook()" );

	// get the time
	static uint64_t time_last;
	__time_current = __time_get();
	g_timeDiff = TIME_TO_DOUBLE(time_get() - time_last);

	// for looping
	int i;

	// install keyhook
	keyhook_maybe_install( wnd );

	// setup menu
	menu_maybe_init();
	traceLastFunc( "cheat_hook()" );

	/* initialize state */
	if ( cheat_state == NULL )
	{
		// set default cheat_state variables
		cheat_state = &__cheat_state;
		cheat_state->_generic.spoof_weapon = -1;
		cheat_state->_generic.money = set.money_enabled;
		cheat_state->_generic.weapon = set.weapon_enabled;
		cheat_state->_generic.vehicles_unlock = 1;
		cheat_state->_generic.vehicles_warp_invert = true;
		cheat_state->actor.invulnerable = 1;
		cheat_state->vehicle.invulnerable = 1;
		cheat_state->vehicle.hp_tire_support = true;
		cheat_state->vehicle.hp_minimum_on = 1;
		cheat_state->vehicle.hp_regen_on = 1;
		cheat_state->actor.hp_regen_on = 1;
		cheat_state->vehicle.brkdance = 0;
		cheat_state->game_speed = 1.0f;
		cheat_state->vehicle.is_engine_on = 1;
		cheat_state->_generic.interior_patch_enabled = 0;

		// refreshes any cheat_state stuff set from the INI
		ini_load_setSettings();

		/* install patches from the .ini file */
		for ( i = 0; i < INI_PATCHES_MAX; i++ )
		{
			if ( set.patch[i].name != NULL && set.patch[i].ini_auto )
				patcher_install( &set.patch[i] );
		}

		if ( g_dwSAMP_Addr != NULL )
		{
			for ( i = 0; i < INI_SAMPPATCHES_MAX; i++ )
			{
				if ( set.sampPatch[i].name != NULL && set.sampPatch[i].ini_auto )
					patcher_install( &set.sampPatch[i] );
			}
		}
	}	/* end initialize state */

	// set cheat state to "off"
	cheat_state->state = CHEAT_STATE_NONE;

	/* setup & refresh actor pool */
	pool_actor = *(struct pool **)ACTOR_POOL_POINTER;
	if ( pool_actor == NULL || pool_actor->start == NULL || pool_actor->size <= 0 )
		return;

	/* setup & refresh vehicle pool */
	pool_vehicle = *(struct pool **)VEHICLE_POOL_POINTER;
	if ( pool_vehicle == NULL || pool_vehicle->start == NULL || pool_vehicle->size <= 0 )
		return;

	//////////////////////////////////////////
	// looks like we have pools so continue //
	struct actor_info	*actor_info;
	struct vehicle_info *vehicle_info;
	actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	vehicle_info = vehicle_info_get( VEHICLE_SELF, 0 );

	/* no vehicle, and no actor. exit. */
	if ( vehicle_info == NULL && actor_info == NULL )
	{
		if ( cheat_state->actor.air_brake
		 ||	 cheat_state->actor.stick
		 ||	 cheat_state->vehicle.air_brake
		 ||	 cheat_state->vehicle.stick )
		{
			cheat_state->actor.air_brake = 0;
			cheat_vehicle_air_brake_set( 0 );
			cheat_state->actor.stick = 0;
			cheat_state->vehicle.stick = 0;
			cheat_state_text( "Air brake / stick disabled" );
		}
	}
	else
	{
		if ( vehicle_info == NULL )
		{
			if ( cheat_state->vehicle.air_brake || cheat_state->vehicle.stick )
			{
				cheat_vehicle_air_brake_set( 0 );
				cheat_state->vehicle.stick = 0;
				cheat_state_text( "Air brake / stick disabled" );
			}

			cheat_state->state = CHEAT_STATE_ACTOR;

			// reset infinite NOS toggle state
			if ( cheat_state->vehicle.infNOS_toggle_on )
			{
				cheat_state->vehicle.infNOS_toggle_on = false;
				patcher_remove( &patch_vehicle_inf_NOS );
			}
		}
		else
		{
			if ( cheat_state->actor.air_brake || cheat_state->actor.stick )
			{
				cheat_state->actor.air_brake = 0;
				cheat_state->actor.stick = 0;
				cheat_state_text( "Air brake / stick disabled" );
			}

			cheat_state->state = CHEAT_STATE_VEHICLE;
		}

		// post GTA initialization initizalization routines
		if ( m_InitStages == 0 )
		{
			// setup CGame & friends
			pGameInterface = new CGameSA();
			pPools = pGameInterface->GetPools();

			//pGameInterface->Initialize(); // all this does so far is disable modshops and pay&sprays
			// this seems to fix SAMP's load hang bug
			//pGameInterface->StartGame();

			// we have to add ourself to the pool first so that we are always the 1st ref
			// NEW --> use the global external: pPedSelf
			pPedSelf = pGameInterface->GetPools()->AddPed( (DWORD *)actor_info );
			pPedSelfSA = pPedSelf->GetPedInterface();

			// install all startup hooks
			cheat_hookers_installhooks();

			// increment stage
			m_InitStages++;
		}
		else if ( m_InitStages == 1 )
		{
			// load all the weapon models
			loadAllWeaponModels();

			// get funky
			//pGameInterface->GetAudio()->PlayBeatTrack(2);

			// increment stage
			m_InitStages++;
		}
	}

	if ( cheat_state->state != CHEAT_STATE_NONE )
	{
		// keep this updated, cos something is switching it now
		pPedSelf = pPools->GetPedFromRef( CPOOLS_PED_SELF_REF );
		pPedSelfSA = pPedSelf->GetPedInterface();
	}

	static bool chat_set_once = false;
	if ( !chat_set_once && set.d3dtext_chat )
	{
		if ( g_Chat != NULL && g_Chat->iChatWindowMode )
		{
			//Log("Disabling SA:MP chat text.");
			g_Chat->iChatWindowMode = 0;
			chat_set_once = true;
		}
	}

	// sets kill text to s0beit mode if enabled from INI
	static bool kill_set_once = false;
	if ( !kill_set_once && set.d3dtext_kill )
	{
		if ( g_DeathList != NULL && g_DeathList->iEnabled )
		{
			g_DeathList->iEnabled = 0;
			kill_set_once = true;
		}
	}

	// more random than random
	if ( rand() % 5000 == 0 )
		srand( rand() + time_get() );

	// OMGWTFBBQ?!?
	if ( cheat_panic() )
	{
		cheat_state->state = CHEAT_STATE_NONE;
		goto out;
	}

	// menus are good
	if(set.use_old_menu)
	menu_run();
	else
	runNewMenu();

	// install volatile patches from the .ini file
	for ( i = 0; i < INI_PATCHES_MAX; i++ )
	{
		if ( set.patch[i].name != NULL && set.patch[i].has_volatile && set.patch[i].installed )
			patcher_install( &set.patch[i] );
	}

	// generic stuff - these want to run even though we're dead
	cheat_handle_debug( wnd );
	cheat_handle_misc();
	cheat_handle_spoof_weapon();
	cheat_handle_weapon();

	
	gta_game_speed_set( cheat_state->game_speed );
	cheat_main_display_debug_stuff(g_timeDiff);

	if ( cheat_state->state != CHEAT_STATE_NONE )
	{
		// generic stuff
		cheat_handle_weapon_disable();
		cheat_handle_money();

		//////////////////////////////////////////////////////////////////
		// this should be removed after reworking weapon cheat function //
		//if ( set.restore_weapons_after_death )
		//	* (uint8_t *)0x5E6320 = 0xC3;

		cheat_handle_unlock();
		cheat_handle_checkpoint();

		// do stuff :p
		if ( cheat_state->state == CHEAT_STATE_VEHICLE )
		{
			cheat_main_vehicle( g_timeDiff );
		}
		else if ( cheat_state->state == CHEAT_STATE_ACTOR )
		{
			cheat_main_actor( g_timeDiff );
		}

		if ( KEY_PRESSED(set.key_disable_Wall_Collisions) )
		{
			cheat_state->_generic.nocols_walls_enabled ^= 1;
			if ( cheat_state->_generic.nocols_walls_enabled )
				patcher_install( &patch_NoColsWalls );
			else
				patcher_remove( &patch_NoColsWalls );
		}

		 if ( KEY_PRESSED(set.key_surfer) ) 
      { 
       cheat_state->_generic.surfer ^= 1; 
       if ( cheat_state->_generic.surfer ); 
      }

		for ( i = 0; i < INI_PATCHES_MAX; i++ )
		{
			if ( set.patch[i].name != NULL && KEY_PRESSED(set.patch[i].ini_hotkey) )
			{
				if ( set.patch[i].installed || set.patch[i].failed )
					patcher_remove( &set.patch[i] );
				else
					patcher_install( &set.patch[i] );
			}
		}

		for ( i = 0; i < INI_SAMPPATCHES_MAX; i++ )
		{
			if ( set.sampPatch[i].name != NULL && KEY_PRESSED(set.sampPatch[i].ini_hotkey) )
			{
				if ( set.sampPatch[i].installed || set.sampPatch[i].failed )
					patcher_remove( &set.sampPatch[i] );
				else
					patcher_install( &set.sampPatch[i] );
			}
		}

		if ( KEY_PRESSED(set.key_vehicle_jumper) )
		{
			int iVehicleID = vehicle_find_nearest( VEHICLE_ALIVE + VEHICLE_NOTBURNING );
			vehicleJumper( iVehicleID );
		}

		if ( KEY_PRESSED(set.key_vehicle_occupied_jumper) )
		{
			int iVehicleID = vehicle_find_nearest( VEHICLE_ALIVE + VEHICLE_NOTBURNING + VEHICLE_OCCUPIED );
			vehicleJumper( iVehicleID );
		}
	}	// cheat_state->state != CHEAT_STATE_NONE

	// hack some SA:MP, shall we?
	if ( g_SAMP && g_renderSAMP_initSAMPstructs )
		sampMainCheat();

out: ;
	if ( gta_menu_active() )
		keyhook_clear_states();
	else
		keyhook_run();
	time_last = time_get();
}
