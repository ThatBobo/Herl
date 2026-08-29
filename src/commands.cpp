#include "herl/commands.hpp"
#include "herl/world.hpp"
#include <format>
#include <vector>
#include <algorithm>

namespace herl::commands {

void register_commands(dpp::cluster& bot) {
    if (!dpp::run_once<struct register_commands>()) return;

    // /join command
    auto join = dpp::slashcommand{"join", "Create your Herl resident", 0};
    join.add_option(dpp::command_option{dpp::co_string, "name", "Your roleplay name", true});
    bot.global_command_create(join);

    // /move command
    auto move = dpp::slashcommand{"move", "Move to another place in Herl", 0};
    dpp::command_option location_opt{dpp::co_string, "place", "Where to go in Herl", true};
    for (const auto& place : World::CITY_LOCATIONS) {
        location_opt.add_choice(dpp::command_option_choice{std::string(place), std::string(place)});
    }
    move.add_option(location_opt);
    bot.global_command_create(move);

    // /work command
    bot.global_command_create(dpp::slashcommand{"work", "Work a shift and earn cash", 0});

    // /fly command
    auto fly = dpp::slashcommand{"fly", "Fly from Herl International Airport", 0};
    fly.add_option(dpp::command_option{dpp::co_string, "destination", "Choose a destination", true}
        .add_choice(dpp::command_option_choice{"Sunhaven Airport", "Sunhaven Airport"})
        .add_choice(dpp::command_option_choice{"Port Azure Airport", "Port Azure Airport"}));
    bot.global_command_create(fly);

    // /me command
    bot.global_command_create(dpp::slashcommand{"me", "See your resident profile", 0});

    // /here command
    bot.global_command_create(dpp::slashcommand{"here", "See residents at your current place", 0});

    // /places command
    bot.global_command_create(dpp::slashcommand{"places", "List locations you can move to", 0});

    // /herl command (help)
    bot.global_command_create(dpp::slashcommand{"herl", "See how to play Herl", 0});
}

void handle_command(const dpp::slashcommand_t& event) {
    const auto action = event.command.get_command_name();
    const auto user_id = event.command.usr.id;
    const auto guild_id = event.command.guild_id;
    auto& world = World::instance();

    // Help command
    if (action == "herl") {
        event.reply("**Welcome to Herl** — a shared-life roleplay world. Create a resident with `/join`, "
                   "visit places with `/move`, work shifts, and fly from the airport. "
                   "Use `/me` to see your profile and `/here` to see who's around.");
        return;
    }

    // Places command
    if (action == "places") {
        std::string places;
        for (size_t i = 0; i < World::CITY_LOCATIONS.size(); ++i) {
            places += World::CITY_LOCATIONS[i];
            if (i < World::CITY_LOCATIONS.size() - 1) places += " · ";
        }
        event.reply(std::format("**Places in Herl**\n{}", places));
        return;
    }

    // Join command
    if (action == "join") {
        try {
            const auto name = std::get<std::string>(event.get_parameter("name"));
            if (name.size() < 2 || name.size() > 24) {
                event.reply(dpp::message{"Choose a name between 2 and 24 characters."}.set_flags(dpp::m_ephemeral));
                return;
            }
            auto& resident = world.get_or_create_resident(user_id, guild_id, name);
            event.reply(std::format("Welcome to **Herl**, {}! You arrive in **City Centre** with **${}**. Use `/move` to explore.",
                                  resident.name, resident.cash));
        } catch (const std::exception& e) {
            event.reply(dpp::message{"Error creating resident."}.set_flags(dpp::m_ephemeral));
        }
        return;
    }

    // All other commands require an existing resident
    auto* resident = world.find_resident(user_id, guild_id);
    if (!resident) {
        event.reply(dpp::message{"Create your Herl resident first with `/join`."}.set_flags(dpp::m_ephemeral));
        return;
    }

    // Move command
    if (action == "move") {
        try {
            const auto place = std::get<std::string>(event.get_parameter("place"));
            resident->location = place;
            event.reply(std::format("**{}** arrives at **{}**. Use `/here` to see who is around.",
                                  resident->name, resident->location));
        } catch (const std::exception& e) {
            event.reply(dpp::message{"Error moving to location."}.set_flags(dpp::m_ephemeral));
        }
        return;
    }

    // Work command
    if (action == "work") {
        resident->shifts++;
        resident->cash += World::SHIFT_EARNINGS;
        event.reply(std::format("**{}** completes a shift and earns **${}**. Balance: **${}**.",
                              resident->name, World::SHIFT_EARNINGS, resident->cash));
        return;
    }

    // Fly command
    if (action == "fly") {
        if (resident->location != "Herl International Airport") {
            event.reply(dpp::message{"You need to be at **Herl International Airport**. Use `/move` first."}.set_flags(dpp::m_ephemeral));
            return;
        }
        if (resident->cash < World::FLIGHT_COST) {
            event.reply(dpp::message{std::format("A ticket costs **${}**. Work a shift with `/work` first.", World::FLIGHT_COST)}.set_flags(dpp::m_ephemeral));
            return;
        }
        try {
            const auto destination = std::get<std::string>(event.get_parameter("destination"));
            resident->cash -= World::FLIGHT_COST;
            resident->location = destination;
            resident->flights++;
            event.reply(std::format("✈️ **{}** boards a flight to **{}**. Ticket: ${}. Balance: **${}**.",
                                  resident->name, destination, World::FLIGHT_COST, resident->cash));
        } catch (const std::exception& e) {
            event.reply(dpp::message{"Error booking flight."}.set_flags(dpp::m_ephemeral));
        }
        return;
    }

    // Me command
    if (action == "me") {
        event.reply(std::format("**{}'s Herl life**\nLocation: **{}**\nCash: **${}**\nShifts: **{}** · Flights: **{}**",
                              resident->name, resident->location, resident->cash, resident->shifts, resident->flights));
        return;
    }

    // Here command
    if (action == "here") {
        auto names = world.get_residents_at_location(guild_id, resident->location);
        std::string nearby;
        for (size_t i = 0; i < names.size(); ++i) {
            nearby += (i ? ", " : "") + names[i];
        }
        event.reply(std::format("**{}** at **{}**\n{}",
                              names.size(), resident->location, nearby.empty() ? "(No one here)" : nearby));
        return;
    }
}

} // namespace herl::commands
