#ifndef font_rendering_h

#define font_rendering_h
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../utils/basic_types.h" 
#include "../render/opengl_basic_wrapper.h"
#include "../gameinfo.h"



// This struct stores a glyph's position in a texture atlas, it's size, bearing, and their stride for the next glyph(advance)
// Advance works with pixels because we bitshift(>> 6) freetype's return values in most functions. 
typedef struct Glyph { // We need line gap info!!
    glm::vec2 tex_pos;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    u32 Advance;
} Glyph;


// All these wrapping functions are mostly because freetype has a very shitty style of writing names. Snake_Camel_Case....
bool  ft_freetype_init(FT_Library *ft);
bool  ft_load_ttf(const char* font_location, FT_Library ft_handler, FT_Face *face_handler);
void  ft_face_set_size(FT_Face face, int width, int height);
bool  ft_face_load_character(FT_Face face, char character);
Glyph ft_face_create_glyph(FT_Face &face);

void  ft_free_face(FT_Face face);
void  ft_free_freetype(FT_Library ft_handler);

typedef struct _TYPEFACE {
    u32 texture_atlas;
    int atlas_width = 0, atlas_height = 0;
    std::map<char, Glyph> Glyphs;
    int size; // might not be necessary
    
} _TYPEFACE;



// This struct contains the basics for freetype to work, a texture atlas for glyphs,
// A map containing glyph objects, accessed by their character as key.
// I also tried to use a different naming style for "private members" but I'm not a big fan of.
typedef struct Font {
    FT_Library _freetype;
    FT_Face _face;
    Shader *_currently_bound_shader;

    std::map<int, _TYPEFACE> _FACES;
    u32 _VAO, _VBO;

    Font(const char *font_filepath, Shader *shader);
    void generate_ascii();
    void render_text(std::string text, glm::vec2 position, int size, glm::vec3 color);

} Font;

typedef struct TextManager {
    Shader *current_text_shader;
    Font *currently_bound_font;
    glm::mat4 text_projection;
    glm::vec3 currently_set_color;
    std::map<std::string, Font> Fonts;
    
    TextManager(GameInfo &GInfo);
    void set_font(std::string font_name);
    void set_color(glm::vec3 color);
    void render(std::string text, glm::vec2 position, int size);
} TextManager;


#endif
