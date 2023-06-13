cmake_minimum_required(VERSION 3.22)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
add_subdirectory(glm)

include_directories(glad/include Libraries)

set(SOURCE_FILES Sources/Camera.cpp Sources/Shader.cpp Sources/stb_image.cpp Sources/texture.cpp)

add_executable(Chess main.cpp glad/src/glad.c ${SOURCE_FILES})

target_link_libraries(Chess glfw)
target_link_libraries(Chess glm)
target_link_libraries(Chess OpenGL::GL)