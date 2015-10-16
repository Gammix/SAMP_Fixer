#if defined _fix_player_included
	#endinput
#endif
#define _fix_player_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_player.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			GetPlayerIp
 * PROBLEM:  	Don't work in OnPlayerDisconnect.
 * SOLUTION:  	Store player ip. under OnPlayerConnect.
 *
 * FIX:			GetPlayerColor
 * PROBLEM:  	Returns an invalid value when used before SetPlayerColor.
 * SOLUTION:  	Set player random color under OnPlayerConnect.
 *
 * FIX:			TogglePlayerSpectating
 * PROBLEM:  	Causes camera bug when used for same conditions.
 * SOLUTION:  	Add player state check before setting to spectate screen.
 *
 * FIX:			ClearAnimations
 * PROBLEM:  	Use ClearAnimation while you are in a vehicle cause the player exit from it.
 * SOLUTION:  	Apply an animation instead of clear animation.
 *
 * FIX:			TogglePlayerControllable
 * PROBLEM:  	Sometimes player see you moving when freezed.
 * SOLUTION:  	Clear animations before freezing a player.
 *
 * FIX:			PutPlayerInVehicle
 * PROBLEM:  	If this is used on a passenger the driver of their old vehicle doesn't see them in their new vehicle.
 * SOLUTION:  	Remove the player from the vehicle first.
 *
 * FIX:			SpawnPlayer
 * PROBLEM:  	When player is in vehicle, he/she is killed.
 * SOLUTION:  	Remove the player from the vehicle first.
 *
 * FIX:			SetPlayerName
 * PROBLEM:  	Doesn't work when the newname is different only in case with the old name.
 * SOLUTION:  	Use SetPlayerName twice in case sensitive cases.
 *
 * FIX:			SetPlayerSkin
 * PROBLEM:     When used in vehicles, causes positioning bug.
 * SOLUTION:  	Temporarily eject player, set skin and put back into vehicle.
 *
 * FIX:			GetPlayerSkin
 * PROBLEM:     Returns the new skin after "SetSpawnInfo" is called but before the player actually respawns to get the new skin.
 * SOLUTION:  	Use PVar to record the skin and return it instead from the native.
 *
 * FIX:			SetPlayerSpecialAction
 * PROBLEM:     Removing jetpacks from players by setting their special action to 0 causes the sound to stay until death.
 * SOLUTION:  	Clear animations before remove jetpack.
 *
 */

static
	t_PlayerIP[MAX_PLAYERS][18]
;

static const t_SetPlayerColor[100] =
{
	0xFF8C13FF, 0xC715FFFF, 0x20B2AAFF, 0xDC143CFF, 0x6495EDFF,
	0xF0E68CFF, 0x778899FF, 0xFF1493FF, 0xF4A460FF, 0xEE82EEFF,
	0xFFD720FF, 0x8B4513FF, 0x4949A0FF, 0x148B8BFF, 0x14FF7FFF,
	0x556B2FFF, 0x0FD9FAFF, 0x10DC29FF, 0x534081FF, 0x0495CDFF,
	0xEF6CE8FF, 0xBD34DAFF, 0x247C1BFF, 0x0C8E5DFF, 0x635B03FF,
	0xCB7ED3FF, 0x65ADEBFF, 0x5C1ACCFF, 0xF2F853FF, 0x11F891FF,
	0x7B39AAFF, 0x53EB10FF, 0x54137DFF, 0x275222FF, 0xF09F5BFF,
	0x3D0A4FFF, 0x22F767FF, 0xD63034FF, 0x9A6980FF, 0xDFB935FF,
	0x3793FAFF, 0x90239DFF, 0xE9AB2FFF, 0xAF2FF3FF, 0x057F94FF,
	0xB98519FF, 0x388EEAFF, 0x028151FF, 0xA55043FF, 0x0DE018FF,
	0x93AB1CFF, 0x95BAF0FF, 0x369976FF, 0x18F71FFF, 0x4B8987FF,
	0x491B9EFF, 0x829DC7FF, 0xBCE635FF, 0xCEA6DFFF, 0x20D4ADFF,
	0x2D74FDFF, 0x3C1C0DFF, 0x12D6D4FF, 0x48C000FF, 0x2A51E2FF,
	0xE3AC12FF, 0xFC42A8FF, 0x2FC827FF, 0x1A30BFFF, 0xB740C2FF,
	0x42ACF5FF, 0x2FD9DEFF, 0xFAFB71FF, 0x05D1CDFF, 0xC471BDFF,
	0x94436EFF, 0xC1F7ECFF, 0xCE79EEFF, 0xBD1EF2FF, 0x93B7E4FF,
	0x3214AAFF, 0x184D3BFF, 0xAE4B99FF, 0x7E49D7FF, 0x4C436EFF,
	0xFA24CCFF, 0xCE76BEFF, 0xA04E0AFF, 0x9F945CFF, 0xDCDE3DFF,
	0x10C9C5FF, 0x70524DFF, 0x0BE472FF, 0x8A2CD7FF, 0x6152C2FF,
	0xCF72A9FF, 0xE59338FF, 0xEEDC2DFF, 0xD8C762FF, 0xD8C762FF
};

