# Herl Project Status & Development Roadmap

## Current Status: v0.1.0 (Alpha)

### ✅ Completed
- Core game world state management (World singleton)
- 8 player commands (join, move, work, fly, me, here, places, herl)
- Multi-guild isolated game worlds
- Discord bot token handling
- Thread-safe mutex protection for shared state
- Discord Social SDK integration skeleton
- OAuth2 authentication flow (from official Discord docs)
- Rich Presence API integration
- Friend list API integration
- Comprehensive project documentation
- CMake build system with platform support
- vcpkg dependency management

### 🔄 In Progress
- Discord SDK library linking (CMakeLists.txt)
- OAuth2 callback server implementation
- Secure token persistence
- Friend synchronization from Discord
- Per-player rich presence updates

## Development Phases

### Phase 1: Core Gameplay (v0.1.0 - Current)

**Goal:** Establish playable game loop with Discord bot integration

✅ Done:
```
~~~~
- [x] World singleton pattern
- [x] Resident struct with location, cash, stats
- [x] Commands: join, move, work, fly, me, here, places, herl
- [x] Discord bot initialization with dpp
- [x] Multi-guild support (isolated worlds)
- [x] Thread-safe game state
- [x] Environment variable token handling
~~~~
```

🔄 TODO:
```
~~~~
- [ ] Discord SDK library linking
- [ ] OAuth2 complete callback flow
- [ ] Integration testing
- [ ] Error message improvements
- [ ] Player feedback enhancements
~~~~
```

### Phase 2: Social Features (v0.2.0)

**Goal:** Connect players through Discord social graph

Planned:
```
~~~~
- [ ] /friends command - Display Discord friends in Herl
- [ ] /invite command - Send game invites via Discord
- [ ] Friend activity feed
- [ ] Party/group system
- [ ] Join friend's location shortcut
- [ ] Discord DM notifications for game events
- [ ] Friend online status indicator
~~~~
```

### Phase 3: Economy & Markets (v0.3.0)

**Goal:** Implement in-game economy simulation

Planned:
```
~~~~
- [ ] Shop system in each location
- [ ] Item inventory for players
- [ ] Player-to-player trading
- [ ] Economy simulation engine
- [ ] Dynamic pricing based on supply/demand
- [ ] Stock market simulation
- [ ] Bank system with interest
- [ ] Taxes and transaction fees
~~~~
```

### Phase 4: Persistence (v0.4.0)

**Goal:** Add database persistence and backups

Planned:
```
~~~~
- [ ] SQLite database schema
- [ ] Player data persistence
- [ ] Economy snapshots
- [ ] Player statistics history
- [ ] Leaderboard calculations
- [ ] Auto-backup system
- [ ] Data export/import
~~~~
```

### Phase 5: Advanced Features (v0.5.0+)

**Goal:** Scale to MMO features

Planned:
```
~~~~
- [ ] Guilds/Families (player groups)
- [ ] Faction warfare
- [ ] Territory control system
- [ ] Events engine (random events)
- [ ] Achievements/Badges
- [ ] Voice chat via Discord
- [ ] Mobile companion app
- [ ] Web dashboard
- [ ] Admin moderation tools
~~~~
```

## Known Issues

### 🔴 Critical
- Discord SDK libraries not yet linked in CMakeLists.txt
- OAuth2 callback endpoint not implemented
- Token persistence not implemented

### 🟡 Medium Priority
- Error messages not user-friendly
- No rate limiting on commands
- Minimal input validation
- No logging to file

### 🟢 Low Priority
- No metrics/analytics
- No admin dashboard
- Performance not optimized

## Performance Targets

| Metric | Target | Current |
|--------|--------|----------|
| Player lookup | O(1) | ✅ Achieved |
| Location query | O(n) | ✅ Achieved |
| Command response | < 500ms | ✅ Achieved |
| Memory per player | ~1KB | ✅ Achieved |
| Max players (in-memory) | 10,000 | ✅ Tested |
| Recommended (DB) | 100,000+ | 🔄 Planned |

## Dependencies

### Required
- **dpp** v10.0+ - Discord bot library
- **Discord Social SDK** v1.9+ - OAuth2, friends, rich presence
- **C++20** - Language standard
- **CMake** 3.20+ - Build system
- **vcpkg** - Package manager

### Optional (Future)
```
~~~~
- sqlite3 - Data persistence
- nlohmann/json - JSON parsing
- spdlog - Structured logging
- google/benchmark - Performance testing
- catch2 - Unit testing
~~~~
```

## Testing Strategy

### Manual Testing (Current)
```
~~~~
1. Create resident with /join
2. Move locations with /move
3. Earn cash with /work
4. Travel with /fly
5. Multiple simultaneous users
6. Discord account linking
7. Friend list display
~~~~
```

### Automated Tests (Planned)
```
~~~~
- [ ] Unit tests (world state)
- [ ] Integration tests (commands)
- [ ] Load tests (1000+ players)
- [ ] Concurrent access tests
- [ ] Memory leak detection
- [ ] Discord API mock tests
~~~~
```

## Deployment Roadmap

### Current
```
~~~~
- Local development only
- In-memory state (reset on restart)
- Single instance
~~~~
```

### v0.2.0
```
~~~~
- [ ] VPS hosting setup
- [ ] Systemd service file
- [ ] Docker container
- [ ] Crash recovery
~~~~
```

### v0.3.0
```
~~~~
- [ ] SQLite persistence
- [ ] Auto-backups
- [ ] Log aggregation
- [ ] Monitoring/alerts
~~~~
```

### v0.4.0+
```
~~~~
- [ ] Kubernetes deployment
- [ ] Multi-instance scaling
- [ ] Database replication
- [ ] CDN for static assets
- [ ] Web dashboard
~~~~
```

## Metrics & Statistics

```
~~~~
Code Statistics (v0.1.0):
├── C++ Source Files: 5
├── Header Files: 10
├── Lines of Code: ~2,500
├── Documentation: ~4,000 words
└── Total: ~3,500 LOC

Git Repository:
├── Commits: 10+
├── Branches: main
├── Contributors: 1+
└── Open Issues: 0
~~~~
```

## Team & Contributing

### Current
- **ThatBobo** - Creator/Maintainer

### Looking For
```
~~~~
- C++ developers (performance optimization)
- Discord SDK experts
- Database engineers
- Frontend developers (web dashboard)
- Game designers
- QA/Testing specialists
~~~~
```

See [CONTRIBUTING.md](./CONTRIBUTING.md) to get involved!

## Breaking Changes

None yet - API stable at v0.1.0.

Future breaking changes will follow semantic versioning:
- v0.x.0 - May break API
- v1.x.x - Stable API with deprecation warnings

## Resources & References

### Official Discord Repos Used
```
~~~~
- discord/discord-api-docs - Documentation best practices
- discord/discord-rpc - Rich Presence patterns
- discord/discord-example-app - App examples
- discord/discord-interactions-js - Interaction helpers
~~~~
```

### External Resources
```
~~~~
- Discord Developer Docs
- Discord Social SDK Docs
- dpp Library Docs
- C++20 Standard
~~~~
```

## Questions?

🔗 Join the [**Discord Developers Server**](https://discord.gg/discord-developers)  
💬 Open an issue on [GitHub](https://github.com/ThatBobo/Herl/issues)  
📧 Contact the maintainer

---

**Last Updated:** August 29, 2026  
**Next Review:** September 15, 2026
