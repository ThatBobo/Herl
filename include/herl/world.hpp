#pragma once

#include <dpp/dpp.h>
#include <string>
#include <unordered_map>
#include <mutex>
#include <array>

namespace herl {

/**
 * @brief Represents a player's resident in Herl.
 */
struct Resident {
    dpp::snowflake guild_id{};
    std::string name;
    std::string location{"City Centre"};
    int cash{250};
    int flights{};
    int shifts{};
};

/**
 * @brief Manages the Herl game world state.
 * Thread-safe singleton that tracks all residents and their properties.
 */
class World {
public:
    static constexpr int STARTING_CASH = 250;
    static constexpr int FLIGHT_COST = 120;
    static constexpr int SHIFT_EARNINGS = 75;
    static constexpr std::array<std::string_view, 5> CITY_LOCATIONS{
        "City Centre",
        "Harbour District",
        "Seaside Park",
        "Herl International Airport",
        "North Hills"
    };

    /**
     * @brief Get the singleton instance.
     */
    static World& instance();

    /**
     * @brief Create or retrieve a resident.
     */
    Resident& get_or_create_resident(dpp::snowflake user_id, dpp::snowflake guild_id, const std::string& name);

    /**
     * @brief Find a resident by user ID.
     * @return Pointer to resident, or nullptr if not found.
     */
    Resident* find_resident(dpp::snowflake user_id, dpp::snowflake guild_id);

    /**
     * @brief Get all residents in a location within a guild.
     */
    std::vector<std::string> get_residents_at_location(dpp::snowflake guild_id, const std::string& location);

    /**
     * @brief Get all residents in a guild.
     */
    std::vector<Resident*> get_guild_residents(dpp::snowflake guild_id);

private:
    World() = default;
    ~World() = default;

    // Deleted copy and move constructors
    World(const World&) = delete;
    World& operator=(const World&) = delete;
    World(World&&) = delete;
    World& operator=(World&&) = delete;

    std::unordered_map<dpp::snowflake, Resident> residents;
    std::mutex world_mutex;
};

} // namespace herl
