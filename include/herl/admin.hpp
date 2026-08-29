#pragma once

#include <string>
#include <vector>
#include <dpp/dpp.h>

namespace herl::admin {

/**
 * @brief Admin commands for server operators.
 */
class AdminCommands {
public:
    /**
     * @brief Register admin commands with the bot.
     */
    static void register_commands(dpp::cluster& bot);

    /**
     * @brief Handle admin command events.
     */
    static void handle_command(const dpp::slashcommand_t& event);

    /**
     * @brief Check if user has admin permissions.
     */
    static bool is_admin(dpp::snowflake user_id);

private:
    AdminCommands() = default;
};

} // namespace herl::admin
