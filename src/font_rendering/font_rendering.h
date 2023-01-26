#ifndef font_rendering_h

#define font_rendering_h
#include "freetype_wrapper.h"


// @Robustness For now we will follow the learnopengl tutorial, which means to update the vbo data for each glyph at a time
// but we will have to use another method for better performance
typedef struct Text {
    float x, y;
    float scale = 1;
    std::string literal_text = "You should have changed me.";

    u32 text_vao, text_vbo; // @Reformat Use our defined structs for VAO and VBO!

    Text();
    void replace_text(const char *text);
    void render_text(Shader &shader, std::map<char, Glyph> Glyphs, glm::vec3 color);
} Text;



#endif