
#ifndef camera_h
#define camera_h
#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/input_basic.h"

typedef struct Camera {
    glm::mat4 view_matrix = glm::mat4(1.0f);
    

    Vector3 position = {0.0f, 0.0f, 0.0f};
    Vector3 up       = {0.0f, 1.0f, 0.0f};
    Vector3 front    = {0.0f, 0.0f, -1.0f};
    float movespeed = 1.0f;
    Vector3 velocity;
    void freelook(Shader current_shader);
    void process_input(double deltatime);
} Camera;

#endif

