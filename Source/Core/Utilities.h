#pragma once

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <inttypes.h>
#include <iostream>
#include <map>
#include <math.h>
#include <stdint.h>
#include <thread>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

//----------------------------------------------------------

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1000
#define WINDOW_HALF_WIDTH 800
#define WINDOW_HALF_HEIGHT 500
static_assert( WINDOW_HALF_WIDTH == WINDOW_WIDTH / 2, "The window's half width must be half the given width" );
static_assert( WINDOW_HALF_HEIGHT == WINDOW_HEIGHT / 2, "The window's half height must be half the given height" );

#define PI = 3.141592659
#define DEGREES_TO_RADIANS 0.0174532924
#define RADIANS_TO_DEGREES 57.29578

//----------------------------------------------------------

#define MURDER_APP *((int*)0) = 3

//----------------------------------------------------------

#define LOG(...) printf( "Log in file \"%s\" at line (%d) says:\t\"", __FILE__, __LINE__ ); printf( __VA_ARGS__ ); printf( "\"\n" )

//----------------------------------------------------------

typedef int8_t          s8;
typedef int16_t         s16;
typedef int32_t         s32;
typedef int64_t         s64;
typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef uint64_t        u64;

//----------------------------------------------------------

#define S8_MIN          INT8_MIN
#define S16_MIN         INT16_MIN
#define S32_MIN         INT32_MIN
#define S64_MIN         INT64_MIN

#define S8_MAX          INT8_MAX
#define S16_MAX         INT16_MAX
#define S32_MAX         INT32_MAX
#define S64_MAX         INT64_MAX

#define U8_MAX          UINT8_MAX
#define U16_MAX         UINT16_MAX
#define U32_MAX         UINT32_MAX
#define U64_MAX         UINT64_MAX

//----------------------------------------------------------

typedef std::chrono::high_resolution_clock              Clock;
typedef std::chrono::seconds                            Seconds;
typedef std::chrono::nanoseconds                        NanoSeconds;
typedef std::chrono::time_point<Clock, NanoSeconds>     TimeStamp;
typedef std::chrono::duration<double>                   DurationSecs;
typedef std::chrono::duration<double, std::milli>       DurationMillis;

//----------------------------------------------------------

#define RAND_SET_SEED( x ) ( srand(x) )
#define RAND_NUM_IN_RANGE(InMin, InMax) ( ( rand() % ( ( InMax ) - ( InMin ) ) ) + ( InMin ) )

//----------------------------------------------------------
