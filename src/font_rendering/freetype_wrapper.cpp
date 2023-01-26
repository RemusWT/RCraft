#include "freetype_wrapper.h"

// bool-returning functions return true if there was an error.

bool ft_load_ttf(FT_Library ft_handler, const char* font_location, FT_Face *face_handler) {
    if (FT_New_Face(ft_handler, font_location, 0, face_handler)) {
        printf("Freetype error: Failed to load Glyph!\n");
        return true;
    }
    return false;
}

void ft_face_set_size(FT_Face face, int width, int height) {
    FT_Set_Pixel_Sizes(face, width, height);
}

bool ft_face_load_character(FT_Face face, char character) {
    if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
        printf("Freetype error: Failed to load '%c' Glyph!\n", character);
        return true;
    }
    return false;
}

Glyph ft_face_create_glyph(FT_Face &face) {
    u32 texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Glyph character = {
        texture_id, 
        glm::ivec2(static_cast<u32>(face->glyph->bitmap.width), static_cast<u32>(face->glyph->bitmap.rows)),
        glm::ivec2(static_cast<u32>(face->glyph->bitmap_left),  static_cast<u32>(face->glyph->bitmap_top)),
        static_cast<u32>(face->glyph->advance.x)
    };
    return character;
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ft_free_face(FT_Face face) {
    FT_Done_Face(face);
}

void ft_free_freetype(FT_Library ft_handler) {
    FT_Done_FreeType(ft_handler);
}