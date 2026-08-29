#pragma once

#include <string>
#include <vector>

namespace herl::market {

/**
 * @brief Represents an item available for purchase in the market.
 */
struct MarketItem {
    std::string id;
    std::string name;
    int price{0};
    int stock{0};
    std::string description;
};

/**
 * @brief Manages in-game market and prices.
 */
class Market {
public:
    /**
     * @brief Get all available items in market.
     */
    static std::vector<MarketItem> get_available_items();

    /**
     * @brief Get market items by category.
     */
    static std::vector<MarketItem> get_items_by_category(const std::string& category);

    /**
     * @brief Purchase an item.
     */
    static bool purchase_item(const std::string& item_id, int quantity = 1);

    /**
     * @brief Get item price.
     */
    static int get_item_price(const std::string& item_id);

    /**
     * @brief Check stock availability.
     */
    static bool is_in_stock(const std::string& item_id, int quantity = 1);

private:
    Market() = default;
};

} // namespace herl::market
