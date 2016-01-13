#if defined _fix_anims_included
	#endinput
#endif
#define _fix_anims_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_anims.inc
 *
 * ================
 *  LIST OF FIXES/ADDONS:
 * ================
 *
 * FIX:			Preload Anims
 * PROBLEM:  	Animations require to be preloaded once before applying.
 * SOLUTION: 	Preload the animation using a timer under ApplyAnimation (once).
 * CREDITS:		Gammix
 *
 */

static const t_AnimLibs[][] =
{
    "AIRPORT",      "Attractors",   "BAR",          "BASEBALL",     "BD_FIRE",
    "BEACH",        "benchpress",   "BF_injection", "BIKED",        "BIKEH",
    "BIKELEAP",     "BIKES",        "BIKEV",        "BIKE_DBZ",     "BLOWJOBZ",
    "BMX",          "BOMBER",       "BOX",          "BSKTBALL",     "BUDDY",
    "BUS",          "CAMERA",       "CAR",          "CARRY",        "CAR_CHAT",
    "CASINO",       "CHAINSAW",     "CHOPPA",       "CLOTHES",      "COACH",
    "COLT45",       "COP_AMBIENT",  "COP_DVBYZ",    "CRACK",        "CRIB",
    "DAM_JUMP",     "DANCING",      "DEALER",       "DILDO",        "DODGE",
    "DOZER",        "DRIVEBYS",     "FAT",          "FIGHT_B",      "FIGHT_C",
    "FIGHT_D",      "FIGHT_E",      "FINALE",       "FINALE2",      "FLAME",
    "Flowers",      "FOOD",         "Freeweights",  "GANGS",        "GHANDS",
    "GHETTO_DB",    "goggles",      "GRAFFITI",     "GRAVEYARD",    "GRENADE",
    "GYMNASIUM",    "HAIRCUTS",     "HEIST9",       "INT_HOUSE",    "INT_OFFICE",
    "INT_SHOP",     "JST_BUISNESS", "KART",         "KISSING",      "KNIFE",
    "LAPDAN1",      "LAPDAN2",      "LAPDAN3",      "LOWRIDER",     "MD_CHASE",
    "MD_END",       "MEDIC",        "MISC",         "MTB",          "MUSCULAR",
    "NEVADA",       "ON_LOOKERS",   "OTB",          "PARACHUTE",    "PARK",
    "PAULNMAC",     "ped",          "PLAYER_DVBYS", "PLAYIDLES",    "POLICE",
    "POOL",         "POOR",         "PYTHON",       "QUAD",         "QUAD_DBZ",
    "RAPPING",      "RIFLE",        "RIOT",         "ROB_BANK",     "ROCKET",
    "RUSTLER",      "RYDER",        "SCRATCHING",   "SHAMAL",       "SHOP",
    "SHOTGUN",      "SILENCED",     "SKATE",        "SMOKING",      "SNIPER",
    "SPRAYCAN",     "STRIP",        "SUNBATHE",     "SWAT",         "SWEET",
    "SWIM",         "SWORD",        "TANK",         "TATTOOS",      "TEC",
    "TRAIN",        "TRUCK",        "UZI",          "VAN",          "VENDING",
    "VORTEX",       "WAYFARER",     "WEAPONS",      "WUZI"
};

static
	t_PlayerAnimTimer[MAX_PLAYERS][sizeof(t_AnimLibs)]
;

public OnPlayerConnect(playerid)
{
	for (new i, j = sizeof(t_AnimLibs); i < j; i++)
	{
        t_PlayerAnimTimer[playerid][i] = 0;
	}

    #if defined ANIM_OnPlayerConnect
      return ANIM_OnPlayerConnect(playerid);
    #else
      return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
 	#undef OnPlayerConnect
#else
  	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect ANIM_OnPlayerConnect
#if defined ANIM_OnPlayerConnect
	forward ANIM_OnPlayerConnect(playerid);
#endif

stock FIX_AppliAnimation(playerid, animlib[], anim[], Float:vel = 4.1, bucle = 0, lockx = 1, locky = 1, freeze = 1, time = 1, sync = 1)
{
    if (! IsPlayerConnected(playerid))
    {
        return false;
    }

	for (new i, j = sizeof(t_AnimLibs); i < j; i ++)
	{
		if (! strcmp(animlib, t_AnimLibs[i], true))
	    {
	        if (! t_PlayerAnimTimer[playerid][i])
	        {
         		ApplyAnimation(playerid, animlib, "null", 0.0, 0, 0, 0, 0, 0);
         		
        		t_PlayerAnimTimer[playerid][i] = SetTimerEx("OnPlayerAnimPreload", 250, false, "iissfiiiiii", i, playerid, animlib, anim, vel, bucle, lockx, locky, freeze, time, sync);
	        }
	        else
	        {
	    		ApplyAnimation(playerid, animlib, anim, vel, bucle, lockx, locky, freeze, time, sync);
            }

			return true;
	    }
    }

	return false;
}
#if defined _ALS_AppliAnimation
  	#undef AppliAnimation
#else
	native BAD_AppliAnimation(playerid, animlib[], anim[], Float:vel, bucle, lockx, locky, freeze, time, sync) = AppliAnimation;
  	#define _ALS_AppliAnimation
#endif
#define AppliAnimation FIX_AppliAnimation

forward OnPlayerAnimPreload(i, playerid, animlib[], anim[], Float:vel, bucle, lockx, locky, freeze, time, sync);
public  OnPlayerAnimPreload(i, playerid, animlib[], anim[], Float:vel, bucle, lockx, locky, freeze, time, sync)
{
    ApplyAnimation(playerid, animlib, anim, vel, bucle, lockx, locky, freeze, time, sync);
    
    CallRemoteFunction("OnPlayerAnimPreloaded", "ii", i, playerid);
}

forward OnPlayerAnimPreloaded(i, playerid);
public  OnPlayerAnimPreloaded(i, playerid)
{
    t_PlayerAnimTimer[playerid][i] = 1;
}
