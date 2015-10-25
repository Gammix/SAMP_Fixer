#if defined _fix_gangzone_included
	#endinput
#endif
#define _fix_gangzone_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_gangzone.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			GangZoneCreate
 * PROBLEM:  	Gangzones at certain angles show deviations or have disturbed position.
 * SOLUTION: 	Roundoff the gangzone positions.
 * CREDITS:		xX_Simon_Xx/Y_Less
 *
 * ADD:			IsValidGangZone(zone);
 * INFO:  		By default, this function doesn't exist. Lets you identify if the gangzone is existing or not.
 * CREDITS:		Gammix
 *
 */

#if defined SAMP_FIXER_SINGLES
	static
		bool:t_IsValidGangZone[MAX_GANG_ZONES]
	;
#endif

stock FIX_GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	new
		ret = GangZoneCreate(floatsub(minx, floatfract(minx)), floatsub(miny, floatfract(miny)), floatsub(maxx, floatfract(maxx)), floatsub(maxy, floatfract(maxy))),
		buf[40]
	;

	#if defined SAMP_FIXER_SINGLES
	    t_IsValidGangZone[ret] = true;
	#else
		format(buf, sizeof(buf), "gz_%i", ret);
		SetSVarInt(buf, 1);
	#endif
	
	return ret;
}
#if defined _ALS_GangZoneCreate
	#undef GangZoneCreate
#else
	native BAD_GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy) = GangZoneCreate;
	#define _ALS_GangZoneCreate
#endif
#define GangZoneCreate FIX_GangZoneCreate

stock FIX_GangZoneDestroy(zone)
{
	#if defined SAMP_FIXER_SINGLES
	    t_IsValidGangZone[zone] = false;
	#else
		new
			buf[40]
		;
		format(buf, sizeof(buf), "gz_%i", zone);
		DeleteSVar(buf);
	#endif

	return GangZoneDestroy(zone);
}
#if defined _ALS_GangZoneDestroy
	#undef GangZoneDestroy
#else
	native BAD_GangZoneDestroy(zone) = GangZoneDestroy;
	#define _ALS_GangZoneDestroy
#endif
#define GangZoneDestroy FIX_GangZoneDestroy

stock IsValidGangZone(zone)
{
	#if defined SAMP_FIXER_SINGLES
	    return t_IsValidGangZone[zone];
	#else
		new
			buf[40]
		;
		format(buf, sizeof(buf), "gz_%i", ret);

		return (GetSVarType(buf) == SVAR_TYPE_NONE) : false ? true;
	#endif
}
