# Herl Architecture & Implementation Guide

## File Organization

### Headers (`include/herl/`)

```
include/herl/
├── world.hpp          # Core game state (Resident, World singleton)
├── commands.hpp       # Player command handlers
├── stats.hpp          # Leaderboards and statistics
├── database.hpp       # Persistence layer (SQLite)
├── location.hpp       # Location management and POIs
├── inventory.hpp      # Player inventory system
├── market.hpp         # In-game market and economy
└── admin.hpp          # Admin commands for operators
```

### Source (`src/`)

```
src/
├── main.cpp           # Bot initialization and event loop
├── world.cpp          # World class implementation
├── commands.cpp       # Command handler implementations
├── stats.cpp          # Statistics tracking (future)
├── database.cpp       # Database operations (future)
├── location.cpp       # Location logic (future)
├── inventory.cpp      # Inventory management (future)
├── market.cpp         # Market operations (future)
└── admin.cpp          # Admin commands (future)
```

## Core Components

### 1. World Management (`world.hpp` / `world.cpp`)
- **Resident struct**: Player character with location, cash, stats
- **World class**: Singleton managing all residents in-memory
- Thread-safe access via `std::mutex`
- Methods:
  - `get_or_create_resident()` — Create/retrieve player
  - `find_resident()` — Look up player
  - `get_residents_at_location()` — Location-based queries
  - `get_guild_residents()` — Guild-specific queries

### 2. Commands (`commands.hpp` / `commands.cpp`)
Player commands:
- `/join` — Create resident
- `/move` — Change location
- `/work` — Earn cash
- `/fly` — Travel to airports
- `/me` — Profile view
- `/here` — See nearby residents
- `/places` — Location list
- `/herl` — Help

### 3. Statistics (`stats.hpp` / `stats.cpp` - future)
- Track earnings and travel distance
- Generate leaderboards
- Record streaks and achievements

### 4. Database (`database.hpp` / `database.cpp` - future)
- SQLite persistence
- Save/load residents
- Query player history
- Backup functionality

### 5. Locations (`location.hpp` / `location.cpp` - future)
- Curated descriptions for each city
- Points of Interest (shops, jobs, entertainment)
- Distance calculations
- Location-based events

### 6. Inventory (`inventory.hpp` / `inventory.cpp` - future)
- Items players can carry
- Item management and trades
- Weight/capacity limits
- Item persistence

### 7. Market (`market.hpp` / `market.cpp` - future)
- In-game economy
- Item prices and stock
- Purchase mechanics
- Supply/demand simulation

### 8. Admin (`admin.hpp` / `admin.cpp` - future)
- Operator-only commands
- Server management
- Economy controls
- Moderation tools

## Implementation Roadmap

### Phase 1 ✅ (Complete)
1. ✅ Core world state management
2. ✅ Basic command handling
3. ✅ Multi-guild support
4. ✅ Project structure

### Phase 2 (Next)
1. Implement `stats.cpp` — Leaderboard system
2. Implement `database.cpp` — SQLite persistence
3. Implement `location.cpp` — Rich location descriptions
4. Write unit tests

### Phase 3 (Future)
1. Implement `inventory.cpp` — Item system
2. Implement `market.cpp` — Economy simulation
3. Implement `admin.cpp` — Operator tools
4. Add mini-games and events

## Building & Running

```bash
# Install dependencies
vcpkg install

# Configure
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-path>/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build --config Release

# Set token
export DISCORD_TOKEN="your-token"

# Run
./build/Release/herl
```

## Adding New Features

### New Command
1. Add to `commands::register_commands()` in `src/commands.cpp`
2. Add handler in `commands::handle_command()`
3. Update `commands.hpp` if needed
4. Test in private Discord server

### New Location
1. Add to `World::CITY_LOCATIONS` in `include/herl/world.hpp`
2. Add description in `location.cpp`
3. Define POIs in location data
4. Test movement commands

### New Item System
1. Extend `Resident` struct with inventory field
2. Implement `inventory.cpp` using `Inventory` class
3. Add inventory view command
4. Link to market system

## Design Patterns Used

- **Singleton** — World, Market, LocationManager
- **RAII** — Automatic mutex locking with `std::lock_guard`
- **Namespace organization** — `herl::`, `herl::commands::`, etc.
- **Thread-safe** — All shared state protected by mutexes
- **Discord++ integration** — Clean wrapper around dpp library

## Testing

Recommended test sequence:
1. Create resident with `/join`
2. Move between locations with `/move`
3. Earn cash with `/work`
4. View profile with `/me`
5. See nearby players with `/here`
6. Fly to airports with `/fly`
7. Multiple users simultaneously

## Common Issues & Solutions

**Bot doesn't respond**: Check DISCORD_TOKEN environment variable
**Commands not showing**: Wait 5-10 minutes for Discord to sync
**Crashes on startup**: Verify dpp library installed via vcpkg
**Multiple bots conflicting**: Use different bot tokens in separate terminals

## Contributing

See CONTRIBUTING.md for guidelines on:
- Code style (C++20, snake_case, UPPER_CONSTANTS)
- Branch naming (feature/*, bugfix/*)
- Commit messages
- Pull request process
