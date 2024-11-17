cmake_minimum_required(VERSION 3.22)
project(Pic-g VERSION 0.1)

file(GLOB_RECURSE SOURCES "src/**")
add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_DEBUG "-ggdb")

# Link libraries to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    X11
    GL
    GLU
)