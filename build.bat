@REM @echo off

::building
cmake -B ./build_cmake
@REM cmake -G "MinGW Makefiles" -B ./build_cmake

:: compiling to exe
@REM cmake --build ./build_cmake --config Debug
