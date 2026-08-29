# Herl — Discord Roleplay Game (C++)

Herl is a multiplayer life-roleplay game for Discord servers. Each player creates a resident, explores shared locations, earns cash through work, and travels by plane between cities.

## Quick Start

### 1. Create a Discord Bot
- Go to [Discord Developer Portal](https://discord.com/developers/applications)
- Create a new application → Add Bot
- Enable scopes: `bot`, `applications.commands`
- Grant permissions: View Channels, Send Messages
- Copy the bot token

### 2. Install & Build

**Windows (PowerShell)**:
```powershell
vcpkg install
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-path>/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
$env:DISCORD_TOKEN = "your-bot-token"
.\build\Release\herl.exe
```

**Linux/macOS (Bash)**:
```bash
./vcpkg/vcpkg install
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
export DISCORD_TOKEN="your-bot-token"
./build/Release/herl
```

### 3. Invite Bot to Server
1. Go to "OAuth2" → "URL Generator" in Developer Portal
2. Select: `bot` + `applications.commands` + `Send Messages`
3. Copy generated URL and open in browser
4. Select your server and authorize

## Gameplay

### Commands

| Command | Description | Example |
|---------|-------------|----------|
| `/join name:Alice` | Create your resident | `Alice` appears in City Centre with $250 |
| `/move place:Harbour District` | Travel to a location | Move to explore different areas |
| `/work` | Earn $75 per shift | `Alice` completes a shift and earns $75 |
| `/fly destination:Sunhaven Airport` | Travel via plane | Costs $120 from Herl International Airport |
| `/me` | View your profile | See location, cash, shifts worked, flights taken |
| `/here` | See who's at your location | Shows other players at same place |
| `/places` | List all locations | City Centre, Harbour District, etc. |
| `/herl` | Display help | Game instructions |

### Locations

- **City Centre** — Main hub
- **Harbour District** — Waterfront commerce
- **Seaside Park** — Recreation area
- **Herl International Airport** — Travel hub (flights: $120)
- **North Hills** — Residential district

## Features

### Current
✅ Multi-guild support — Each Discord server has separate residents
✅ Persistent character stats — Tracks cash, shifts, flights
✅ Location-based gameplay — See other players at same place
✅ Economy system — Earn $75/shift, $120 flight tickets
✅ Thread-safe — Handles multiple players simultaneously

### Planned
🔲 Database persistence — Save game state to SQLite
🔲 Leaderboards — Top earners, frequent travelers
🔲 Inventory system — Buy, sell, trade items
🔲 Points of Interest — Shops, jobs, restaurants in each location
🔲 Admin tools — Operator commands for server management

## Architecture

Herl is built with a modular C++20 architecture:

```
include/herl/
├── world.hpp      # Resident management (World singleton)
├── commands.hpp   # Player commands
├── stats.hpp      # Leaderboards
├── database.hpp   # Persistence (SQLite)
├── location.hpp   # Location management
├── inventory.hpp  # Item system
├── market.hpp     # Economy
└── admin.hpp      # Operator commands
```

See **ARCHITECTURE.md** for design details.
See **BUILD.md** for build instructions.
See **CODE_STRUCTURE.md** for modularization roadmap.

## Contributing

Contributions welcome! See **CONTRIBUTING.md** for:
- Code style (C++20, snake_case)
- Workflow (fork, branch, pull request)
- What to work on (high priority: persistence, modularization)

## License

MIT License — See LICENSE file

## Discord Support

For issues or questions:
- Open an issue on GitHub
- Start a discussion on GitHub
- DM the bot owner

---

**Herl v0.1.0** — A shared life-roleplay world for Discord 🎮
