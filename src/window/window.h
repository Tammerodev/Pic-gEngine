#pragma once
#include "../PREPROCESSOR/OS.h"
#include "../math/vector2D.h"
#include "GL/glx.h"
#include "../globals/input.h"
#include "../graphics/graphicsGL.h"


#if LINUX
#include <X11/Xlib.h>
#endif

void picg_test_support();

void picg_window_create(int windowSizeX, int windowSizeY, const char* windowTitle);
void picg_window_setTitle(const char* windowTitle);

picg_vec2I picg_window_mouse_getPosition();

int picg_keyboard_keydown(char *targetString);

void picg_window_display();