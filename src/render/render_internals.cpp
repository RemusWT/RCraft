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
    glGenerateMipmap(GL_TEXTURE_2D); // if you don't generate mipmaps and use GL MIPMAP filters it will fail!!!
    stbi_image_free(data);
}

void Texture::texture_filtering(GLint filter) {
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Texture::texture_wrapping(GLint wrap_state) {
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_state);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_state);
}

void Texture::update_texture(const char* filepath) {
    unsigned char *data;
    glGenTextures(GL_TEXTURE_2D, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}
