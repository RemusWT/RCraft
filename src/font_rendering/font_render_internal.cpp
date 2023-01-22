#include "font_render_internal.h"

void load_font(FT_Library ft_handler, const char* font_location, FT_Face *font_handler) {
    if (FT_New_Face(ft_handler, font_location, 0, font_handler)) {
        printf("Freetype error: Failed to load Glyph!\n");
    }
}

void set_font_pixelsize(FT_Face font, int width, int height) {
    FT_Set_Pixel_Sizes(font, width, height);
}
int load_font_character(FT_Face font, char character) {
    if (FT_Load_Char(font, character, FT_LOAD_RENDER)) {
        printf("Freetype error: Failed to load '%c' Glyph!\n", character);
        return -1;
    }
    return 0;
}

Character font_generate_character_texture(FT_Face font) {
    u32 texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        font->glyph->bitmap.width,
        font->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        font->glyph->bitmap.buffer
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    struct Character character = {
        texture_id, 
        glm::ivec2(static_cast<u32>(font->glyph->bitmap.width), static_cast<u32>(font->glyph->bitmap.rows)),
        glm::ivec2(static_cast<u32>(font->glyph->bitmap_left), static_cast<u32>(font->glyph->bitmap_top)),
        static_cast<u32>(font->glyph->advance.x)
    };
    return character;
}