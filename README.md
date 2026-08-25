# Herl — Discord Roleplay Game (C++)

Herl is a multiplayer life-roleplay game for a Discord server. Each player creates a resident, explores shared locations, earns cash through work, and travels by plane from Herl International Airport.

## Current game loop

1. `/join name:<roleplay name>` — create your resident with $250.
2. `/move place:<location>` — explore Herl's five locations.
3. `/work` — earn $75.
4. Move to **Herl International Airport**, then use `/fly` to visit Sunhaven or Port Azure.
5. `/here` shows other players roleplaying at the same location.

Use `/me`, `/places`, and `/herl` for your profile, locations, and help.

This is multiplayer within a Discord server, but it is a text-based social world rather than a live 3D game. The current in-memory world resets when the bot stops; the natural next feature is SQLite saving, followed by homes, vehicles, shops, jobs, and interactive map/buttons.

## Discord setup

Create a bot application in the Discord Developer Portal. Enable the `bot` and `applications.commands` installation scopes. Grant only **View Channels** and **Send Messages**; do not grant Administrator.

Set the secret bot token in your terminal only:

```powershell
$env:DISCORD_TOKEN = "your-bot-token"
```

Never commit or paste this token.

## Build on Windows

Install a C++20 compiler, CMake, and [vcpkg](https://github.com/microsoft/vcpkg). Then:

```powershell
vcpkg install
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
.\build\Release\herl.exe
```

## GitHub access

Log in with `gh auth login` once GitHub CLI is installed. If you use a fine-grained personal access token, restrict it to this repository and give **Contents: Read and write** only. No account-wide or Administrator access is needed.

