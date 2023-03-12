#include "font_rendering.h"

// bool-returning functions return true if there was an error.
bool  ft_freetype_init(FT_Library *ft) {
    if (FT_Init_FreeType(ft)) {
        printf("Freetype error: Could not initialize FreeType Library.\n");
        return true;
    }
    return false;
}



bool ft_load_ttf(const char* font_location, FT_Library ft_handler, FT_Face *face_handler) {
    if (FT_New_Face(ft_handler, font_location, 0, face_handler)) {
        printf("Freetype error: Failed to load font %s!\n", font_location);
        return true;
    }
    return false;
}

void ft_face_set_size(FT_Face face, int width, int height) { //@Deprecated
    FT_Set_Pixel_Sizes(face, width, height);
}

bool ft_face_load_character(FT_Face face, char character) {
    if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
        printf("Freetype error: Failed to load '%c' Glyph!\n", character);
        return true;
    }
    return false;
}

void ft_free_face(FT_Face face) {
    FT_Done_Face(face);
}

void ft_free_freetype(FT_Library ft_handler) {
    FT_Done_FreeType(ft_handler);
}

Font::Font(const char *font_filepath, Shader *shader) {
    ft_freetype_init(&_freetype);
    ft_load_ttf(font_filepath, _freetype, &_face);
    _currently_bound_shader = shader;

    ft_face_set_size(_face, 0, 12); // We might want to remove this

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    // Generating a Buffer with the size of a single quad.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void Font::render_text(std::string text, glm::vec2 position, int size, glm::vec3 color) {
    // @BUG Currently, the text can be invisible because of what I guess to be a Field of View problem.
    // If you get close to a block the text in the corner of the screen will be faded as if it hides behind the block.
    // I believe this is because the text on the screen is placed further in front of the camera and the blocks can
    // be rendered closer to the screen.


    
    _currently_bound_shader->use();GL_CHECK_ERROR
    glUniform3f(glGetUniformLocation(_currently_bound_shader->ID, "textColor"), color.r, color.g, color.b);GL_CHECK_ERROR
    //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(), 0.0f, static_cast<float>(SCR_HEIGHT));

    if (_FACES.find(size) == _FACES.end()) {
        _TYPEFACE typeface;
        glGenTextures(1, &typeface.texture_atlas);
        ft_face_set_size(_face, 0, size);

        // Generating ASCII 

        // determining the total size for all ascii glyphs to fit inside the texture atlas
        for (u8 c = 0; c < 128; c++) {
            if (ft_face_load_character(_face, c)) continue;

            typeface.atlas_width += static_cast<s32>(_face->glyph->advance.x >> 6);
            if (typeface.atlas_height < static_cast<s32>(_face->glyph->bitmap.rows)) {
                typeface.atlas_height = static_cast<s32>(_face->glyph->bitmap.rows);
            }
        }

        // allocating enough memory for the texture atlas
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, typeface.texture_atlas);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, typeface.atlas_width, typeface.atlas_height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);GL_CHECK_ERROR

        // Populating the new texture atlas with glyphs and also storing glyph objects in the map.
        int advance_x = 0;
        for (u8 c = 0; c < 128; c++) {
            if (ft_face_load_character(_face, c)) continue;
            // Creating the glyph with the necessary info
            int glyph_bitmap_width  =  _face->glyph->bitmap.width;
            int glyph_bitmap_height =  _face->glyph->bitmap.rows;
            u32 glyph_advance       =  static_cast<u32>(_face->glyph->advance.x >> 6);


            Glyph c_glyph = {
                glm::vec2(static_cast<float>(advance_x), static_cast<float>(glyph_bitmap_height)),
                glm::vec2(glyph_bitmap_width, glyph_bitmap_height),
                glm::ivec2(static_cast<u32>(_face->glyph->bitmap_left),  static_cast<u32>(_face->glyph->bitmap_top)),
                glyph_advance
            };
            typeface.Glyphs[c] = c_glyph;

            // Adding the glyph to the texture_atlas
            glTexSubImage2D(GL_TEXTURE_2D,
                            0,
                            advance_x, // glyphs is placed at advance_x pixel coordinate
                            0,         // and placed at y 0 coordinate
                            glyph_bitmap_width,
                            glyph_bitmap_height,
                            GL_RED,
                            GL_UNSIGNED_BYTE,
                            _face->glyph->bitmap.buffer); GL_CHECK_ERROR
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // moves the cursor for the next glyph in the atlas
            advance_x += (_face->glyph->advance.x >> 6);
        }

        _FACES.insert(std::pair<int, _TYPEFACE>(size, typeface));
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _FACES[size].texture_atlas);
    glBindVertexArray(_VAO);
    


    // @TODO Current implemenation is not very efficient. We send a single quad each time to the gpu when we should create a large vertex data
    // and batch it together to the gpu. One vertex transfer and once draw call. WE NEED BATCHING

    // iterate through all characters
    std::string::const_iterator c;
    float advance_x = position.x; // starting point relative to where the whole text is supposed to be placed.
    std::vector<float> batched_vectices;
    batched_vectices.reserve(text.size() * 6 * 4);

    for (c = text.begin(); c != text.end(); c++) {
        Glyph ch = _FACES[size].Glyphs[*c];


        // Glyph quad mesh generation
        float xpos = advance_x + ch.Bearing.x ;
        float ypos = position.y - (ch.Size.y - ch.Bearing.y) ;

        float w = ch.Size.x ;
        float h = ch.Size.y ;

        float texture_x = ch.tex_pos.x;
        float texture_y = ch.tex_pos.y;

        float texture_atlas_width  = _FACES[size].atlas_width;
        float texture_atlas_height = _FACES[size].atlas_height;

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
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                batched_vectices.push_back(vertices[i][j]);
            }
        }

        // update content of VBO memory
        //glBindBuffer(GL_ARRAY_BUFFER, _VBO);GL_CHECK_ERROR
        //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

        // render quad
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        advance_x += ch.Advance; 
    }
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, batched_vectices.size() * sizeof(float), &batched_vectices[0], GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);GL_CHECK_ERROR
}

TextManager::TextManager(GameInfo &GInfo) {
    std::string loaded_text_vertex_source   = file_get_contents("../../asset/shaders/text_vert.glsl");
    std::string loaded_text_fragment_source = file_get_contents("../../asset/shaders/text_frag.glsl");
    current_text_shader = new Shader(loaded_text_vertex_source.c_str(), loaded_text_fragment_source.c_str());
    
    current_text_shader->use();
    glm::mat4 text_projection = glm::ortho(0.0f, static_cast<float>(GInfo.resolution_x), 0.0f, static_cast<float>(GInfo.resolution_y));
    glUniformMatrix4fv(glGetUniformLocation(current_text_shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(text_projection));
    
    currently_set_color = glm::vec3(255.0f, 255.0f, 255.0f);
    Font Coolvetica("../../asset/fonts/coolvetica.otf", current_text_shader);

    Fonts.insert(std::pair<std::string, Font>("Coolvetica", Coolvetica));
}

void TextManager::set_font(std::string font_name) {
    if (Fonts.find(font_name) != Fonts.end()) {
        currently_bound_font = &Fonts.at(font_name);
    }
    else {
        printf("TextManager error: Font '%s' is not loaded", font_name.c_str());
    }
}

void TextManager::render(std::string text, glm::vec2 position, int size) {
    currently_bound_font->render_text(text, position, size, currently_set_color);
}
