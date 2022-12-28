#ifndef render_internals_h
#define render_internals_h
#include "../basic_modules/opengl_basic_wrapper.h"

std::string defaultVertexSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"\n"
"out vec4 vertex_color;\n"
"void main() {\n"
"    gl_Position = vec4(aPos, 1.0f);\n"
"    vertex_color = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}";
std::string defaultFragmentSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"in vec4 vertex_color;\n"
"\n"
"void main() {\n"
"    FragColor = vertex_color;\n"
"}";

typedef struct Texture {
    u32 ID;
    std::string type; // was made because of learnopengl.com
    int width, height, nrChannels; // we contain this on the struct scope not in a function because we might find
    // usefullness in the future for these variables.
    Texture(const char* filepath);
    void textureFiltering(GLint filter);
    void updateTexture(const char* filepath);
} Texture;


#endif
