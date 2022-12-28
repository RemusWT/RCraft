#ifndef gameinfo_h
#define gameinfo_h

#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/rcf_basic.h"


typedef struct GameInfo {
    int resolution_x, resolution_y;
    int viewport_x, viewport_y;
    GLFWwindow* window;
    bool vsync = false;
    void set_vsync(bool state);
    void window_init();
    void set_viewport(int res_x, int res_y);
} GameInfo;

std::string gameinfo_get_fileconfig(); // Should change it to gameinfo_get_settings or smth

void gameinfo_load_config(GameInfo *GameSettings);

#endif
