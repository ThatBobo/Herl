#define DISCORDPP_IMPLEMENTATION
#include "herl/discord_integration.hpp"
#include "herl/world.hpp"
#include <iostream>
#include <format>

namespace herl::discord {

std::shared_ptr<discordpp::Client> DiscordIntegration::client = nullptr;
bool DiscordIntegration::initialized = false;
std::atomic<bool> DiscordIntegration::ready = false;
discordpp::CodeVerifier DiscordIntegration::code_verifier;

bool DiscordIntegration::initialize() {
    if (initialized) return true;
    
    std::cout << "🚀 Initializing Discord SDK...\n";
    
    try {
        // Create Discord client
        client = std::make_shared<discordpp::Client>();
        
        // Set up logging callback
        client->AddLogCallback([](auto message, auto severity) {
            std::cout << "[Discord] [" << discordpp::Client::SeverityToString(severity) << "] " << message << std::endl;
        }, discordpp::LoggingSeverity::Info);
        
        // Set up status callback
        client->SetStatusChangedCallback([](discordpp::Client::Status status, discordpp::Client::Error error, int32_t errorDetail) {
            std::cout << "🔄 Discord Status: " << discordpp::Client::StatusToString(status) << std::endl;
            
            if (status == discordpp::Client::Status::Ready) {
                ready.store(true);
                std::cout << "✅ Discord Client is ready!\n";
                
                // Display friend count
                auto client = DiscordIntegration::get_client();
                if (client) {
                    auto friend_count = client->GetRelationships().size();
                    std::cout << "👥 Friends Count: " << friend_count << std::endl;
                }
            } else if (error != discordpp::Client::Error::None) {
                std::cerr << "❌ Discord Error: " << discordpp::Client::ErrorToString(error) 
                          << " (Details: " << errorDetail << ")" << std::endl;
                ready.store(false);
            }
        });
        
        initialized = true;
        std::cout << "✅ Discord SDK initialized\n";
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Discord initialization failed: " << e.what() << std::endl;
        return false;
    }
}

void DiscordIntegration::authenticate() {
    if (!client) {
        std::cerr << "❌ Discord client not initialized" << std::endl;
        return;
    }
    
    std::cout << "🔐 Starting Discord OAuth2 authentication...\n";
    
    // Generate code verifier for PKCE security
    code_verifier = client->CreateAuthorizationCodeVerifier();
    
    // Set up authorization arguments
    discordpp::AuthorizationArgs args{};
    args.SetClientId(APPLICATION_ID);
    args.SetScopes(discordpp::Client::GetDefaultPresenceScopes());
    args.SetCodeChallenge(code_verifier.Challenge());
    
    // Begin OAuth2 authorization flow
    client->Authorize(args, [](auto result, auto code, auto redirectUri) {
        if (!result.Successful()) {
            std::cerr << "❌ Authorization failed: " << result.Error() << std::endl;
            return;
        }
        
        std::cout << "✅ Authorization successful! Exchanging code for token...\n";
        
        // Exchange auth code for access token
        auto client = DiscordIntegration::get_client();
        if (!client) return;
        
        client->GetToken(APPLICATION_ID, code, DiscordIntegration::code_verifier.Verifier(), redirectUri,
            [](discordpp::ClientResult result,
               std::string accessToken,
               std::string refreshToken,
               discordpp::AuthorizationTokenType tokenType,
               int32_t expiresIn,
               std::string scope) {
                
                if (!result.Successful()) {
                    std::cerr << "❌ Token exchange failed" << std::endl;
                    return;
                }
                
                std::cout << "🔓 Access token received! Establishing connection...\n";
                
                auto client = DiscordIntegration::get_client();
                if (!client) return;
                
                // Update token and connect
                client->UpdateToken(discordpp::AuthorizationTokenType::Bearer, accessToken, 
                    [](discordpp::ClientResult result) {
                        if (result.Successful()) {
                            std::cout << "🔑 Token updated, connecting to Discord...\n";
                            auto client = DiscordIntegration::get_client();
                            if (client) {
                                client->Connect();
                            }
                        } else {
                            std::cerr << "❌ Token update failed" << std::endl;
                        }
                    });
            });
    });
}

int DiscordIntegration::get_friend_count() {
    if (!client || !ready.load()) return 0;
    return client->GetRelationships().size();
}

void DiscordIntegration::update_presence(const std::string& state, const std::string& details) {
    if (!client || !ready.load()) return;
    
    // Configure rich presence activity
    discordpp::Activity activity;
    activity.SetType(discordpp::ActivityTypes::Playing);
    activity.SetState(state);
    activity.SetDetails(details);
    
    // Update rich presence
    client->UpdateRichPresence(activity, [](discordpp::ClientResult result) {
        if (result.Successful()) {
            std::cout << "🎮 Rich Presence updated!\n";
        } else {
            std::cerr << "❌ Rich Presence update failed\n";
        }
    });
}

bool DiscordIntegration::is_ready() {
    return initialized && ready.load() && client != nullptr;
}

void DiscordIntegration::update() {
    if (!client) return;
    // Process all pending Discord callbacks
    discordpp::RunCallbacks();
}

void DiscordIntegration::shutdown() {
    if (client) {
        std::cout << "🔌 Disconnecting from Discord...\n";
        client.reset();
    }
    initialized = false;
    ready.store(false);
    std::cout << "✅ Discord SDK shutdown\n";
}

std::shared_ptr<discordpp::Client> DiscordIntegration::get_client() {
    return client;
}

} // namespace herl::discord
