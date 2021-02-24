#pragma once

#define MAX_SCRIPT_VARS 16              // Size of our variable saving array
#define MAX_SCRIPT_SIZE 255             // Size of ScriptBuf - Max is really (2+(13*5))

struct GAME_SCRIPT_THREAD               // 0xE0 bytes total.
{
	BYTE    Pad1[0x14];                 // 0x00 [0x14]
	DWORD   dwScriptIP;                 // 0x14 [0x04]
	BYTE    Pad2[0x24];                 // 0x18 [0x24]
	DWORD   dwLocalVar[18];				// 0x3C [0x48]
	BYTE    Pad3[0x41];                 // 0x84 [0x41]
	DWORD   dwIfFlag;                   // 0xC5 [0x04]
	BYTE    Pad4[0xF];                  // 0xC9 [0x0F]
	DWORD   dwIndexSomething;			// 0xD8 [0x04]  (indexes into 0xA49960)
	BYTE    bHasLocalCopy;				// 0xDC [0x01]  (has local copy of something, if 1, then uses .data:00A48960 CTheScripts_LocalCopy instead of var0)
	BYTE    Pad5[0x3];                  // 0xDD [0x03]
};

struct SCRIPT_COMMAND                   // Params
{										//	  i = integer
	WORD    OpCode;						//	  f = float
	char    Params[MAX_SCRIPT_VARS];    //	  v = variable
};										//	  s = string
void                                    InitScripting();
int                                     ScriptCommand(const SCRIPT_COMMAND *pScriptCommand, ...);

const SCRIPT_COMMAND    toggle_player_controllable =						{ 0x01B4, "ii" };
const SCRIPT_COMMAND    lock_actor =										{ 0x04D7, "ii" };
const SCRIPT_COMMAND    put_actor_in_car =									{ 0x036A, "ii" };
const SCRIPT_COMMAND    put_actor_in_car_passenger =						{ 0x0430, "iii" };
const SCRIPT_COMMAND    restore_camera_with_jumpcut =						{ 0x02EB, "" };
const SCRIPT_COMMAND    set_camera_directly_behind =						{ 0x0373, "" };
const SCRIPT_COMMAND    remove_actor_from_car_and_put_at =					{ 0x0362, "ifff" };
const SCRIPT_COMMAND    apply_momentum_in_direction_XYZ =					{ 0x07D5, "iffffff" };
const SCRIPT_COMMAND    apply_rotory_pulse_about_an_axis_XYZ =				{ 0x07DA, "ifff" };
const SCRIPT_COMMAND    repair_car =										{ 0x0A30, "i" };
const SCRIPT_COMMAND    get_actor_car =										{ 0x03C0, "iv" };
const SCRIPT_COMMAND    camera_on_actor =									{ 0x0159, "iii" };
const SCRIPT_COMMAND    camera_on_vehicle =									{ 0x0158, "iii" };
const SCRIPT_COMMAND    put_trailer_on_cab =								{ 0x0893, "ii" };
const SCRIPT_COMMAND    enter_car_as_driver =								{ 0x05CB, "iii" };
const SCRIPT_COMMAND    set_car_lights =									{ 0x067F, "ii" };
const SCRIPT_COMMAND    show_text_highpriority =							{ 0x0ACD, "si" };
const SCRIPT_COMMAND	player_perform_animation_at_x_times_normal_rate =   { 0x0393, "isf" }; //0393=3,actor %1d% perform_animation %2h% at %3d% times_normal_rate
const SCRIPT_COMMAND	play_sound =										{ 0x018C, "fffi" };
const SCRIPT_COMMAND	perform_animation =									{ 0x0812, "issfiiiii" };
const SCRIPT_COMMAND    write_memory =										{ 0x0A8C, "iiii" };
const SCRIPT_COMMAND    read_memory =										{ 0x0A8D, "iiiii" };
const SCRIPT_COMMAND	cam_set_pos =										{ 0x0936, "ffffffii" }; 
const SCRIPT_COMMAND	car_damage_component =								{ 0x0730, "ii" };
const SCRIPT_COMMAND	set_car_remove_componentA_visible_effect_flag =		{ 0x0689, "iii" };
const SCRIPT_COMMAND	set_car_remove_componentB_visible_effect_flag =		{ 0x0697, "iii" };
const SCRIPT_COMMAND	no_obstacles_between_A_and_B =						{ 0x06BD, "ffffffiiiii" };
const SCRIPT_COMMAND	draw_box_position =									{ 0x038E, "ffffiiii" };
const SCRIPT_COMMAND	enable_text_draw =									{ 0x03F0, "i" };
const SCRIPT_COMMAND	distance_between_XYZ_and_XYZ =						{ 0x050A, "ffffffv" };
const SCRIPT_COMMAND	sine =												{ 0x02F6, "fv" };
const SCRIPT_COMMAND	cosine =											{ 0x02F7, "fv" };
const SCRIPT_COMMAND	int_to_float =										{ 0x0093, "vv" };
const SCRIPT_COMMAND	store_coords_to_x_from_actor_x_with_offset_x =		{ 0x04C4, "fffifff" };
const SCRIPT_COMMAND	get_model_x_dimensions_cornerA_to_B	=				{ 0x07E4, "iffffff" };
const SCRIPT_COMMAND	store_actor_position_to_x =							{ 0x00A0, "ifff" };
const SCRIPT_COMMAND	put_actor_at_x =									{ 0x00A1, "ifff" };

const SCRIPT_COMMAND	load_txd_dictionary =								{ 0x0390, "s" };
const SCRIPT_COMMAND	load_texture =										{ 0x038F, "sv" };
const SCRIPT_COMMAND	draw_texture =										{ 0x038D, "iffffiiii" };
const SCRIPT_COMMAND anim_speed = { 0x0393, "isf" };
const SCRIPT_COMMAND register_int_stat = { 0x0627, "if" };

//00A1: put_actor $PLAYER_ACTOR at 345.5621 306.2212 998.4484
/*
0390: load_txd_dictionary 'LD_BEAT' 
038F: load_texture "upr" as 1 
038D: draw_texture 1 position 320.0 240.0 size 640.0 480.0 RGBA 255 255 255 255
*/


