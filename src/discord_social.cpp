#include "herl/discord_social.hpp"
#include "herl/discord_integration.hpp"
#include <algorithm>

namespace herl::discord {

std::vector<DiscordFriend> DiscordSocial::get_friends() {
    auto client = DiscordIntegration::get_client();
    if (!client) return std::vector<DiscordFriend>();
    
    std::vector<DiscordFriend> herl_friends;
    
    // Get relationships from Discord SDK
    auto relationships = client->GetRelationships();
    
    for (const auto& relationship : relationships) {
        DiscordFriend friend_info;
        friend_info.username = relationship.User().Username();
        friend_info.user_id = std::to_string(relationship.User().Id());
        friend_info.online = relationship.User().IsActive();
        herl_friends.push_back(friend_info);
    }
    
    return herl_friends;
}

bool DiscordSocial::is_friend(const std::string& user_id) {
    auto friends = get_friends();
    return std::any_of(friends.begin(), friends.end(),
        [&user_id](const DiscordFriend& f) { return f.user_id == user_id; });
}

std::string DiscordSocial::get_username() {
    auto client = DiscordIntegration::get_client();
    if (!client) return "UnknownUser";
    
    try {
        return client->GetUser().Username();
    } catch (...) {
        return "UnknownUser";
    }
}

int DiscordSocial::get_friend_count() {
    return DiscordIntegration::get_friend_count();
}

} // namespace herl::discord
