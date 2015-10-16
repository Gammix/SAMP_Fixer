#if defined _fix_tickcount_included
	#endinput
#endif
#define _fix_tickcount_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_tickcount.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			GetTickCount
 * PROBLEM:  	GetTickCount will cause problems on servers with uptime of over 24 days.
 * SOLUTION: 	Add 2147483647 to the original tick count when the value is negative.
 *
 * FIX:			tickcount
 * PROBLEM:  	tickcount will cause problems on servers with uptime of over 24 days.
 * SOLUTION: 	Add 2147483647 to the original tick count when the value is negative.
 *
 */

stock FIX_GetTickCount()
{
	new
		ret = GetTickCount()
	;
	if (ret < 0)
	{
		ret += 2147483647;
	}
	return ret;
}
#if defined _ALS_GetTickCount
	#undef GetTickCount
#else
	#define _ALS_GetTickCount
#endif

#define GetTickCount FIX_GetTickCount

stock FIX_tickcount()
{
	new
		ret = tickcount()
	;
	if (ret < 0)
	{
		ret += 2147483647;
	}
	return ret;
}
#if defined _ALS_tickcount
	#undef tickcount
#else
	#define _ALS_tickcount
#endif
#define tickcount FIX_tickcount
