#pragma once

#include <string>
#include <vector>
#include <memory>

namespace herl::inventory {

/**
 * @brief Represents an item in a resident's inventory.
 */
struct Item {
    std::string id;
    std::string name;
    std::string description;
    int value{0};
    int quantity{1};
};

/**
 * @brief Manages resident inventory.
 */
class Inventory {
public:
    /**
     * @brief Add an item to inventory.
     */
    void add_item(const Item& item);

    /**
     * @brief Remove an item from inventory.
     */
    bool remove_item(const std::string& item_id, int quantity = 1);

    /**
     * @brief Get an item from inventory.
     */
    Item* get_item(const std::string& item_id);

    /**
     * @brief Get all items.
     */
    const std::vector<Item>& get_all_items() const { return items; }

    /**
     * @brief Calculate total inventory value.
     */
    int get_total_value() const;

private:
    std::vector<Item> items;
};

} // namespace herl::inventory
