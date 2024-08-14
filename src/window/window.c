#include "window.h"
#include "../PREPROCESSOR/OS.h"
#include "../math/vector2D.h"

#if LINUX
#include "X11/Xlib.h"

Display* display = NULL;
Window* window = NULL;
XEvent event;

void picg_create_window(int windowSizeX, int windowSizeY) 
{
    display = XOpenDisplay(NULL);
    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 100, 100, windowSizeX, windowSizeY, 1, BlackPixel(display, 0), WhitePixel(display, 0));
    XMapWindow(display, window);
    XSelectInput(display, window, ExposureMask);


    for (int t = 0;;t++) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            XDrawString(display, window, DefaultGC(display, 0), 100, 100, "Test.", 5);
        }
    }
}

int picg_window_created() 
{
    return (display != NULL) && (window != NULL);
}

#elif WINDOWS

void picg_create_window() 
{

}


int picg_window_created() 
{

}

#endif