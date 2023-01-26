#ifndef font_rendering_h

#define font_rendering_h
#include "freetype_wrapper.h"


// @Robustness For now we will follow the learnopengl tutorial, which means to update the vbo data for each glyph at a time
// but we will have to use another method for better performance

typedef struct Font {
    FT_Library freetype;
    FT_Face face;
    Shader *currently_bound_shader;

    std::map<char, Glyph> Glyphs;
    u32 vao, vbo;

    float size;
    Font(const char *font_filepath, Shader *shader);
    void generate_ascii_glyphs();
    void set_size(float fsize);
    void render_text(std::string text, glm::vec2 position, float fsize, glm::vec3 color);

} Font;



#endif