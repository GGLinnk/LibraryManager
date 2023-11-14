@echo off
setlocal

set "buildDir=winbuild"

if not exist "%buildDir%" (
    mkdir "%buildDir%"
)

cd "%buildDir%"

if not exist "CMakeCache.txt" (
    cmake ..
)

cmake --build .

endlocal