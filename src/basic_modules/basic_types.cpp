#include "basic_types.h"

Vector3 vector3_normalize(Vector3 vector) {
    Vector3 normalized;
    if (vector.x == 0.0f) normalized.x = 0.0f;
    else normalized.x = 1 / vector.x;
    if (vector.y == 0.0f) normalized.y = 0.0f;
    else normalized.y = 1 / vector.y;
    if (vector.z == 0.0f) normalized.z = 0.0f;
    else normalized.z = 1 / vector.z;
    return normalized;
    
    
}

Vector3 vector3_zero() {
    Vector3 zero = {0.0f, 0.0f, 0.0f};
    return zero;
}
