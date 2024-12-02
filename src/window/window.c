#include "window.h"
#include "../PREPROCESSOR/OS.h"
#include "../math/vector2D.h"
#include <stdio.h>

#if LINUX
#include "X11/Xlib.h"

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

void picg_window_create(int windowSizeX, int windowSizeY, const char *windowTitle)
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
    picg_vec2I result = {};

    printf("Read position: x=%f, y=%f\n", result.x, result.y);
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