#include "camera.h"

Camera::Camera(GameInfo *gameinfo) {
    ginfo = gameinfo;
}

void Camera::freelook(Shader &current_shader) { // not to be confused with look_at. we only look what is in front of the camera.
    current_shader.use();GL_CHECK_ERROR
    view_matrix = glm::lookAt(position, position + front, up);
    current_shader.set4MatUniform("view_matrix", view_matrix);
}

void Camera::process_input(double deltatime) {
    float speed = movespeed * deltatime; // should create a variable in struct scope so we dont alloc each time?
    glm::vec3 direction = glm::vec3(0.0f);

    // Player movement relative to camera's orientation. I don't fully understand my own implementation, but it works.
    // Current implementation allows the player to move on the y axis based on the direction it's currently looking.
    // Future gameplay will not consist this. Freeflight will also NOT use this. Only exception might be for noclip mode
    // but only if we actually will need a noclip mode for whatever reason.

    if (Input.is_key_pressed(GLFW_KEY_D)) {
        direction.x += 1;
    }
    if (Input.is_key_pressed(GLFW_KEY_A)) {
        direction.x -= 1;
    }
    if (Input.is_key_pressed(GLFW_KEY_S)) {
        direction.z -= 1;
    }
    if (Input.is_key_pressed(GLFW_KEY_W)) {
        direction.z += 1;
    }
    if (Input.is_key_pressed(GLFW_KEY_LEFT_SHIFT)) {
        direction.y -= 1;
    }
    if (Input.is_key_pressed(GLFW_KEY_SPACE)) {
        direction.y += 1;
    }

    float length = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
    if (length != 0.0f) direction = glm::normalize(direction);

    position   += direction.x * glm::normalize(glm::cross(front, up)) * speed;
    position   += direction.z * front * speed;

    if (direction.y > 0) position.y += speed; // this looks odd bcs its an exception, we don't change the y value relative to the camera.
    else if (direction.y < 0) position.y -= speed;
    if (Input.is_key_pressed(GLFW_KEY_LEFT_ALT)) { // @Bug toggling movespeed sometimes doesn't work.
        if (moving_fast) {movespeed = 2.0f; moving_fast = false;}
        else {movespeed = 10.0f; moving_fast = true;}
        printf("Moving fast: %i\n", moving_fast);
    }

    
    // Camera rotation relative to mouse input.
    // Current implementation is from learnopengl.com camera section.
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
