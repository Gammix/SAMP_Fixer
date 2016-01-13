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
 */

stock FIX_GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	return GangZoneCreate(floatsub(minx, floatfract(minx)), floatsub(miny, floatfract(miny)), floatsub(maxx, floatfract(maxx)), floatsub(maxy, floatfract(maxy))),
}
#if defined _ALS_GangZoneCreate
	#undef GangZoneCreate
#else
	native BAD_GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy) = GangZoneCreate;
	#define _ALS_GangZoneCreate
#endif
#define GangZoneCreate FIX_GangZoneCreate
