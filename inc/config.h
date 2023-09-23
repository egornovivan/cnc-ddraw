#ifndef CONFIG_H
#define CONFIG_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


typedef struct CNCDDRAWCONFIG
{
    RECT window_rect;
    int window_state;
    int borderless_state;
    char ini_path[MAX_PATH];
    char game_path[MAX_PATH];
    char process_file_name[MAX_PATH];
    char process_file_ext[MAX_PATH];
    
    /* Optional settings */

    BOOL fullscreen;
    BOOL windowed;
    BOOL maintas;
    BOOL boxing;
    int maxfps;
    BOOL vsync;
    BOOL adjmouse;
    char shader[MAX_PATH];
    char renderer[256];
    BOOL devmode;
    BOOL border;
    int save_settings;
    BOOL resizable;
    int d3d9_filter;
    BOOL vhack;
    char screenshot_dir[MAX_PATH];
    BOOL toggle_borderless;

    /* Compatibility settings */

    BOOL noactivateapp;
    int maxgameticks;
    int minfps;
    BOOL nonexclusive;
    BOOL singlecpu;
    int resolutions;
    int fixchilds;
    BOOL hook_peekmessage;

    /* Undocumented settings */

    BOOL releasealt;
    BOOL fixnotresponding;
    int hook;
    int guard_lines;
    int max_resolutions;
    BOOL limit_bltfast;
    BOOL lock_surfaces;
    BOOL allow_wmactivate;
    BOOL flipclear;
    BOOL fixmousehook;
    BOOL rgb555;
    BOOL no_dinput_hook;
    int refresh_rate;
    int anti_aliased_fonts_min_size;
    int custom_width;
    int custom_height;
    int min_font_size;

    /* Hotkeys */

    struct
    {
        int toggle_fullscreen;
        int toggle_maximize;
        int unlock_cursor1;
        int unlock_cursor2;
        int screenshot;
    } hotkeys;

    /* Game specific settings */

    BOOL remove_menu;
    
    BOOL armadahack;
    BOOL tshack;
    BOOL infantryhack;
    BOOL stronghold_hack;
    BOOL mgs_hack;

} CNCDDRAWCONFIG;

extern CNCDDRAWCONFIG g_config;

void cfg_load();
void cfg_save();

#endif
