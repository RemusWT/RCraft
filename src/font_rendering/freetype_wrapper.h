#ifndef freetype_wrapper_h

#define freetype_wrapper_h

#include <ft2build.h>
#include FT_FREETYPE_H
#include "../utils/basic_types.h" 
#include "../render/opengl_basic_wrapper.h"


// @Rename we should change the name style of this functions to something more clear and perhaps modular.
// -font_load_ttf()
// -font_set_pixelsize()
// -font_load_character()
//  etc..

typedef struct CharacterGlyph {
    u32 TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    u32 Advance;
} CharacterGlyph;

bool ft_load_ttf(FT_Library ft_handler, const char* font_location, FT_Face *face_handler);
void ft_face_set_pixelsize(FT_Face face, int width, int height);
bool ft_face_load_character(FT_Face face, char character);
CharacterGlyph ft_face_generate_character_glyph(FT_Face face);

void ft_free_face(FT_Face face);
void ft_free_freetype(FT_Library ft_handler);

#endif