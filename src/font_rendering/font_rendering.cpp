#include "font_rendering.h"


Font::Font(const char *font_filepath, Shader *shader) {
    ft_freetype_init(&freetype);GL_CHECK_ERROR
    ft_load_ttf(font_filepath, freetype, &face);GL_CHECK_ERROR
    currently_bound_shader = shader;GL_CHECK_ERROR
    ft_face_set_size(face, 0, 38); GL_CHECK_ERROR// We might want to remove this
    size = 38;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Generating a Buffer with the size of a single quad.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glGenTextures(1, &texture_atlas);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Font::generate_ascii() {

    // determining the total size for all ascii glyphs to fit
    for (u8 c = 0; c < 128; c++) {
        if (ft_face_load_character(face, c)) continue;

        texture_atlas_width += static_cast<s32>(face->glyph->advance.x >> 6);
        if (texture_atlas_height < static_cast<s32>(face->glyph->bitmap.rows)) {
            texture_atlas_height = static_cast<s32>(face->glyph->bitmap.rows); // thus creating just a long texture atlas
        }
    }

    // allocating enough memory for the texture atlas
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_atlas);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture_atlas_width, texture_atlas_height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);GL_CHECK_ERROR

    // Populating the new texture atlas with glyphs and also storing glyph objects in the map.
    int advance_x = 0;
    for (u8 c = 0; c < 128; c++) {
        if (ft_face_load_character(face, c)) continue;
        // Creating the glyph with the necessary info
        int glyph_bitmap_width  =  face->glyph->bitmap.width;
        int glyph_bitmap_height =  face->glyph->bitmap.rows;
        u32 glyph_advance       =  static_cast<u32>(face->glyph->advance.x >> 6);


        Glyph c_glyph = {
            glm::vec2(static_cast<float>(advance_x), static_cast<float>(glyph_bitmap_height)),
            glm::vec2(glyph_bitmap_width, glyph_bitmap_height),
            glm::ivec2(static_cast<u32>(face->glyph->bitmap_left),  static_cast<u32>(face->glyph->bitmap_top)),
            glyph_advance
        };
        Glyphs[c] = c_glyph; GL_CHECK_ERROR
        

        // Adding the glyph to the texture_atlas
        glTexSubImage2D(GL_TEXTURE_2D,
                        0,
                        advance_x, // glyphs is placed at advance_x pixel coordinate
                        0,         // and placed at y 0 coordinate
                        glyph_bitmap_width,
                        glyph_bitmap_height,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer); GL_CHECK_ERROR
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // moves the cursor for the next glyph in the atlas
        advance_x += (face->glyph->advance.x >> 6);
    }
}




void Font::render_text(std::string text, glm::vec2 position, glm::vec3 color) {
    // @TODO Current implemenation is not very efficient. We send a single quad each time to the gpu when we should create a large vertex data
    // and batch it together to the gpu. One vertex transfer and once draw call.

    currently_bound_shader->use();GL_CHECK_ERROR
    glUniform3f(glGetUniformLocation(currently_bound_shader->ID, "textColor"), color.r, color.g, color.b);GL_CHECK_ERROR

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_atlas);
    glBindVertexArray(vao); 
    

    // iterate through all characters
    std::string::const_iterator c;
    float advance_x = position.x; // starting point relative to where the whole text is supposed to be placed.

    for (c = text.begin(); c != text.end(); c++) {
        Glyph ch = Glyphs[*c];


        // Glyph quad mesh generation
        float xpos = advance_x + ch.Bearing.x ;
        float ypos = position.y - (ch.Size.y - ch.Bearing.y) ;

        float w = ch.Size.x ;
        float h = ch.Size.y ;

        float texture_x = ch.tex_pos.x;
        float texture_y = ch.tex_pos.y;

        // update VBO for each character
        // Texture Coordinates are divided by the width and height of the atlas so we can get normalized values.
        float vertices[6][4] = {
            { xpos,     ypos + h,   texture_x / texture_atlas_width, 0.0f },            
            { xpos,     ypos,       texture_x / texture_atlas_width, texture_y / texture_atlas_height },
            { xpos + w, ypos,       (texture_x + ch.Advance) / texture_atlas_width, texture_y / texture_atlas_height },

            { xpos,     ypos + h,   texture_x / texture_atlas_width, 0.0f },
            { xpos + w, ypos,       (texture_x + ch.Advance) / texture_atlas_width, texture_y / texture_atlas_height },
            { xpos + w, ypos + h,   (texture_x + ch.Advance) / texture_atlas_width, 0.0f }
        };

        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);GL_CHECK_ERROR
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        advance_x += ch.Advance ; 
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);GL_CHECK_ERROR
}

