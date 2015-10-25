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
 * FIX:			ApplyAnimation
 * PROBLEM:  	Crashes when invalid library passed in. Rapid executions may cause a crash as well.
 * SOLUTION: 	Validity check for animlibs and last execution check to prevent crash.
 * CREDITS:		Gammix
 *
 * ADD:			Preload Anims
 * PROBLEM:  	Animations require to be preloaded once before applying.
 * SOLUTION: 	Preload all animations under OnPlayerSpawn (once only).
 * CREDITS:		Gammix
 *
 */

enum e_ANIM_DATA
{
	bool:   animLoaded,
	        animLastExtecution,
	        animLast[32]
};

static
	t_PlayerAnim[MAX_PLAYERS][e_ANIM_DATA]
;

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

public OnPlayerSpawn(playerid)
{
	if (! t_PlayerAnim[playerid][animLoaded])
	{
    	for (new i, j = sizeof(t_AnimLibs); i < j; i++)
    	{
        	ApplyAnimation(playerid, t_AnimLibs[i], "null", 4.0, 0, 0, 0, 0, 0, 1);
    	}

    	t_PlayerAnim[playerid][animLoaded] = true;
	}

    #if defined ANIM_OnPlayerSpawn
      	return ANIM_OnPlayerSpawn(playerid);
    #else
      	return 1;
    #endif
}
#if defined _ALS_OnPlayerSpawn
  	#undef OnPlayerSpawn
#else
  	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn ANIM_OnPlayerSpawn
#if defined ANIM_OnPlayerSpawn
	forward ANIM_OnPlayerSpawn(playerid);
#endif

public OnPlayerConnect(playerid)
{
    t_PlayerAnim[playerid][animLoaded] = false;
    t_PlayerAnim[playerid][animLastExtecution] = 0;
    t_PlayerAnim[playerid][animLast][0] = EOS;

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

    if (! strcmp(t_PlayerAnim[playerid][animLast], anim, true))
    {
    	if (t_PlayerAnim[playerid][animLastExecution] > gettime())
   		{
         	return false;
 		}
   	}

	for (new i, j = sizeof(t_AnimLibs); i < j; i ++)
	{
		if (! strcmp(animlib, t_AnimLibs[i], true))
	    {
	    	ApplyAnimation(playerid, animlib, anim, vel, bucle, lockx, locky, freeze, time, sync);
            format(t_PlayerAnim[playerid][animLast], 32, anim);
            t_PlayerAnim[playerid][animLastExecution] = gettime() + 1;

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
