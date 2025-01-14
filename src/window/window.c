#include "window.h"
#include "../PREPROCESSOR/OS.h"
#include "../math/vector2D.h"
#include <stdio.h>

#if LINUX
#include "X11/Xlib.h"
#include "X11/Xatom.h"

static Window window;
static Display *display = NULL;
static GLXContext glxContext;
static XVisualInfo *visualInfo;
static Colormap colormap;
static XSetWindowAttributes winAttr;
static XEvent xevent;

void picg_test_support()
{   
    printf("TODO: Implement compability test!");
}

void picg_window_create(int windowSizeX, int windowSizeY, const char *windowTitle, int fullscreen)
{
    picg_test_support();

    display = XOpenDisplay(NULL);

    // Choose a visual that supports OpenGL
    int visualAttribs[] = {
        GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 24, None
    };

    visualInfo = glXChooseVisual(display, DefaultScreen(display), visualAttribs);

    if(visualInfo == NULL) 
    {
        printf("Error: Visual not supported!\n");
        return;
    }

    // Create a colormap
    colormap = XCreateColormap(display, RootWindow(display, visualInfo->screen), visualInfo->visual, AllocNone);
    winAttr.colormap = colormap;

    // Event mask
    winAttr.event_mask = ExposureMask | KeyPressMask;

    window = XCreateWindow(display, RootWindow(display, visualInfo->screen), 0, 0, windowSizeX, windowSizeY, 0, visualInfo->depth,
                                InputOutput, visualInfo->visual, CWColormap | CWEventMask, &winAttr);


    if(fullscreen) {
        Atom wm_state   = XInternAtom (display, "_NET_WM_STATE", 1 );
        Atom wm_fullscreen = XInternAtom (display, "_NET_WM_STATE_FULLSCREEN", 1 );

        XChangeProperty(display, window, wm_state, XA_ATOM, 32,
                        PropModeReplace, (unsigned char *)&wm_fullscreen, 1);
    }


    XMapWindow(display, window);
    XStoreName(display, window, windowTitle);

    // Create an OpenGL context
    glxContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
    if(!glxContext) 
    {
        printf("Error: Failed to create GLX context\n");
        return;
    }

    glXMakeCurrent(display, window, glxContext);
    glViewport(0.f, 0.f, windowSizeX, windowSizeY);

    XNextEvent(display, &xevent);
}

void picg_window_setTitle(const char *windowTitle)
{
    XStoreName(display, window, windowTitle);
}

picg_vec2I picg_window_mouse_getPosition()
{
    picg_vec2I result = {0, 0};
    int win_x, win_y;

    Window window_returned;
    unsigned int mask_return;

    XQueryPointer(display, window, &window_returned,
                &window_returned, &result.x, &result.y, &win_x, &win_y,
                &mask_return);

    return result;
}

picg_vec2I picg_window_getPosition()
{
    picg_vec2I position = {0, 0};
    Window childWindow;

    XTranslateCoordinates(display, window, RootWindow(display, 0), 0, 0, &position.x, &position.y, &childWindow);

    return position;
}

picg_vec2I picg_window_getSize()
{
    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, window, &windowAttributes);

    picg_vec2I size = {windowAttributes.width, windowAttributes.height};
    return size;
}

void picg_window_mouse_setPosition(const picg_vec2I position)
{
    XWarpPointer(display, None, window, 0, 0, 0, 50, position.x, position.y);
}

int picg_keyboard_keydown(char *targetString)
{
    char keys_return[32] = {0};
    KeySym targetSym = XStringToKeysym(targetString);
    KeyCode targetCode = XKeysymToKeycode(display, targetSym);

    int targetByte = targetCode / 8;
    int targetBit = targetCode % 8;
    int targetMask = 0x01 << targetBit;
    
    XQueryKeymap(display, keys_return);
    return keys_return[targetByte] & targetMask;
}

int picg_input_keyboard_ispressed(unsigned int)
{
    return 0;
}

void picg_window_display()
{
    picg_gl_flush();
    glXSwapBuffers(display, window);
}

int picg_window_created() 
{
    return display != NULL;
}

#elif WINDOWS

void picg_create_window() 
{

}


int picg_window_created() 
{

}

#endif