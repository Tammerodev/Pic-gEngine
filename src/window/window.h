#pragma once
#include "../PREPROCESSOR/OS.h"
#include "../math/vector2D.h"
#include "GL/glx.h"

#if LINUX
#include <X11/Xlib.h>
#endif

void picg_window_create(int windowSizeX, int windowSizeY, const char* windowTitle);
int picg_keyboard_keydown(char *targetString);
void picg_window_swapbuffers();
void picg_test_support();