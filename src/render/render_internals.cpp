#include "render_internals.h"


Texture::Texture(const char* filepath, GLenum texture_type, GLenum slot, GLenum format, GLenum pixel_type) {
    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texture_type, ID);
    
    unsigned char *data;
    data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (data == NULL ) { // stbi_load shouldn't return an invalid address
        data = stbi_load("../../../asset/error_texture.jpg", &width, &height, &nrChannels, 0);
    }
    
    glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(texture_type, 0, format, width, height, 0, format, pixel_type, data); 
    glGenerateMipmap(texture_type); // if you don't generate mipmaps but you use GL MIPMAP filters it will fail!!!
    stbi_image_free(data);
}

void Texture::texture_filtering(GLint filter) { // designed for 3D graphics, not pixelart!!!
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

void Texture::texture_unit() {
}
