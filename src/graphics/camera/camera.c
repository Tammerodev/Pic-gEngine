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

void picg_camera_push(picg_camera *cam)
{
    glLoadIdentity();

    glRotatef(cam->rotation.x, 1.f, 0.f, 0.f);
    glRotatef(cam->rotation.y, 0.f, 1.f, 0.f);
    glRotatef(cam->rotation.z, 0.f, 0.f, 1.f);

    glTranslatef(cam->position.x, cam->position.y, cam->position.z);
}

void picg_camera_pop(picg_camera* cam)
{
    glTranslatef(-cam->position.x, -cam->position.y, -cam->position.z);
    
    glRotatef(-cam->rotation.x, 1.f, 0.f, 0.f);
    glRotatef(-cam->rotation.y, 0.f, 1.f, 0.f);
    glRotatef(-cam->rotation.z, 0.f, 0.f, 1.f);
}