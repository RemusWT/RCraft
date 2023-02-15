#ifndef render_manager_h

#define render_manager_h
#include "render_internals.h"
#include "../gameinfo.h"


typedef struct RenderManager {
    Shader *CubeShader;
    u32 VAO, VBO, EBO;

    // Collected block data for batch render
    std::vector<float> vertex_data;
    
    // Vertex data to instantiate
    std::vector<float> cube_model_vertex_data;
    
    // Project matrix for the glsl uniform
    glm::mat4 proj_matrix;

    RenderManager(GameInfo &GInfo);
    void add_block_to_render(glm::vec3 block_pos);
    void render_blocks();
    void clear_vertex_data();


    void render_camera();
} RenderManager;

#endif
