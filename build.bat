@REM @echo off
::figure out whether cmake is downloaded
where cmake
if %errorlevel% == 1 (
echo Failed to find cmake
exit)

set generator=
::check if Visual Studio is on
cmake /? | findstr /C:"Visual Studio" > nul 
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
cmake -G %generator% .
pause
