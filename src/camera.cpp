#include "camera.h"

void Camera::freelook(Shader current_shader) { // not to be confused with look_at. we only look what is in front of the camera.
    view_matrix = glm::lookAt(position, position + front, up);
    current_shader.set4MatUniform("view_matrix", view_matrix);
}

void Camera::process_input(double deltatime) {
    velocity = movespeed * deltatime;
    // @Bug after holding a button it will stop. That's because the key is not pressed anymore but HELD.
    if (Input.is_key_pressed(GLFW_KEY_D)) {
        position.x += velocity;
    }
    if (Input.is_key_pressed(GLFW_KEY_A)) {
        position.x -= velocity;
    }
    if (Input.is_key_pressed(GLFW_KEY_S)) {
        position.z += velocity;
    }
    if (Input.is_key_pressed(GLFW_KEY_W)) {
        position.z -= velocity;
    }
}
