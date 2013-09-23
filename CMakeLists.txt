cmake_minimum_required(VERSION 2.8)

project( FIRST ) # this is case sensitive 

######################################
# finds OpenGL, GLU and X11
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)
set(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable(first first.cpp)

# linking "glfw" and not "glfw3" 
# assumes that glfw was built with BUILD_SHARED_LIBS to ON
target_link_libraries(first glfw ${GL_LIBRARY} m)
