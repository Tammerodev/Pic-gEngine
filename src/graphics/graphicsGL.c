#include "graphicsGL.h"

void picg_gl_clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer  
}

void picg_gl_flush() {
    glFlush();  // Display
}

void picg_gl_getError()
{
    GLenum code = glGetError();

    if(code == GL_NO_ERROR) return;

    switch(code) {
        case GL_INVALID_ENUM:
            PICG_ERROR("CODE GL_INVALID_ENUM");
            break;
        case GL_INVALID_VALUE:
            PICG_ERROR("CODE GL_INVALID_VALUE");
            break;
        case GL_INVALID_OPERATION:
            PICG_ERROR("CODE GL_INVALID_OPERATION");
            break;
        case GL_STACK_OVERFLOW:
            PICG_ERROR("CODE GL_STACK_OVERFLOW");
            break;
        case GL_STACK_UNDERFLOW:
            PICG_ERROR("CODE GL_STACK_UNDERFLOW");
            break;
        case GL_OUT_OF_MEMORY:
            PICG_ERROR("CODE GL_OUT_OF_MEMORY");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            PICG_ERROR("CODE GL_INVALID_FRAMEBUFFER_OPERATION");
            break;
        case GL_CONTEXT_LOST:
            PICG_ERROR("CODE GL_CONTEXT_LOST");
            break;
        case GL_TABLE_TOO_LARGE:
            PICG_ERROR("CODE GL_TABLE_TOO_LARGE");
            break;

        default:
            PICG_ERROR("CODE unknown error");
    }
}

void picg_gl_beginTransparentRender()
{
    glEnable(GL_BLEND); 
    glBlendFunc(GL_ONE, GL_ONE); 
    glDepthMask(GL_FALSE); 
}

void picg_gl_endTransparentRender()
{
    glDepthMask(GL_TRUE); 
    glDisable(GL_BLEND); 
}
