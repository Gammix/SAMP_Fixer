/*
 * ============
 * 	INTRODUCTION
 * ============
 *
 * SAMP Fixer v1.0 - (c) 2015
 * Community patch for buggy SA:MP functions.
 *
 *
 * ============
 * 	LIST OF LIBRARIES
 * ============
 *
 * fix_anims [IMPORTANT]
 * fix_attachments [IMPORTANT]
 * fix_checkpoint
 * fix_files [IMPORTANT]
 * fix_gametext
 * fix_gangzone
 * fix_kickban
 * fix_menu [IMPORTANT]
 * fix_others [IMPORTANT]
 * fix_players [IMPORTANT]
 * fix_server
 * fix_string [IMPORTANT]
 * fix_tildes [IMPORTANT]
 * fix_tickcount
 * fix_vehicles [IMPORTANT]
 *
 * ============
 * 	AUTHOR
 * ============
 *
 * Gammix
 *
 * ============
 * 	SPECIAL THANKS
 * ============
 *
 * SA-MP Community
 * Y_Less
 * Slice
 * xX_Simon_Xx
 * RyDeR`
 * MP2
 * KHKKhalid
 * JernejL
 *
*/

#tryinclude "a_samp"

#include "SAMP_Fixer/fix_anims"
#include "SAMP_Fixer/fix_attachments"
#include "SAMP_Fixer/fix_checkpoint"
#include "SAMP_Fixer/fix_file"
#include "SAMP_Fixer/fix_gametext"
#include "SAMP_Fixer/fix_gangzone"
#include "SAMP_Fixer/fix_kickban"
#include "SAMP_Fixer/fix_menu"
#include "SAMP_Fixer/fix_others"
#include "SAMP_Fixer/fix_player"
#include "SAMP_Fixer/fix_server"
#include "SAMP_Fixer/fix_string"
#include "SAMP_Fixer/fix_tickcount"
#include "SAMP_Fixer/fix_tildes"
#include "SAMP_Fixer/fix_vehicles"

public OnGameModeInit()
{
	EnableTirePopping(1);
	AllowInteriorWeapons(1);
	AllowAdminTeleport(0);
	EnableZoneNames(0);
	EnableVehicleNames(0);

	#if defined FIXES_OnGameModeInit
		return FIXES_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit FIXES_OnGameModeInit
#if defined FIXES_OnGameModeInit
	forward FIXES_OnGameModeInit();
#endif
