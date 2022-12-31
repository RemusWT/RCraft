#ifndef render_internals_h
#define render_internals_h
#include "../basic_modules/opengl_basic_wrapper.h"

extern std::string defaultVertexSource;
extern std::string defaultFragmentSource;

// if we go by the module_object_function() style, it might be useful to know that these
// struct also come from "module x". Or if it is only used by render_internals then we can explictily
// say it is static(?)

typedef struct Texture {
    u32 ID;
    std::string type; // was made because of learnopengl.com
    int width, height, nrChannels; // I keep this info for now. Might be useful to have these variables.
    Texture(const char* filepath);
    void textureFiltering(GLint filter);
    void updateTexture(const char* filepath);
} Texture;



#endif
