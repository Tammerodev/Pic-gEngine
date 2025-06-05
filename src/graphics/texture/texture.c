#include "texture.h"
#include <stb_image.h>

void picg_texture_load(picg_image* image)
{

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &image->textureID);
    glBindTexture(GL_TEXTURE_2D, image->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
    
    stbi_image_free(image->data);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void picg_texture_unbind()
{
}

void picg_texture_bind(const picg_image* image)
{   
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glScalef(image->width / 10.f, image->height / 10.f, 1.0f);
    glTranslatef(0.f, 0.f, 100.f);
    glRotatef(0.2f, 0.1f, 0.f, 0.f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image->textureID);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom-left
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f); // Bottom-right
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f); // Top-right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f); // Top-left
    glEnd();


    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void picg_texture_texCoord(int i)
{

}
