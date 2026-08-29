# Herl Code Structure

## Overview

Herl is a Discord multiplayer roleplay game written in C++20. The project uses the [dpp](https://github.com/brainboxdotcc/DPP) (Discord++) library for Discord bot functionality.

## Architecture

### Current Layout

- **src/main.cpp** — Entry point; sets up the Discord bot and initializes command handlers.

### Planned Modularization

As Herl grows, the code will be organized into these components:

#### `include/herl/world.hpp`
Manages game world state:
- `Resident` struct — represents a player's character
- `World` class — singleton managing all residents and game logic
- Constants (locations, costs, earnings)

#### `include/herl/commands.hpp`
Handles Discord slash commands:
- `/join` — create or get a resident
- `/move` — change location
- `/work` — earn cash
- `/fly` — travel to another airport
- `/me` — view resident profile
- `/here` — list residents at current location
- `/places` — list all locations
- `/herl` — display game help

#### `src/world.cpp` (future)
Implementation of world state management with thread-safe resident tracking.

#### `src/commands.cpp` (future)
Implementation of all command handlers with validation and game logic.

## Key Design Patterns

### Thread Safety
- Uses `std::mutex` to protect shared game state
- All resident access is protected by locks

### Game Constants
- Located in `World` class for easy configuration
- Flight cost, starting cash, shift earnings, and locations

### Singleton Pattern
- `World::instance()` provides global access to game state
- Ensures only one world exists across the application

## Adding New Features

1. **New Location:** Add to `World::CITY_LOCATIONS` array
2. **New Command:** Add to `commands::register_commands()` and `commands::handle_command()`
3. **Resident Property:** Add field to `Resident` struct, update `World` queries
4. **Persistence:** Implement database layer in `World` class (SQLite recommended)

## Dependencies

- **dpp** — Discord C++ library (handles bot communication, slash commands, events)
- **C++20 standard library** — STL containers, threading, string formatting

## Building

```bash
vcpkg install
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
./build/Release/herl  # or herl.exe on Windows
```

## Next Steps

1. **Implement `World` class** — move game state from anonymous namespace
2. **Extract commands** — move command registration and handling to separate file
3. **Add persistence** — save game state to database (SQLite)
4. **Expand locations** — add more cities and interaction points
5. **Add inventory system** — items, trading, shops
6. **Implement economy** — prices, wages, taxes
