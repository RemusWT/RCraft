#ifndef gameinfo_h
#define gameinfo_h

#include "render/opengl_basic_wrapper.h"
#include "utils/rcf_basic.h"



// TODO: GInfo global singleton. Useful so we can access the game's info from anywhere. Think more about it.
// We will also need to have gamestate. hide_cursor and show_cursor are functions that will be used in different types of gamestates.
// What I mean by gamestates is a different logic to how things interact with each other, different menus perhaps.
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

typedef struct DiagInfo {
    std::map<std::string, std::string> Diagnoses;

    void add_diagnose(std::string diag_key,);
} DiagInfo;




std::string gameinfo_get_fileconfig(); // Should change it to gameinfo_get_settings or smth




#endif
