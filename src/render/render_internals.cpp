#include "render_internals.h"


Texture::Texture(const char* filepath) {
    unsigned char *data;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    
    data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (data == NULL ) { // stbi_load shouldn't return an invalid address
        data = stbi_load("../../../asset/error_texture.jpg", &width, &height, &nrChannels, 0);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

void Texture::textureFiltering(GLint filter) {
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}
void Texture::updateTexture(const char* filepath) {
    unsigned char *data;
    glGenTextures(GL_TEXTURE_2D, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}