#if defined SAMP_FIXER_SINGLES
	static
	    t_PlayerSkin[MAX_PLAYERS]
	;
#endif

public OnPlayerConnect(playerid)
{
	SetPlayerColor(playerid, t_SetPlayerColor[random(sizeof(t_SetPlayerColor))]);

	GetPlayerIp(playerid, t_PlayerIP[playerid], 18);

    #if defined PLAYER_OnPlayerConnect
		return PLAYER_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect PLAYER_OnPlayerConnect
#if defined PLAYER_OnPlayerConnect
	forward PLAYER_OnPlayerConnect(playerid);
#endif

public OnPlayerSpawn(playerid)
{
	#if defined SAMP_FIXER_SINGLES
	    t_PlayerSkin[playerid] = GetPlayerSkin(playerid);
	#else
		SetPVarInt(playerid, "FIX_GetPlayerSkin", GetPlayerSkin(playerid));
	#endif
	
    #if defined PLAYER_OnPlayerSpawn
		return PLAYER_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn PLAYER_OnPlayerSpawn
#if defined PLAYER_OnPlayerSpawn
	forward PLAYER_OnPlayerSpawn(playerid);
#endif

stock FIX_GetPlayerIp(playerid, name[], len)
{
	name[0] = EOS;
	return strcat(name, t_PlayerIP[playerid], len);
}
#if defined _ALS_GetPlayerIp
	#undef GetPlayerIp
#else
	native BAD_GetPlayerIp(playerid, name[], len) = GetPlayerIp;
	#define _ALS_GetPlayerIp
#endif
#define GetPlayerIp FIX_GetPlayerIp

stock FIX_TogglePlayerSpectating(playerid, set)
{
	if (set)
	{
		if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
		{
		    return TogglePlayerSpectating(playerid, true);
		}
	}
	else
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
		{
		    return TogglePlayerSpectating(playerid, false);
		}
	}

	return false;
}
#if defined _ALS_TogglePlayerSpectating
    #undef TogglePlayerSpectating
#else
	native BAD_TogglePlayerSpectating(playerid, set) = TogglePlayerSpectating;
    #define _ALS_TogglePlayerSpectating
#endif
#define TogglePlayerSpectating FIX_TogglePlayerSpectating

stock FIX_ClearAnimations(playerid, forcesync = 0)
{
	if (IsPlayerInAnyVehicle(playerid))
	{
		return ApplyAnimation(playerid, "PED", "CAR_SIT", 4.0, 0, 0, 0, 0, 1, forcesync);
	}

	new
		ret = ClearAnimations(playerid, forcesync)
	;
	ApplyAnimation(playerid, "PED", "IDLE_STANCE", 4.0, 0, 0, 0, 0, 1, forcesync);
	ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.0, 0, 0, 0, 0, 1, forcesync);
	ApplyAnimation(playerid, "PED", "WALK_PLAYER", 4.0, 0, 0, 0, 0, 1, forcesync);

	return ret;
}
#if defined _ALS_ClearAnimations
    #undef ClearAnimations
#else
	native BAD_ClearAnimations(playerid, forcesync) = ClearAnimations;
    #define _ALS_ClearAnimations
#endif
#define ClearAnimations FIX_ClearAnimations

stock FIX_TogglePlayerControllable(playerid, toggle)
{
	if (! toggle)
	{
		ClearAnimations(playerid, 1);
	}

	return TogglePlayerControllable(playerid, false);
}
#if defined _ALS_TogglePlayerControllable
    #undef TogglePlayerControllable
#else
	native BAD_TogglePlayerControllable(playerid, toggle) = TogglePlayerControllable;
    #define _ALS_TogglePlayerControllable
