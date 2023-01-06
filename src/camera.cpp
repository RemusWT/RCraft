#include "camera.h"

void Camera::freelook(Shader current_shader) { // not to be confused with look_at. we only look what is in front of the camera.
    view_matrix = glm::lookAt(position, vector3_glm(position + front), up);
    current_shader.set4MatUniform("view_matrix", view_matrix);
}

void Camera::process_input(double deltatime) {
    float speed; // should create a variable in struct scope so we dont alloc each time?
    velocity = vector3_zero();
    
    if (Input.is_key_pressed(GLFW_KEY_D)) {
        velocity.x += 1.0f;
    }
    if (Input.is_key_pressed(GLFW_KEY_A)) {
        velocity.x += -1.0f;
    }
    if (Input.is_key_pressed(GLFW_KEY_S)) {
        velocity.z += 1.0f;
    }
    if (Input.is_key_pressed(GLFW_KEY_W)) {
        velocity.z += -1.0f;
    }
    if (Input.is_key_pressed(GLFW_KEY_LEFT_SHIFT)) {
        velocity.y += -1.0f;
    }
    if (Input.is_key_pressed(GLFW_KEY_SPACE)) {
        velocity.y += 1.0f;
    }
    if (Input.is_key_pressed(GLFW_KEY_LEFT_ALT)) {
        speed = (movespeed/2) * deltatime;
    } else speed = movespeed * deltatime;

    printf("Velocity before normalize: %f %f %f\n", velocity.x, velocity.y, velocity.z);
    velocity = vector3_normalize(velocity);
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
    position.z += velocity.z * speed;
    printf("Velocity: %f %f %f\n", velocity.x, velocity.y, velocity.z);
    
}
