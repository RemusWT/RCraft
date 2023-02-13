#include "render/opengl_basic_wrapper.h"
#include "input_basic.h"
#include "utils/rcf_basic.h"
#include "gameinfo.h"
#include "render/render_internals.h"
#include "camera.h"
#include "clock.h"
#include "font_rendering/font_rendering.h"
#include "utils/debug.h"
#include "render/render_manager.h"

// @Bug There is a major problem between Release mode and Debug mode in VS.
// It needs to be resolved at some point. Debug mode compiles and runs just fine.
// Release mode compiles ok but there are problems. Nothing renderings. The shaders don't compile.

// @TODO Write documentation for our modules.


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// void cursor_callback(GLFWwindow* window, double xpos, double ypos) { //@Refactor should be moved somewhere else
// }




int main() {
    printf("Hello, Sailor!\n");

    glfwInit();
    opengl_context_init();
    
    GameInfo GInfo;
    GInfo.load_config();

    std::string loaded_text_vertex_source   = file_get_contents("../../asset/shaders/text_vert.glsl");
    std::string loaded_text_fragment_source = file_get_contents("../../asset/shaders/text_frag.glsl");
    Shader textShader(loaded_text_vertex_source.c_str(), loaded_text_fragment_source.c_str());

    textShader.use();
    // These should be moved somewhere else entirely
    glm::mat4 text_proj = glm::ortho(0.0f, static_cast<float>(GInfo.resolution_x), 0.0f, static_cast<float>(GInfo.resolution_y));
    glUniformMatrix4fv(glGetUniformLocation(textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(text_proj));


    // For now this is fine, but we should create a system of sorts for containing multiple textures, even if we will have a texture atlas.
    Texture cube_texture("../../asset/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE); // @TODO @Robustness maybe we should have a find asset folder functin or something. Cause otherwise we will have to edit a lot of textures in the future

    Camera PlayerCamera(&GInfo);
    

    glfwSetFramebufferSizeCallback(GInfo.window, framebuffer_size_callback); // maybe move them somewhere else
    glfwSetKeyCallback(GInfo.window, key_callback);


    // Manually set to experiment.
    GInfo.hide_cursor();
    GInfo.set_vsync(false);


    RenderManager RManager(GInfo);
    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 300; j++) {
            RManager.add_block_to_render(glm::vec3((float)(i), 0.0f, (float)(j)));
        }
    }


    Font Alagard("../../asset/fonts/alagard.ttf", &textShader); GL_CHECK_ERROR
    Font Coolvetica("../../asset/fonts/coolvetica.otf", &textShader);

    Clock GameClock;
    FPSCounter FPS;
    while (!glfwWindowShouldClose(GInfo.window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        if (Input.is_key_pressed(GLFW_KEY_ESCAPE)) { // should create a function for basic functionality.
            break;
        }

        PlayerCamera.freelook(*RManager.CubeShader);
        PlayerCamera.process_input(GameClock.deltatime); 

        //VAO_.bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cube_texture.ID);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        RManager.render_blocks();

        Alagard.render_text("Hello Sailor!", glm::vec2(20.0f, 20.0f), 32, glm::vec3(0.2f, 0.2f, 0.8f));
        
        FPS.update();
        show_debug_info(Coolvetica, GInfo, PlayerCamera, FPS);




        glfwPollEvents();
        GameClock.update();
        glfwSwapBuffers(GInfo.window); GL_CHECK_ERROR
    }

    
    glfwTerminate();
    printf("Goodbye, Sailor!\n");
    return 0;
}

