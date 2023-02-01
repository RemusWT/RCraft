
#ifndef camera_h
#define camera_h
#include "render/opengl_basic_wrapper.h"
#include "input_basic.h"
#include "gameinfo.h"

typedef struct Camera {
    GameInfo *ginfo; // We keep a copy of GameInfo singleton so we can pull information within our member functions.
    Camera(GameInfo *gameinfo); // Mainly to initialize the ginfo variable
    void change_ginfo(GameInfo *gameinfo);

    // Consider it private
    glm::mat4 view_matrix = glm::mat4(1.0f);
    
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front    = glm::vec3(0.0f, 0.0f, -1.0f);
    
    bool moving_fast = false;
    float movespeed = 0.5f;
    Vector3 velocity;
    void freelook(Shader &current_shader);
    void process_input(double deltatime);
    
    // Consider it private. Variables for in-game camera movement relative to mouse input.
    Vector2 mouse_position;
    bool first_mouse = true;
    float yaw = -90.0f;
    float pitch = 0.0f;
    
} Camera;

#endif

