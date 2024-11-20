#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "../../math/vector3D.h"
#include <stdio.h>

typedef struct {
    picg_vec3F position;
    picg_vec3F rotation;
} picg_camera;

picg_camera* picg_camera_create();

void picg_camera_push(picg_camera*);

void picg_camera_pop(picg_camera*);