#pragma once

#include "discordpp.h"
#include <string>
#include <vector>

namespace herl::discord {

/**
 * @brief Represents a Discord friend.
 */
struct DiscordFriend {
    std::string username;
    std::string user_id;
    bool online{false};
};

/**
 * @brief Manages Discord social features for Herl players.
 */
class DiscordSocial {
public:
    /**
     * @brief Get list of player's Discord friends.
     */
    static std::vector<DiscordFriend> get_friends();

    /**
     * @brief Check if a user is friends with another user on Discord.
     */
    static bool is_friend(const std::string& user_id);

    /**
     * @brief Get player's Discord username.
     */
    static std::string get_username();

    /**
     * @brief Get total friend count from Discord.
     */
    static int get_friend_count();

private:
    DiscordSocial() = default;
};

} // namespace herl::discord
