#ifndef gamesettings_h
#define gamesettings_h

#include "basic_modules/rcf_basic.h"


typedef struct GameSettings_ {
    int resolution_x, resolution_y;
} GameSettings_;
std::string gamesettings_get_fileconfig();

void gamesettings_load_config(GameSettings_ *GameSettings);

#endif
