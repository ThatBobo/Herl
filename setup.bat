@echo off
REM Setup script for Herl on Windows

setlocal enabledelayedexpansion

echo.
echo 🎮 Herl Setup Script
echo ===================
echo.

echo 🔨 Building Herl...
echo.

REM Check vcpkg_installed
if not exist vcpkg_installed (
    echo 📦 Installing dependencies with vcpkg...
    call .\vcpkg\vcpkg install
)

REM Configure
echo ⚙️  Configuring CMake...
set "VCPKG_PATH=%cd%\vcpkg"
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="%VCPKG_PATH%\scripts\buildsystems\vcpkg.cmake"

REM Build
echo 🔨 Building...
cmake --build build --config Release

echo.
echo ✅ Build complete!
echo.
echo 🚀 To start Herl:
echo    set DISCORD_TOKEN=your_token_here
echo    .\build\Release\herl.exe
echo.
