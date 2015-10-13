#if defined _fix_pause_included
	#endinput
#endif
#define _fix_pause_included
#pragma library fix_pause

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_pause.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * ADD:   		IsPlayerPaused(playerid);
 * INFO:  		Return 1 if the player is in pause menu or 0 if not.
 *
 * ADD:   		OnPlayerPause(playerid) / OnPlayerUnpause(playerid)
 * INFO:  		called when a player goes or returns to paused state.
 *
 * ADD:			GetPlayerPausedTime(playerid);
 * INFO:  		Get player pause interval in seconds.
 *
 */

enum e_PAUSE_DATA
{
			pauseTimer,
			pauseLastTime,
	bool:	pauseCheck
};
static
	t_PlayerPaused[MAX_PLAYERS][e_PAUSE_DATA]
;

#define PLAYER_STATE_PAUSED (10)

public OnPlayerConnect(playerid)
{
    t_PlayerPaused[playerid][pauseTimer] = -1;
    t_PlayerPaused[playerid][pauseLastTime] = 0;
    t_PlayerPaused[playerid][pauseCheck] = false;

    #if defined PAUSE_OnPlayerConnect
		return PAUSE_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect PAUSE_OnPlayerConnect
#if defined PAUSE_OnPlayerConnect
	forward PAUSE_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if (t_PlayerPaused[playerid][pauseTimer] != -1)
	{
		KillTimer(t_PlayerPaused[playerid][pauseTimer]);
	}

    #if defined PAUSE_OnPlayerDisconnect
       	return PAUSE_OnPlayerDisconnect(playerid, reason);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect PAUSE_OnPlayerDisconnect
#if defined PAUSE_OnPlayerDisconnect
    forward PAUSE_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerRequestClass(playerid, classid)
{
	if (t_PlayerPaused[playerid][pauseTimer] != -1)
	{
		KillTimer(t_PlayerPaused[playerid][pauseTimer]);
	}

    #if defined PAUSE_OnPlayerRequestClass
       	return PAUSE_OnPlayerRequestClass(playerid, classid);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerRequestClass
    #undef OnPlayerRequestClass
#else
    #define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass PAUSE_OnPlayerRequestClass
#if defined PAUSE_OnPlayerRequestClass
    forward PAUSE_OnPlayerRequestClass(playerid, classid);
#endif

public OnPlayerSpawn(playerid)
{
	if (! t_PlayerPaused[playerid][pauseCheck])
	{
		if (GetPVarType(playerid, "Pause_Update") == PLAYER_VARTYPE_NONE)
		{
		    SetPVarInt(playerid, "Pause_Update", 1);
	    	t_PlayerPaused[playerid][pauseCheck] = true;

			if (t_PlayerPaused[playerid][pauseTimer] != -1)
			{
				KillTimer(t_PlayerPaused[playerid][pauseTimer]);
			}
		    t_PlayerPaused[playerid][pauseTimer] = SetTimerEx("PAUSE_OnPlayerTimeUpdate", 1000, true, "i", playerid);
		}
	}

    #if defined PAUSE_OnPlayerSpawn
		return PAUSE_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn PAUSE_OnPlayerSpawn
#if defined PAUSE_OnPlayerSpawn
	forward PAUSE_OnPlayerSpawn(playerid);
#endif

forward PAUSE_OnPlayerTimeUpdate(playerid);
public  PAUSE_OnPlayerTimeUpdate(playerid)
{
    if (GetPVarType(playerid, "PlayerPaused") == PLAYER_VARTYPE_NONE)
    {
        if (gettime() - t_PlayerPaused[playerid][pauseLastTime] > 1)
		{
        	CallRemoteFunction("OnPlayerPause", "i", playerid);

			KillTimer(t_PlayerPaused[playerid][pauseTimer]);
			t_PlayerPaused[playerid][pauseTimer] = -1;

			SetPVarInt(playerid, "PlayerPaused", 1);
		}
    }
}

public OnPlayerUpdate(playerid)
{
	if (t_PlayerPaused[playerid][pauseCheck])
	{
	    if (GetPVarType(playerid, "PlayerPaused") != PLAYER_VARTYPE_NONE)
		{
	        CallRemoteFunction("OnPlayerUnpause", "i", playerid);

	    	t_PlayerPaused[playerid][pauseTimer] = SetTimerEx("PAUSE_OnPlayerTimeUpdate", 1000, true, "i", playerid);

			DeletePVar(playerid, "PlayerPaused");
	    }
	    else
	    {
	        t_PlayerPaused[playerid][pauseLastTime] = gettime();
	    }
	}

    #if defined PAUSE_OnPlayerUpdate
		return PAUSE_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
   #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate PAUSE_OnPlayerUpdate
#if defined PAUSE_OnPlayerUpdate
	forward PAUSE_OnPlayerUpdate(playerid);
#endif

stock IsPlayerPaused(playerid)
{
	if (GetPVarType(playerid, "PlayerPaused") != PLAYER_VARTYPE_NONE)
	{
	    return true;
	}

	return false;
}

stock GetPlayerPausedTime(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_PAUSED)
	{
	    return 0;
	}
	else
	{
		return gettime() - t_PlayerPaused[playerid][pauseLastTime];
	}
}
