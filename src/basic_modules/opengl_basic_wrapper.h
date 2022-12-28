#ifndef opengl_basic_wrapper_h
#define opengl_basic_wrapper_h

#include "basic_types.h"
#include "../../includes/glad/glad.h"
#include "../../includes/glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "filesystem_basic.h"
#include "stb_image.h"



// Initialization
void opengl_context_init();
void opengl_glad_load();
void opengl_print_error();
void window_validate(GLFWwindow *window);

// BUFFERS
typedef struct VBO {
    u32 ID;
    VBO();
    VBO(const void *data, GLsizeiptr size);
    void bind();
    void update_vertex_buffer(const void *data, GLsizeiptr size); // maybe we can just use size_t
    void unbind();
} VBO;

typedef struct VAO {
    u32 ID;
    VAO();
    void attribute(u32 index, s32 size, GLenum type, u32 stride, u32 offset);
    void bind();
    void unbind();
} VAO;

typedef struct EBO {
    u32 ID;
    EBO();
    EBO(const void *data, GLsizeiptr size);
    void update_element_buffer(const void *data, GLsizeiptr size);
    void bind();
    void unbind();
} EBO;

// SHADERS
typedef u32 VertexShaderID;
typedef u32 FragmentShaderID;
typedef u32 ProgramShaderID;

typedef struct Shader{ // @TODO Add uniform functions.
    u32 ID;
    Shader(const char* vertexSource, const char* fragmentSource);
    void use();
    void set1Float(const char* name, float value);
    void set3Float(const char* name, Floats3 vector);
    void set4Float(const char* name, Floats4 vector);
    
} Shader;

void shaders_vertex_compile(VertexShaderID vertexShader, const char* vertexShaderSource);
void shaders_vertex_compile(VertexShaderID vertexShader, std::string vertexShaderSource);
void shaders_fragment_compile(FragmentShaderID fragmentShader, const char* fragmentShaderSource);
void shaders_fragment_compile(FragmentShaderID fragmentShader, std::string fragmentShaderSource);
void shaders_program_link(ProgramShaderID shaderProgram, VertexShaderID vertexShader, FragmentShaderID fragmentShader);

void shaders_uniform_m4(u32 matrix_shader_location, glm::mat4 matrix_data);

#endif
