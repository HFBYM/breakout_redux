# basic setting
cmake_minimum_required(VERSION 3.6)
project(Breakout CXX)
set(CMAKE_CXX_STANDARD 11)
# debug by default 
set(CMAKE_BUILD_TYPE Debug)
# set the path of directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build_cmake)
# set(CMAKE_SUPPRESS_REGENERATION true) #depose the middle files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/output)
# if generator is VS
# set the include path
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/freetype)
include_directories(${CMAKE_SOURCE_DIR}/GLAD)
include_directories(${CMAKE_SOURCE_DIR}/GLFW)
include_directories(${CMAKE_SOURCE_DIR}/glm)
include_directories(${CMAKE_SOURCE_DIR}/irrKlang)
include_directories(${CMAKE_SOURCE_DIR}/KHR)
include_directories(${CMAKE_SOURCE_DIR}/stb_image)
# set the libs
link_directories(${CMAKE_SOURCE_DIR}/freetype)
link_directories(${CMAKE_SOURCE_DIR}/GLFW)
link_directories(${CMAKE_SOURCE_DIR}/irrKlang/lib/Winx64-visualStudio)

link_libraries(opengl32.lib)
link_libraries(glfw3.lib)
link_libraries(irrKlang.lib)
link_libraries(freetyped.lib)
# find the src files
file(GLOB MAIN_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB MAIN_SRC ${CMAKE_SOURCE_DIR}/src/*.c)
# the dlls need to be in the same directory of exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(breakout MAIN_SRC)