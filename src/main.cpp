#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/input_basic.h"
#include "basic_modules/rcf_basic.h"
#include "gameinfo.h"
#include "render/render_internals.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


int main() {
    printf("Hello, Sailor!\n");
    glfwInit();
    opengl_context_init();
    
    GameInfo GInfo;
    GInfo.load_config();
    std::string loaded_vertex_source = file_get_contents("vertex.glsl");
    std::string loaded_fragment_source = file_get_contents("fragment.glsl");
    Shader defaultShader(loaded_vertex_source.c_str(), loaded_fragment_source.c_str());
    defaultShader.use();
    
    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    VAO VAO_;
    VBO VBO_(vertices.data(), vertices.size() * sizeof(float));
    
    VAO_.attribute(0, 3, GL_FLOAT, 5, 0);
    VAO_.attribute(1, 2, GL_FLOAT, 5, 3);
    Texture cube_texture("../../../asset/cube_texture.png");
    cube_texture.textureFiltering(GL_REPEAT);
    opengl_print_error();
    
    glfwSetFramebufferSizeCallback(GInfo.window, framebuffer_size_callback);
    glfwSetKeyCallback(GInfo.window, key_callback);

    while (!glfwWindowShouldClose(GInfo.window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (Input.is_key_pressed(GLFW_KEY_ESCAPE)) { // should create a function for basic functionality.
            break;
        }
        glDrawArrays(GL_TRIANGLES, 0, 6);
        opengl_print_error();
        
        glfwSwapBuffers(GInfo.window);
        glfwPollEvents();
    }

    
    glfwTerminate();
    printf("Goodbye, Sailor!\n");
    return 0;
}
