 

#include "opengl_basic_wrapper.h"


Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    ID = glCreateProgram();
    u32 vertexShader, fragmentShader;
    vertexShader   = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    shaders_vertex_compile(vertexShader, vertexSource);
    shaders_fragment_compile(fragmentShader, fragmentSource);
    shaders_program_link(ID, vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
void Shader::use() {
    glUseProgram(ID);
}

void Shader::set4MatUniform(const char* name, glm::mat4 value) {
    int uniformLocation = glGetUniformLocation(ID, name);
    glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(value));
}


void shaders_vertex_compile(u32 vertexShader, const char* VertexShaderSource) {
    const char* vertexSource = VertexShaderSource;
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infolog);
    }
    else printf("Vertex Shader compiled successfuly.\n");
}

void shaders_fragment_compile(u32 fragmentShader, const char* fragmentShaderSource) {
    const char* fragSource = fragmentShaderSource;
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infolog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infolog);
    }
    else printf("Fragment Shader compiled successfuly.\n");
}
    
void shaders_program_link(u32 shaderProgram, u32 vertexShader, u32 fragmentShader) {
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    int success;
    char infolog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        printf("Failed to link shaders.\n");
    }
    else printf("Program Shader linked successfuly.\n");
}

void shaders_uniform_m4(u32 matrix_shader_location, glm::mat4 matrix_data) {
    glUniformMatrix4fv(matrix_shader_location, 1, GL_FALSE, glm::value_ptr(matrix_data));
}
