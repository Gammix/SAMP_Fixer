#if defined _fix_checkpoint_included
	#endinput
#endif
#define _fix_checkpoint_included
#pragma library fix_checkpoint

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_checkpoint.inc
 *
 * ================
 *  LIST OF FIXES/ADDONS:
 * ================
 *
 * FIX:			IsPlayerInAnyCheckpoint
 * PROBLEM:  	Function returns an undefined value if it is called before any other checkpoint functions are called to initialise the value.
 * SOLUTION: 	Call DisablePlayerCheckpoint when a player connects.
 *
 * FIX:			IsPlayerInAnyRaceCheckpoint
 * PROBLEM:  	Function returns an undefined value if it is called before any other race checkpoint functions are called to initialise the value.
 * SOLUTION: 	Call DisablePlayerRaceCheckpoint when a player connects.
 *
 * FIX:			SetPlayerCheckpoint
 * PROBLEM:  	If a checkpoint is already set it will use the size of that checkpoint instead of the new one.
 * SOLUTION: 	Call DisablePlayerCheckpoint before setting a new checkpoint.
 *
 * FIX:			SetPlayerRaceCheckpoint
 * PROBLEM:  	If a race checkpoint is already set it will use the size of that race checkpoint instead of the new one.
 * SOLUTION: 	Call DisablePlayerRaceCheckpoint before setting a new race checkpoint.
 *
 * ADD:			GetPlayerCheckpoint(playerid, &Float:x, &Float:y, &Float:z, &Float:size);
 * INFO:  		Read the last checkpoint info.
 *
 * ADD:			GetPlayerRaceCheckpoint(playerid, &type, &Float:x, &Float:y, &Float:z,& Float:nextx, &Float:nexty, &Float:nextz, &Float:size);
 * INFO:  		Read the last race checkpoint info.
 *
 */

public OnPlayerConnect(playerid)
{
    DisablePlayerCheckpoint(playerid);
    DisablePlayerRaceCheckpoint(playerid);

    #if defined CP_OnPlayerConnect
		return CP_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect CP_OnPlayerConnect
#if defined CP_OnPlayerConnect
	forward CP_OnPlayerConnect(playerid);
#endif

stock FIX_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size)
{
	if (GetPVarType(playerid, "cp_x") != PLAYER_VARTYPE_NONE)
	{
	    DisablePlayerCheckpoint(playerid);
	}

	new
	    ret = SetPlayerCheckpoint(playerid, x, y, z, size)
	;
	if (ret)
	{
		SetPVarFloat(playerid, "cp_x", x);
		SetPVarFloat(playerid, "cp_y", y);
		SetPVarFloat(playerid, "cp_z", z);
		SetPVarFloat(playerid, "cp_size", size);
	}

	return ret;
}
#if defined _ALS_SetPlayerCheckpoint
    #undef SetPlayerCheckpoint
#else
	native BAD_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size) = SetPlayerCheckpoint;
    #define _ALS_SetPlayerCheckpoint
#endif
#define SetPlayerCheckpoint FIX_SetPlayerCheckpoint

stock GetPlayerCheckpoint(playerid, &Float:x, &Float:y, &Float:z, &Float:size)
{
	if (GetPVarType(playerid, "cp_x") != PLAYER_VARTYPE_NONE)
	{
		x = GetPVarFloat(playerid, "cp_x");
		y = GetPVarFloat(playerid, "cp_y");
		z = GetPVarFloat(playerid, "cp_z");
		size = GetPVarFloat(playerid, "cp_size");

	    return true;
	}
	else
	{
	    return false;
	}
}

stock FIX_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size)
{
	if (GetPVarType(playerid, "rcp_x") != PLAYER_VARTYPE_NONE)
	{
	    DisablePlayerRaceCheckpoint(playerid);
	}

	new
	    ret = SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size)
	;
	if (ret)
	{
		SetPVarFloat(playerid, "rcp_type", type);
		SetPVarFloat(playerid, "rcp_x", x);
		SetPVarFloat(playerid, "rcp_y", y);
		SetPVarFloat(playerid, "rcp_z", z);
		SetPVarFloat(playerid, "rcp_nextx", nextx);
		SetPVarFloat(playerid, "rcp_nexty", nexty);
		SetPVarFloat(playerid, "rcp_nextz", nextz);
		SetPVarFloat(playerid, "cp_size", size);
	}

	return ret;
}
#if defined _ALS_SetPlayerRaceCheckpoint
    #undef SetPlayerRaceCheckpoint
#else
	native BAD_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size) = SetPlayerRaceCheckpoint;
    #define _ALS_SetPlayerRaceCheckpoint
#endif
#define SetPlayerRaceCheckpoint FIX_SetPlayerRaceCheckpoint

stock GetPlayerRaceCheckpoint(playerid, &type, &Float:x, &Float:y, &Float:z,& Float:nextx, &Float:nexty, &Float:nextz, &Float:size)
{
	if (GetPVarType(playerid, "rcp_x") != PLAYER_VARTYPE_NONE)
	{
		type = GetPVarFloat(playerid, "rcp_type");
		x = GetPVarFloat(playerid, "rcp_x");
		y = GetPVarFloat(playerid, "rcp_y");
		z = GetPVarFloat(playerid, "rcp_z");
		nextx = GetPVarFloat(playerid, "rcp_nextx");
		nexty = GetPVarFloat(playerid, "rcp_nexty");
		nextz = GetPVarFloat(playerid, "rcp_nextz");
		size = GetPVarFloat(playerid, "rcp_size");

	    return true;
	}
	else
	{
	    return false;
	}
}
