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

HDC hdc;
HWND hwnd;

void Win32Opengl_init() {
    hdc = GetDC(hwnd);

    // Set pixel format descriptor
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,                          // Version number
        PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW, // Flags
        PFD_TYPE_RGBA,              // Color format
        24,                         // Color depth
        0, 0, 0, 0, 0, 0,          // Ignore color bits
        0,                          // No alpha buffer
        0,                          // No accumulation buffer
        0, 0, 0,                    // No depth, stencil, and auxiliary buffers
        32,                         // 32-bit depth buffer
        0,                          // No stencil buffer
        0,                          // No auxiliary buffers
        PFD_MAIN_PLANE,             // Main drawing plane
        0,                          // Reserved
        0, 0, 0                     // Layer, visible, and reserved fields
    };

    // Choose pixel format
    int pixelformat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelformat, &pfd);

    HGLRC hglrc;
    hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);
}

void picg_test_support() {

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void picg_window_create(int windowSizeX, int windowSizeY, const char* windowTitle, int fullscreen) {
    const char* CLASS_NAME  = "Sample Window Class";
    
    // Get the instance handle
    HINSTANCE hInstance = GetModuleHandle(NULL); // Current application instance

    // Set up the window class
    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc;  
    wc.hInstance     = hInstance;         
    wc.lpszClassName = CLASS_NAME;       

    RegisterClass(&wc);

    DWORD style = WS_OVERLAPPEDWINDOW;
    if (fullscreen) {
        style = WS_POPUP; // Fullscreen mode (no borders, no title bar)
    }

    // Create the window
    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        windowTitle,                    // Window title
        style,                          // Window style (fullscreen or windowed)

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, windowSizeX, windowSizeY,

        NULL,                           // Parent window    
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    Win32Opengl_init();

    UpdateWindow(hwnd);
    ShowWindow(hwnd, SW_SHOWNORMAL);
}

void picg_window_setTitle(const char* windowTitle) {
    // TODO 
}

picg_vec2I picg_window_mouse_getPosition() {
    picg_vec2I pos;
    return pos;
}

picg_vec2I picg_window_getPosition() {
    picg_vec2I pos;
    return pos;
}

picg_vec2I picg_window_getSize() {
    picg_vec2I pos;
    return pos;
}

void picg_window_mouse_setPosition(const picg_vec2I) {

}

int picg_keyboard_keydown(char *targetString) {
    return 0;
}

void picg_window_display() {
    SwapBuffers(hdc);
}

#endif