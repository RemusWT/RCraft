#ifndef clock_h
#define clock_h
#include "basic_modules/opengl_basic_wrapper.h"

typedef struct Clock {
    double current_time = 0.0f;
    double last_time = 0.0f;
    double deltatime = 0.0f;
    void update();
} Clock;

#endif
