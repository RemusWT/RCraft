#ifndef input_basic_h

#define input_basic_h
#include "basic_types.h"
#include "opengl_basic_wrapper.h"
// NOTE: When we are making themes for Emendo make sure to make one dedicated for Sonar Systems.

const int KEY_F1 = GLFW_KEY_F1;
const int KEY_F2 = GLFW_KEY_F2;
const int KEY_F3 = GLFW_KEY_F3;
const int KEY_F4 = GLFW_KEY_F4;
const int KEY_F5 = GLFW_KEY_F5;
const int KEY_F6 = GLFW_KEY_F6;
const int KEY_F7 = GLFW_KEY_F7;
const int KEY_F8 = GLFW_KEY_F8;
const int KEY_F9 = GLFW_KEY_F9;
const int KEY_F10 = GLFW_KEY_F10;
const int KEY_F11 = GLFW_KEY_F11;
const int KEY_F12 = GLFW_KEY_F12;

const int KEY_A = GLFW_KEY_A;
const int KEY_B = GLFW_KEY_B;
const int KEY_C = GLFW_KEY_C;
const int KEY_D = GLFW_KEY_D;
const int KEY_E = GLFW_KEY_E;
const int KEY_F = GLFW_KEY_F;
const int KEY_G = GLFW_KEY_G;
const int KEY_H = GLFW_KEY_H;
const int KEY_I = GLFW_KEY_I;
const int KEY_J = GLFW_KEY_J;
const int KEY_K = GLFW_KEY_K;
const int KEY_L = GLFW_KEY_L;
const int KEY_M = GLFW_KEY_M;
const int KEY_N = GLFW_KEY_N;
const int KEY_O = GLFW_KEY_O;
const int KEY_P = GLFW_KEY_P;
const int KEY_Q = GLFW_KEY_Q;
const int KEY_R = GLFW_KEY_R;
const int KEY_S = GLFW_KEY_S;
const int KEY_T = GLFW_KEY_T;
const int KEY_U = GLFW_KEY_U;
const int KEY_V = GLFW_KEY_V;
const int KEY_W = GLFW_KEY_W;
const int KEY_X = GLFW_KEY_X;
const int KEY_Y = GLFW_KEY_Y;
const int KEY_Z = GLFW_KEY_Z;


typedef struct Key {
    int key, scancode, action, mods;
} Key;

// Singleton for catching key callbacks. You don't need to poll through each one of them.
// You can access a key's information anytime in the program.
typedef struct KeyInfo {
    std::map<int, Key> keys;
    bool is_key_pressed(int key);
    bool is_key_released(int key);
} KeyInfo;

extern KeyInfo Input; // not sure if extern keyword is necessary.

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);






#endif
