#ifndef render_internals_h
#define render_internals_h
#include "opengl_basic_wrapper.h"


// @Deprecated Is this even used?
//extern std::string defaultVertexSource;
//extern std::string defaultFragmentSource;




typedef struct Texture {
    u32 ID;
    std::string type; // was made because of learnopengl.com
    int width, height, nrChannels; // I keep this info for now. Might be useful to have these variables.
    Texture(const char* filepath, GLenum texture_type, GLenum slot, GLenum format, GLenum pixel_type);
    void texture_filtering(GLint filter);
    void texture_wrapping(GLint wrap_state);
    void update_texture(const char* filepath);
    void texture_unit();
} Texture;



#endif
