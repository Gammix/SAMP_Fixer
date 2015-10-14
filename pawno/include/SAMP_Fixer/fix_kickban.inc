#if defined _fix_kickban_included
	#endinput
#endif
#define _fix_kickban_included
#pragma library fix_kickban

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_kickban.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			Kick
 * PROBLEM:  	While kick is executed on a player, other elements such as client messages, dialogs etc. doesn't work.
 * SOLUTION: 	Add delay between the kick final execution. (see "delay" param)
 *
 * FIX:			Ban
 * PROBLEM:  	While ban is executed on a player, other elements such as client messages, dialogs etc. doesn't work.
 * SOLUTION: 	Add delay between the ban final execution. (see "delay" param)
 *
 * FIX:			BanEx
 * PROBLEM:  	While banex is executed on a player, other elements such as client messages, dialogs etc. doesn't work.
 * SOLUTION: 	Add delay between the banex final execution. (see "delay" param)
 *
 */

enum e_KICKBAN_DATA
{
	kbTimer,
	kbType,
	kbReason[150]
};

static
	t_DelayKB[MAX_PLAYERS][e_KICKBAN_DATA]
;

forward OnPlayerDelayKicked(playerid);
public	OnPlayerDelayKicked(playerid)
{
	t_DelayKB[playerid][kbTimer] = -1;

	switch (t_DelayKB[playerid][kbType])
	{
		case 0:
		{
			Kick(playerid);
		}
		case 1:
		{
			Ban(playerid);
		}
		case 2:
		{
			BanEx(playerid, t_DelayKB[playerid][kbReason]);
		}
	}
}

stock FIX_Kick(playerid, delay = 150)
{
	if (! IsPlayerConnected(playerid) || t_DelayKB[playerid][kbTimer] != -1)
	{
		return false;
	}

	t_DelayKB[playerid][kbTimer] = SetTimerEx("OnPlayerDelayKicked", delay, false, "i", playerid);
	t_DelayKB[playerid][kbType] = 0;
	t_DelayKB[playerid][kbReason][0] = EOS;

	return true;
}
#if defined _ALS_Kick
	#undef Kick
#else
	native BAD_Kick(playerid) = Kick;
	#define _ALS_Kick
#endif
#define Kick FIX_Kick

stock FIX_Ban(playerid, delay = 150)
{
	if (! IsPlayerConnected(playerid) || t_DelayKB[playerid][kbTimer] != -1)
	{
		return false;
	}

	t_DelayKB[playerid][kbTimer] = SetTimerEx("OnPlayerDelayKicked", delay, false, "i", playerid);
	t_DelayKB[playerid][kbType] = 1;
	t_DelayKB[playerid][kbReason][0] = EOS;

	return true;
}
#if defined _ALS_Ban
	#undef Ban
#else
	native BAD_Ban(playerid) = Ban;
	#define _ALS_Ban
#endif
#define Ban FIX_Ban

stock FIX_BanEx(playerid, const reason[], delay = 150)
{
	if (! IsPlayerConnected(playerid) || t_DelayKB[playerid][kbTimer] != -1)
	{
		return false;
	}

	t_DelayKB[playerid][kbTimer] = SetTimerEx("OnPlayerDelayKicked", delay, false, "i", playerid);
	t_DelayKB[playerid][kbType] = 2;
	t_DelayKB[playerid][kbReason][0] = EOS;
	strcat(t_DelayKB[playerid][kbReason], reason);

	return true;
}
#if defined _ALS_BanEx
	#undef BanEx
#else
	native BAD_BanEx(playerid, const reason[]) = BanEx;
	#define _ALS_BanEx
#endif
#define BanEx FIX_BanEx

public OnPlayerConnect(playerid)
{
	t_DelayKB[playerid][kbTimer] = -1;

	#if defined KB_OnPlayerConnect
		return KB_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif

}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect KB_OnPlayerConnect
#if defined KB_OnPlayerConnect
	forward KB_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if (t_DelayKB[playerid][kbTimer] != -1)
	{
		KillTimer(t_DelayKB[playerid][kbTimer]);
		t_DelayKB[playerid][kbTimer] = -1;
		
		OnPlayerDelayKicked(playerid);
	}

	#if defined KB_OnPlayerDisconnect
		return KB_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect KB_OnPlayerDisconnect
#if defined KB_OnPlayerDisconnect
forward KB_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerUpdate(playerid)
{
	if (t_DelayKB[playerid][kbTimer] != -1)
	{
		return 0;
	}

	#if defined KB_OnPlayerUpdate
		return KB_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate KB_OnPlayerUpdate
#if defined KB_OnPlayerUpdate
	forward KB_OnPlayerUpdate(playerid);
#endif

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (t_DelayKB[playerid][kbTimer] != -1)
	{
		return 0;
	}

	#if defined KB_OnPlayerCommandText
		return KB_OnPlayerCommandText(playerid, cmdtext);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText KB_OnPlayerCommandText
#if defined KB_OnPlayerCommandText
	forward KB_OnPlayerCommandText(playerid, cmdtext[]);
#endif

public OnPlayerText(playerid, text[])
{
	if (t_DelayKB[playerid][kbTimer] != -1)
	{
		return 0;
	}

	#if defined KB_OnPlayerText
		return KB_OnPlayerText(playerid, text);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText KB_OnPlayerText
#if defined KB_OnPlayerText
	forward KB_OnPlayerText(playerid, text[]);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (t_DelayKB[playerid][kbTimer] != -1)
	{
		return 0;
	}

	#if defined KB_OnDialogResponse
		return KB_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 0;
	#endif
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse KB_OnDialogResponse
#if defined KB_OnDialogResponse
	forward KB_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	if (t_DelayKB[playerid][kbTimer] != -1)
	{
		return 0;
	}

	#if defined KB_OnPlayerDeath
		return KB_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath KB_OnPlayerDeath
#if defined KB_OnPlayerDeath
	forward KB_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnVehicleMod(playerid, vehicleid, componentid)
{
	if (t_DelayKB[playerid][kbTimer] != -1)
	{
		return 0;
	}

	#if defined KB_OnVehicleMod
		return KB_OnVehicleMod(playerid, vehicleid, componentid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnVehicleMod
	#undef OnVehicleMod
#else
	#define _ALS_OnVehicleMod
#endif
#define OnVehicleMod KB_OnVehicleMod
#if defined KB_OnVehicleMod
	forward KB_OnVehicleMod(playerid, vehicleid, componentid);
#endif

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	if (t_DelayKB[playerid][kbTimer] != -1)
	{
		return 0;
	}

	#if defined KB_OnVehicleRespray
		return KB_OnVehicleRespray(playerid, vehicleid, color1, color2);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif
#define OnVehicleRespray KB_OnVehicleRespray
#if defined KB_OnVehicleRespray
	forward KB_OnVehicleRespray(playerid, vehicleid, color1, color2);
#endif
