cmake_minimum_required(VERSION 3.5.0)

set(LIBRARY_NAME tinyalgebralib)

set(SOURCES
    src/math/math.cpp
    src/math/Vector.cpp
)

add_library(${LIBRARY_NAME} STATIC ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

export(TARGETS ${LIBRARY_NAME} FILE ${CMAKE_BINARY_DIR}/tinyalgebralib.cmake)