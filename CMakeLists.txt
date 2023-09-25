cmake_minimum_required(VERSION 3.24)
project(FlockingAI)

message("Compiler used =" ${CMAKE_CXX_COMPILER_ID})

set(CMAKE_CXX_STANDARD 17)
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Output/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

set(SDL_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/SDL-release-2.28.3/)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/imgui-1.89.9/)

include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/SDL-release-2.28.3/include/)
include_directories(${IMGUI_DIR})
link_directories(${OUTPUT_DIR})

add_subdirectory("${IMGUI_DIR}")

add_executable(FlockingAI
        Source/main.cpp
        Source/Core/Vec2.cpp
        Source/Core/Vec2.h
        Source/Core/Utilities.h
        Source/Core/Application.cpp
        Source/Core/Application.h
        )
target_link_libraries(FlockingAI PRIVATE imgui SDL2main SDL2)
