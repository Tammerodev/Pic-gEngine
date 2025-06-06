#pragma once
#include <GL/gl.h>
#include <stdio.h>
#include "../../math/vector3D.h"
#include "../../globals/runtime.h"

void picg_addlight_diffuse(unsigned int lightNumber, GLfloat color[], GLfloat pos[]);
void picg_disablelight(unsigned int lightNumber);

void picg_addlight_ambient(GLfloat color[]);
