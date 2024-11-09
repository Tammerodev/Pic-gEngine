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


    glBegin(mesh->renderType);

    for(int vIndex = 0; vIndex < mesh->faceCount; ++vIndex)
    {

        for(int i = 0; i < mesh->faces[vIndex].verticesPerFace; ++i) {
            /*glColor4f(
                mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].r,
                mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].g,
                mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].b,
                mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].a
            );*/

            glVertex3f(
                mesh->position.x + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].x,
                mesh->position.y + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].y,
                mesh->position.z + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].z
            );
        }
    }
    
    glEnd();

    glRotatef(mesh->rotation.x, 1.f, 0.f, 0.f);
    glRotatef(mesh->rotation.y, 0.f, 1.f, 0.f);
    glRotatef(mesh->rotation.z, 0.f, 0.f, 1.f);

    // Reset rotation
    mesh->rotation.x = 0.f;
    mesh->rotation.y = 0.f;
    mesh->rotation.z = 0.f;

}