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
     * Game recognition will be implemented in the next step.
     *
     * We intentionally do not guess or hard-code a GameCode yet.
     * Until verified ROM identities are added, this plugin remains inactive.
     */
    (void)game;
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
