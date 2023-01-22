#include "font_render_internal.h"

void load_font(FT_Library ft_handler, const char* font_location, FT_Face *font_handler) {
    if (FT_New_Face(ft_handler, font_location, 0, font_handler)) {
        printf("Freetype error: Failed to load Glyph!\n");
    }
}

void set_font_pixelsize(FT_Face font, int width, int height) {
    FT_Set_Pixel_Sizes(font, width, height);
}

void load_font_character(FT_Face font, char character) {
    if (FT_Load_Char(font, character, FT_LOAD_RENDER)) {
        printf("Freetype error: Failed to load '%c' Glyph!\n", character);
    }
}