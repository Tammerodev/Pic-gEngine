#pragma once
#include <GL/gl.h>
#include <globals/runtime.h>

void picg_gl_setClearColor(float, float, float, float);
void picg_gl_init3D(int winX, int winY);
void picg_gl_setPerspective(int winX, int winY, float FOV, float zNear, float zFar);

void picg_gl_clear();
void picg_gl_flush();
void picg_gl_getError();