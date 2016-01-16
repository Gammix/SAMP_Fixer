#if defined _fix_lagcomp_included
	#endinput
#endif
#define _fix_lagcomp_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_lagcomp.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			SAMP Lagcomp
 * PROBLEM:  	Lagcomp at certain points/situtations doesn't call hits/damage, also melee attack is completely bugged.
 * SOLUTION:    Set all players to same team and handle damage server sided.
 * CREDITS:		Gammix
 *
 */

static
    t_PlayerTeam[MAX_PLAYERS]
;

public OnPlayerSpawn(playerid)
{
	t_PlayerTeam[playerid] = GetPlayerTeam(playerid);
	
	#if defined LC_OnPlayerSpawn
        return LC_OnPlayerSpawn(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn LC_OnPlayerSpawn
#if defined LC_OnPlayerSpawn
    forward LC_OnPlayerSpawn(playerid);
#endif

forward OnPlayerTeamSet(playerid, teamid);
public 	OnPlayerTeamSet(playerid, teamid)
{
    t_PlayerTeam[playerid] = teamid;
}

stock LC_SetPlayerTeam(playerid, teamid)
{
    if (playerid < 0 || playerid >= MAX_PLAYERS)
	{
		return false;
	}

	CallRemoteFunction("OnPlayerTeamSet", "ii", playerid, teamid);

	return true;
}
#if defined _ALS_SetPlayerTeam
    #undef SetPlayerTeam
#else
	native OLD_SetPlayerTeam(playerid, teamid) = SetPlayerTeam;
    #define _ALS_SetPlayerTeam
#endif
#define SetPlayerTeam LC_SetPlayerTeam

stock LC_GetPlayerTeam(playerid)
{
    if (playerid < 0 || playerid >= MAX_PLAYERS)
	{
		return false;
	}

	return t_PlayerTeam[playerid];
}
#if defined _ALS_GetPlayerTeam
    #undef GetPlayerTeam
#else
	native OLD_GetPlayerTeam(playerid) = GetPlayerTeam;
    #define _ALS_GetPlayerTeam
#endif
#define GetPlayerTeam LC_GetPlayerTeam

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    if (t_PlayerTeam[playerid] == NO_TEAM || t_PlayerTeam[issuerid] == NO_TEAM || GetPlayerTeam(playerid) != GetPlayerTeam(issuerid))
    {
        if (issuerid != INVALID_PLAYER_ID)
        {
	        if (weaponid == WEAPON_KNIFE && _:amount == _:0.0)
	        {
	            SetPlayerHealth(playerid, 0.0);
	        }
	        else
	        {
	            new Float:health;
	            GetPlayerHealth(playerid, health);
	
	            new Float:armour;
	            GetPlayerArmour(playerid, armour);
	
	            if (amount >= health + armour)
			    {
				    SetPlayerArmour(playerid, 0.0);
			    	SetPlayerHealth(playerid, 0.0);
			    }
			    else
			    {
			        if (armour)
					{
					    new Float:loss = armour - amount;
		   				SetPlayerArmour(playerid, armour - amount);
	
						if (loss < 0.0)
						{
						    SetPlayerHealth(playerid, health + loss);
						}
					}
					else
					{
					    SetPlayerHealth(playerid, health - amount);
					}
				}
		    }
        }
    }

	#if defined LC_OnPlayerTakeDamage
        return LC_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerTakeDamage
    #undef OnPlayerTakeDamage
#else
    #define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage LC_OnPlayerTakeDamage
#if defined LC_OnPlayerTakeDamage
    forward LC_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
#endif
