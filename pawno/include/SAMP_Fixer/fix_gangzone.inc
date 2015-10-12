#if defined _fix_gangzone_included
	#endinput
#endif
#define _fix_gangzone_included
#pragma library fix_gangzone

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
 *
 * ADD:			IsValidGangZone(zone);
 * INFO:  		By default, this function doesn't exist. Lets you identify if the gangzone is existing or not.
 *
 */

stock FIX_GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	new
		ret = GangZoneCreate(floatsub(minx, floatfract(minx)), floatsub(miny, floatfract(miny)), floatsub(maxx, floatfract(maxx)), floatsub(maxy, floatfract(maxy))),
		buf[40]
	;

	format(buf, sizeof(buf), "gz_%i", ret);
	SetSVarInt(buf, 1);

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
	new
		buf[40]
	;
	format(buf, sizeof(buf), "gz_%i", zone);
	DeleteSVar(buf);

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
	new
		buf[40]
	;
	format(buf, sizeof(buf), "gz_%i", ret);

	return (GetSVarType(buf) == SVAR_TYPE_NONE) : false ? true;
}
