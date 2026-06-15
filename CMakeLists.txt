cmake_minimum_required(VERSION 3.15)
project(Engine VERSION 0.0.1)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

set(ENGINE_SOURCES
    src/shader.cpp
    src/vertexbuffer.cpp
    src/indexbuffer.cpp
    src/render.cpp
    src/vertexarray.cpp
    src/window.cpp
    src/camera.cpp
    src/chunks.cpp
)

add_library(EngineCore STATIC ${ENGINE_SOURCES})

target_include_directories(EngineCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/include>
)

target_link_libraries(EngineCore
    PUBLIC
        OpenGL::GL
        glfw
        GLEW::GLEW
)

add_executable(Engine src/main.cpp src/app.cpp)

target_compile_definitions(Engine PRIVATE SHADER_FILE="${CMAKE_SOURCE_DIR}/src/shaders/shader.shader")

target_link_libraries(Engine
    PRIVATE
        EngineCore
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
