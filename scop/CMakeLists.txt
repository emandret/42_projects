cmake_minimum_required(VERSION 3.13)

# set the project name
project(scop)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# generates a list of all source files that match the globbing expression
file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(scop ${SRC_FILES})

# specifies the include directory
target_include_directories(scop PRIVATE inc)

# links to 3rd party libraries
target_link_libraries(scop glfw)
target_link_libraries(scop OpenGL::GL)