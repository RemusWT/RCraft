#include "camera.h"

Camera::Camera(GameInfo *gameinfo) {
    ginfo = gameinfo;
}

void Camera::freelook(Shader current_shader) { // not to be confused with look_at. we only look what is in front of the camera.
    view_matrix = glm::lookAt(position, position + front, up);
    current_shader.set4MatUniform("view_matrix", view_matrix);
}

void Camera::process_input(double deltatime) {
    float speed = movespeed * deltatime; // should create a variable in struct scope so we dont alloc each time?

    // @Bug We are moving faster diagonaly.
    if (Input.is_key_pressed(GLFW_KEY_D)) {
        position += glm::normalize(glm::cross(front, up)) * speed;
    }
    if (Input.is_key_pressed(GLFW_KEY_A)) {
        position -= glm::normalize(glm::cross(front, up)) * speed;
    }
    if (Input.is_key_pressed(GLFW_KEY_S)) {
        position -= speed * front;
    }
    if (Input.is_key_pressed(GLFW_KEY_W)) {
        position += speed * front;
    }
    if (Input.is_key_pressed(GLFW_KEY_LEFT_SHIFT)) {
        position.y -= speed;
    }
    if (Input.is_key_pressed(GLFW_KEY_SPACE)) {
        position.y += speed;
    }

    if (Input.is_key_pressed(GLFW_KEY_LEFT_ALT)) { // @Bug toggling movespeed sometimes doesn't work.
        if (moving_fast) {movespeed = 0.5f; moving_fast = false;}
        else {movespeed = 1.0f; moving_fast = true;}
        printf("Moving fast: %i\n", moving_fast);
    }

    
    double mouse_current_x, mouse_current_y;
    glfwGetCursorPos(ginfo->window, &mouse_current_x, &mouse_current_y);
    if (first_mouse) {
        mouse_position.x = mouse_current_x;
        mouse_position.y = mouse_current_y;
        first_mouse = false;
    }
    float xoffset = mouse_current_x  - mouse_position.x;
    float yoffset = mouse_position.y - mouse_current_y;

    mouse_position.x = mouse_current_x;
    mouse_position.y = mouse_current_y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw   += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f)  pitch =  89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 new_front;
    new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    new_front.y = sin(glm::radians(pitch));
    new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(new_front);
    
}

void Camera::change_ginfo(GameInfo *gameinfo) {
    ginfo = gameinfo;
}
