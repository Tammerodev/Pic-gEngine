#include "objects.h"
#include <stdlib.h>

#include "../material/material.h"

// TODO: Make it smarter
picg_vertex3F *modelVertices = NULL;
int modelVertexCount = 0;

picg_face* faces = NULL;
int modelFaceCount = 0;

picg_bool hasTexture = false;

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
    faces[faceIndex].hasNormals = false;

    obj_renderType = GL_TRIANGLES;
}


void picg_modelObj_readFace_6(const char buffer[], const int faceIndex) {
    int v[3];
    int vt[3];
    int vn[3];

    int values = sscanf(buffer, "f %d//%d %d//%d %d//%d",
        &v[0], &vn[0],
        &v[1], &vn[1],
        &v[2], &vn[2]
    );  


    if(values == 6) {
        for(int i = 0; i < 3; ++i) {
            faces[faceIndex].verticeIndexes[i] = v[i];
            faces[faceIndex].normalIndexes[i] = vn[i];
        }
    } else {
        sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",
            &v[0], &vt[0], &vn[0],
            &v[1], &vt[1], &vn[1],
            &v[2], &vt[2], &vn[2]
        );  

        for(int i = 0; i < 3; ++i) {
            faces[faceIndex].verticeIndexes[i] = v[i];
            faces[faceIndex].normalIndexes[i] = vn[i];
            faces[faceIndex].textureIndexes[i] = vt[i];
        }

        faces[faceIndex].hasTexture = true; 
    }

    faces[faceIndex].verticesPerFace = 3;
    faces[faceIndex].hasNormals = true;

    obj_renderType = GL_TRIANGLES;
}

void picg_modelObj_readFace_8(const char buffer[], const int faceIndex) {
    // Store values we dont want
    int N = 0;

    // Get formatted output of face data
    //             vertex/texture/normal x4
    sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
        &faces[faceIndex].verticeIndexes[0], &faces[faceIndex].textureIndexes[0], &faces[faceIndex].normalIndexes[0],
        &faces[faceIndex].verticeIndexes[1], &faces[faceIndex].textureIndexes[1], &faces[faceIndex].normalIndexes[1],
        &faces[faceIndex].verticeIndexes[2], &faces[faceIndex].textureIndexes[2], &faces[faceIndex].normalIndexes[2],
        &faces[faceIndex].verticeIndexes[3], &faces[faceIndex].textureIndexes[3], &faces[faceIndex].normalIndexes[3]
    );

    faces[faceIndex].verticesPerFace = 4;
    faces[faceIndex].hasNormals = true;
    faces[faceIndex].hasTexture = true;

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
        // It is a vertex or a face
        if(buffer[0] == 'v') 
        {   // Vertex
            ++vertexCount;
        } 

        if(buffer[0] == 'f') 
        {   // Vertex
            faceCount++;
        } 
    }

    rewind(objFile);

    const int originalVertexCount = vertexCount;
    PICG_LOG("Vertex count: %d", (int)vertexCount);
    PICG_LOG("Face count: %d", (int)faceCount);

    modelVertices = calloc(1, (sizeof(picg_vertex3F) * originalVertexCount));

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

            ++vertexCount;
        }
    }

    // Rewind, read normal data
    rewind(objFile);

    int normalCount = 0;

    while(fgets(buffer, bufferLength, objFile)) {
        if(buffer[0] == 'v' && buffer[1] == 'n'){
            sscanf(buffer, "vn %f %f %f \n", 
                &modelVertices[normalCount].xn,
                &modelVertices[normalCount].yn,
                &modelVertices[normalCount].zn);

            ++normalCount;
        }
    }

    // Rewind, read vertex texture data
    rewind(objFile);

    int textureCount = 0;

    while(fgets(buffer, bufferLength, objFile)) {
        if(buffer[0] == 'v' && buffer[1] == 't'){
            sscanf(buffer, "vt %f %f \n", 
                &modelVertices[textureCount].xt,
                &modelVertices[textureCount].yt);

            ++textureCount;
        }
    }

    /*
        Rewinds the file and reads the face data 
    */
    rewind(objFile);

    // TODO: This is so funny terrible! Fix this, QUICK!
    // Allocate memory for faceCount x faces with 6x unsigned integers 
    faces = (picg_face*)calloc(1, 
        faceCount * sizeof(picg_face));

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
    modelVertexCount = vertexCount;
    modelFaceCount = faceIndex;
    fclose(objFile);

    return 0;
}

picg_mesh* picg_modelObj_create(const char* model_path) 
{
    picg_mesh* mesh = calloc(1, sizeof(modelVertices) + sizeof(faces) + sizeof(picg_mesh));

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

    if(modelVertexCount == 0) {
        PICG_ERROR("Error: Model does not contain vertices!");
        return picg_cube_create();
    }

    mesh->renderType = obj_renderType;
    mesh->vertices = modelVertices;
    mesh->vertexCount = modelVertexCount; 

    // Special case
    if(mesh->vertexCount == 1) mesh->renderType = GL_POINTS; 

    mesh->faces = faces;
    mesh->faceCount = modelFaceCount;

    mesh->scaling.x = 1.f;
    mesh->scaling.y = 1.f;
    mesh->scaling.z = 1.f;

    mesh->render = true;
    
    PICG_SUCC("Successfully loaded model with %d vertices\n", mesh->vertexCount);
    
    return mesh;
}