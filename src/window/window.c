#include "window.h"
#include "../PREPROCESSOR/OS.h"
#include "../math/vector2D.h"

#if LINUX
#include "X11/Xlib.h"

Display* display = NULL;
Window* window = NULL;
GLXContext glxContext;
XVisualInfo *visualInfo;
Colormap colormap;
XSetWindowAttributes winAttr;
XEvent event;


void picg_window_create(int windowSizeX, int windowSizeY, const char* windowTitle) 
{
    display = XOpenDisplay(NULL);

    // Choose a visual that supports OpenGL
    static int visualAttribs[] = {
        GLX_RGBA, GLX_DEPTH_SIZE, 24, None
    };
    visualInfo = glXChooseVisual(display, DefaultScreen(display), visualAttribs);

    // Create a colormap
    colormap = XCreateColormap(display, RootWindow(display, visualInfo->screen), visualInfo->visual, AllocNone);
    winAttr.colormap = colormap;
    winAttr.event_mask = ExposureMask | KeyPressMask;

    // Create an X11 window
    window = XCreateWindow(display, RootWindow(display, visualInfo->screen),
                           0, 0, windowSizeX, windowSizeY, 0, visualInfo->depth, InputOutput,
                           visualInfo->visual, CWColormap | CWEventMask, &winAttr);

    XMapWindow(display, window);
    XStoreName(display, window, windowTitle);

    // Create an OpenGL context
    glxContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
    glXMakeCurrent(display, window, glxContext);

    XNextEvent(display, &event);
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