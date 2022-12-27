#ifndef clock_h

#define clock_h
#include "opengl_basic_wrapper.h"

typedef struct Clock {
    float current_time = 0.0f, last_time = 0.0f, deltatime = 0.0f;
    void update();
} Clock;



#endif
