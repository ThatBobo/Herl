# Herl Build & Deployment

## Prerequisites

- **C++20 Compiler**
  - Windows: MSVC 2019+ or MinGW with C++20 support
  - Linux: GCC 10+ or Clang 11+
  - macOS: Clang 12+ (via Xcode or Homebrew)

- **CMake** 3.20+
  ```bash
  # Check version
  cmake --version
  ```

- **vcpkg** (Package Manager)
  ```bash
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  ./bootstrap-vcpkg.sh  # Linux/macOS
  .\bootstrap-vcpkg.bat # Windows
  ```

## Build Instructions

### Windows (PowerShell)

```powershell
# 1. Install dependencies
.\vcpkg\vcpkg install

# 2. Configure
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake"

# 3. Build
cmake --build build --config Release

# 4. Set token
$env:DISCORD_TOKEN = "your-bot-token-here"

# 5. Run
.\build\Release\herl.exe
```

### Linux/macOS (Bash)

```bash
# 1. Install dependencies
./vcpkg/vcpkg install

# 2. Configure
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

# 3. Build
cmake --build build --config Release

# 4. Set token
export DISCORD_TOKEN="your-bot-token-here"

# 5. Run
./build/Release/herl
```

## Configuration

### Environment Variables

```bash
# Required
DISCORD_TOKEN=your-bot-token

# Optional (future features)
HERL_DB_PATH=./herl.db
HERL_LOG_LEVEL=info
HERL_PORT=8080
```

### CMake Options

```bash
# Enable debug symbols
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug

# Custom install path
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=/opt/herl

# Verbose output
cmake --build build --verbose
```

## Discord Bot Setup

### 1. Create Application
1. Go to [Discord Developer Portal](https://discord.com/developers/applications)
2. Click "New Application"
3. Give it a name (e.g., "Herl")
4. Go to "Bot" → "Add Bot"

### 2. Configure Permissions
1. Go to "OAuth2" → "URL Generator"
2. Select scopes: `bot`, `applications.commands`
3. Select permissions:
   - ✅ Send Messages
   - ✅ Read Messages/View Channels
   - ✅ Use Slash Commands
4. Copy generated URL

### 3. Invite Bot
1. Paste the URL in your browser
2. Select your Discord server
3. Click "Authorize"

### 4. Get Token
1. Go to "Bot" tab
2. Click "Reset Token"
3. Copy token (keep it secret!)
4. Set as `DISCORD_TOKEN` environment variable

## Running

### Development

```bash
export DISCORD_TOKEN="your-token"
./build/Release/herl
```

Bot will log to console and respond to commands in any server where it's installed.

### Production

```bash
# Run in background
nohup ./build/Release/herl > herl.log 2>&1 &

# Or use systemd service (Linux)
sudo systemctl start herl
```

## Troubleshooting

### Build Fails

**"dpp not found"**
```bash
# Reinstall dependencies
rm -rf vcpkg_installed CMakeCache.txt
./vcpkg/vcpkg install
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=...
```

**"C++20 not supported"**
- Update compiler:
  - Windows: Install latest Visual Studio
  - Linux: `sudo apt install g++-11`
  - macOS: `brew install llvm`

### Runtime Issues

**"DISCORD_TOKEN is not set"**
```bash
export DISCORD_TOKEN="your-actual-token"
```

**"Commands don't appear in Discord"**
- Wait 5-10 minutes for Discord to sync
- Check bot has proper permissions
- Restart bot: `pkill herl && ./build/Release/herl`

**"Connection refused"**
- Discord API may be down
- Check internet connection
- Verify bot token is still valid

## Performance Tuning

### Optimization Flags

```cmake
# In CMakeLists.txt
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Release>:-march=native>
)
```

### Memory Usage

- Residents stored in `std::unordered_map` — O(1) lookup
- Mutex-protected for thread safety
- ~1KB per resident in memory
- Database recommended for 1000+ players

## Deployment Checklist

- [ ] Bot token stored securely (never in code)
- [ ] CMakeLists.txt includes all source files
- [ ] All headers in `include/herl/` properly included
- [ ] No hardcoded paths or local dependencies
- [ ] Error handling for Discord API failures
- [ ] Logging enabled for debugging
- [ ] Commands tested in private server
- [ ] README and docs up to date

## Continuous Integration

Example GitHub Actions workflow:

```yaml
name: Build

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Install dependencies
        run: |
          sudo apt-get install -y cmake g++-11
          git clone https://github.com/microsoft/vcpkg.git
      - name: Build
        run: |
          ./vcpkg/vcpkg install
          cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$(pwd)/vcpkg/scripts/buildsystems/vcpkg.cmake
          cmake --build build --config Release
```
