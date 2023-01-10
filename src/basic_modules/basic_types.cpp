#include "basic_types.h"

Vector3 vector3_normalize(Vector3 vector) {
    Vector3 normalized;
    float length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    if (vector.x == 0.0f) normalized.x = 0.0f;
    else normalized.x = vector.x / length;
    if (vector.y == 0.0f) normalized.y = 0.0f;
    else normalized.y = vector.y / length;
    if (vector.z == 0.0f) normalized.z = 0.0f;
    else normalized.z = vector.z / length;
    return normalized;
}

Vector3 vector3_zero() {
    Vector3 zero = {0.0f, 0.0f, 0.0f};
    return zero;
}
