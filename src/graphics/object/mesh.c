#include "mesh.h"
#include <stdio.h>
#include <stdlib.h>

void picg_mesh_render(picg_mesh *mesh)
{  
    glPushMatrix();

    glTranslatef(mesh->position.x, mesh->position.y, mesh->position.z);
    glRotatef(mesh->rotation.x, 1.f, 0.f, 0.f);
    glRotatef(mesh->rotation.y, 0.f, 1.f, 0.f);
    glRotatef(mesh->rotation.z, 0.f, 0.f, 1.f);

    glScalef(mesh->scaling.x, mesh->scaling.y, mesh->scaling.z);

    // Check mesh validity
    if(mesh->vertices == NULL)
        PICG_ERROR("Trying to render mesh with vertices set to NULL");

#if PICG_DEBUG
    if(g_runtime_debug) 
    {

        glBegin(GL_LINES);
        for(int vIndex = 0; vIndex < mesh->faceCount; ++vIndex)
        {
            if(!mesh->faces) break;
            if(!mesh->faceCount) break;
            if(!mesh->faces[0].hasNormals) break;

            for(size_t i = 0; i < mesh->faces[vIndex].verticesPerFace; ++i) {

                glColor3f(1.0f, 0.f, 0.f);

                glVertex3f(mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].x,
                            mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].y,
                            mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].z);

                glVertex3f( mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].x + mesh->vertices[mesh->faces[vIndex].normalIndexes[i] - 1].xn * 1.1f,
                            mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].y + mesh->vertices[mesh->faces[vIndex].normalIndexes[i] - 1].yn * 1.1f,
                            mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].z + mesh->vertices[mesh->faces[vIndex].normalIndexes[i] - 1].zn * 1.1f);
            }
        }
        glEnd();
    }
#endif

glBegin(mesh->renderType);
    if(mesh->faceCount == 0) 
    {
        // Render by vertices if there are 0 faces (also no normals!!!)
        for(int vIndex = 0; vIndex < mesh->vertexCount; ++vIndex)
        {
            glColor4f(1.f, 1.f, 1.f, 1.f);

            glVertex3f(
                mesh->vertices[vIndex].x,
                mesh->vertices[vIndex].y,
                mesh->vertices[vIndex].z
            );
        }
    } else {
        // Otherwise, render by faces
        for(int vIndex = 0; vIndex < mesh->faceCount; ++vIndex)
        {
            for(int i = 0; i < mesh->faces[vIndex].verticesPerFace; ++i) {
                glColor4f(1.f, 1.f, 1.f, 1.f);

                if(mesh->faces[vIndex].hasNormals) {
                    glNormal3f(mesh->vertices[mesh->faces[vIndex].normalIndexes[i] - 1].xn,
                            mesh->vertices[mesh->faces[vIndex].normalIndexes[i] - 1].yn,
                            mesh->vertices[mesh->faces[vIndex].normalIndexes[i] - 1].zn);
                }

                const picg_vertex3F* vertexTex = &mesh->vertices[mesh->faces[vIndex].textureIndexes[i] - 1];

                if(mesh->faces[vIndex].hasTexture) {
                    glTexCoord2f(vertexTex->xt, vertexTex->yt);
                }

                glVertex3f(
                    mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].x,
                    mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].y,
                    mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].z
                );
            }
        }
    }
glEnd();
    
    glPopMatrix();

}