#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/input_basic.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main() {
    printf("Hello, Sailor!\n");
    glfwInit();
    opengl_context_init();

    // TODO: Resolution values should be in a seperate struct
    GLFWwindow* window = glfwCreateWindow(800, 600, "RCraft", NULL, NULL);
    glfwMakeContextCurrent(window);
    opengl_glad_load();

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSwapInterval(1); // vsync

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.7f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (Input.is_key_pressed(GLFW_KEY_ESCAPE)) {
            break;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwTerminate();
    printf("Goodbye, Sailor!\n");
    return 0;
}
