#if defined _fix_others_included
	#endinput
#endif
#define _fix_others_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_others.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			KEY_AIM
 * PROBLEM:  	By default this macro isn't defined.
 * SOLUTION:  	Define it.
 *
 * FIX:			SPECIAL_ACTION_PISSING
 * PROBLEM:  	By default this macro isn't defined.
 * SOLUTION: 	Define it.
 *
 * FIX:			random
 * PROBLEM:  	When passed negative numbers, this native doesn't work.
 * SOLUTION: 	Multiply with "-" to get results
 *
 * FIX:			IsPlayerConnected
 * PROBLEM:  	The native doesn't mask the numbers.
 * SOLUTION:    Add an additional check.
 *
 * FIX:			Weapon crasher
 * PROBLEM:  	Illegal weapons and bullets can crash server.
 * SOLUTION:    Detect under OnPlayerWeaponShot and desync when invalid
 *
 */

#if ! defined KEY_AIM
	#define KEY_AIM (128)
#endif

#if ! defined SPECIAL_ACTION_PISSING
	#define SPECIAL_ACTION_PISSING (68)
#endif

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if (weaponid < 22 || weaponid > 38)
 	{
	 	return 0;
	}

	new
		Float:x,
		Float:y,
		Float:z
	;
    GetPlayerPos(playerid, x, y, z);

	if ( !(-20000.0 <= z <= 20000.0))
 	{
	 	return 0;
	}

    #if defined EX_OnPlayerWeaponShot
		return EX_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerWeaponShot
   #undef OnPlayerWeaponShot
#else
    #define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot EX_OnPlayerWeaponShot
#if defined EX_OnPlayerWeaponShot
	forward EX_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif

stock FIX_random(max)
{
	if (max < 0)
	{
		return -random(-max);
	}
	else
	{
		return random(max);
	}
}
#if defined _ALS_random
	#undef random
#else
	native BAD_random(max) = random;
	#define _ALS_random
#endif
#define random FIX_random

stock FIX_IsPlayerConnected(playerid)
{
	if (playerid & 0xFFFF0000)
	{
		return false;
	}
 	else
	{
		return IsPlayerConnected(playerid);
	}
}
#if defined _ALS_IsPlayerConnected
	#undef IsPlayerConnected
#else
	native BAD_IsPlayerConnected(playerid) = IsPlayerConnected;
	#define _ALS_IsPlayerConnected
#endif
#define IsPlayerConnected FIX_IsPlayerConnected
