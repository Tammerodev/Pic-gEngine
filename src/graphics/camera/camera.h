#pragma once
#include "../../math/vector3D.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

typedef struct
{
    picg_vec3F position;
    picg_vec3F rotation;
} picg_camera;

/*
    Create and destroy camera object
*/

picg_camera* picg_camera_create();
void picg_camera_destroy(picg_camera*);
/*
    Apply function shold be called before rendering
    the target and flush after rendering.

    Not doing one of them causes the camera to go out-of-bounds
*/

void picg_camera_apply(picg_camera*);
void picg_camera_flush(picg_camera*);
