#pragma once
#include <GL/gl.h>
#include <stdio.h>
#include "../../math/vector3D.h"

void picg_addlight(unsigned int lightNumber, GLfloat color[], GLfloat pos[], GLenum lightType);