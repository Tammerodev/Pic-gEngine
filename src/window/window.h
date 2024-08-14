#pragma once
#include "../PREPROCESSOR/OS.h"
#include "../math/vector2D.h"

#if LINUX
#include <X11/Xlib.h>
#endif

void picg_create_window(int windowSizeX, int windowSizeY);
int picg_window_created();