#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <stdint.h>

#include <SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

//----------------------------------------------------------

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;

//----------------------------------------------------------

#define MURDER_APP *((int*)0) = 3

//----------------------------------------------------------

#define LOG(...) printf("Log in file \"%s\" at line (%d) says:\t\"", __FILE__, __LINE__);printf(__VA_ARGS__); printf("\"\n")

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

#define String std::string
#define Array std::vector
#define Map std::map

//----------------------------------------------------------
