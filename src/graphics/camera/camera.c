#include "camera.h"

picg_camera *picg_camera_create()
{  
    return malloc(sizeof(picg_camera));
}

void picg_camera_destroy(picg_camera* cam)
{
    free(cam);
}

void picg_camera_apply(picg_camera* cam) {
}

void picg_camera_flush(picg_camera* cam)
{

}
