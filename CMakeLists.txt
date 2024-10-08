cmake_minimum_required(VERSION 3.25.0)

project(tinyalgebra VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/math/math.cpp
    src/math/Vector.cpp
    src/Camera.cpp
    
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -march=native -ffast-math)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

export(TARGETS ${PROJECT_NAME} FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.cmake)

add_executable(vector_test tests/vector_test.cpp)
target_link_libraries(vector_test ${PROJECT_NAME})