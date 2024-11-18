#include "mesh.h"

void picg_mesh_render(picg_mesh *mesh)
{  
    glLoadIdentity();

    glTranslatef(mesh->position.x, mesh->position.y, mesh->position.z);
    glRotatef(mesh->rotation.x, 1.f, 0.f, 0.f);
    glRotatef(mesh->rotation.y, 0.f, 1.f, 0.f);
    glRotatef(mesh->rotation.z, 0.f, 0.f, 1.f);
    glTranslatef(-mesh->position.x, -mesh->position.y, -mesh->position.z);

    // Check mesh validity
    if(mesh->vertices == NULL)
        printf("Error: picg_mesh_render() failed with: Trying to render mesh with vertices set to NULL");


glBegin(mesh->renderType);
    if(mesh->faceCount == 0) 
    {
        // Render by vertices if there are 0 faces
        for(int vIndex = 0; vIndex < mesh->vertexCount; ++vIndex)
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
        }
    } else {
        // Otherwise, render by faces
        for(int vIndex = 0; vIndex < mesh->faceCount; ++vIndex)
        {

            for(int i = 0; i < mesh->faces[vIndex].verticesPerFace; ++i) {
                glColor4f(
                    mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].r,
                    mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].g,
                    mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].b,
                    mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].a
                );

                glVertex3f(
                    mesh->position.x + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].x,
                    mesh->position.y + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].y,
                    mesh->position.z + mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].z
                );
            }
        }
    }
glEnd();
    
}