
#ifndef camera_h
#define camera_h
#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/input_basic.h"

typedef struct Camera {
    glm::mat4 view_matrix = glm::mat4(1.0f);
    
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front    = glm::vec3(0.0f, 0.0f, -1.0f);
    bool moving_fast = false;
    float movespeed = 0.5f;
    Vector3 velocity;
    void freelook(Shader current_shader);
    void process_input(double deltatime);
} Camera;

#endif

