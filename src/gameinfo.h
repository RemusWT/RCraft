#ifndef gameinfo_h
#define gameinfo_h

#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/rcf_basic.h"



// TODO: GInfo global singleton. Useful so we can access the game's info from anywhere. Think more about it.
typedef struct GameInfo {
    int resolution_x, resolution_y;

    GLFWwindow* window;
    GameInfo();
    
    bool vsync = false;
    void set_vsync(bool state);
    void set_viewport(int res_x, int res_y);
    void load_config();
    void hide_cursor();
    void show_cursor();

    
} GameInfo;

std::string gameinfo_get_fileconfig(); // Should change it to gameinfo_get_settings or smth


#endif
