cmake_minimum_required(VERSION 3.22)
project(Pic-g VERSION 0.1)

set(CMAKE_TOOLCHAIN_FILE windows-toolchain.cmake_host_system_information())

file(GLOB_RECURSE SOURCES "src/**")
add_executable(${PROJECT_NAME} ${SOURCES})

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