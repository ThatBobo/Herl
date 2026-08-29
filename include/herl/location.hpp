#pragma once

#include <string>
#include <vector>
#include <optional>

namespace herl::location {

/**
 * @brief Represents a point of interest or business in Herl.
 */
struct PointOfInterest {
    std::string name;
    std::string location;
    std::string description;
    int min_interaction_cost{0};
    int max_interaction_reward{0};
};

/**
 * @brief Manages locations and points of interest.
 */
class LocationManager {
public:
    /**
     * @brief Get description of a location.
     */
    static std::string get_location_description(const std::string& location);

    /**
     * @brief Get points of interest in a location.
     */
    static std::vector<PointOfInterest> get_poi(const std::string& location);

    /**
     * @brief Check if a location is valid.
     */
    static bool is_valid_location(const std::string& location);

    /**
     * @brief Get distance between two locations.
     */
    static int get_distance(const std::string& from, const std::string& to);

private:
    LocationManager() = default;
};

} // namespace herl::location
