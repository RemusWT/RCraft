#include "basic_types.h"


Vector3 operator + (Vector3 lvec, Vector3 rvec) {
    Vector3 new_vec;
    new_vec.x = lvec.x + rvec.x;
    new_vec.y = lvec.y + rvec.y;
    new_vec.z = lvec.z + rvec.z;
    return new_vec;
}

// @Refactor should be in another source file
Vector3 vector3_normalize(Vector3 vector) { // @Bug it doesn't actually do anything
    Vector3 normalized = {0.0f, 0.0f, 0.0f};
    float length = vector.x + vector.y + vector.z;
    if (length == 0.0f) return normalized;
    
    if (vector.x != 0.0f) normalized.x = vector.x / length;
    if (vector.y != 0.0f) normalized.y = vector.y / length;
    if (vector.z != 0.0f) normalized.z = vector.z / length;
    printf("Inside the vector3_normalize function: %f %f %f", vector.x, vector.y, vector.z);
    return normalized;
}
glm::vec3 vector3_glm(Vector3 vec) {
    glm::vec3 glm_vec;
    glm_vec.x = vec.x;
    glm_vec.y = vec.y;
    glm_vec.z = vec.z;
    return glm_vec;
}

Vector3 vector3_zero() {
    Vector3 zero = {0.0f, 0.0f, 0.0f};
    return zero;
}
