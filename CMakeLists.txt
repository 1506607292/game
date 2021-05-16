cmake_minimum_required(VERSION 3.9)
project(untitled2)
set(CMAKE_CXX_STANDARD 20)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})

#find_package(X11)
#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
#find_library(M_LIBRARY m)
#find_library(GLEW_LIBRARY GLEW)

set(CMAKE_CXX_STANDARD 11)

# 添加头文件
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
set(GLFW_H /usr/local/Cellar/glfw/3.3.3/include)
set(GLAD_H /usr/local/Cellar/glad/include)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H})

# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.3/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

# 执行编译命令
set(SOURCE_FILES src/glad.c src/main.cpp include/circle.h include/board.h)

add_executable(untitled2 ${SOURCE_FILES})

#if (APPLE)
#    target_link_libraries(SmartPointTest "-framework OpenGL")
#endif()