#include <dpp/dpp.h>
#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
constexpr int flight_cost = 120;
const std::array<std::string, 5> city_locations{"City Centre", "Harbour District", "Seaside Park", "Herl International Airport", "North Hills"};
struct Resident { dpp::snowflake guild_id{}; std::string name; std::string location{"City Centre"}; int cash{250}; int flights{}; int shifts{}; };
std::unordered_map<dpp::snowflake, Resident> residents;
std::mutex world_mutex;

dpp::slashcommand command(std::string name, std::string description) { return dpp::slashcommand{name, description, 0}; }
dpp::command_option location_option() {
    dpp::command_option option{dpp::co_string, "place", "Where to go in Herl", true};
    for (const auto& place : city_locations) option.add_choice(dpp::command_option_choice{place, place});
    return option;
}
} // namespace

int main() {
    const char* token = std::getenv("DISCORD_TOKEN");
    if (!token || std::string{token}.empty()) { std::fprintf(stderr, "DISCORD_TOKEN is not set.\n"); return 1; }

    dpp::cluster bot{token, dpp::i_default_intents};
    bot.on_log(dpp::utility::cout_logger());
    bot.on_ready([&bot](const dpp::ready_t&) {
        if (dpp::run_once<struct register_commands>()) {
            auto join = command("join", "Create your Herl resident");
            join.add_option(dpp::command_option{dpp::co_string, "name", "Your roleplay name", true});
            auto move = command("move", "Move to another place in Herl"); move.add_option(location_option());
            auto fly = command("fly", "Fly from Herl International Airport");
            fly.add_option(dpp::command_option{dpp::co_string, "destination", "Choose a destination", true}
                .add_choice(dpp::command_option_choice{"Sunhaven Airport", "Sunhaven Airport"})
                .add_choice(dpp::command_option_choice{"Port Azure Airport", "Port Azure Airport"}));
            bot.global_command_create(join); bot.global_command_create(command("herl", "See how to play Herl"));
            bot.global_command_create(move); bot.global_command_create(fly);
            bot.global_command_create(command("work", "Work a shift and earn cash"));
            bot.global_command_create(command("me", "See your resident profile"));
            bot.global_command_create(command("here", "See residents at your current place"));
            bot.global_command_create(command("places", "List locations you can move to"));
        }
    });

    bot.on_slashcommand([&](const dpp::slashcommand_t& event) {
        const auto action = event.command.get_command_name();
        const auto user_id = event.command.usr.id;
        const auto guild_id = event.command.guild_id;
        if (action == "herl") { event.reply("**Welcome to Herl** — a shared-life roleplay world. Create a resident with `/join`, visit places with `/move`, work shifts, and fly from the airport. Use `/here` to meet other residents."); return; }
        if (action == "places") { event.reply("**Places in Herl**\nCity Centre · Harbour District · Seaside Park · Herl International Airport · North Hills"); return; }
        if (action == "join") {
            const auto name = std::get<std::string>(event.get_parameter("name"));
            if (name.size() < 2 || name.size() > 24) { event.reply(dpp::message{"Choose a name between 2 and 24 characters."}.set_flags(dpp::m_ephemeral)); return; }
            std::lock_guard lock{world_mutex}; residents[user_id] = Resident{guild_id, name};
            event.reply(std::format("Welcome to **Herl**, {}! You arrive in **City Centre** with **$250**. Use `/move` to explore.", name)); return;
        }
        std::lock_guard lock{world_mutex};
        const auto resident = residents.find(user_id);
        if (resident == residents.end() || resident->second.guild_id != guild_id) { event.reply(dpp::message{"Create your Herl resident here first with `/join`."}.set_flags(dpp::m_ephemeral)); return; }
        auto& player = resident->second;
        if (action == "move") {
            player.location = std::get<std::string>(event.get_parameter("place"));
            event.reply(std::format("**{}** arrives at **{}**. Use `/here` to see who is around.", player.name, player.location));
        } else if (action == "work") {
            ++player.shifts; player.cash += 75;
            event.reply(std::format("**{}** completes a shift and earns **$75**. Balance: **${}**.", player.name, player.cash));
        } else if (action == "fly") {
            if (player.location != "Herl International Airport") { event.reply(dpp::message{"You need to be at **Herl International Airport**. Use `/move` first."}.set_flags(dpp::m_ephemeral)); return; }
            if (player.cash < flight_cost) { event.reply(dpp::message{"A ticket costs **$120**. Work a shift with `/work` first."}.set_flags(dpp::m_ephemeral)); return; }
            const auto destination = std::get<std::string>(event.get_parameter("destination"));
            player.cash -= flight_cost; player.location = destination; ++player.flights;
            event.reply(std::format("✈️ **{}** boards a flight to **{}**. Ticket: $120. Balance: **${}**.", player.name, destination, player.cash));
        } else if (action == "me") {
            event.reply(std::format("**{}'s Herl life**\nLocation: **{}**\nCash: **${}**\nShifts: **{}** · Flights: **{}**", player.name, player.location, player.cash, player.shifts, player.flights));
        } else if (action == "here") {
            std::vector<std::string> names;
            for (const auto& [_, other] : residents) if (other.guild_id == guild_id && other.location == player.location) names.push_back(other.name);
            std::ranges::sort(names); std::string nearby;
            for (std::size_t i = 0; i < names.size(); ++i) nearby += (i ? ", " : "") + names[i];
            event.reply(std::format("**{}** at **{}**\n{}", names.size(), player.location, nearby));
        }
    });
    bot.start(dpp::st_wait);
}

