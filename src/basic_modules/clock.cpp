#include "clock.h"


void Clock::update() {
    current_time = glfwGetTime();
    deltatime = current_time - last_time;
    last_time = current_time;
}
