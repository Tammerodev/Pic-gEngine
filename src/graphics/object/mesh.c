#include "mesh.h"

void picg_mesh_render(picg_mesh *mesh)
{   
    /*for(int vIndex = 0; vIndex < mesh->vertexCount; ++vIndex)
    {
        glColor4f(
            mesh->vertices[vIndex].r,
            mesh->vertices[vIndex].g,
            mesh->vertices[vIndex].b,
            mesh->vertices[vIndex].a
        );

        glVertex3f(
            mesh->vertices[vIndex].x + mesh->position.x,
            mesh->vertices[vIndex].y + mesh->position.y,
            mesh->vertices[vIndex].z + mesh->position.z
        );
    }*/


    glBegin(GL_QUADS);

    for(int vIndex = 0; vIndex < mesh->faceCount; ++vIndex)
    {
        glColor4f(
            1.0, 0.5, 0.2, 1.0
        );

        for(int i = 0; i < 4; ++i) {
            glVertex3f(
                mesh->position.x + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].x,
                mesh->position.y + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].y,
                mesh->position.z + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].z
            );
        }
    }
    
    glEnd();

    glTranslatef(mesh->position.x, mesh->position.y, mesh->position.z);
    glRotatef(0.01, 0.3, 0.2, 0.1);
    glTranslatef(-mesh->position.x, -mesh->position.y, -mesh->position.z);

}