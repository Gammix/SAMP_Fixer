#if defined _fix_gametext_included
	#endinput
#endif
#define _fix_gametext_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_gametext.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			GameTextForPlayer/GameTextForAll
 * PROBLEM:  	Few game text styles have a static timer which ignores "time" set in the native.
 * SOLUTION: 	Use custom textdraws for gametexts, allows to have a dynamic timer and custom colours.
 * CREDITS:		Gammix
 *
 * ADD:         GameTextForPlayer/GameTextForAll
 * INFO:        Adds new param "color" which allows you to have custom gametext color (hex)
 * CREDITS:		Gammix
 *
 */

#define GAMETEXT_MAX_STYLES (7)

#define _setaplha(%1,%2) (%1 & ~0xFF) | clamp(%2, 0x00, 0xFF)

enum e_GAMETEXT_DATA
{
	PlayerText:	gametextTD,
	            gametextTimer,
	            gametextColor,
	            gametextFadeLevel,
	            gametextExpireTime
};

static
	t_GameText[MAX_PLAYERS][GAMETEXT_MAX_STYLES][e_GAMETEXT_DATA]
;

static const t_GameTextDefaultColor[GAMETEXT_MAX_STYLES] =
{
	0x906210FF,
	0x906210FF,
	0xE1E1E1FF,
	0x906210FF,
	0x906210FF,
	0xE1E1E1FF,
	0xACCBF1FF
};

stock FIX_GameTextForPlayer(playerid, string[], time, style, color = -1)
{
	if (! IsPlayerConnected(playerid))
	{
		return false;
	}

	if (t_GameText[playerid][style][gametextTimer] != -1)
	{
		KillTimer(t_GameText[playerid][style][gametextTimer]);
	}

	if (color == -1)
	{
	    color = t_GameTextDefaultColor[style];
	}

	t_GameText[playerid][style][gametextColor] = color;
	t_GameText[playerid][style][gametextFadeLevel] = 0;
	t_GameText[playerid][style][gametextExpireTime] = time;

	PlayerTextDrawColor(playerid, t_GameText[playerid][style][gametextTD], _setaplha(color, 0));
	PlayerTextDrawSetString(playerid, t_GameText[playerid][style][gametextTD], string);
	PlayerTextDrawShow(playerid, t_GameText[playerid][style][gametextTD]);

	t_GameText[playerid][style][gametextTimer] = SetTimerEx("OnGameTextUpdate", 30, true, "iii", playerid, style, 0);

	return true;
}
#if defined _ALS_GameTextForPlayer
	#undef GameTextForPlayer
#else
	native BAD_GameTextForPlayer(playerid, const string[], time, style) = GameTextForPlayer;
	#define _ALS_GameTextForPlayer
#endif
#define GameTextForPlayer FIX_GameTextForPlayer

stock FIX_GameTextForAll(string[], time, style, color = -1)
{
	for (new i, j = GetPlayerPoolSize(); i <= j; i++)
	{
		if (IsPlayerConnected(i))
		{
		    FIX_GameTextForPlayer(i, string, time, style, color);
		}
	}

	return true;
}
#if defined _ALS_GameTextForAll
	#undef GameTextForAll
#else
	native BAD_GameTextForAll(const string[], time, style) = GameTextForAll;
	#define _ALS_GameTextForAll
#endif
#define GameTextForAll FIX_GameTextForAll

forward OnGameTextUpdate(playerid, style, fadetype);
public  OnGameTextUpdate(playerid, style, fadetype)
{
	switch (fadetype)
	{
	    case 0:
	    {
	        t_GameText[playerid][style][gametextFadeLevel] += 15;
			PlayerTextDrawColor(playerid, t_GameText[playerid][style][gametextTD], _setaplha(t_GameText[playerid][style][gametextColor], t_GameText[playerid][style][gametextFadeLevel]));

			if (t_GameText[playerid][style][gametextFadeLevel] >= 255)
			{
				KillTimer(t_GameText[playerid][style][gametextTimer]);
				OnGameTextUpdate(playerid, style, 1);
			}
			PlayerTextDrawShow(playerid, t_GameText[playerid][style][gametextTD]);
	    }
	    case 1:
	    {
			t_GameText[playerid][style][gametextTimer] = SetTimerEx("OnGameTextUpdate", t_GameText[playerid][style][gametextExpireTime], false, "iii", playerid, style, 2);
	    }
	    case 2:
	    {
	        KillTimer(t_GameText[playerid][style][gametextTimer]);
			t_GameText[playerid][style][gametextTimer] = SetTimerEx("OnGameTextUpdate", 30, true, "iii", playerid, style, 3);
	    }
	    case 3:
	    {
	        t_GameText[playerid][style][gametextFadeLevel] -= 15;
			PlayerTextDrawColor(playerid, t_GameText[playerid][style][gametextTD], _setaplha(t_GameText[playerid][style][gametextColor], t_GameText[playerid][style][gametextFadeLevel]));

			if (t_GameText[playerid][style][gametextFadeLevel] <= 0)
			{
				PlayerTextDrawHide(playerid, t_GameText[playerid][style][gametextTD]);

				KillTimer(t_GameText[playerid][style][gametextTimer]);
				t_GameText[playerid][style][gametextTimer] = -1;
			}
			else
			{
				PlayerTextDrawShow(playerid, t_GameText[playerid][style][gametextTD]);
			}
	    }
	}
}

