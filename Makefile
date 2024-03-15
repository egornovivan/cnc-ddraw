-include config.mk

CC        = i686-w64-mingw32-gcc
CXX       = i686-w64-mingw32-g++
WINDRES  ?= i686-w64-mingw32-windres
LDFLAGS   = -Wl,--enable-stdcall-fixup -s -static
CFLAGS    = -Iinc -O2 -march=i486 -Wall
LIBS      = -lgdi32 -lwinmm -lpsapi -ldbghelp -lole32

FILES = src/IDirect3D/IDirect3D.c \
        src/IDirect3D/IDirect3D2.c \
        src/IDirect3D/IDirect3D3.c \
        src/IDirect3D/IDirect3D7.c \
        src/IDirectDraw/IDirectDraw.c \
        src/IDirectDraw/IDirectDrawPalette.c \
        src/IDirectDraw/IDirectDrawClipper.c \
        src/IDirectDraw/IDirectDrawSurface.c \
        src/IDirectDraw/IDirectDrawGammaControl.c \
        src/IAMMediaStream/IAMMediaStream.c \
        src/crc32.c \
        src/ini.c \
        src/blt.c \
        src/dd.c \
        src/ddpalette.c \
        src/ddsurface.c \
        src/ddclipper.c \
        src/render_ogl.c \
        src/render_gdi.c \
        src/render_d3d9.c \
        src/debug.c \
        src/mouse.c \
        src/winapi_hooks.c \
        src/screenshot.c \
        src/config.c \
        src/lodepng.c \
        src/directinput.c \
        src/hook.c \
        src/dllmain.c \
        src/wndproc.c \
        src/utils.c \
        src/fps_limiter.c \
        src/opengl_utils.c

all:
	$(WINDRES) -J rc ddraw.rc ddraw.rc.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o ddraw.dll $(FILES) ddraw.def ddraw.rc.o $(LIBS)

clean:
	$(RM) ddraw.dll ddraw.rc.o
