#ifndef freetype_wrapper_h

#define freetype_wrapper_h

#include <ft2build.h>
#include FT_FREETYPE_H
#include "../utils/basic_types.h" 
#include "../render/opengl_basic_wrapper.h"


typedef struct Glyph { // We need line gap info!!
    glm::vec2 tex_pos;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    u32 Advance;
} Glyph;

bool  ft_freetype_init(FT_Library *ft);
bool  ft_load_ttf(const char* font_location, FT_Library ft_handler, FT_Face *face_handler);
void  ft_face_set_size(FT_Face face, int width, int height);
bool  ft_face_load_character(FT_Face face, char character);
Glyph ft_face_create_glyph(FT_Face &face);

void  ft_free_face(FT_Face face);
void  ft_free_freetype(FT_Library ft_handler);

#endif