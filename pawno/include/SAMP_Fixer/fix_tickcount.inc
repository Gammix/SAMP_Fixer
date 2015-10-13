/*
		This library hooks and fixes GetTickCount() and tickcount() 
		
		Main issue, from SA-MP wiki, "GetTickCount will cause problems on servers with uptime of over 24 days (SA:MP server, not physical server !!!) 
		as GetTickCount will eventually warp past the integer size constraints".
		
		This code hooks both functions to adjust and convert return-values from negative to positive by adding 2,147,483,647 to negative values.

*/

// Fix GetTickCount
stock _HOOKED_GetTickCount()
{
	new _RETURNED_TICKCOUNT = GetTickCount();
	if(_RETURNED_TICKCOUNT < 0) // Check if it's negative
	{
		// Make it positive by addition. Btw, 2147483647 is the max value for a 32-bit signed binary integer.
		_RETURNED_TICKCOUNT = 2147483647 + _RETURNED_TICKCOUNT;
	}
	return _RETURNED_TICKCOUNT;
}
 
#if defined _ALS_GetTickCount
	#undef GetTickCount
#else
	#define _ALS_GetTickCount
#endif
 
#define GetTickCount _HOOKED_GetTickCount

// Fix tickcount
stock _HOOKED_tickcount()
{
	new _RETURNED_TICKCOUNT = tickcount();
	if(_RETURNED_TICKCOUNT < 0) // Check if it's negative
	{
		// Make it positive by addition. Btw, 2147483647 is the max value for a 32-bit signed binary integer.
		_RETURNED_TICKCOUNT = 2147483647 + _RETURNED_TICKCOUNT;
	}
	return _RETURNED_TICKCOUNT;
}
 
#if defined _ALS_tickcount
	#undef tickcount
#else
	#define _ALS_tickcount
#endif
 
#define tickcount _HOOKED_tickcount