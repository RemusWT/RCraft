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
#include "chunk_manager.h"

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
    

    // For now this is fine, but we should create a system of sorts for containing multiple textures, even if we will have a texture atlas.
    Texture cube_texture("../../asset/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE); // @TODO @Robustness maybe we should have a find asset folder functin or something. Cause otherwise we will have to edit a lot of textures in the future

    
    

    glfwSetFramebufferSizeCallback(GInfo.window, framebuffer_size_callback); // maybe move them somewhere else
    glfwSetKeyCallback(GInfo.window, key_callback);


    // Manually set to experiment.
    GInfo.hide_cursor();
    GInfo.set_vsync(false);

    Block Test_Block;
    Test_Block.type = 1;
    Test_Block.position = glm::vec3(0.0f, 1.0f, 0.0f);
    
    Chunk Test_Chunk;
    Test_Chunk.position.x = 0;
    Test_Chunk.position.y = 0;
    Test_Chunk.add_block(Test_Block);
    
    ChunkManager CManager;
    CManager.load_chunk(Test_Chunk);

    RenderManager RManager(GInfo);
    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            for (int y = 0; y < 256; y++) {
                Block blocky;
                blocky.type = 1;
                blocky.position = glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                Test_Chunk.add_block(blocky);                
            }
        }
    }
    RManager.add_chunk_to_render(Test_Chunk);

    TextManager TextManager(GInfo);
    TextManager.set_font("Coolvetica");
    Camera PlayerCamera(&GInfo, RManager.CubeShader);
    

    Clock GameClock;
    FPSCounter FPS;
    while (!glfwWindowShouldClose(GInfo.window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        if (Input.is_key_pressed(GLFW_KEY_ESCAPE)) { // should create a function for basic functionality.
            break;
        }

        PlayerCamera.freelook();
        PlayerCamera.process_input(GameClock.deltatime);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cube_texture.ID);
        RManager.render_blocks();


        TextManager.render("Hello, there!", glm::vec2(20.0f, 20.0f), 24);

        
        FPS.update();
        show_debug_info(TextManager, GInfo, PlayerCamera, FPS);


        glfwPollEvents();
        GameClock.update();
        glfwSwapBuffers(GInfo.window); GL_CHECK_ERROR
    }

    
    glfwTerminate();
    printf("Goodbye, Sailor!\n");
    return 0;
}

