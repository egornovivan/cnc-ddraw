# cnc-ddraw
cnc-ddraw can fix compatibility issues in older games, such as black screen, bad performance, crashes or defective Alt+Tab.

&nbsp;

### Features

 - Supports Windows 2000, XP, Vista, 7, 8, 10, 11, Wine (Linux/macOS) and Virtual Machines
 - GDI / OpenGL / Direct3D 9 renderer (With automatic renderer selection)
 - Upscaling via glsl shaders - https://imgur.com/a/kxsM1oY | https://imgur.com/a/wjrhpFV
 - Windowed Mode / Fullscreen Exclusive Mode / Borderless Mode
 - Alt+Enter support to switch quickly between Fullscreen and Windowed mode
 - Automatically saves and restores window position/size/state
 - FPS Limiter
 - VSync
 - Optional mouse sensitivity scaling
 - Preliminary libretro shader support - https://github.com/libretro/glsl-shaders
 - ...
 
&nbsp;

### Instructions

1. Download [cnc-ddraw.zip](https://github.com/FunkyFr3sh/cnc-ddraw/releases/latest/download/cnc-ddraw.zip) and extract it into your game folder
2. Start the game

Wine (Linux/macOS) only: override `ddraw` in [winecfg](https://wiki.winehq.org/Winecfg#Libraries) manually or run cnc-ddraw config.exe once.

&nbsp;

If you use cnc-ddraw with a game that got its own windowed mode built in then **make sure you disable the games own windowed mode** first. You can enable windowed mode via cnc-ddraw config.exe instead.

&nbsp;

**If the game starts but it doesn't work perfectly** then open the config program and check the **Compatibility settings**.

&nbsp;

**cnc-ddraw does not support Direct3D/Glide**, it will only work with games that use a **DirectDraw (Software)** renderer. Usually you can tell by the look of the game if it's a 3D game or not, but you can also let cnc-ddraw generate a debug log and search for "IDirect3D" - Link: https://github.com/FunkyFr3sh/cnc-ddraw/issues/44

&nbsp;

Some games may require additional steps before they can be used with cnc-ddraw, please check the [wiki](https://github.com/FunkyFr3sh/cnc-ddraw/wiki) for more details.

&nbsp;

**If the game doesn't start at all or it's crashing**, [then please generate a debug log file and upload it.](https://github.com/FunkyFr3sh/cnc-ddraw/issues/44)  

&nbsp;

### Hotkeys
* [Alt] + [Enter]                  = Switch between windowed and fullscreen mode
* [Ctrl] + [Tab]                    = Unlock cursor
* [Right Alt] + [Right Ctrl]  = Unlock cursor
* [Alt] + [Page Down]        = Maximize window

&nbsp;

### Supported Games

 - Command & Conquer Gold
 - Command & Conquer: Red Alert
 - Command & Conquer: Tiberian Sun
 - Command & Conquer: Red Alert 2
 - Captain Claw
 - Carmageddon
 - Carmageddon 2
 - Warcraft 2
 - StarCraft
 - Diablo
 - Diablo 2
 - Age of Empires
 - Age of Empires II
 - Theme Hospital
 - Populous: The Beginning
 - Outlaws
 - Dungeon Keeper
 - Dark Reign: The Future of War
 - Star Wars: Galactic Battlegrounds
 - Atomic Bomberman
 - Dune 2000
 - Oddworld: Abe's Oddysee
 - Commandos
 - Red Baron 3D
 - F-16 Multirole Fighter
 - F-22 Raptor
 - Nox
 - ...

There are a lot more games supported but I don't usually update the list, just give it a try and if it doesn't work then check the instructions above.


[![](https://img.shields.io/github/downloads/FunkyFr3sh/cnc-ddraw/total)](https://github.com/FunkyFr3sh/cnc-ddraw/releases/latest/download/cnc-ddraw.zip)
