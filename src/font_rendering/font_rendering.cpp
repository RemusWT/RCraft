#include "font_rendering.h"

Text::Text() {
    glGenVertexArrays(1, &text_vao);
    glGenBuffers(1, &text_vbo);

    glBindVertexArray(text_vao);
    glBindBuffer(GL_ARRAY_BUFFER, text_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Text::replace_text(const char *text) {
    literal_text = text;
}

void Text::render_text(Shader &shader, std::map<char, Glyph> Glyphs, glm::vec3 color) {
    // activate corresponding render state	
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_vao); // will have to changed to just text_vao

    // iterate through all characters
    std::string::const_iterator c;
    float advance_x = x;
    for (c = literal_text.begin(); c != literal_text.end(); c++) 
    {
        Glyph ch = Glyphs[*c];

        float xpos = advance_x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
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
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        advance_x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}



Font::Font(const char *font_filepath, Shader *shader) {
    ft_freetype_init(&freetype);
    ft_load_ttf(font_filepath, freetype, &face);
    currently_bound_shader = shader;
    ft_face_set_size(face, 0, 12); // We might want to remove this
}
void Font::generate_ascii_glyphs() {
    for (u8 c = 0; c < 128; c++) {
        if (ft_face_load_character(face, c)) continue;
        Glyph c_glyph = ft_face_create_glyph(face);
        Glyphs.insert(std::pair<char, Glyph>(c, c_glyph));
    }
}

void Font::change_size(float size) {
    ft_face_set_size(face, 0, size);
}
void Font::render_text(std::string text, glm::vec2 position, float scale, glm::vec3 color) {
    // activate corresponding render state	
    currently_bound_shader->use();
    glUniform3f(glGetUniformLocation(currently_bound_shader->ID, "textColor"), color.r, color.g, color.b);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao); // will have to changed to just text_vao

    // iterate through all characters
    std::string::const_iterator c;
    float advance_x = position.x;

    for (c = text.begin(); c != text.end(); c++) {
        Glyph ch = Glyphs[*c];

        float xpos = advance_x + ch.Bearing.x * scale;
        float ypos = position.y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
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
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        advance_x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

