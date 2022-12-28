#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/input_basic.h"
#include "basic_modules/rcf_basic.h"
#include "gamesettings.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


int main() {
    printf("Hello, Sailor!\n");

    
    GameSettings_ GameSettings;
    std::string gamesettings_string = gamesettings_get_fileconfig();
    GameSettings.resolution_x = rcf_fetch_ivalue(gamesettings_string, "resolution_x");
    GameSettings.resolution_y = rcf_fetch_ivalue(gamesettings_string, "resolution_y");
    
    glfwInit();
    opengl_context_init();

    // TODO: Resolution values should be in a seperate struct
    GLFWwindow* window = glfwCreateWindow(GameSettings.resolution_x, GameSettings.resolution_y, "RCraft", NULL, NULL);
    glfwMakeContextCurrent(window);
    opengl_glad_load();

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSwapInterval(1); // vsync

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.7f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (Input.is_key_pressed(GLFW_KEY_ESCAPE)) { // should create a function for basic functionality.
            break;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwTerminate();
    printf("Goodbye, Sailor!\n");
    return 0;
}
