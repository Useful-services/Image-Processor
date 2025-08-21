@echo off
echo Starting Image Processor Web Server...
echo.

if not exist "build\Release\WEB_SERVER.exe" (
    echo Error: WEB_SERVER.exe not found!
    echo Please build the project first using: build.bat
    pause
    exit /b 1
)

echo Server will be available at: http://localhost:8080
echo Press Ctrl+C to stop the server
echo.

cd build\Release
WEB_SERVER.exe 