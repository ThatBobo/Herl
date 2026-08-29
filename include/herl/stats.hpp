#pragma once

#include <string>
#include <vector>
#include <ctime>

namespace herl {

/**
 * @brief Statistics for a resident.
 */
struct ResidentStats {
    int total_earnings{0};
    int total_distance{0};
    std::time_t last_worked{};
    int current_streak{0};
};

/**
 * @brief Leaderboard entry.
 */
struct LeaderboardEntry {
    std::string name;
    int score{0};
    int rank{0};
};

/**
 * @brief Manages game statistics and leaderboards.
 */
class Stats {
public:
    /**
     * @brief Record earnings for a resident.
     */
    static void add_earnings(const std::string& resident_name, int amount);

    /**
     * @brief Record travel distance.
     */
    static void add_travel(const std::string& resident_name, int distance);

    /**
     * @brief Get top earners leaderboard.
     */
    static std::vector<LeaderboardEntry> get_top_earners(int limit = 10);

    /**
     * @brief Get top travelers leaderboard.
     */
    static std::vector<LeaderboardEntry> get_top_travelers(int limit = 10);

private:
    Stats() = default;
};

} // namespace herl
