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
set(SDL_IMAGE_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_image-2.6.3/)

include_directories(${SDL_DIR}include/)
include_directories(${IMGUI_DIR})
include_directories("${SDL_IMAGE_DIR}")
link_directories(${OUTPUT_DIR})

add_subdirectory("${IMGUI_DIR}")
add_subdirectory("${SDL_IMAGE_DIR}")

add_executable(FlockingAI
        Source/main.cpp
        Source/Core/Vec2.inl
        Source/Core/Vec2.h
        Source/Core/Utilities.h
        Source/Core/Application.cpp
        Source/Core/Application.h
        Source/Game/SteeringBehaviours.cpp
        Source/Game/SteeringBehaviours.h
        Source/Game/Boid.cpp
        Source/Game/Boid.h
        Source/Core/Transform.h
        Source/Core/World.cpp
        Source/Core/World.h
        Source/Core/GameObject.cpp
        Source/Core/GameObject.h
        Source/Core/RenderUtils.cpp
        Source/Core/RenderUtils.h)
target_link_libraries(FlockingAI PRIVATE imgui SDL2main SDL2 SDL2_image)
