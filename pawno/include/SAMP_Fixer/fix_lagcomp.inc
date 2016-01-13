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
        if (weaponid == WEAPON_KNIFE && amount > 1.0)
        {
            SetPlayerHealth(playerid, 0.0);
        }
        else if (issuerid != INVALID_PLAYER_ID)
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

	return 1;
}
