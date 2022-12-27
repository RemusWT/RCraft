#include "input_basic.h"

bool KeyInfo::is_key_pressed(int key) {
    if (keys[key].key == key) {
        if (keys[key].action == GLFW_PRESS) {
            return true;
        }
    } return false;
}
bool KeyInfo::is_key_released(int key) {
    if (keys[key].key == key) {
        if (keys[key].action == GLFW_RELEASE) {
            return true;
        }
    } return false;
}

KeyInfo Input;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Input.keys[key].key      = key;
    Input.keys[key].scancode = scancode;
    Input.keys[key].action   = action;
    Input.keys[key].mods     = mods;
}
