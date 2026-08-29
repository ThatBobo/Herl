#!/bin/bash
# Setup script for Herl

set -e

echo "🎮 Herl Setup Script"
echo "==================="

echo "🔨 Building Herl..."

# Install dependencies
if [ ! -d "vcpkg_installed" ]; then
    echo "📦 Installing dependencies with vcpkg..."
    ./vcpkg/vcpkg install
fi

# Configure
echo "⚙️  Configuring CMake..."
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$(pwd)/vcpkg/scripts/buildsystems/vcpkg.cmake"

# Build
echo "🔨 Building..."
cmake --build build --config Release

echo "✅ Build complete!"
echo ""
echo "🚀 To start Herl:"
echo "   export DISCORD_TOKEN=your_token_here"
echo "   ./build/Release/herl"
echo ""
