#include "herl/world.hpp"
#include "herl/commands.hpp"
#include <dpp/dpp.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

int main() {
    std::cout << "🎮 Herl - Discord Roleplay Game" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << std::endl;

    // Get token from environment variable
    const char* token = std::getenv("DISCORD_TOKEN");
    if (!token || std::string{token}.empty()) {
        std::fprintf(stderr, "💥 Error: DISCORD_TOKEN environment variable not set\n");
        std::fprintf(stderr, "\nSet it before running Herl:\n");
        std::fprintf(stderr, "  Linux/macOS: export DISCORD_TOKEN=your_token\n");
        std::fprintf(stderr, "  Windows:     set DISCORD_TOKEN=your_token\n");
        return 1;
    }

    try {
        std::cout << "✅ Token loaded" << std::endl;
        std::cout << "🔌 Connecting to Discord..." << std::endl;
        std::cout << std::endl;

        dpp::cluster bot{token, dpp::i_default_intents};
        bot.on_log(dpp::utility::cout_logger());

        // Register all commands on bot ready
        bot.on_ready([&bot](const dpp::ready_t&) {
            std::cout << "\n✅ Bot is ready!" << std::endl;
            std::cout << "📝 Registering commands..." << std::endl;
            herl::commands::register_commands(bot);
        });

        // Handle all slash commands
        bot.on_slashcommand([](const dpp::slashcommand_t& event) {
            herl::commands::handle_command(event);
        });

        std::cout << "🚀 Starting Herl bot..." << std::endl;
        bot.start(dpp::st_wait);

    } catch (const std::exception& e) {
        std::fprintf(stderr, "💥 Fatal error: %s\n", e.what());
        return 1;
    }

    return 0;
}
