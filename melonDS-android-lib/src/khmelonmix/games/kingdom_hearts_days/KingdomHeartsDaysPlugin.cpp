#include "KingdomHeartsDaysPlugin.h"

namespace KHMelonMix
{

std::string KingdomHeartsDaysPlugin::GetName() const
{
    return "Kingdom Hearts 358/2 Days";
}

bool KingdomHeartsDaysPlugin::SupportsGame(const GameIdentity& game) const
{
    /*
     * Phase 1 game identification.
     *
     * Do NOT activate the plugin from the ROM title alone.
     * Nintendo DS GameCode is the authoritative identifier.
     *
     * We first capture the real GameCode from a verified
     * Kingdom Hearts 358/2 Days ROM at runtime.
     */

    if (!game.IsValid())
        return false;

    // Temporary diagnostic recognition only.
    // This intentionally does NOT activate the plugin yet.
    const bool titleLooksLikeKingdomHeartsDays =
        game.Title.find("KINGDOM") != std::string::npos ||
        game.Title.find("Kingdom") != std::string::npos;

    (void)titleLooksLikeKingdomHeartsDays;

    return false;
}

bool KingdomHeartsDaysPlugin::Initialize()
{
    GameLoaded = false;
    return true;
}

void KingdomHeartsDaysPlugin::Shutdown()
{
    GameLoaded = false;
}

void KingdomHeartsDaysPlugin::Reset()
{
    // Reserved for game-specific runtime state.
}

void KingdomHeartsDaysPlugin::OnGameLoaded(const GameIdentity& game)
{
    (void)game;
    GameLoaded = true;
}

void KingdomHeartsDaysPlugin::OnGameUnloaded()
{
    GameLoaded = false;
}

}
