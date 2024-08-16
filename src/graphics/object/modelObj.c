#include "objects.h"
#include <stdlib.h>

// TODO: Make it smarter
picg_vertex3F *modelVertices = NULL;
int modelVertexCount = 0;

picg_face* faces = NULL;
int modelFaceCount = 0;

int loadObj(const char* filepath) 
{
    FILE* objFile;

    // Open file in read mode
    objFile = fopen(filepath, "r");

    // File not found
    if(objFile == NULL) 
    {
        printf("Error loading OBJ file!\n");
        return -1;
    }

    const int bufferLength = 100;
    char buffer[bufferLength];

    long vertexCount = 0;
    long faceCount = 0;

    while(fgets(buffer, bufferLength, objFile)) 
    {
        if(buffer[1] == ' ') 
        {   // It is a vertex or a face
            if(buffer[0] == 'v') 
            {   // Vertex
                ++vertexCount;
            } 

            if(buffer[0] == 'v') 
            {   // Vertex
                faceCount++;
            } 
        }
    }

    rewind(objFile);

    const int originalVertexCount = vertexCount;
    printf("Vertex count: %d", (int)vertexCount);
    modelVertices = malloc(100 + (sizeof(picg_vertex3F) * originalVertexCount));

    vertexCount = 0;

    /*
        Reads the vertice data into modelVertices[]
    */
    while(fgets(buffer, bufferLength, objFile)) 
    {
        if(buffer[0] == 'v' && buffer[1] == ' ') 
        {
            printf(buffer);

            // Read vertex data into the array
            sscanf(buffer, "v %f %f %f \n", 
                &modelVertices[vertexCount].x,
                &modelVertices[vertexCount].y,
                &modelVertices[vertexCount].z);

            printf("read %f,%f,%f\n", 
                modelVertices[vertexCount].x,
                modelVertices[vertexCount].y,
                modelVertices[vertexCount].z);

            modelVertices[vertexCount].r = 1.0f;
            modelVertices[vertexCount].g = 1.0f;
            modelVertices[vertexCount].b = 1.0f;
            modelVertices[vertexCount].a = 1.0f;

            ++vertexCount;
        }
    }

    /*
        Rewinds the file and reads the face data 
    */
    rewind(objFile);

    // Allocate memory for faceCount x faces with 4x unsigned integers 
    faces = (picg_face*)malloc(
        faceCount * 4 * sizeof(unsigned int));

    int faceIndex = 0;

    while(fgets(buffer, bufferLength, objFile)) 
    {
        if(buffer[0] == 'f' && buffer[1] == ' ') 
        {
            // Store values we dont want
            int N = 0;

            // Get formatted output of face data
            //             vertex/texture/normal x4
            sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
            &faces[faceIndex].verticeIndexes[0], &N, &N,
            &faces[faceIndex].verticeIndexes[1], &N, &N,
            &faces[faceIndex].verticeIndexes[2], &N, &N,
            &faces[faceIndex].verticeIndexes[3], &N, &N
            );

            printf("FACE READ\n");

            ++faceIndex;
        }
    }

    for(int f = 0; f < faceIndex; f++) {
        printf("Face data: %d, %d, %d, %d \n", 
            (int)(faces[f].verticeIndexes[0]),
            (int)(faces[f].verticeIndexes[1]),
            (int)(faces[f].verticeIndexes[2]),
            (int)(faces[f].verticeIndexes[3]));
    }


    modelVertexCount = vertexCount;
    modelFaceCount = faceIndex;
    fclose(objFile);
}

picg_mesh* picg_modelObj_create() 
{
    picg_mesh* mesh = malloc(sizeof(picg_mesh));

    int result = loadObj("../dev/Models/cube.obj");
 
    if(modelVertices == NULL) {
        printf("Error: Model vertices pointer is null returning a cube!\n");
        return picg_cube_create();
    }

    if(faces == NULL) {
        printf("Error: Model faces pointer is null returning a cube!\n");
        return picg_cube_create();
    }

    mesh->renderType = GL_QUAD_STRIP;
    mesh->vertices = modelVertices;
    mesh->vertexCount = modelVertexCount;   

    mesh->faces = faces;
    mesh->faceCount = modelFaceCount;

    mesh->position.x = 0;
    mesh->position.y = 0;
    mesh->position.z = -5;

    mesh->rotation.x = 0;
    mesh->rotation.y = 10;
    mesh->rotation.z = 0;

    return mesh;
}