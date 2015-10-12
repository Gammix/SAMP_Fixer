#if defined _fix_attachments_included
	#endinput
#endif
#define _fix_attachments_included
#pragma library fix_attachments

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_attachments.inc
 *
 * ================
 *  LIST OF FIXES/ADDONS:
 * ================
 *
 * FIX:			SetPlayerAttachedObject
 * PROBLEM:  	The attached objects hovers the camera while zooming with certain weapons like Sniper rifle, RPG etc.
 * SOLUTION: 	Temporarily remove player attached objects while player is in zooming session.
 *
 * FIX:			Destroy attached objects
 * PROBLEM:  	The attached objects doesn't get auto destroy when player disconnects.
 * SOLUTION: 	Destroy them under OnPlayerDisconnect.
 *
 * ADD:         GetPlayerAttachedObject(playerid, index, &modelid, &bone, &Float:fOffsetX, &Float:fOffsetY, &Float:fOffsetZ, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fScaleX, &Float:fScaleY, &Float:fScaleZ, &materialcolor1, &materialcolor2);
 * INFO:  		You can read all attachement info. by specifing the index into the stock.
 *
 */

public OnPlayerDisconnect(playerid, reason)
{
	new
		buf[40]
	;
	for (new i; i < MAX_PLAYER_ATTACHED_OBJECTS; i++)
	{
 		format(buf, sizeof(buf), "att%_used", i);
		if (GetPVarInt(playerid, buf))
	    {
	        RemovePlayerAttachedObject(playerid, i);
	    }
	}

    #if defined ATT_OnPlayerDisconnect
       	return ATT_OnPlayerDisconnect(playerid, reason);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect ATT_OnPlayerDisconnect
#if defined ATT_OnPlayerDisconnect
    forward ATT_OnPlayerDisconnect(playerid, reason);
#endif

#if ! defined KEY_AIM
	#define KEY_AIM 128
#endif

#if ! defined HOLDING
    #define HOLDING(%0) ((newkeys & (%0)) == (%0))
#endif

#if ! defined RELEASED
	#define RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (HOLDING(KEY_AIM))
	{
	    switch (GetPlayerWeapon(playerid))
		{
			case WEAPON_SNIPER, WEAPON_ROCKETLAUNCHER, WEAPON_HEATSEEKER, WEAPON_CAMERA:
			{
				new
			 		buf[40]
				;
			    for (new i; i < MAX_PLAYER_ATTACHED_OBJECTS; i++)
				{
					format(buf, sizeof(buf), "att%i_used", i);
				    if (IsPlayerAttachedObjectSlotUsed(playerid, i) && GetPVarInt(playerid, buf))
				    {
						RemovePlayerAttachedObject(playerid, i);
	     			}
		        }
		    }
		}
	}
	else if(RELEASED(KEY_AIM))
	{
		new
			buf[40]
		;
	    for (new i; i < MAX_PLAYER_ATTACHED_OBJECTS; i++)
		{
			format(buf, sizeof(buf), "att%i_used", i);
		    if (! IsPlayerAttachedObjectSlotUsed(playerid, i) && GetPVarInt(playerid, buf))
		    {
		        new
		            		modelid,
		            		boneid,
		            Float:  offset[3],
		            Float:  rot[3],
		            Float:  scale[3],
		                    color[2]
				;
				format(buf, sizeof(buf), "att%_modelid", i);
				modelid = GetPVarInt(playerid, buf);

				format(buf, sizeof(buf), "att%_bone", i);
				boneid = GetPVarInt(playerid, buf);

				format(buf, sizeof(buf), "att%_offset_x", i);
				offset[0] = GetPVarFloat(playerid, buf);
				format(buf, sizeof(buf), "att%_offset_y", i);
				offset[1] = GetPVarFloat(playerid, buf);
				format(buf, sizeof(buf), "att%_offset_z", i);
				offset[2] = GetPVarFloat(playerid, buf);

				format(buf, sizeof(buf), "att%_rot_x", i);
				rot[0] = GetPVarFloat(playerid, buf);
				format(buf, sizeof(buf), "att%_rot_y", i);
				rot[1] = GetPVarFloat(playerid, buf);
				format(buf, sizeof(buf), "att%_rot_z", i);
				rot[2] = GetPVarFloat(playerid, buf);

				format(buf, sizeof(buf), "att%_scale_x", i);
				scale[0] = GetPVarFloat(playerid, buf);
				format(buf, sizeof(buf), "att%_scale_y", i);
				scale[1] = GetPVarFloat(playerid, buf);
				format(buf, sizeof(buf), "att%_scale_z", i);
				scale[2] = GetPVarFloat(playerid, buf);

				format(buf, sizeof(buf), "att%_color_1", i);
				color[0] = GetPVarInt(playerid, buf);
				format(buf, sizeof(buf), "att%_color_2", i);
				color[1] = GetPVarInt(playerid, buf);

		        SetPlayerAttachedObject(playerid, i, modelid, boneid, offset[0], offset[1], offset[2], rot[0],rot[1], rot[2], scale[0], scale[1], scale[2], color[0], color[1]);
		    }
		}
	}

	#if defined ATT_OnPlayerKeyStateChange
       	return ATT_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange ATT_OnPlayerKeyStateChange
#if defined ATT_OnPlayerKeyStateChange
    forward ATT_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

stock ATT_SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0)
{
	if (SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2))
	{
		new
		    buf[40]
		;
		format(buf, sizeof(buf), "att%_modelid", index);
		SetPVarInt(playerid, buf, modelid);

		format(buf, sizeof(buf), "att%_bone", index);
		SetPVarInt(playerid, buf, bone);

		format(buf, sizeof(buf), "att%_offset_x", index);
		SetPVarFloat(playerid, buf, fOffsetX);
		format(buf, sizeof(buf), "att%_offset_y", index);
		SetPVarFloat(playerid, buf, fOffsetY);
		format(buf, sizeof(buf), "att%_offset_z", index);
		SetPVarFloat(playerid, buf, fOffsetZ);

		format(buf, sizeof(buf), "att%_rot_x", index);
		SetPVarFloat(playerid, buf, fRotX);
		format(buf, sizeof(buf), "att%_rot_y", index);
		SetPVarFloat(playerid, buf, fRotY);
		format(buf, sizeof(buf), "att%_rot_z", index);
		SetPVarFloat(playerid, buf, fRotZ);

		format(buf, sizeof(buf), "att%_scale_x", index);
		SetPVarFloat(playerid, buf, fScaleX);
		format(buf, sizeof(buf), "att%_scale_y", index);
		SetPVarFloat(playerid, buf, fScaleY);
		format(buf, sizeof(buf), "att%_scale_z", index);
		SetPVarFloat(playerid, buf, fScaleZ);

		format(buf, sizeof(buf), "att%_color_1", index);
		SetPVarInt(playerid, buf, materialcolor1);
		format(buf, sizeof(buf), "att%_color_2", index);
		SetPVarInt(playerid, buf, materialcolor2);

		format(buf, sizeof(buf), "att%_used", index);
		SetPVarInt(playerid, buf, 1);

		return true;
	}
	else
	{
		return false;
	}
}
#if defined _ALS_SetPlayerAttachedObject
    #undef SetPlayerAttachedObject
