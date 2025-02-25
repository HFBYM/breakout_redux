@REM @echo off
::figure out whether cmake is downloaded
where cmake > nul
if %errorlevel% == 1 (
echo Failed to find cmake
exit)

::building
cmake -B ./build_cmake
@REM cmake -G "MinGW Makefiles" -B ./build_cmake

:: compiling to exe
@REM cmake --build ./build_cmake --config Debug
