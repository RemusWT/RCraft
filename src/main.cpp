#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/input_basic.h"
#include "basic_modules/rcf_basic.h"
#include "gamesettings.h"
#include "render/render_internals.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


int main() {
    printf("Hello, Sailor!\n");
    
    GameSettings_ GameSettings;
    gamesettings_load_config(&GameSettings);
    glfwInit();
    opengl_context_init();


    GLFWwindow* window = glfwCreateWindow(GameSettings.resolution_x, GameSettings.resolution_y, "RCraft", NULL, NULL);
    glfwMakeContextCurrent(window);
    opengl_glad_load();

    Shader defaultShader(defaultVertexSource.c_str(), defaultFragmentSource.c_str());
    defaultShader.use();
    
    std::vector<float> triangle_vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    VAO VAO_;
    VBO VBO_(&triangle_vertices[0], triangle_vertices.size() * sizeof(float));
    
    VAO_.attribute(0, 3, GL_FLOAT, 3, 0);
    opengl_print_error();
    
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    GameSettings.set_vsync(true);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (Input.is_key_pressed(GLFW_KEY_ESCAPE)) { // should create a function for basic functionality.
            break;
        }
        glDrawArrays(GL_TRIANGLES, 0, 3);
        opengl_print_error();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwTerminate();
    printf("Goodbye, Sailor!\n");
    return 0;
}
