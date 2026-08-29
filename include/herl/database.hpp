#pragma once

#include <string>
#include <vector>

namespace herl::database {

/**
 * @brief Database interface for persisting game state.
 */
class Database {
public:
    /**
     * @brief Initialize database connection.
     */
    static bool initialize(const std::string& db_path = "herl.db");

    /**
     * @brief Save a resident to database.
     */
    static bool save_resident(const struct herl::Resident& resident);

    /**
     * @brief Load a resident from database.
     */
    static bool load_resident(const std::string& name);

    /**
     * @brief Load all residents from database.
     */
    static bool load_all_residents();

    /**
     * @brief Check if database exists.
     */
    static bool exists(const std::string& db_path = "herl.db");

private:
    Database() = default;
};

} // namespace herl::database
