#ifndef render_manager_h

#define render_manager_h
#include "render_internals.h"
#include "../gameinfo.h"
#include "../chunk_manager.h"



// RenderManager is responsible for managing all renderable objects in the world.
// currently, RM can be used by adding a single block to render.
// @TODO To be implemented an option to add a whole chunk to render.

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
    void add_chunk_to_render(Chunk &chunk);


    void render_camera();
} RenderManager;

#endif
