#ifndef clock_h
#define clock_h
#include "render/opengl_basic_wrapper.h"

// @Refactor maybe we should move this to gameinfo.h

// A clock object to keep track of time.
// update() contains information about how much time it took since the last update() and stores it in deltatime.
// then last_time gets set at the current_time.
typedef struct Clock {
    double current_time = 0.0f;
    double last_time = 0.0f;
    double deltatime = 0.0f;
    void update();
    double get_current_time(); // returns in seconds
} Clock;

#endif
