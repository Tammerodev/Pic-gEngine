#pragma once
#include <graphics/graphicsGL.h>

typedef struct
{
    unsigned char* data;
    int width, height;
    int channels;
    GLuint textureID;
} picg_image;


// Returns raw data
picg_image picg_image_load(const char* filepath);