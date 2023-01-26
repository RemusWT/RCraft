#include "render/opengl_basic_wrapper.h"
#include "input_basic.h"
#include "utils/rcf_basic.h"
#include "gameinfo.h"
#include "render/render_internals.h"
#include "camera.h"
#include "clock.h"
#include "font_rendering/font_rendering.h"
//#include "font_rendering/font_rendering.h"

// @Bug There is a major problem between Release mode and Debug mode in VS.
// It needs to be resolved at some point. Debug mode compiles and runs just fine.
// Release mode compiles ok but there are problems. Nothing renderings. The shaders don't compile.

// @TODO Write documentation for our modules.


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// void cursor_callback(GLFWwindow* window, double xpos, double ypos) { //@Refactor should be moved somewhere else
// }


std::map<char, Glyph> Glyphs;


int main() {
    printf("Hello, Sailor!\n");

    glfwInit();
    opengl_context_init();
    
    GameInfo GInfo;
    GInfo.load_config();

    std::string loaded_vertex_source        = file_get_contents("../../asset/shaders/vertex.glsl");
    std::string loaded_fragment_source      = file_get_contents("../../asset/shaders/frag.glsl");
    std::string loaded_text_vertex_source   = file_get_contents("../../asset/shaders/text_vert.glsl");
    std::string loaded_text_fragment_source = file_get_contents("../../asset/shaders/text_frag.glsl");

    Shader defaultShader(loaded_vertex_source.c_str(), loaded_fragment_source.c_str());
    defaultShader.use();
    Shader textShader(loaded_text_vertex_source.c_str(), loaded_text_fragment_source.c_str());
    textShader.use();
    glm::mat4 text_proj = glm::ortho(0.0f, static_cast<float>(GInfo.resolution_x), 0.0f, static_cast<float>(GInfo.resolution_y));
    glUniformMatrix4fv(glGetUniformLocation(textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(text_proj));
    
    // Font rendering experimenting
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        printf("Freetype error: Could not init FreeType Library.\n");
        return -1;
    }
    FT_Face face;
    ft_load_ttf(ft, "../../asset/fonts/alagard.ttf", &face);

    ft_face_set_size(face, 0, 24);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (u8 c = 0; c < 128; c++) {
        if (ft_face_load_character(face, c)) continue;
        Glyph c_glyph = ft_face_create_glyph(face);
        Glyphs.insert(std::pair<char, Glyph>(c, c_glyph));
    }

    ft_free_face(face);
    ft_free_freetype(ft);


    Text sample_text;
    sample_text.x = 20.0f;
    sample_text.y = 20.0f;



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

    Texture cube_texture("../../asset/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE); // @Robustness maybe we should have a find asset folder functin or something. Cause otherwise we will have to edit a lot of textures in the future

    Camera PlayerCamera(&GInfo);
    
    glm::mat4 model_matrix = glm::mat4(1.0f);
    glm::mat4 proj_matrix  = glm::mat4(1.0f);
    
    proj_matrix = glm::perspective(glm::radians(70.0f),((float)GInfo.resolution_x/(float)GInfo.resolution_y), 0.1f, 100.0f);
    
    defaultShader.use();
    defaultShader.set4MatUniform("model_matrix", model_matrix);
    defaultShader.set4MatUniform("view_matrix",  PlayerCamera.view_matrix);
    defaultShader.set4MatUniform("proj_matrix",  proj_matrix);
    
    glfwSetFramebufferSizeCallback(GInfo.window, framebuffer_size_callback); // maybe move them somewhere else
    glfwSetKeyCallback(GInfo.window, key_callback);

    glEnable(GL_DEPTH_TEST);
    Clock GameClock;
    GInfo.hide_cursor();



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glfwSetCursorPosCallback(GInfo.window, cursor_callback);

    while (!glfwWindowShouldClose(GInfo.window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (Input.is_key_pressed(GLFW_KEY_ESCAPE)) { // should create a function for basic functionality.
            break;
        }
        defaultShader.use();
        PlayerCamera.freelook(defaultShader); GL_CHECK_ERROR
        PlayerCamera.process_input(GameClock.deltatime); GL_CHECK_ERROR

        // VAO_.bind();
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, cube_texture.ID);
        // glDrawArrays(GL_TRIANGLES, 0, 36); GL_CHECK_ERROR
        
        sample_text.render_text(textShader, Glyphs, glm::vec3(0.5, 0.8f, 0.2f));
        
        glfwSwapBuffers(GInfo.window);
        glfwPollEvents();
        GameClock.update();
    }

    
    glfwTerminate();
    printf("Goodbye, Sailor!\n");
    return 0;
}

