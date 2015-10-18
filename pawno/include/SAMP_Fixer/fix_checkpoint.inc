#if defined _fix_checkpoint_included
	#endinput
#endif
#define _fix_checkpoint_included

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
 */
 
#if defined SAMP_FIXER_SINGLES
	static
		t_PlayerCPTimer[MAX_PLAYERS][2]
	;
#endif

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

forward FIX_OnCheckpointSet(playerid, type, Float:x, Float:y, Float:z, Float:size, Float:nextx, Float:nexty, Float:nextz);
public 	FIX_OnCheckpointSet(playerid, type, Float:x, Float:y, Float:z, Float:size, Float:nextx, Float:nexty, Float:nextz)
{
	if (type == -1)
	{
	    SetPlayerCheckpoint(playerid, x, y, z, size);
	}
	else
	{
	    SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size);
	}
	
	#if defined SAMP_FIXER_SINGLES
	    if (type == -1)
	    {
        	t_PlayerCPTimer[playerid][0] = -1;
		}
		else
		{
        	t_PlayerCPTimer[playerid][1] = -1;
		}
 	#else
	    if (type == -1)
	    {
        	DeletePVar(playerid, "PlayerCPTimer");
		}
		else
		{
        	DeletePVar(playerid, "PlayerRCPTimer");
		}
	#endif
}

stock FIX_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size)
{
	DisablePlayerCheckpoint(playerid);

    #if defined SAMP_FIXER_SINGLES
        if (t_PlayerCPTimer[playerid][0] != -1)
        {
            KillTimer(t_PlayerCPTimer[playerid][0]);
        }
        t_PlayerCPTimer[playerid][0] = SetTimerEx("FIX_OnCheckpointSet", 250, false, "iiffffff", playerid, -1, x, y, z, 0.0, 0.0, 0.0);
	#else
        if (GetPVarType(playerid, "PlayerCPTimer") != PLAYER_VARTYPE_NONE)
        {
            KillTimer(GetPvarInt(playerid, "PlayerCPTimer"));
        }
        SetPvarInt(playerid, "PlayerCPTimer", SetTimerEx("FIX_OnCheckpointSet", 250, false, "iiffffff", playerid, -1, x, y, z, 0.0, 0.0, 0.0));
	#endif
	
	return true;
}
#if defined _ALS_SetPlayerCheckpoint
    #undef SetPlayerCheckpoint
#else
	native BAD_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size) = SetPlayerCheckpoint;
    #define _ALS_SetPlayerCheckpoint
#endif
#define SetPlayerCheckpoint FIX_SetPlayerCheckpoint

stock FIX_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size)
{
	DisablePlayerRaceCheckpoint(playerid);

    #if defined SAMP_FIXER_SINGLES
        if (t_PlayerCPTimer[playerid][1] != -1)
        {
            KillTimer(t_PlayerCPTimer[playerid][1]);
        }
        t_PlayerCPTimer[playerid][1] = SetTimerEx("FIX_OnCheckpointSet", 250, false, "iiffffff", playerid, type, x, y, z, nextx, nexty, nextz);
	#else
        if (GetPVarType(playerid, "PlayerRCPTimer") != PLAYER_VARTYPE_NONE)
        {
            KillTimer(GetPvarInt(playerid, "PlayerRCPTimer"));
        }
        SetPvarInt(playerid, "PlayerRCPTimer", SetTimerEx("FIX_OnCheckpointSet", 250, false, "iiffffff", playerid, type, x, y, z, nextx, nexty, nextz));
	#endif
	
	return true;
}
#if defined _ALS_SetPlayerRaceCheckpoint
    #undef SetPlayerRaceCheckpoint
#else
	native BAD_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size) = SetPlayerRaceCheckpoint;
    #define _ALS_SetPlayerRaceCheckpoint
#endif
#define SetPlayerRaceCheckpoint FIX_SetPlayerRaceCheckpoint
