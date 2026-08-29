#include "herl/world.hpp"
#include "herl/commands.hpp"
#include <dpp/dpp.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

int main() {
    const char* token = std::getenv("DISCORD_TOKEN");
    if (!token || std::string{token}.empty()) {
        std::fprintf(stderr, "DISCORD_TOKEN environment variable is not set.\n");
        return 1;
    }

    try {
        dpp::cluster bot{token, dpp::i_default_intents};
        bot.on_log(dpp::utility::cout_logger());

        // Register all commands on bot ready
        bot.on_ready([&bot](const dpp::ready_t&) {
            herl::commands::register_commands(bot);
        });

        // Handle all slash commands
        bot.on_slashcommand([](const dpp::slashcommand_t& event) {
            herl::commands::handle_command(event);
        });

        std::cout << "Starting Herl bot..." << std::endl;
        bot.start(dpp::st_wait);

    } catch (const std::exception& e) {
        std::fprintf(stderr, "Fatal error: %s\n", e.what());
        return 1;
    }

    return 0;
}
