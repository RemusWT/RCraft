#ifndef gamesettings_h
#define gamesettings_h

#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/rcf_basic.h"


typedef struct GameSettings_ {
    int resolution_x, resolution_y;
    bool vsync = false;
    void set_vsync(bool state);
} GameSettings_;
std::string gamesettings_get_fileconfig();

void gamesettings_load_config(GameSettings_ *GameSettings);

#endif
