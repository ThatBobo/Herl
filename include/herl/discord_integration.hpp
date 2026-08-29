#pragma once

#include "discordpp.h"
#include <cstdint>
#include <string>
#include <memory>
#include <functional>
#include <thread>
#include <atomic>

namespace herl::discord {

/**
 * @brief Discord Social SDK integration for Herl game.
 * Uses official Discord++ library for authentication, friends, and rich presence.
 */
class DiscordIntegration {
public:
    // Discord Application ID for Herl
    static constexpr uint64_t APPLICATION_ID = 1349146942634065960;

    /**
     * @brief Initialize Discord SDK and set up callbacks.
     */
    static bool initialize();

    /**
     * @brief Authenticate player with Discord via OAuth2.
     */
    static void authenticate();

    /**
     * @brief Get player's Discord friend count.
     */
    static int get_friend_count();

    /**
     * @brief Update rich presence showing player activity.
     */
    static void update_presence(const std::string& state, const std::string& details);

    /**
     * @brief Check if Discord is connected and ready.
     */
    static bool is_ready();

    /**
     * @brief Process Discord SDK callbacks (call in main game loop).
     */
    static void update();

    /**
     * @brief Disconnect from Discord.
     */
    static void shutdown();

    /**
     * @brief Get the Discord client instance.
     */
    static std::shared_ptr<discordpp::Client> get_client();

private:
    DiscordIntegration() = default;
    
    static std::shared_ptr<discordpp::Client> client;
    static bool initialized;
    static std::atomic<bool> ready;
    
    // OAuth2 code verifier
    static discordpp::CodeVerifier code_verifier;
};

} // namespace herl::discord