#endif
#define TogglePlayerControllable FIX_TogglePlayerControllable

stock FIX_PutPlayerInVehicle(playerid, vehicleid, seatid)
{
	if (IsPlayerInAnyVehicle(playerid))
	{
		new
		    Float:x,
		    Float:y,
		    Float:z
		;
		GetVehiclePos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z);
	}

	return PutPlayerInVehicle(playerid, vehicleid, seatid);
}
#if defined _ALS_PutPlayerInVehicle
    #undef PutPlayerInVehicle
#else
	native BAD_PutPlayerInVehicle(playerid, vehicleid, seatid) = PutPlayerInVehicle;
    #define _ALS_PutPlayerInVehicle
#endif
#define PutPlayerInVehicle FIX_PutPlayerInVehicle

stock FIX_SpawnPlayer(playerid)
{
	if (IsPlayerInAnyVehicle(playerid))
	{
		new
		    Float:x,
		    Float:y,
		    Float:z
		;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z);
	}

	return SpawnPlayer(playerid);
}
#if defined _ALS_SpawnPlayer
	#undef SpawnPlayer
#else
	native BAD_SpawnPlayer(playerid) = SpawnPlayer;
	#define _ALS_SpawnPlayer
#endif
#define SpawnPlayer FIX_SpawnPlayer

stock FIX_SetPlayerName(playerid, const name[])
{
    new
		oldname[MAX_PLAYER_NAME]
	;
	GetPlayerName(playerid, oldname,MAX_PLAYER_NAME);
	if (! strcmp(name, oldname, true))
	{
		SetPlayerName(playerid, name);
		if (SetPlayerName(playerid, name) == -1)
		{
			SetPlayerName(playerid, oldname);
			return -1;
		}
		else
		{
			return 1;
		}
	}

	return SetPlayerName(playerid, name);
}
#if defined _ALS_SetPlayerName
	#undef SetPlayerName
#else
	native BAD_SetPlayerName(playerid, const name[]) = SetPlayerName;
	#define _ALS_SetPlayerName
#endif
#define SetPlayerName FIX_SetPlayerName

stock FIX_SetPlayerSkin(playerid, skinid)
{
	if (IsPlayerInAnyVehicle(playerid))
	{
		new
			Float:x,
		    Float:y,
		    Float:z,
		    ret,
		    vehicleid = GetPlayerVehicleID(playerid),
		    seatid = GetPlayerVehicleSeat(playerid)
		;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z);

		ret = SetPlayerSkin(playerid, skinid);
		
		#if defined SAMP_FIXER_SINGLES
		    t_PlayerSkin[playerid] = skinid;
		#else
			SetPVarInt(playerid, "FIX_GetPlayerSkin", skinid);
		#endif

		PutPlayerInVehicle(playerid, vehicleid, seatid);

		return ret;
	}

	return SetPlayerSkin(playerid, skinid);
}
#if defined _ALS_SetPlayerSkin
	#undef SetPlayerSkin
#else
	native BAD_SetPlayerSkin(playerid, skinid) = SetPlayerSkin;
	#define _ALS_SetPlayerSkin
#endif
#define SetPlayerSkin FIX_SetPlayerSkin

stock FIX_GetPlayerSkin(playerid)
{
	#if defined SAMP_FIXER_SINGLES
	    return t_PlayerSkin[playerid];
	#else
		return GetPVarInt(playerid, "FIX_GetPlayerSkin");
	#endif
}
#if defined _ALS_GetPlayerSkin
	#undef GetPlayerSkin
#else
	native BAD_GetPlayerSkin(playerid) = GetPlayerSkin;
	#define _ALS_GetPlayerSkin
#endif
#define GetPlayerSkin FIX_GetPlayerSkin

stock FIX_SetPlayerSpecialAction(playerid, actionid)
{
	if (actionid == SPECIAL_ACTION_USEJETPACK)
	{
		ClearAnimations(playerid, 1);
	}

	return SetPlayerSpecialAction(playerid, actionid);
}
#if defined _ALS_SetPlayerSpecialAction
    #undef SetPlayerSpecialAction
#else
	native BAD_SetPlayerSpecialAction(playerid, actionid) = SetPlayerSpecialAction;
    #define _ALS_SetPlayerSpecialAction
#endif
#define SetPlayerSpecialAction FIX_SetPlayerSpecialAction
