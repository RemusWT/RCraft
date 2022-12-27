#include "engine.h"

void window_validate(GLFWwindow *window) {
    if (window == NULL) {
         printf("Failed to create GLFW window.\n"); 
         glfwTerminate();
    }
}
