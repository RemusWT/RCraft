#include "render_internals.h"

std::string defaultVertexSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord);\n"
"\n"
"out vec4 vertex_color;\n"
"out vec2 texCoord;\n"
"void main() {\n"
"    gl_Position = vec4(aPos, 1.0f);\n"
"    texCoord = aTexCoord;\n"
"    vertex_color = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}";

std::string defaultFragmentSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"in vec4 vertex_color;\n"
"in vec2 texCoord;\n"
"uniform sampler2D ourTexture;\n"
"\n"
"void main() {\n"
"    FragColor = texture(ourTexture, TexCoord);\n"
"}";

Texture::Texture(const char* filepath) {
    unsigned char *data;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    data = stbi_load(filepath, &width, &height, &nrChannels, 0);
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
