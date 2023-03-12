#include "render_manager.h"

RenderManager::RenderManager(GameInfo &GInfo) {
    cube_model_vertex_data = {
            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right 
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
                         
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
                           
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
                    
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
                    
            // Left face
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left 
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
            
            // Right face
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
                      
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-lefta
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
            
            // Bottom face          
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
                    
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
            
            // Top face
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
                            
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f // bottom-left  
                          
    };
    vertex_data.reserve(1000); // This number should be relative to render distance
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), cube_model_vertex_data.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float))); 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    std::string loaded_vertex_source        = file_get_contents("../../asset/shaders/vertex.glsl");
    std::string loaded_fragment_source      = file_get_contents("../../asset/shaders/frag.glsl");
    CubeShader = new Shader(loaded_vertex_source.c_str(), loaded_fragment_source.c_str());

    proj_matrix = glm::perspective(glm::radians(70.0f),((float)GInfo.resolution_x/(float)GInfo.resolution_y), 0.1f, 100.0f);
    CubeShader->use();
    CubeShader->set4MatUniform("proj_matrix", proj_matrix);
    

}

void RenderManager::add_block_to_render(glm::vec3 block_pos) {
    std::vector<float> temp_vertex_data = cube_model_vertex_data;
    for (int i=0; i < 180; i += 5) {
        for (int j=0; j < 3; j++) {
            switch (j) {
                case 0:
                temp_vertex_data[i+j] += block_pos.x;
                break;
                case 1:
                temp_vertex_data[i+j] += block_pos.y;
                break;
                case 2:
                temp_vertex_data[i+j] += block_pos.z;
                break;
            }
        }
    }
    vertex_data.insert(vertex_data.end(), temp_vertex_data.begin(), temp_vertex_data.end());
}

void RenderManager::add_chunk_to_render(Chunk &chunk)  {
    for (int i=0; i < static_cast<int>(chunk.Blocks.size()); i++) {
        glm::vec3 relative_to_chunk_pos = chunk.Blocks[i].position;
        relative_to_chunk_pos.x += chunk.position.x;
        relative_to_chunk_pos.z += chunk.position.y;
        add_block_to_render(relative_to_chunk_pos); // technically this should be called correctly.
    }
}

void RenderManager::render_blocks() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), &vertex_data[0], GL_DYNAMIC_DRAW);GL_CHECK_ERROR
    glDrawArrays(GL_TRIANGLES, 0, vertex_data.size());GL_CHECK_ERROR
}

void RenderManager::clear_vertex_data() {
    vertex_data.clear();
}
