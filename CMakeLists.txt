# basic setting
cmake_minimum_required(VERSION 3.12)
project(breakout_redux)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# debug by default 
set(CMAKE_BUILD_TYPE Debug)

# set the macro
add_compile_definitions(PROJECT_DIR="${CMAKE_SOURCE_DIR}")

#depose the middle files
set(CMAKE_SUPPRESS_REGENERATION true)

# find the src files
file(GLOB_RECURSE MAIN_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

# the dlls need to be in the same directory of exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-windows-x64)
add_executable(breakout ${MAIN_SRC})

# set the include path
target_include_directories(breakout PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/dependencies/GLAD
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW
    ${CMAKE_SOURCE_DIR}/dependencies/glm
    ${CMAKE_SOURCE_DIR}/dependencies/irrKlang
    ${CMAKE_SOURCE_DIR}/dependencies/KHR
    ${CMAKE_SOURCE_DIR}/dependencies/stb_image
    ${CMAKE_SOURCE_DIR}/dependencies/json_parser
)

target_precompile_headers(breakout PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/src/utils/pch.h>)

# set the libs
target_link_directories(breakout PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW
    ${CMAKE_SOURCE_DIR}/dependencies/irrKlang/lib/Winx64-visualStudio
)

target_link_libraries(breakout PRIVATE opengl32 glfw3 irrKlang imm32)

set(DLL_SRC_DIR ${CMAKE_SOURCE_DIR}/dependencies/irrKlang/lib/Winx64-visualStudio)

add_custom_command(TARGET breakout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${DLL_SRC_DIR}/ikpMP3.dll
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
add_custom_command(TARGET breakout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${DLL_SRC_DIR}/irrKlang.dll
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
