# CMakeLists.txt
#
# MIT License
#
# Copyright (c) 2025 Lauri Etelämäki
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.22)
project(Pic-g VERSION 0.1)

# Export CWD to projectt
configure_file(src/globals/cwd.h.in srcout/globals/cwd.h)
include_directories(${CMAKE_BINARY_DIR}/srcout)

file(GLOB_RECURSE SOURCES "src/**" "user/**")
add_executable(${PROJECT_NAME} ${SOURCES})

# Set compiler flags
set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS "-O3")

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_DEBUG "-ggdb")


add_custom_target(clean_build_dir
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/build
    COMMENT "Removing build files"
)

target_include_directories(Pic-g PRIVATE ${CMAKE_BINARY_DIR}/../src)
target_include_directories(Pic-g PRIVATE ${CMAKE_BINARY_DIR}/../dep/stb)


# Link libraries to the executable
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        opengl32
        glu32
        m
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        X11
        GL
        GLU
        m
    )
endif()