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
 * fix_gametext
 * fix_gangzone
 * fix_kickban
 * fix_others [IMPORTANT]
 * fix_pause
 * fix_players [IMPORTANT]
 * fix_server
 * fix_string [IMPORTANT]
 * fix_vehicles [IMPORTANT]
 * fix_tickcount
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
 *
*/

#tryinclude "a_samp"

#include "SAMP_Fixer/fix_anims"
#include "SAMP_Fixer/fix_attachments"
#include "SAMP_Fixer/fix_checkpoint"
#include "SAMP_Fixer/fix_gametext"
#include "SAMP_Fixer/fix_gangzone"
#include "SAMP_Fixer/fix_kickban"
#include "SAMP_Fixer/fix_others"
#include "SAMP_Fixer/fix_pause"
#include "SAMP_Fixer/fix_player"
#include "SAMP_Fixer/fix_server"
#include "SAMP_Fixer/fix_string"
#include "SAMP_Fixer/fix_vehicles"
#include "SAMP_Fixer/fix_tickcount"

public OnGameModeInit()
{
	print("\n======================\n");
	print("SA-MP Fixer v1.0");
	print("Librarby loaded...");
	print("\n======================\n");

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
