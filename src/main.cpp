#include "basic_modules/opengl_basic_wrapper.h"
#include "basic_modules/input_basic.h"
#include "basic_modules/rcf_basic.h"
#include "gameinfo.h"
#include "render/render_internals.h"
#include "camera.h"
#include "clock.h"


// @Bug There is a major problem between Release mode and Debug mode in VS.
// It needs to be resolved at some point. Debug mode compiles and runs just fine.
// Release mode compiles ok but there are problems. Nothing renderings. The shaders don't compile.


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos) { //@Refactor should be moved somewhere else
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
    
    Texture cube_texture("../../../asset/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE); // @Robustness maybe we should have a find asset folder functin or something. Cause otherwise we will have to edit a lot of textures in the future

    Camera PlayerCamera(&GInfo);
    
    glm::mat4 model_matrix = glm::mat4(1.0f);
    glm::mat4 proj_matrix  = glm::mat4(1.0f);
    
    proj_matrix = glm::perspective(glm::radians(70.0f),((float)GInfo.resolution_x/(float)GInfo.resolution_y), 0.1f, 100.0f);
    
    defaultShader.set4MatUniform("model_matrix", model_matrix);
    defaultShader.set4MatUniform("view_matrix",  PlayerCamera.view_matrix);
    defaultShader.set4MatUniform("proj_matrix",  proj_matrix);
    
    glfwSetFramebufferSizeCallback(GInfo.window, framebuffer_size_callback); // maybe move them somewhere else
    glfwSetKeyCallback(GInfo.window, key_callback);

    glEnable(GL_DEPTH_TEST);
    Clock GameClock;
    GInfo.hide_cursor();

    glfwSetCursorPosCallback(GInfo.window, cursor_callback);
    
    while (!glfwWindowShouldClose(GInfo.window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (Input.is_key_pressed(GLFW_KEY_ESCAPE)) { // should create a function for basic functionality.
            break;
        }
        
        PlayerCamera.freelook(defaultShader);
        PlayerCamera.process_input(GameClock.deltatime);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        opengl_check_error("While loop");
        
        
        glfwSwapBuffers(GInfo.window);
        glfwPollEvents();
        GameClock.update();
    }

    
    glfwTerminate();
    printf("Goodbye, Sailor!\n");
    return 0;
}
