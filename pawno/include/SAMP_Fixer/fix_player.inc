#if defined _fix_string_included
	#endinput
#endif
#define _fix_string_included

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
 * CREDITS:		Slice/Y_Less
 *
 * FIX:         valstr
 * PROBLEM:  	Crashes on large numbers.
 * SOLUTION:  	Use "format" instead.
 * CREDITS:		Slice
 *
 * FIX:         strcmp
 * PROBLEM:  	Return 0 if anyone of the string is empty.
 * SOLUTION:  	Return 1 if the 1 string is empty and second is not.
 * CREDITS:		Gammix
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
		__cellmin[] = !"-2147483648"
	;
	if (value == cellmin)
	{
		pack && strpack(dest, __cellmin, 12) || strunpack(dest, __cellmin, 12);
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

stock FIX_strcmp(const string1[], const string2[], bool:ignorecase = false, length = cellmax)
{
	if (ignorecase)
	{
		if (string1[0] != string2[0])
		{
			return 1;
		}
	}
	else
	{
		if (strlen(string1) != strlen(string2))
		{
			return 1;
		}
	}

	return strcmp(string1, string2, ignorecase, length);
}
#if defined _ALS_strcmp
	#undef strcmp
#else
	native BAD_strcmp(const string1[], const string2[], bool:ignorecase = false, length = cellmax) = strcmp;
	#define _ALS_strcmp
#endif
#define strcmp FIX_strcmp
