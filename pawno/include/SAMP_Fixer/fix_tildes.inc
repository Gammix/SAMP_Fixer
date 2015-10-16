#if defined _fix_tildes_included
	#endinput
#endif
#define _fix_tildes_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_tildes.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			Textdraw/Gametext blank
 * PROBLEM:  	When the string of textdaws/gametexts is set to "", the server crashes.
 * SOLUTION: 	Check if the string's 0th element is 'EOS' and replace it with " ".
 *
 * FIX:			Uneven '~'s
 * PROBLEM:  	Manier times when you have uneven '~'s or placed them wrong, the server crashes.
 * SOLUTION: 	Add a check before setting the string of textdraws/gametexts.
 *
 * FIX:			Textdraw/Gametext encoding
 * PROBLEM:  	Sometimes textdraws or gametexts have un identified characters in them.
 * SOLUTION: 	Convert them into identified chars.
 *
 */

stock static const FIX_Encoding[256] =
{
	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
	16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
	32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
	48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
	64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
	80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
	96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
	112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160,  94, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
	124, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 175,
	128, 129, 130, 195, 131, 197, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141,
	208, 173, 142, 143, 144, 213, 145, 215, 216, 146, 147, 148, 149, 221, 222, 150,
	151, 152, 153, 227, 154, 229, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
	240, 174, 165, 166, 167, 245, 168, 247, 248, 169, 170, 171, 172, 253, 254, 255
};

stock static FIX_ReturnSafeString(string[])
{
	new
        safetil = -5
	;
        
	for (new i, j = strlen(string); i < j; ++i)
	{
	    switch (string[i])
		{
			case '0'..'9', 'A'..'Z', 'a'..'z', '~', '`', '!', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '[', ']', ';', ':', '"', '<', '>', '/', '?':
			{
		        if ((string[i] == 126) && (i > safetil))
		        {
		            if (i >= strlen(string) - 1)
		            {
		                return false;
					}
		            else if (string[i + 1] == 126)
		            {
						return false;
					}
		            else if (string[i + 2] != 126)
		            {
						return false;
					}
					else
					{
		            	safetil = i + 2;
		        	}
		        }
		        
		        continue;
	        }
			default:
			{
			    new
			        chr = string[i]
				;
			    if (0 <= chr < 256)
				{
					string[i] = FIX_Encoding[chr];
				}
				else
				{
				    string[i] = '?';
				}
	        }
   		}
	}
	
	return true;
}

stock TEXT_GameTextForPlayer(playerid, string[], time, style)
{
	if (string[0] == '\0' || (string[0] == '\1' && string[1] == '\0'))
	{
	    return GameTextForPlayer(playerid, " ", time, style);
	}
	else if (! FIX_ReturnSafeString(string))
	{
	    return -1;
	}
	else return GameTextForPlayer(playerid, string, time, style);
}
#if defined _ALS_GameTextForPlayer
	#undef GameTextForPlayer
#else
	#define _ALS_GameTextForPlayer
#endif
#define GameTextForPlayer TEXT_GameTextForPlayer

stock TEXT_GameTextForAll(string[], time, style)
{
	if (string[0] == '\0' || (string[0] == '\1' && string[1] == '\0'))
	{
	    return GameTextForAll(" ", time, style);
	}
	else if (! FIX_ReturnSafeString(string))
	{
	    return -1;
	}
	else return GameTextForAll(string, time, style);
}
#if defined _ALS_GameTextForAll
	#undef GameTextForAll
#else
	#define _ALS_GameTextForAll
#endif
#define GameTextForAll TEXT_GameTextForAll

stock Text:TEXT_TextDrawCreate(Float:x, Float:y, text[])
{
	if (text[0] == '\0' || (text[0] == '\1' && text[1] == '\0'))
	{
	    return TextDrawCreate(x, y, " ");
	}
	else if (! FIX_ReturnSafeString(text))
	{
	    return Text:INVALID_TEXT_DRAW;
	}
	else return TextDrawCreate(x, y, text);
}
#if defined _ALS_TextDrawCreate
	#undef TextDrawCreate
#else
	#define _ALS_TextDrawCreate
#endif
#define TextDrawCreate TEXT_TextDrawCreate

stock PlayerText:TEXT_CreatePlayerTextDraw(playerid, Float:x, Float:y, text[])
{
	if (text[0] == '\0' || (text[0] == '\1' && text[1] == '\0'))
	{
	    return CreatePlayerTextDraw(playerid, x, y, " ");
	}
	else if (! FIX_ReturnSafeString(text))
	{
	    return PlayerText:INVALID_TEXT_DRAW;
	}
	else return CreatePlayerTextDraw(playerid, x, y, text);
}
#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw TEXT_CreatePlayerTextDraw

stock TEXT_TextDrawSetString(Text:text, string[])
{
	if (string[0] == '\0' || (string[0] == '\1' && string[1] == '\0'))
	{
	    return TextDrawSetString(text, " ");
	}
	else if (! FIX_ReturnSafeString(string))
	{
	    return -1;
	}
	else return TextDrawSetString(text, string);
}

#if defined _ALS_TextDrawSetString
	#undef TextDrawSetString
#else
	#define _ALS_TextDrawSetString
#endif
#define TextDrawSetString TEXT_TextDrawSetString

stock TEXT_PlayerTextDrawSetString(playerid, PlayerText:text, string[])
{
	if (string[0] == '\0' || (string[0] == '\1' && string[1] == '\0'))
	{
	    return PlayerTextDrawSetString(playerid, text, " ");
	}
	else if (! FIX_ReturnSafeString(string))
	{
	    return -1;
	}
	return PlayerTextDrawSetString(playerid, text, string);
}

#if defined _ALS_PlayerTextDrawSetString
	#undef PlayerTextDrawSetString
#else
	#define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString TEXT_PlayerTextDrawSetString
