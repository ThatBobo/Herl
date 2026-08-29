# Contributing to Herl

Thanks for your interest in contributing to Herl! Here's how to get started.

## Development Setup

### Prerequisites

- **C++20 compiler** (MSVC on Windows, GCC/Clang on Linux/macOS)
- **CMake** 3.20+
- **vcpkg** — dependency manager for C++

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/ThatBobo/Herl.git
   cd Herl
   ```

2. Install dependencies with vcpkg:
   ```bash
   vcpkg install
   ```

3. Build the project:
   ```bash
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
   cmake --build build --config Release
   ```

4. Set your Discord bot token (do **not** commit this):
   ```bash
   # On Windows PowerShell:
   $env:DISCORD_TOKEN = "your-token-here"
   
   # On Linux/macOS bash:
   export DISCORD_TOKEN="your-token-here"
   ```

5. Run the bot:
   ```bash
   ./build/Release/herl
   ```

## Code Style

- **Language Standard:** C++20
- **Formatting:** Use `const`/`constexpr` where possible, prefer `auto` with clear types
- **Naming:**
  - Classes/structs: `PascalCase` (e.g., `Resident`, `World`)
  - Functions/variables: `snake_case` (e.g., `get_resident`, `flight_cost`)
  - Constants: `UPPER_SNAKE_CASE` (e.g., `FLIGHT_COST`, `STARTING_CASH`)
- **Comments:** Document public functions and complex logic
- **Namespaces:** Keep code in `herl::` namespace

## Making Changes

### 1. Create a branch
```bash
git checkout -b feature/your-feature-name
```

### 2. Make your changes
- Keep commits small and focused
- Reference any related issues in commit messages
- Update comments and documentation as needed

### 3. Test your changes
- Manually test the bot in a private Discord server
- Verify existing commands still work
- Test edge cases (invalid input, missing permissions, etc.)

### 4. Push and create a pull request
```bash
git push origin feature/your-feature-name
```
- Describe what your changes do
- Link any related issues
- Include screenshots if UI-related

## What to Work On

### 🎯 High Priority
- **Persistence:** Save game state to a database (SQLite)
- **Modularization:** Extract `world.cpp` and `commands.cpp` from `main.cpp`
- **Error handling:** Graceful recovery from Discord API failures

### 🚀 Medium Priority
- Additional locations and points of interest
- Inventory system (items, storage)
- Player-to-player transactions (gifting money, trading)
- Leaderboards (top earners, most traveled)

### 💡 Low Priority
- Visual embeds and rich message formatting
- Guilds/families for grouping players
- Mini-games for earning cash
- Admin commands for server operators

## Questions?

Open an issue or start a discussion. Have fun building Herl! 🎮
