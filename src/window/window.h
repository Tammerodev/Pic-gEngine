#pragma once
#include "../PREPROCESSOR/OS.h"
#include "../math/vector2D.h"
#include "../globals/macro.h"
#include "../graphics/graphicsGL.h"


#if LINUX
#include <X11/Xlib.h>
#include "GL/glx.h"
#elif WINDOWS
#include <windows.h>
#endif

void picg_test_support();

void picg_window_create(int windowSizeX, int windowSizeY, const char* windowTitle, int fullscreen);
void picg_window_setTitle(const char* windowTitle);

picg_vec2I picg_window_mouse_getPosition();
picg_vec2I picg_window_getPosition();
picg_vec2I picg_window_getSize();

void picg_window_mouse_setPosition(const picg_vec2I);
void picg_window_mouse_cursor_hide();

int picg_keyboard_keydown(char *targetString);

void picg_window_display();