#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "dd.h"
#include "ddpalette.h"
#include "ddsurface.h"
#include "lodepng.h"
#include "blt.h"
#include "config.h"


static BOOL ss_screenshot_8bit(char* filename, IDirectDrawSurfaceImpl* src)
{
    LodePNGState state;

    lodepng_state_init(&state);

    for (int i = 0; i < 256; i++)
    {
        RGBQUAD* c = &src->palette->data_rgb[i];
        lodepng_palette_add(&state.info_png.color, c->rgbRed, c->rgbGreen, c->rgbBlue, 255);
        lodepng_palette_add(&state.info_raw, c->rgbRed, c->rgbGreen, c->rgbBlue, 255);
    }

    state.info_png.color.colortype = LCT_PALETTE;
    state.info_png.color.bitdepth = 8;
    state.info_raw.colortype = LCT_PALETTE;
    state.info_raw.bitdepth = 8;
    state.encoder.auto_convert = 0;

    unsigned char* dst_buf = NULL;
    size_t dst_buf_size = 0;

    unsigned int error = 
        lodepng_encode(
            &dst_buf, 
            &dst_buf_size, 
            dds_GetBuffer(src), 
            src->pitch / src->bytes_pp, /* can't specify pitch so we use bitmap real width */
            src->height,
            &state);

    if (!error && dst_buf)
        lodepng_save_file(dst_buf, dst_buf_size, filename);

    lodepng_state_cleanup(&state);

    if (dst_buf)
        free(dst_buf);

    return !error;
}

static BOOL ss_screenshot_16bit(char* filename, IDirectDrawSurfaceImpl* src)
{
    unsigned int error = TRUE;
    unsigned int* buf = malloc(src->width * src->height * 4);

    if (buf)
    {
        if (g_config.rgb555)
        {
            blt_rgb555_to_rgba8888(
                buf,
                0,
                0,
                src->width,
                src->height,
                src->width * 4,
                dds_GetBuffer(src),
                0,
                0,
                src->pitch);
        }
        else
        {
            blt_rgb565_to_rgba8888(
                buf,
                0,
                0,
                src->width,
                src->height,
                src->width * 4,
                dds_GetBuffer(src),
                0,
                0,
                src->pitch);
        }

        error = lodepng_encode32_file(filename, (unsigned char*)buf, src->width, src->height);

        free(buf);
    }

    return !error;
}

static BOOL ss_screenshot_32bit(char* filename, IDirectDrawSurfaceImpl* src)
{
    unsigned int error = TRUE;
    unsigned int* buf = malloc(src->width * src->height * 4);

    if (buf)
    {
        blt_bgra8888_to_rgba8888(
            buf,
            0,
            0,
            src->width,
            src->height,
            src->width * 4,
            dds_GetBuffer(src),
            0,
            0,
            src->pitch);

        error = lodepng_encode32_file(filename, (unsigned char*)buf, src->width, src->height);

        free(buf);
    }

    return !error;
}

BOOL ss_take_screenshot(IDirectDrawSurfaceImpl* src)
{
    if (!src || !dds_GetBuffer(src) || !src->width || !src->height)
        return FALSE;

    char title[128];
    char filename[128];
    char str_time[64];
    time_t t = time(NULL);

    strncpy(title, g_ddraw->title, sizeof(g_ddraw->title));

    for (int i = 0; i < strlen(title); i++)
    {
        if (title[i] == ' ')
        {
            title[i] = '_';
        }
        else
        {
            title[i] = tolower(title[i]);
        }
    }

    CreateDirectoryA(g_config.screenshot_dir, NULL);

    strftime(str_time, sizeof(str_time), "%Y-%m-%d-%H_%M_%S", localtime(&t));
    _snprintf(filename, sizeof(filename), "%s%s-%s.png", g_config.screenshot_dir, title, str_time);

    if (src->bpp == 8 && src->palette)
    {
        return ss_screenshot_8bit(filename, src);
    }
    else if (src->bpp == 16)
    {
        return ss_screenshot_16bit(filename, src);
    }
    else if (src->bpp == 32)
    {
        return ss_screenshot_32bit(filename, src);
    }

    return FALSE;
}
