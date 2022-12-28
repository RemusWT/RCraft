#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertex_color;

void main() {
    gl_Position = vec4(aPos, 1.0f);
    vertex_color = vec4(0.4f, 0.1f, 0.0f, 1.0f);
}
