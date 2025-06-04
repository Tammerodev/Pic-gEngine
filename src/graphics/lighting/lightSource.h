#pragma once
#include <GL/gl.h>
#include <stdio.h>
#include "../../math/vector3D.h"

void picg_addlight_diffuse(unsigned int lightNumber, GLfloat color[], GLfloat pos[]);
void picg_addlight_ambient(GLfloat color[]);
