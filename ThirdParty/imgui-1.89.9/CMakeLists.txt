cmake_minimum_required(VERSION 3.24)
project(imgui)

set(CMAKE_CXX_STANDARD 17)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/../../Output/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(SDL_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/SDL-release-2.28.3/)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/imgui-1.89.9/)

option(IMGUI_DISABLE_OBSOLETE_FUNCTIONS "Disable deprecated functions" ON)
option(IMGUI_DISABLE_OBSOLETE_KEYIO "Disable legacy input handling" ON)
option(IMGUI_DISABLE_FILE_FUNCTIONS "Disable use of file functions" OFF)
option(IMGUI_ENABLE_STDLIB_SUPPORT "Enable extra functions taking stdlib types" OFF)
option(IMGUI_ENABLE_COVERAGE "Enable coverage testing for supported compilers" OFF)
option(IMGUI_ENABLE_ASAN "Enable compiler-based sanitizers" OFF)
option(IMGUI_ENABLE_TRACY "Enable tracy profiling" OFF)
option(IMGUI_ENABLE_FREETYPE "Enable FreeType font rasterizer" ON)
option(IMGUI_IMPL_SDL "Build the SDL implementation (only if supported)" ON)

include_directories(${SDL_DIR}include/)
include_directories(${IMGUI_DIR})
add_library(imgui STATIC
        ${IMGUI_DIR}imgui.cpp
        ${IMGUI_DIR}imgui_draw.cpp
        ${IMGUI_DIR}imgui_tables.cpp
        ${IMGUI_DIR}imgui_widgets.cpp
        ${IMGUI_DIR}backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}backends/imgui_impl_sdlrenderer2.cpp)
