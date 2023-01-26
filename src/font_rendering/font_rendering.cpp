#include "font_rendering.h"


Font::Font(const char *font_filepath, Shader *shader) {
    ft_freetype_init(&freetype);GL_CHECK_ERROR
    ft_load_ttf(font_filepath, freetype, &face);GL_CHECK_ERROR
    currently_bound_shader = shader;GL_CHECK_ERROR
    ft_face_set_size(face, 0, 12); GL_CHECK_ERROR// We might want to remove this

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Font::generate_ascii_glyphs() {
    for (u8 c = 0; c < 128; c++) {
        if (ft_face_load_character(face, c)) continue;
        Glyph c_glyph = ft_face_create_glyph(face);
        Glyphs[c] = c_glyph;
    }
}

void Font::set_size(float fsize) {
    if (size != fsize) {
        FT_Set_Pixel_Sizes(face, 0, fsize);
        size = fsize;
    }
    

}
void Font::render_text(std::string text, glm::vec2 position, float fsize, glm::vec3 color) {
    // activate corresponding render state

    if (size != fsize) {
        FT_Set_Pixel_Sizes(face, 0, fsize);
        size = fsize;
        generate_ascii_glyphs();
        printf("got called\n");
    }
    currently_bound_shader->use();GL_CHECK_ERROR
    glUniform3f(glGetUniformLocation(currently_bound_shader->ID, "textColor"), color.r, color.g, color.b);GL_CHECK_ERROR
    glActiveTexture(GL_TEXTURE0);GL_CHECK_ERROR
    glBindVertexArray(vao); 

    // iterate through all characters
    std::string::const_iterator c;
    float advance_x = position.x;

    for (c = text.begin(); c != text.end(); c++) {
        Glyph ch = Glyphs[*c];

        float xpos = advance_x + ch.Bearing.x ;
        float ypos = position.y - (ch.Size.y - ch.Bearing.y) ;

        float w = ch.Size.x ;
        float h = ch.Size.y ;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);GL_CHECK_ERROR
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);GL_CHECK_ERROR
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        advance_x += (ch.Advance >> 6) ; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);GL_CHECK_ERROR
}

