#ifndef UTIL_H
#define UTIL_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float  	 f32;
typedef double   f64;
typedef Rectangle rect;
typedef Vector2 vec2 ;

typedef struct {
	f32 x, y;
	f32 r;
} circle;
#define CIRCLE(x, y, r) (circle) { x, y, r }

#define VEC2(x, y) (vec2) { x, y }
#define VEC2_0() (vec2) { 0, 0 }

typedef struct {
	f32 x, y, z;
} vec3;
#define VEC3(x, y, z) (vec3) { x, y, z }
#define VEC3_0() (vec3) { 0, 0, 0 }

typedef struct {
	vec2 p1, p2, p3;
} triangle;
#define TRIANGLE(p1, p2, p3) (triangle) { p1, p2, p3 }

#define RECT(x, y, w, h) (rect) { x, y, w, h }

#define dt GetFrameTime()
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#define RANDOM_INT_RANGE(min, max) ((rand() % ((max) - (min) + 1)) + (min))
#define RANDOM_FLOAT_RANGE(min, max) (((float)rand() / RAND_MAX) * ((max) - (min)) + (min))
#endif
