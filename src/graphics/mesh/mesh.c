#include "mesh.h"
#include <stdio.h>
#include <stdlib.h>

void picg_mesh_render_debug(picg_mesh *mesh) {
    /*
        We should minimally change opengl state, as this is a debug function
    */
    GLboolean wasLightingEnabled = glIsEnabled(GL_LIGHTING);
    
    glDisable(GL_LIGHTING);

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

                glVertex3f( mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].x + mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].x * 1.1f,
                            mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].y + mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].y * 1.1f,
                            mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].z + mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].z * 1.1f);
            }
        }
    glEnd();

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

                glVertex3f( mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].x + mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].x * 1.1f,
                            mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].y + mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].y * 1.1f,
                            mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1].z + mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].z * 1.1f);
            }
        }
    glEnd();

    if(wasLightingEnabled == GL_TRUE) {
        glEnable(GL_LIGHTING);
    }
}

void picg_mesh_render(picg_mesh *mesh)
{  
    if(!mesh) {
        PICG_ERROR("Mesh is null!");
        return;
    }
    if(!mesh->render) return;

    glPushMatrix();

    /*
        Apply rotations to the mesh we are rendering
    */

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
        /* 
            Draw some debug info
        */
        picg_mesh_render_debug(mesh);
    }
#endif

    /*
        Start the actual rendering
    */

    glBegin(mesh->renderType);

    if(mesh->faceCount == 0) 
    {
        /*
            Render 0-face object by just points (this will be phased out)
        */
        for(int vIndex = 0; vIndex < mesh->vertexCount; ++vIndex)
        {
            glColor4f(1.f, 1.f, 1.f, 1.f - mesh->inv_alpha);

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
                glColor4f(1.f, 1.f, 1.f, 1.f - mesh->inv_alpha);

                if(mesh->faces[vIndex].hasNormals) {
                    glNormal3f(mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].x,
                            mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].y,
                            mesh->normals[mesh->faces[vIndex].normalIndexes[i] - 1].z);
                }

                const picg_vertex3F* vertexTex = &mesh->texcoords[mesh->faces[vIndex].textureIndexes[i] - 1];

                if(mesh->faces[vIndex].hasTexture) {
                    glTexCoord2f(vertexTex->x, vertexTex->y);
                }

                const picg_vertex3F* vertex = &mesh->vertices[mesh->faces[vIndex].verticeIndexes[i] - 1];

                glVertex3f(
                    vertex->x,
                    vertex->y,
                    vertex->z
                );
            }
        }
    }
    
    glEnd();

#if PICG_DEBUG
    picg_gl_getError();
#endif

    glPopMatrix();
}