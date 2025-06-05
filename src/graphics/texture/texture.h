#pragma once
#include "image.h"

void picg_texture_load(picg_image* image);
void picg_texture_bind(const picg_image* image);
void picg_texture_unbind();
void picg_texture_texCoord(int i);