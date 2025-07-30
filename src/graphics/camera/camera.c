#include "camera.h"

picg_camera* picg_camera_create()
{
    picg_camera* cam = malloc(sizeof(picg_camera));
    cam->position.x = 0.f;
    cam->position.y = 0.f;
    cam->position.z = 0.f;

    cam->rotation.x = 0.f;
    cam->rotation.y = 0.f;
    cam->rotation.z = 0.f;

    return cam;
}

#include <math.h>

void picg_camera_apply(picg_camera *cam)
{
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();

    glRotatef(cam->rotation.x, 1.f, 0.f, 0.f);
    glRotatef(cam->rotation.y, 0.f, 1.f, 0.f);
    glRotatef(cam->rotation.z, 0.f, 0.f, 1.f);

    picg_vec3F position_transform_apply_rotation = cam->position;

    // Rotate the vector by cam->rotation

    glTranslatef(position_transform_apply_rotation.x, 
                 position_transform_apply_rotation.y, 
                 position_transform_apply_rotation.z);
}