public OnPlayerConnect(playerid)
{
	t_GameText[playerid][0][gametextTD] = CreatePlayerTextDraw(playerid, 320.000000, 214.000000, "_");
	PlayerTextDrawAlignment(playerid, t_GameText[playerid][0][gametextTD], 2);
	PlayerTextDrawBackgroundColor(playerid, t_GameText[playerid][0][gametextTD], 255);
	PlayerTextDrawFont(playerid, t_GameText[playerid][0][gametextTD], 3);
	PlayerTextDrawLetterSize(playerid, t_GameText[playerid][0][gametextTD], 1.299998, 3.599998);
	PlayerTextDrawColor(playerid, t_GameText[playerid][0][gametextTD], t_GameTextDefaultColor[0]);
	PlayerTextDrawSetOutline(playerid, t_GameText[playerid][0][gametextTD], 2);
	PlayerTextDrawSetProportional(playerid, t_GameText[playerid][0][gametextTD], 1);
	PlayerTextDrawSetSelectable(playerid, t_GameText[playerid][0][gametextTD], 0);

	t_GameText[playerid][1][gametextTD] = CreatePlayerTextDraw(playerid, 620.000000, 310.000000, "_");
	PlayerTextDrawAlignment(playerid, t_GameText[playerid][1][gametextTD], 3);
	PlayerTextDrawBackgroundColor(playerid, t_GameText[playerid][1][gametextTD], 255);
	PlayerTextDrawFont(playerid, t_GameText[playerid][1][gametextTD], 3);
	PlayerTextDrawLetterSize(playerid, t_GameText[playerid][1][gametextTD], 1.000000, 2.599998);
	PlayerTextDrawColor(playerid, t_GameText[playerid][1][gametextTD], t_GameTextDefaultColor[1]);
	PlayerTextDrawSetOutline(playerid, t_GameText[playerid][1][gametextTD], 2);
	PlayerTextDrawSetProportional(playerid, t_GameText[playerid][1][gametextTD], 1);
	PlayerTextDrawSetSelectable(playerid, t_GameText[playerid][1][gametextTD], 0);

	t_GameText[playerid][2][gametextTD] = CreatePlayerTextDraw(playerid, 320.000000, 156.000000, "_");
	PlayerTextDrawAlignment(playerid, t_GameText[playerid][2][gametextTD], 2);
	PlayerTextDrawBackgroundColor(playerid, t_GameText[playerid][2][gametextTD], 255);
	PlayerTextDrawFont(playerid, t_GameText[playerid][2][gametextTD], 0);
	PlayerTextDrawLetterSize(playerid, t_GameText[playerid][2][gametextTD], 2.099998, 4.199998);
	PlayerTextDrawColor(playerid, t_GameText[playerid][2][gametextTD], t_GameTextDefaultColor[2]);
	PlayerTextDrawSetOutline(playerid, t_GameText[playerid][2][gametextTD], 3);
	PlayerTextDrawSetProportional(playerid, t_GameText[playerid][2][gametextTD], 1);
	PlayerTextDrawSetSelectable(playerid, t_GameText[playerid][2][gametextTD], 0);

	t_GameText[playerid][3][gametextTD] = CreatePlayerTextDraw(playerid, 320.000000, 154.000000, "_");
	PlayerTextDrawAlignment(playerid, t_GameText[playerid][3][gametextTD], 2);
	PlayerTextDrawBackgroundColor(playerid, t_GameText[playerid][3][gametextTD], 255);
	PlayerTextDrawFont(playerid, t_GameText[playerid][3][gametextTD], 2);
	PlayerTextDrawLetterSize(playerid, t_GameText[playerid][3][gametextTD], 0.600000, 2.750000);
	PlayerTextDrawColor(playerid, t_GameText[playerid][3][gametextTD], t_GameTextDefaultColor[3]);
	PlayerTextDrawSetOutline(playerid, t_GameText[playerid][3][gametextTD], 2);
	PlayerTextDrawSetProportional(playerid, t_GameText[playerid][3][gametextTD], 1);
	PlayerTextDrawSetSelectable(playerid, t_GameText[playerid][3][gametextTD], 0);

	t_GameText[playerid][4][gametextTD] = CreatePlayerTextDraw(playerid, 320.000000, 115.000000, "_");
	PlayerTextDrawAlignment(playerid, t_GameText[playerid][4][gametextTD], 2);
	PlayerTextDrawBackgroundColor(playerid, t_GameText[playerid][4][gametextTD], 255);
	PlayerTextDrawFont(playerid, t_GameText[playerid][4][gametextTD], 2);
	PlayerTextDrawLetterSize(playerid, t_GameText[playerid][4][gametextTD], 0.600000, 2.750000);
	PlayerTextDrawColor(playerid, t_GameText[playerid][4][gametextTD], t_GameTextDefaultColor[4]);
	PlayerTextDrawSetOutline(playerid, t_GameText[playerid][4][gametextTD], 2);
	PlayerTextDrawSetProportional(playerid, t_GameText[playerid][4][gametextTD], 1);
	PlayerTextDrawSetSelectable(playerid, t_GameText[playerid][4][gametextTD], 0);

	t_GameText[playerid][5][gametextTD] = CreatePlayerTextDraw(playerid, 320.000000, 217.000000, "_");
	PlayerTextDrawAlignment(playerid, t_GameText[playerid][5][gametextTD], 2);
	PlayerTextDrawBackgroundColor(playerid, t_GameText[playerid][5][gametextTD], 255);
	PlayerTextDrawFont(playerid, t_GameText[playerid][5][gametextTD], 2);
	PlayerTextDrawLetterSize(playerid, t_GameText[playerid][5][gametextTD], 0.600000, 2.750000);
	PlayerTextDrawColor(playerid, t_GameText[playerid][5][gametextTD], t_GameTextDefaultColor[5]);
	PlayerTextDrawSetOutline(playerid, t_GameText[playerid][5][gametextTD], 2);
	PlayerTextDrawSetProportional(playerid, t_GameText[playerid][5][gametextTD], 1);
	PlayerTextDrawSetSelectable(playerid, t_GameText[playerid][5][gametextTD], 0);

	t_GameText[playerid][6][gametextTD] = CreatePlayerTextDraw(playerid, 320.000000, 60.000000, "_");
	PlayerTextDrawAlignment(playerid, t_GameText[playerid][6][gametextTD], 2);
	PlayerTextDrawBackgroundColor(playerid, t_GameText[playerid][6][gametextTD], 255);
	PlayerTextDrawFont(playerid, t_GameText[playerid][6][gametextTD], 3);
	PlayerTextDrawLetterSize(playerid, t_GameText[playerid][6][gametextTD], 1.000000, 3.599999);
	PlayerTextDrawColor(playerid, t_GameText[playerid][6][gametextTD], t_GameTextDefaultColor[6]);
	PlayerTextDrawSetOutline(playerid, t_GameText[playerid][6][gametextTD], 2);
	PlayerTextDrawSetProportional(playerid, t_GameText[playerid][6][gametextTD], 1);
	PlayerTextDrawSetSelectable(playerid, t_GameText[playerid][6][gametextTD], 0);

	#if defined GT_OnPlayerConnect
        return GT_OnPlayerConnect(playerid);
    #else
    	return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect GT_OnPlayerConnect
#if defined GT_OnPlayerConnect
	forward GT_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	for(new i; i < GAMETEXT_MAX_STYLES; i++)
	{
		t_GameText[playerid][i][gametextTD] = PlayerText:INVALID_TEXT_DRAW;
		if (t_GameText[playerid][i][gametextTimer] != -1)
		{
		    KillTimer(t_GameText[playerid][i][gametextTimer]);
		    t_GameText[playerid][i][gametextTimer] = -1;
		}
	}

	#if defined GT_OnPlayerDisconnect
        return GT_OnPlayerDisconnect(playerid, reason);
    #else
    	return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect GT_OnPlayerDisconnect
#if defined GT_OnPlayerDisconnect
	forward GT_OnPlayerDisconnect(playerid, reason);
#endif

#undef GAMETEXT_MAX_STYLES
#undef _setaplha
