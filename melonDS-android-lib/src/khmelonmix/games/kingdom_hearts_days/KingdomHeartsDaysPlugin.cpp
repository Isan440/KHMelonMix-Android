#include "KingdomHeartsDaysPlugin.h"

namespace KHMelonMix
{

std::string KingdomHeartsDaysPlugin::GetName() const
{
    return "Kingdom Hearts 358/2 Days";
}

bool KingdomHeartsDaysPlugin::SupportsGame(const GameIdentity& game) const
{
    // Verified directly from ROM header:
    // Title     : 358/2 DAYS
    // GameCode  : YKGE
    // MakerCode : GD
    return game.IsValid() && game.GameCode == "YKGE";
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

void KingdomHeartsDaysPlugin::OnFrame(melonDS::NDS& nds)
{
    if (!GameLoaded)
        return;

    // Runtime bridge established.
    // Memory access will be added only after this callback is wired
    // safely from MelonInstance::runFrame().
    (void)nds;
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
