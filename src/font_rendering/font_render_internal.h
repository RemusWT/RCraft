#ifndef font_render_internal_h

#define font_render_internal_h

#include <ft2build.h>
#include FT_FREETYPE_H
#include "../utils/basic_types.h" 
#include "../render/opengl_basic_wrapper.h"

typedef struct Character {
    u32 TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    u32 Advance;
} Character;

void load_font(FT_Library ft_handler, const char* font_location, FT_Face *font_handler);
void set_font_pixelsize(FT_Face font, int width, int height);
void load_font_character(FT_Face font, char character);

#endif