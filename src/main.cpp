#include "stuff.h"
#include "../includes/glfw/glfw3.h"

int main() {
    printf("Hello, Sailor!\n");
    print_stuff();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwTerminate();
    return 0;
}
