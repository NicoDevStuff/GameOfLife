cmake_minimum_required(VERSION 3.0)
project(GameOfLife)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

message(STATUS "Src dir: ${CMAKE_SOURCE_DIR}")
message(STATUS "Output dir: ${CMAKE_BINARY_DIR}")
file(GLOB SOURCES
    src/*.c

    libs/vec/src/vec.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    src/

    libs/vec/src
)


target_link_libraries(${PROJECT_NAME}
    raylib
    GL
    m
    pthread
    dl
    rt
    X11
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
endif()

if(UNIX AND CMAKE_GENERATOR MATCHES "Makefiles")
    target_compile_options(${PROJECT_NAME} PRIVATE -DBX_CONFIG_DEBUG=1)
endif()
