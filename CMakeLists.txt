cmake_minimum_required(VERSION 2.8)

# Project Name
project(test)

# Set cmake module path
set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCEDIR}/cmake
  ${CMAKE_MODULE_PATH})

# Include needed libraries
# GLM (OpenGL Math)
find_package(GLM REQUIRED)

if (NOT GLM_FOUND)
  message("ERROR: GLM not found")
endif(NOT GLM_FOUND)

# OpenGL
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
  message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)
set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(${GLM_INCLUDE_DIR})

# Source file list
set(SOURCES "${CMAKE_SOURCE_DIR}/src/test.cpp")

# build program
add_executable(${PROJECT_NAME} ${SOURCES})

# Linking Libraries
# Linking glfw and not glfw3
target_link_libraries(${PROJECT_NAME} glfw ${GL_LIBRARY} m)
