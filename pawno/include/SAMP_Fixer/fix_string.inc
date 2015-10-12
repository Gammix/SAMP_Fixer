#if defined _fix_string_included
	#endinput
#endif
#define _fix_string_included
#pragma library fix_string

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_string.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			strins
 * PROBLEM:  	Ignores the "maxlength" parameter causing possible crashes.
 * SOLUTION:   	Manually check the length.
 *
 * FIX:         valstr
 * PROBLEM:  	Crashes on large numbers.
 * SOLUTION:  	Use "format" instead.
 *
 * ADD:			strsplit(source[], dest[][], delimeter = ' ', size = sizeof(dest[]));
 * INFO:  		Distribute strings with respect to a special character.
 *
 * ADD:			strbin(source[], const dest[], maxlength = sizeof(dest));
 * INFO:  		Convert a string into its binary form (1s and 0s).
 *
 * ADD:			strreplace(source[], const search[], const replace[], bool:ignorecase = false, limit = -1);
 * INFO:  		Replace special characters from the whole string.
 *
 */

stock FIX_strins(string[], const substr[], pos, maxlength = sizeof(string))
{
	if (string[0] > 255)
	{
		new
			strlength = strlen(string),
			sublength = strlen(substr),
			m4 = maxlength * 4
		;

		if (strlength + sublength >= m4)
		{
			if (pos + sublength >= m4)
			{
				return string{pos} = '\0', strcat(string, substr, maxlength);
			}
			else
			{
				string{maxlength - sublength - 1} = '\0';
			}
		}
		return strins(string, substr, pos, maxlength);
	}
	else if (substr[0] > 255)
	{
		new
			strlength = strlen(string),
			sublength = strlen(substr)
		;

		if (strlength + sublength >= maxlength)
		{
			if (pos + sublength >= maxlength)
			{
				return string[pos] = '\0', strcat(string, substr, maxlength);
			}
			else
			{
				string[maxlength - sublength - 1] = '\0';
			}
		}

		return strins(string, substr, pos, maxlength);
	}
	else
	{
		return format(string, maxlength, "%.*s%s%s", pos, string, substr, string[pos]);
	}
}
#if defined _ALS_strins
	#undef strins
#else
	native BAD_strins(string[], const substr[], pos, maxlength = sizeof(string)) = strins;
	#define _ALS_strins
#endif
#define strins FIX_strins

stock FIX_valstr(dest[], value, bool:pack = false)
{
	static const
		cellmin[] = !"-2147483648"
	;
	if (value == cellmin)
	{
		pack && strpack(dest, sc_szCellmin, 12) || strunpack(dest, sc_szCellmin, 12);
	}
	else
	{
		format(dest, 12, "%d", value), pack && strpack(dest, dest, 12);
	}

	return 0;
}
#if defined _ALS_valstr
	#undef valstr
#else
	native BAD_valstr(dest[], value, bool:pack = false) = valstr;
	#define _ALS_valstr
#endif
#define valstr FIX_valstr

stock strsplit(source[], dest[][], delimeter = ' ', size = sizeof(dest[]))
{
	new
	    k,
	    l
	;
	for (new i, j = strlen(src); i <= j; i++)
	{
		if (src[i] == delimeter || i == j)
		{
			new
			    m = strmid(dest[k], src, l, i, size)
			;

   			dest[k][m] = 0;

   			l = i + 1;
   			k += 1;
		}
	}

	return k;
}

stock strbin(source[], const dest[], maxlength = sizeof(dest))
{
	for (new i, j = strlen(source); i < j; i++)
	{
		new
			mask = 1 << (8 - 1),
			bits[8]
		;

		for (new d; d < 8; d++)
		{
			if ((str[i] & mask) == 0)
			{
				bits[d] = '0';
			}
			else
			{
				bits[d] = '1';
			}

			mask >>= 1;
		}

		strcat(dest, bits, maxlength);
   	}
}

stock strreplace(source[], const search[], const replace[], bool:ignorecase = false, limit = -1)
{
	new
		count,
		i = strfind(source, search, ignorecase)
	;

	while (i != -1 && count <= limit)
	{
		strdel(source, i, i + (l[1] - 1));
		strins(source, replace, i, l[0]);

		i = strfind(source, search, ignorecase);
		
		count++;
			
		if (limit >= 0 && count > limit)
		{
			return count;
		}
	}

	return count;
}
