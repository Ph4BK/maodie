@echo off
setlocal

echo Generating build system with CMake...
cmake -G "Visual Studio 17 2022" -A x64 -B build
if errorlevel 1 (
    echo CMake generation failed!
    exit /b %errorlevel%
)

echo Building the project in Release mode...
cmake --build build --config Release
if errorlevel 1 (
    echo Build failed!
    exit /b %errorlevel%
)

echo Build completed successfully.
endlocal
pause