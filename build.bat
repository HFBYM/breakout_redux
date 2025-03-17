@REM @echo off

::building
cmake -B ./build_cmake

:: compiling to exe
cmake --build ./build_cmake --config Debug
@REM pause
