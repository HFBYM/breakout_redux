# basic setting
cmake_minimum_required(VERSION 3.12)
project(breakout_redux)
set(CMAKE_CXX_STANDARD 17)

# debug by default 
# set(CMAKE_BUILD_TYPE Debug)

# set the macro
add_compile_definitions(PROJECT_DIR="${CMAKE_SOURCE_DIR}")

#depose the middle files
set(CMAKE_SUPPRESS_REGENERATION true)

# set the include path
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/freetype)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/GLAD)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/GLFW)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/glm)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/irrKlang)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/KHR)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/stb_image)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/json_parser)

# set the libs
link_directories(${CMAKE_SOURCE_DIR}/dependencies/freetype)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/GLFW)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/irrKlang/lib/Winx64-visualStudio)

link_libraries(opengl32.lib)
link_libraries(glfw3.lib)
link_libraries(irrKlang.lib)
link_libraries(freetyped.lib)
link_libraries(imm32.lib)

# find the src files
file(GLOB_RECURSE MAIN_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

# the dlls need to be in the same directory of exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(breakout ${MAIN_SRC})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()
# copy the dlls
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
    set(DLL_DES_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
else()
    set(DLL_DES_DIR ${CMAKE_SOURCE_DIR}/bin)
endif()
set(DLL_SRC_DIR ${CMAKE_SOURCE_DIR}/dependencies/irrKlang/lib/Winx64-visualStudio)

execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${DLL_SRC_DIR}/ikpMP3.dll ${DLL_DES_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${DLL_SRC_DIR}/irrKlang.dll ${DLL_DES_DIR})
