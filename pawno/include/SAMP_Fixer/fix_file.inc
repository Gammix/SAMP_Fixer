#if defined _fix_files_included
	#endinput
#endif
#define _fix_files_included

/*
 * ===============
 *  LIBRARY:
 * ===============
 *
 * fix_files.inc
 *
 * ================
 *  LIST OF FIXES:
 * ================
 *
 * FIX:			File function crashes
 * PROBLEM:  	When an invalid file is or handle is passes through any of the SA-MP file functions, the server crashes.
 * SOLUTION:  	Check if the file is valid, if not return false.
 * CREDITS:		Y_Less
 *
 */

stock FIX_fclose(File:handle)
{
	if (handle)
	{
		return fclose(handle);
	}
	else return false;
}
#if defined _ALS_fclose
	#undef fclose
#else
	native BAD_fclose(File:handle) = fclose;
	#define _ALS_fclose
#endif
#define fclose FIX_fclose

stock FIX_fwrite(File:handle, const string[])
{
	if (handle)
	{
		return fwrite(handle, string);
	}
	else return false;
}
#if defined _ALS_fwrite
	#undef fwrite
#else
	native BAD_fwrite(File:handle, const string[]) = fwrite;
	#define _ALS_fwrite
#endif
#define fwrite FIX_fwrite

stock FIX_fread(File:handle, string[], size = sizeof (string), bool:pack = false)
{
	if (handle)
	{
		return fread(handle, string, size, pack);
	}
	else return false;
}
#if defined _ALS_fread
	#undef fread
#else
	native BAD_fread(File:handle, string[], size = sizeof (string), bool:pack = false) = fread;
	#define _ALS_fread
#endif
#define fread FIX_fread

stock FIX_fputchar(File:handle, value, bool:utf8 = true)
{
	if (handle)
	{
		return fputchar(handle, value, utf8);
	}
	else return false;
}
#if defined _ALS_fputchar
	#undef fputchar
#else
	native BAD_fputchar(File:handle, value, bool:utf8 = true) = fputchar;
	#define _ALS_fputchar
#endif
#define fputchar FIX_fputchar

stock FIX_fgetchar(File:handle, value, bool:utf8 = true)
{
	if (handle)
	{
		return fgetchar(handle, value, utf8);
	}
	else return 0;
}
#if defined _ALS_fgetchar
	#undef fgetchar
#else
	native BAD_fgetchar(File:handle, value, bool:utf8 = true) = fgetchar;
	#define _ALS_fgetchar
#endif
#define fgetchar FIX_fgetchar

stock FIX_fblockwrite(File:handle, const buffer[], size = sizeof (buffer))
{
	if (handle)
	{
		return fblockwrite(handle, buffer, size);
	}
	else return 0;
}
#if defined _ALS_fblockwrite
	#undef fblockwrite
#else
	native BAD_fblockwrite(File:handle, const buffer[], size = sizeof (buffer)) = fblockwrite;
	#define _ALS_fblockwrite
#endif
#define fblockwrite FIX_fblockwrite

stock FIX_fblockread(File:handle, buffer[], size = sizeof (buffer))
{
	if (handle)
	{
		return fblockread(handle, buffer, size);
	}
	else return 0;
}
#if defined _ALS_fblockread
	#undef fblockread
#else
	native BAD_fblockread(File:handle, buffer[], size = sizeof (buffer)) = fblockread;
	#define _ALS_fblockread
#endif
#define fblockread FIX_fblockread

stock FIX_fseek(File:handle, position = 0, seek_whence:whence = seek_start)
{
	if (handle)
	{
		return fseek(handle, position, whence);
	}
	else return 0;
}
#if defined _ALS_fseek
	#undef fseek
#else
	native BAD_fseek(File:handle, position = 0, seek_whence:whence = seek_start) = fseek;
	#define _ALS_fseek
#endif
#define fseek FIX_fseek

stock FIX_flength(File:handle)
{
	if (handle)
	{
		return flength(handle);
	}
	else return 0;
}
#if defined _ALS_flength
	#undef flength
#else
	native BAD_flength(File:handle) = flength;
	#define _ALS_flength
#endif
#define flength FIX_flength
