#if defined _fix_menu_included
	#endinput
#endif
#define _fix_menu_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_menu.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:   		Menu function crashes
 * PROBLEM:   	When an invalid menu is passes through any of the SA-MP file functions, the server crashes.
 * SOLUTION:  	Check if the menu is valid, if not return false.
 *
 */

#if defined SAMP_FIXER_SINGLES
	static
		bool:	t_IsValidMenu[MAX_MENUS],
		        t_PlayerMenu[MAX_PLAYERS]
	;
#endif

stock Menu:FIX_CreateMenu(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0)
{
	new
		Menu:ret = CreateMenu(title, columns, x, y, col1width, col2width)
	;

	if (Menu:0 <= ret < Menu:MAX_MENUS)
	{
		#if defined SAMP_FIXER_SINGLES
        	t_IsValidMenu[_:ret] = true;
		#else
		    new
		        buf[40]
			;
			format(buf, sizeof(buf), "menu_%i", _:ret);
			SetSVarInt(buf, 1);
		#endif
	}

	return ret;
}
#if defined _ALS_CreateMenu
	#undef CreateMenu
#else
	native Menu:BAD_CreateMenu(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0) = CreateMenu;
	#define _ALS_CreateMenu
#endif
#define CreateMenu FIX_CreateMenu

stock FIX_IsValidMenu(Menu:menudid)
{
    if (! (Menu:0 <= menuid < Menu:MAX_MENUS))
    {
		return false;
	}
    
	#if defined SAMP_FIXER_SINGLES
	    return t_IsValidMenu[_:ret];
	#else
 		new
			buf[40]
		;
		format(buf, sizeof(buf), "menu_%i", _:ret);
		return (GetSvarType(buf) == SERVER_VARTYPE_NONE) ? false : true;
	#endif
}
#if defined _ALS_IsValidMenu
	#undef IsValidMenu
#else
	native Menu:BAD_IsValidMenu(Menu:menuid) = IsValidMenu;
	#define _ALS_IsValidMenu
#endif
#define IsValidMenu FIX_IsValidMenu

stock FIX_DestroyMenu(Menu:menuid)
{
	if (! FIX_IsValidMenu(menudid))
	{
	    return false;
	}

	new
	    ret = DestroyMenu(menuid)
	;
	if (ret)
	{
	    t_IsValidMenu[_:menuid] = false;

		for (new i, j = GetPlayerPoolSize(); i <= j; i++)
		{
		    #if defined SAMP_FIXER_SINGLES
		        if (t_PlayerMenu[playerid] == menuid)
			#else
				if (GetPVarInt(playerid, "PlayerMenu") == _:menuid)
			#endif
			{
				if (HideMenuForPlayer(menuid, playerid))
				{
		    		#if defined SAMP_FIXER_SINGLES
		    		    t_PlayerMenu[playerid] = INVALID_MENU;
		    		#else
						DeletePVar(playerid, "PlayerMenu");
					#endif
				}
			}
		}
	}

	return ret;
}
#if defined _ALS_DestroyMenu
	#undef DestroyMenu
#else
	native BAD_DestroyMenu(Menu:menuid) = DestroyMenu;
	#define _ALS_DestroyMenu
#endif
#define DestroyMenu FIX_DestroyMenu

stock FIX_AddMenuItem(Menu:menuid, column, const menutext[])
{
	if (! FIX_IsValidMenu(menudid))
	{
	    return false;
	}
	else return AddMenuItem(menuid, column, menutext);
}
#if defined _ALS_AddMenuItem
	#undef AddMenuItem
#else
	native BAD_AddMenuItem(Menu:menuid, column, const menutext[]) = AddMenuItem;
	#define _ALS_AddMenuItem
#endif
#define AddMenuItem FIX_AddMenuItem

stock FIX_SetMenuColumnHeader(Menu:menuid, column, const columnheader[])
{
	if (! FIX_IsValidMenu(menudid))
	{
	    return false;
	}
	else return SetMenuColumnHeader(menuid, column, columnheader);
}
#if defined _ALS_SetMenuColumnHeader
	#undef SetMenuColumnHeader
#else
	native BAD_SetMenuColumnHeader(Menu:menuid, column, const columnheader[]) = SetMenuColumnHeader;
	#define _ALS_SetMenuColumnHeader
#endif
#define SetMenuColumnHeader FIX_SetMenuColumnHeader

stock FIX_ShowMenuForPlayer(Menu:menuid, playerid)
{
	if (! FIX_IsValidMenu(menudid))
	{
	    return false;
	}
	else
	{
 		#if defined SAMP_FIXER_SINGLES
   			t_PlayerMenu[playerid] = menuid;
		#else
	    	SetPVarInt(playerid, "PlayerMenu", _:menuid);
	    #endif
		return ShowMenuForPlayer(menuid, playerid);
	}
}
#if defined _ALS_ShowMenuForPlayer
	#undef ShowMenuForPlayer
#else
	native BAD_ShowMenuForPlayer(Menu:menuid, playerid) = ShowMenuForPlayer;
	#define _ALS_ShowMenuForPlayer
#endif
#define ShowMenuForPlayer FIX_ShowMenuForPlayer

stock FIX_HideMenuForPlayer(Menu:menuid, playerid)
{
	if (! FIX_IsValidMenu(menudid))
	{
	    return false;
	}
	else
	{
 		#if defined SAMP_FIXER_SINGLES
   			t_PlayerMenu[playerid] = INVALID_MENU;
		#else
			DeletePVar(playerid, "PlayerMenu");
	    #endif
		return HideMenuForPlayer(menuid, playerid);
	}
}
#if defined _ALS_HideMenuForPlayer
	#undef HideMenuForPlayer
#else
	native BAD_HideMenuForPlayer(Menu:menuid, playerid) = HideMenuForPlayer;
	#define _ALS_HideMenuForPlayer
#endif
#define HideMenuForPlayer FIX_HideMenuForPlayer

stock FIX_DisableMenu(Menu:menuid)
{
	if (! FIX_IsValidMenu(menudid))
	{
	    return false;
	}
	else return DisableMenu(menuid);
}
#if defined _ALS_DisableMenu
	#undef DisableMenu
#else
	native BAD_DisableMenu(Menu:menuid) = DisableMenu;
	#define _ALS_DisableMenu
#endif
#define DisableMenu FIX_DisableMenu

stock FIX_DisableMenuRow(Menu:menuid, row)
{
	if (! FIX_IsValidMenu(menudid))
	{
	    return false;
	}
	else return DisableMenuRow(menuid, row);
}
#if defined _ALS_DisableMenuRow
	#undef DisableMenuRow
#else
	native BAD_DisableMenuRow(Menu:menuid, row) = DisableMenuRow;
	#define _ALS_DisableMenuRow
#endif
#define DisableMenuRow FIX_DisableMenuRow

stock Menu:FIX_GetPlayerMenu(playerid)
{
	if (0 <= playerid < MAX_PLAYERS)
	{
 		#if defined SAMP_FIXER_SINGLES
			return t_PlayerMenu[playerid];
		#else
			return GetPVarInt(playerid, "PlayerMenu");
		#endif
	}
	else return Menu:INVALID_MENU;
}
#if defined _ALS_GetPlayerMenu
	#undef GetPlayerMenu
#else
	native BAD_GetPlayerMenu(playerid) = GetPlayerMenu;
	#define _ALS_GetPlayerMenu
#endif
#define GetPlayerMenu FIX_GetPlayerMenu
