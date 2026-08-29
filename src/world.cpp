#include "herl/world.hpp"
#include <algorithm>

namespace herl {

World& World::instance() {
    static World world;
    return world;
}

Resident& World::get_or_create_resident(dpp::snowflake user_id, dpp::snowflake guild_id, const std::string& name) {
    std::lock_guard lock{world_mutex};
    auto& resident = residents[user_id];
    if (resident.name.empty()) {
        resident.guild_id = guild_id;
        resident.name = name;
        resident.location = "City Centre";
        resident.cash = STARTING_CASH;
        resident.flights = 0;
        resident.shifts = 0;
    }
    return resident;
}

Resident* World::find_resident(dpp::snowflake user_id, dpp::snowflake guild_id) {
    std::lock_guard lock{world_mutex};
    auto it = residents.find(user_id);
    if (it == residents.end() || it->second.guild_id != guild_id) {
        return nullptr;
    }
    return &it->second;
}

std::vector<std::string> World::get_residents_at_location(dpp::snowflake guild_id, const std::string& location) {
    std::lock_guard lock{world_mutex};
    std::vector<std::string> names;
    for (const auto& [_, resident] : residents) {
        if (resident.guild_id == guild_id && resident.location == location) {
            names.push_back(resident.name);
        }
    }
    std::ranges::sort(names);
    return names;
}

std::vector<Resident*> World::get_guild_residents(dpp::snowflake guild_id) {
    std::lock_guard lock{world_mutex};
    std::vector<Resident*> result;
    for (auto& [_, resident] : residents) {
        if (resident.guild_id == guild_id) {
            result.push_back(&resident);
        }
    }
    return result;
}

} // namespace herl
