# SAMP_Fixer `Build 2`
Community patch for buggy SA:MP functions and glitches experienced in game.

## Requirements
Latest SA-MP update only: http://forum.sa-mp.com/showthread.php?t=581259

## Visit the thread
http://forum.sa-mp.com/showthread.php?t=591458

## Library structure
There are 12 branches of this librarby:
 * fix_anims [IMPORTANT]
 * fix_attachments [IMPORTANT]
 * fix_checkpoint
 * fix_files [IMPORTANT]
 * fix_gametext
 * fix_gangzone
 * fix_kickban
 * fix_menu [IMPORTANT]
 * fix_others [IMPORTANT]
 * fix_players [IMPORTANT]
 * fix_server
 * fix_string [IMPORTANT]
 * fix_tildes [IMPORTANT]
 * fix_tickcount
 * fix_vehicles [IMPORTANT]

## Why to use this?
There are few reasons why fixes is insecure or not that good to use, firstly there is silent kick which can be causing trouble (as far i have experienced), the include sometimes causes random kicks or crashes. Secondly there are few better methods to perform or fix some natives, the code has completely ran into complexity. The SAMP Fixer library has few more areas which fixes.inc doesn't cover. And last but not the least, the timer fix plugin (fixes plugin) is still buggy. I have experienced time difference till yet.

## How to use?
Include this just after `#include <a_samp>`.
```pawn
#include <a_samp>

#include <samp_fixer>
```

The above method includes all libraries in one, i.e. `samp_fixer.inc`. If you want to individually add libraries, just specify the each library name after the folder name. 
Example:
```pawn
#include <a_samp>

#include <SAMP_Fixer/fix_anims>
#include <SAMP_Fixer/fix_players>
#include ...
```

The samp_fixer.inc also have a game mode initiation phase where the include setups `fix_server` for default changes.

If you are using individual includes and not including samp_fixer, you have to add these under `OnGameModeInit` in case you don't want your mod's default features.
```pawn
public OnGameModeInit()
{
	EnableTirePopping(1);
	AllowInteriorWeapons(1);
	AllowAdminTeleport(0);
	EnableZoneNames(0);
	EnableVehicleNames(0);

	return 1;
}
```
#SAMP_FIXER_SINGLES ?
Build 2 now supports normal arrays than PVars and SVars. By default the this feature is disabled.

- What is advantage of using SINGLES?
> `The speed of performing actions and reading data is increased.`

- What is the disadvantage of not using SINGLES?
> `You cannot access the data accross multiple platforms, you won't get the correct FIX value in other scripts.`

- How to enable SINGLES?
> Before including the library, add/define this macro:
```pawn
#define SAMP_FIXER_SINGLES
```
