cmake_minimum_required(VERSION 3.15)
project(Engine VERSION 0.0.1)
include(GNUInstallDirs)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(SRCS src/main.cpp 
src/shader.cpp 
src/vertexbuffer.cpp 
src/indexbuffer.cpp 
src/render.cpp 
src/vertexarray.cpp 
src/window.cpp 
src/app.cpp 
src/camera.cpp
src/chunks.cpp
)

include_directories(src/include)
add_executable(Engine ${SRCS} ) 

target_link_libraries(Engine ${../lib} GL)
target_link_libraries(Engine ${../lib} GLEW)
target_link_libraries(Engine ${../lib} glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
