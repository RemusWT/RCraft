#ifndef input_basic_h

#define input_basic_h
#include "utils/basic_types.h"
#include "render/opengl_basic_wrapper.h"
// NOTE: When we are making themes for Emendo make sure to make one dedicated for Sonar Systems.


typedef struct Key {
    int key, scancode, action, mods;
} Key;

// Singleton-use struct for catching key callbacks. You don't need to poll through each one of them.
// You can access a key's information anytime in the program.
typedef struct KeyInfo {
    std::map<int, Key> keys;
    bool is_key_pressed(int key);
    bool is_key_released(int key);
} KeyInfo;

extern KeyInfo Input; // not sure if extern keyword is necessary.

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);






#endif
