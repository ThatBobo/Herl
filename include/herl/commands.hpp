#pragma once

#include <dpp/dpp.h>

namespace herl::commands {

/**
 * @brief Register all slash commands with the bot.
 */
void register_commands(dpp::cluster& bot);

/**
 * @brief Handle slash command events.
 */
void handle_command(const dpp::slashcommand_t& event);

} // namespace herl::commands
