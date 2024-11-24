@REM @echo off
::figure out whether cmake is downloaded
where cmake > nul
if %errorlevel% == 1 (
echo Failed to find cmake
exit)

set generator=
::check if Visual Studio is on
cmake /? | findstr /C:"Visual Studio" >nul
if %errorlevel% == 0 (set generator="Visual Studio")^
else (
    :: check if gcc is on
    cmake /? | findstr /C:"MinGW Makefiles" > nul
    if %errorlevel% == 0 (set generator="MinGW Makefiles")^
    else (echo Neither Visual Studio nor GCC
        exit
    )
)

::building
cmake -G "Visual Studio 17 2022" -B ./build_cmake
@REM cmake -G "MinGW Makefiles" -B ./build_cmake
@REM cmake --build ./build_cmake --config Debug
pause
