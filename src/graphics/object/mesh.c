#include "mesh.h"

void picg_mesh_render(struct picg_mesh *mesh)
{   
    glBegin(mesh->renderType);

    for(int vIndex = 0; vIndex < mesh->meshSize; ++vIndex)
    {
        /*glColor4f(
            mesh->vertices[vIndex].r,
            mesh->vertices[vIndex].g,
            mesh->vertices[vIndex].b,
            mesh->vertices[vIndex].a
        );*/

        glColor4f(1.0, 1.0, 1.0, 1.0);

        glVertex3f(
            mesh->vertices[vIndex].x + mesh->position.x,
            mesh->vertices[vIndex].y + mesh->position.y,
            mesh->vertices[vIndex].z + mesh->position.z
        );


    }

    glEnd();
}