#ifndef basic_types_h
#define basic_types_h

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <cmath>


typedef uint64_t  u64;
typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;
typedef int64_t   s64;
typedef int32_t   s32;
typedef int16_t   s16;
typedef int8_t    s8;


typedef struct Vector3 {
    float x, y, z;
} Vector3;

Vector3 vector3_normalize(Vector3 vector);
Vector3 vector3_zero();

#endif

