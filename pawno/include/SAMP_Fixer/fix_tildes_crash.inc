/*
		Safe game-text script. No more crash due to bad use of '~' character. 
		
		Basically, this script counts how many tildes are in a text, and checks if it's an odd number, then there's something wrong!
*/

#if defined _fix_tildes_crash_included
	#endinput
#endif
#define _fix_tildes_crash_included
#pragma library fix_tildes_crash

// Checks whether an integer is even or odd
#define IsOdd(%0) ((%0)&1)
#define IsEven(%0) (!IsOdd(%0))

// Checks whether a text is safe or might crash clients.
IsSafeGametext(text[])
{
	new cnt = 0;
	for(new i = 0, j = strlen(text); i < j; i ++)
	{
		if(text[i] == '~')
			cnt ++;
	}
	if(!IsEven(cnt))
		return 0;
	return 1;
}

// -- Hooked some functions to make them automatically reject unsafe game-texts and print out errors.


stock _HOOKED_GameTextForPlayer(playerid, string[], time, style)
{
	if(!IsSafeGametext(string))
	{
		printf("Error: bad use of tildes (~) in game-text\nRef: GameTextForPlayer(%d, %s, %d, %d)", playerid, string, time, style);
		return -1;
	}
	return GameTextForPlayer(playerid, string, time, style);
}

#if defined _ALS_GameTextForPlayer
	#undef GameTextForPlayer
#else
	#define _ALS_GameTextForPlayer
#endif

#define GameTextForPlayer _HOOKED_GameTextForPlayer

stock _HOOKED_GameTextForAll(string[], time, style)
{
	if(!IsSafeGametext(string))
	{
		printf("Error: bad use of tildes (~) in game-text\nRef: GameTextForAll(%s, %d, %d)", string, time, style);
		return -1;
	}

	return GameTextForAll(string, time, style);
}

#if defined _ALS_GameTextForAll
	#undef GameTextForAll
#else
	#define _ALS_GameTextForAll
#endif

#define GameTextForAll _HOOKED_GameTextForAll

stock Text:_HOOKED_TextDrawCreate(Float:x, Float:y, text[])
{
	if(!IsSafeGametext(text))
	{
		printf("Error: bad use of tildes (~) in game-text\nRef: TextDrawCreate(%f, %f, %s)", x, y, text);
	    return Text:INVALID_TEXT_DRAW;
	}
	return TextDrawCreate(x, y, text);
}

#if defined _ALS_TextDrawCreate
	#undef TextDrawCreate
#else
	#define _ALS_TextDrawCreate
#endif

#define TextDrawCreate _HOOKED_TextDrawCreate

stock PlayerText:_HOOKED_CreatePlayerTextDraw(playerid, Float:x, Float:y, text[])
{
	if(!IsSafeGametext(text))
	{
		printf("Error: bad use of tildes (~) in game-text\nRef: CreatePlayerTextDraw(%d, %f, %f, %s)", playerid, x, y, text);
	    return PlayerText:INVALID_TEXT_DRAW;
	}
	return CreatePlayerTextDraw(playerid, x, y, text);
}

#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif

#define CreatePlayerTextDraw _HOOKED_CreatePlayerTextDraw

stock _HOOKED_TextDrawSetString(Text:text, string[])
{
	if(!IsSafeGametext(string))
	{
		printf("Error: bad use of tildes (~) in game-text\nRef: TextDrawSetString(%s)", string);
		return -1;
	}

	return TextDrawSetString(text, string);
}

#if defined _ALS_TextDrawSetString
	#undef TextDrawSetString
#else
	#define _ALS_TextDrawSetString
#endif

#define TextDrawSetString _HOOKED_TextDrawSetString

stock _HOOKED_PlayerTextDrawSetString(playerid, PlayerText:text, string[])
{
	if(!IsSafeGametext(string))
	{
		printf("Error: bad use of tildes (~) in game-text\nRef: PlayerTextDrawSetString(%d, %s)", playerid, string);
		return -1;
	}

	return PlayerTextDrawSetString(playerid, text, string);
}

#if defined _ALS_PlayerTextDrawSetString
	#undef PlayerTextDrawSetString
#else
	#define _ALS_PlayerTextDrawSetString
#endif

#define PlayerTextDrawSetString _HOOKED_PlayerTextDrawSetString