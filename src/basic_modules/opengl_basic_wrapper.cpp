#include "opengl_basic_wrapper.h"

void opengl_context_init() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void opengl_glad_load() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD.\n");
    }
}

void window_validate(GLFWwindow *window) {
    if (window == NULL) {
         printf("Failed to create GLFW window.\n"); 
         glfwTerminate();
    }
}

void opengl_print_error() {
    GLenum error = glGetError();
    switch (error) {
    case GL_NO_ERROR:
        break;
    case GL_INVALID_ENUM:
        printf("GL_INVALID_ENUM detected! Enumeration parameter is not legal.\n");
        break;
    case GL_INVALID_VALUE:
        printf("GL_INVALID_VALUE detected! Value parameter is not legal.\n");
        break;
    case GL_INVALID_OPERATION:
        printf("GL_INVALID_OPERATION detected! State for a command is not legal for its given parameters.\n");
        break;
    case GL_STACK_OVERFLOW:
        printf("GL_STACK_OVERFLOW detected! A stack pushing operation causes a stack overflow.\n");
        break;
    case GL_STACK_UNDERFLOW:
        printf("GL_STACK_UNDERFLOW detected! A stack popping operation occured while the stack was at its lowest point.\n");
        break;
    case GL_OUT_OF_MEMORY:
        printf("GL_OUT_OF_MEMORY detected! A memory allocation couldn't allocate (enough) memory.\n");
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        printf("GL_INVALID_FRAMEBUFFER_OPERATION detected! A reading or a writing operation occured to a framebuffer that is not complete.\n");
        break;
    }
}



VBO::VBO() {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
VBO::VBO(const void *data, GLsizeiptr size) { // @TODO specify the GL Draw method.
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void VBO::update_vertex_buffer(const void *data, GLsizeiptr size) {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VAO::VAO() {
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
}
void VAO::attribute(u32 index, s32 size, GLenum type, u32 stride, u32 offset) {
    glBindVertexArray(ID);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride * sizeof(type), (void*)(offset * sizeof(type)));
    glEnableVertexAttribArray(index);
    
}
void VAO::bind() {
    glBindVertexArray(ID);
}
void VAO::unbind() {
    glBindVertexArray(0);
}


EBO::EBO() {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
EBO::EBO(const void *data, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void EBO::update_element_buffer(const void *data, GLsizeiptr size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}


