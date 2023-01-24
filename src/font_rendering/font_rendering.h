#ifndef font_rendering_h

#define font_rendering_h
#include "freetype_wrapper.h"


// @Robustness For now we will follow the learnopengl tutorial, which means to update the vbo data for each glyph at a time
// but we will have to use another method for better performance
typedef struct Text {
    float x, y;
    std::string literal_text = "You should have changed me.";
    u32 VAO, VBO; // @Reformat Use our defined structs for VAO and VBO!
    glm::mat4 text_proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f); // to be changed relative to screen resolution
    Text();
    void replace_text(const char *text);
    void render_text(Shader &s, std::map<char, Glyph> &Glyphs, float scale, glm::vec3 color);
} Text;



#endif