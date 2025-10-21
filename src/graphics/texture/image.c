#include "image.h"



#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

picg_image picg_image_load(const char *filepath)
{
    picg_image image;

    stbi_set_flip_vertically_on_load(1);

    image.data 
        = stbi_load(filepath, &image.width, &image.height, &image.channels, 3);

    PICG_LOG("Loaded image %s, width %i, height %i, channels %i \n \n", filepath, image.width, image.height, image.channels);

    if(!image.data)
        PICG_ERROR("Could not load image!");

    return image;
}