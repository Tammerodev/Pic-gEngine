#include "objects.h"
#include <stdlib.h>

// TODO: Make it smarter
picg_vertex3F *modelVertices = NULL;
int modelVertexCount = 0;

picg_face* faces = NULL;
int modelFaceCount = 0;

int obj_renderType = GL_TRIANGLES;

void picg_modelObj_readFace_0(const char buffer[], const int faceIndex) {
    // Store values we dont want
    int N = 0;

    // Get formatted output of face data
    //             vertex/texture/normal x4
    sscanf(buffer, "f %d %d %d",
        &faces[faceIndex].verticeIndexes[0],
        &faces[faceIndex].verticeIndexes[1],
        &faces[faceIndex].verticeIndexes[2]
    );

    // Todo: We cant really assume this
    faces[faceIndex].verticesPerFace = 3;

    obj_renderType = GL_TRIANGLES;
}


void picg_modelObj_readFace_6(const char buffer[], const int faceIndex) {
    // Get formatted output of face data
    //             vertex//normal x3
    sscanf(buffer, "f %d//%d %d//%d %d//%d",
        &faces[faceIndex].verticeIndexes[0], &faces[faceIndex].normalIndexes[0],
        &faces[faceIndex].verticeIndexes[1], &faces[faceIndex].normalIndexes[1],
        &faces[faceIndex].verticeIndexes[2], &faces[faceIndex].normalIndexes[2]
    );

    faces[faceIndex].verticesPerFace = 3;

    obj_renderType = GL_TRIANGLES;
}

void picg_modelObj_readFace_8(const char buffer[], const int faceIndex) {
    // Store values we dont want
    int N = 0;

    // Get formatted output of face data
    //             vertex/texture/normal x4
    sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
        &faces[faceIndex].verticeIndexes[0], &N, &faces[faceIndex].normalIndexes[0],
        &faces[faceIndex].verticeIndexes[1], &N, &faces[faceIndex].normalIndexes[1],
        &faces[faceIndex].verticeIndexes[2], &N, &faces[faceIndex].normalIndexes[2],
        &faces[faceIndex].verticeIndexes[3], &N, &faces[faceIndex].normalIndexes[3]
    );

    faces[faceIndex].verticesPerFace = 4;

    obj_renderType = GL_QUADS;
}


int loadObj(const char* filepath) 
{
    FILE* objFile;

    // Open file in read mode
    objFile = fopen(filepath, "r");

    // File not found
    if(objFile == NULL) 
    {
        PICG_ERROR("Error loading OBJ file!\n");
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

            if(buffer[0] == 'f') 
            {   // Vertex
                faceCount++;
            } 
        }
    }

    rewind(objFile);

    const int originalVertexCount = vertexCount;
    printf("Vertex count: %d\n", (int)vertexCount);
    printf("Face count: %d\n", (int)faceCount);

    modelVertices = malloc(100 + (sizeof(picg_vertex3F) * originalVertexCount));

    vertexCount = 0;

    /*
        Reads the vertice data into modelVertices[]
    */
    while(fgets(buffer, bufferLength, objFile)) 
    {
        if(buffer[0] == 'v' && buffer[1] == ' ') 
        {
            // Read vertex data into the array
            sscanf(buffer, "v %f %f %f \n", 
                &modelVertices[vertexCount].x,
                &modelVertices[vertexCount].y,
                &modelVertices[vertexCount].z);

            modelVertices[vertexCount].r = 0.5f;
            modelVertices[vertexCount].g = 0.5f;
            modelVertices[vertexCount].b = 0.5f;

            modelVertices[vertexCount].a = 1.0f;

            ++vertexCount;
        }
    }

    // Rewind, read normal data
    rewind(objFile);

    vertexCount = 0;

    while(fgets(buffer, bufferLength, objFile)) {
        if(buffer[0] == 'v' && buffer[1] == 'n'){
            sscanf(buffer, "vn %f %f %f \n", 
                &modelVertices[vertexCount].xn,
                &modelVertices[vertexCount].yn,
                &modelVertices[vertexCount].zn);

            ++vertexCount;
        }
    }

    /*
        Rewinds the file and reads the face data 
    */
    rewind(objFile);

    // TODO: This is so funny terrible! Fix this, QUICK!
    // Allocate memory for faceCount x faces with 6x unsigned integers 
    faces = (picg_face*)malloc(
        faceCount * 10 * sizeof(unsigned int));

    int faceIndex = 0;

    while(fgets(buffer, bufferLength, objFile)) 
    {
        if(buffer[0] == 'f' && buffer[1] == ' ') 
        {
            int slashesFound = picg_string_countContainsCharacter(buffer, '/');
            
                 if(slashesFound == 0) picg_modelObj_readFace_0(buffer, faceIndex);
            else if(slashesFound == 6) picg_modelObj_readFace_6(buffer, faceIndex);
            else if(slashesFound == 8) picg_modelObj_readFace_8(buffer, faceIndex);

            ++faceIndex;
        }
    }

    printf("Done now saving counts\n");

    modelVertexCount = vertexCount;
    modelFaceCount = faceIndex;
    fclose(objFile);

    printf("Done reading .obj data!\n");

    return 0;
}

picg_mesh* picg_modelObj_create(const char* model_path) 
{
    picg_mesh* mesh = malloc(sizeof(modelVertices) + sizeof(faces) + sizeof(picg_mesh));

    int result = loadObj(model_path);

    if(result == -1) {
        PICG_ERROR("Error: Could not open model file!");
        return picg_cube_create();
    }
 
    if(modelVertices == NULL) {
        PICG_ERROR("Error: Model vertices pointer is null returning a cube!");
        return picg_cube_create();
    }

    if(faces == NULL) {
        PICG_ERROR("Error: Model faces pointer is null returning a cube!");
        return picg_cube_create();
    }

    mesh->renderType = obj_renderType;
    mesh->vertices = modelVertices;
    mesh->vertexCount = modelVertexCount;   

    mesh->faces = faces;
    mesh->faceCount = modelFaceCount;

    mesh->position.x = 0;
    mesh->position.y = 0;
    mesh->position.z = -5;

    mesh->rotation.x = 0;
    mesh->rotation.y = 0;
    mesh->rotation.z = 0;

    printf("Successfully loaded model with %d", mesh->vertexCount);
    
    return mesh;
}