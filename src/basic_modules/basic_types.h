#ifndef basic_types_h
#define basic_types_h

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>


typedef uint64_t  u64;
typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;
typedef int64_t   s64;
typedef int32_t   s32;
typedef int16_t   s16;
typedef int8_t    s8;

typedef struct Floats3{
    float float1, float2, float3;
    Floats3(float float1_, float flaot2_, float float3_);
} Float3;

typedef struct Floats4{
    float float1, float2, float3, float4;
    Floats4(float float1_, float flaot2_, float float3_, float float4_);
} Floats4;


#endif

