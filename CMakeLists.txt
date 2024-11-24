# basic setting
cmake_minimum_required(VERSION 3.6)
project(Breakout)
set(CMAKE_CXX_STANDARD 11)

# debug by default 
# set(CMAKE_BUILD_TYPE Debug)

# set the macro
add_compile_definitions(PROJECT_DIR="${CMAKE_SOURCE_DIR}")

# set the path of directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build_cmake/binary_build)  #??
set(CMAKE_SUPPRESS_REGENERATION true) #depose the middle files      ??

# if generator is VS
# set the include path
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/freetype)  #??file system
include_directories(${CMAKE_SOURCE_DIR}/dependencies/GLAD)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/GLFW)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/glm)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/irrKlang)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/KHR)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/stb_image)

# set the libs
link_directories(${CMAKE_SOURCE_DIR}/dependencies/freetype)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/GLFW)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/irrKlang/lib/Winx64-visualStudio)

link_libraries(opengl32.lib)
link_libraries(glfw3.lib)
link_libraries(irrKlang.lib)
link_libraries(freetyped.lib)

# find the src files
file(GLOB MAIN_SRC_CPP ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB MAIN_SRC_C ${CMAKE_SOURCE_DIR}/src/*.c)

# the dlls need to be in the same directory of exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(breakout  ${MAIN_SRC_C} ${MAIN_SRC_CPP})