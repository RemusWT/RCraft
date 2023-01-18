#ifndef clock_h
#define clock_h
#include "render/opengl_basic_wrapper.h"

// @Refactor maybe we should move this to gameinfo.h

typedef struct Clock {
    double current_time = 0.0f;
    double last_time = 0.0f;
    double deltatime = 0.0f;
    void update();
} Clock;

#endif
