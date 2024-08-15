#include "objects.h"
#include <stdlib.h>

// TODO: Make it smarter
struct picg_vertex3F *modelVertices;
int modelVertexCount = 0;

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

    float vertexData[vertexCount * 3 + 3];

    int vertexIndex = 0;

    vertexCount = 0;

    while(fgets(buffer, bufferLength, objFile)) 
    {
        if(buffer[0] == 'v' && buffer[1] == ' ') 
        {
            // Read vertex data into the array
            sscanf(buffer, "v %f %f %f", 
                &vertexData[vertexIndex + 0],
                &vertexData[vertexIndex + 1],
                &vertexData[vertexIndex + 2]);

            printf("read %f,%f,%f\n", 
                vertexData[vertexIndex + 0],
                vertexData[vertexIndex + 1],
                vertexData[vertexIndex + 2]);

            vertexIndex += 3;  // Move to the next set of x, y, z
            ++vertexCount;
        }
    }

    for(int ind = 0; ind < originalVertexCount * 3; ind++) {
        printf("%f\n", vertexData[ind]);
    }

    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    int meshFloatStep = 0;
    int meshVerticeStep = 0;

    modelVertices = malloc(100 + (sizeof(struct picg_vertex3F) * originalVertexCount));

    for(int ind = 0; ind < originalVertexCount * 3; ind++) {
        float data = vertexData[ind];

        switch (meshFloatStep)
        {
        case 0:
            x = data;
            break;
        case 1:
            y = data;
            break;
        case 2:
            z = data;
            break;
        }

        ++meshFloatStep;

        if(meshFloatStep == 3) {
            modelVertices[meshVerticeStep].x = x;
            modelVertices[meshVerticeStep].y = y;
            modelVertices[meshVerticeStep].z = z;

            meshVerticeStep++;
            meshFloatStep = 0;

            printf("Vertex data: x(%f) y(%f) z(%f) \n", x, y, z);
        }
    }


    modelVertexCount = meshVerticeStep;

    fclose(objFile);
}

picg_mesh* picg_modelObj_create() 
{
    picg_mesh* mesh = malloc(sizeof(picg_mesh));

    int result = loadObj("../dev/Models/cube.obj");
 
    mesh->renderType = GL_QUADS;
    mesh->vertices = modelVertices;
    mesh->meshSize = modelVertexCount;   

    mesh->position.x = 0;
    mesh->position.y = 0;
    mesh->position.z = 0;

    mesh->rotation.x = 0;
    mesh->rotation.y = 10;
    mesh->rotation.z = 0;

    return mesh;
}