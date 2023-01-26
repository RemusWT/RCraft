#include "font_rendering.h"

Text::Text() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Text::replace_text(const char *text) {
    literal_text = text;
}

void Text::render_text(Shader &text_shader, std::map<char, Glyph> &Glyphs, float scale, glm::vec3 color) {
    text_shader.use();
    glUniform3f(glGetUniformLocation(text_shader.ID, "textColor"), color.r, color.g, color.b); GL_CHECK_ERROR
    glUniformMatrix4fv(glGetUniformLocation(text_shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(text_proj)); GL_CHECK_ERROR
    
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = literal_text.begin(); c != literal_text.end(); c++) {
        Glyph ch = Glyphs[*c];
        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0 , sizeof(vertices), vertices); GL_CHECK_ERROR
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x += (ch.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}
