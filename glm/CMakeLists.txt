cmake_minimum_required(VERSION 2.8)

# Project Name
project(test)

# Include needed libraries
find_package(GLM REQUIRED)

if (NOT GLM_FOUND)
  message("ERROR: GLM not found")
endif(NOT GLM_FOUND)


include_directories(${GLM_INCLUDE_DIRS})

# build program
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