#else
	native BAD_SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0) = SetPlayerAttachedObject;
    #define _ALS_SetPlayerAttachedObject
#endif
#define SetPlayerAttachedObject ATT_SetPlayerAttachedObject

stock GetPlayerAttachedObject(playerid, index, &modelid, &bone, &Float:fOffsetX, &Float:fOffsetY, &Float:fOffsetZ, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fScaleX, &Float:fScaleY, &Float:fScaleZ, &materialcolor1, &materialcolor2)
{
	new
	    buf[40]
	;
 	format(buf, sizeof(buf), "att%_used", index);
    if (GetPVarInt(playerid, buf))
    {
	    format(buf, sizeof(buf), "att%_modelid", index);
	    modelid = GetPVarInt(playerid, buf);

	    format(buf, sizeof(buf), "att%_bone", index);
	    boneid = GetPVarInt(playerid, buf);

	    format(buf, sizeof(buf), "att%_offset_x", index);
	    foffsetX = GetPVarFloat(playerid, buf);
	    format(buf, sizeof(buf), "att%_offset_y", index);
	    foffsetY = GetPVarFloat(playerid, buf);
	    format(buf, sizeof(buf), "att%_offset_z", index);
	    foffsetZ = GetPVarFloat(playerid, buf);

	    format(buf, sizeof(buf), "att%_rot_x", index);
	    fRotX = GetPVarFloat(playerid, buf);
	    format(buf, sizeof(buf), "att%_rot_y", index);
	    fRrotY = GetPVarFloat(playerid, buf);
	    format(buf, sizeof(buf), "att%_rot_z", index);
	    fRotZ = GetPVarFloat(playerid, buf);

	    format(buf, sizeof(buf), "att%_scale_x", index);
	    fScaleX = GetPVarFloat(playerid, buf);
	    format(buf, sizeof(buf), "att%_scale_y", index);
	    fScaleY = GetPVarFloat(playerid, buf);
	    format(buf, sizeof(buf), "att%_scale_z", index);
	    fScaleZ = GetPVarFloat(playerid, buf);

	    format(buf, sizeof(buf), "att%_color_1", index);
	    materialcolor1 = GetPVarInt(playerid, buf);
	    format(buf, sizeof(buf), "att%_color_2", index);
	    materialcolor2 = GetPVarInt(playerid, buf);

        return true;
    }
    else
    {
		return false;
	}
}

stock ATT_RemovePlayerAttachedObject(playerid, index)
{
	if (RemovePlayerAttachedObject(playerid, index))
	{
		new
		    buf[40]
		;
	 	format(buf, sizeof(buf), "att%_used", index);
	 	SetPVarInt(playerid, buf, 0);

		return true;
	}
	else
	{
		return false;
	}
}
#if defined _ALS_RemovePlayerAttachedObject
    #undef RemovePlayerAttachedObject
#else
	native BAD_RemovePlayerAttachedObject(playerid, index) = RemovePlayerAttachedObject;
    #define _ALS_RemovePlayerAttachedObject
#endif
#define RemovePlayerAttachedObject ATT_RemovePlayerAttachedObject
