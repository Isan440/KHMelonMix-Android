#pragma once

#include <string>
#include "GameIdentity.h"

namespace melonDS
{
class NDS;
}

namespace KHMelonMix
{

class Plugin
{
public:
    virtual ~Plugin() = default;

    virtual std::string GetName() const = 0;

    // Return true if this plugin supports the loaded game.
    virtual bool SupportsGame(const GameIdentity& game) const = 0;

    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void Reset() = 0;

    // Called once after each emulated frame.
    virtual void OnFrame(melonDS::NDS& nds)
    {
        (void)nds;
    }

    // Called when a supported ROM has successfully been identified.
    virtual void OnGameLoaded(const GameIdentity& game)
    {
        (void)game;
    }

    // Called before switching away from the active game/plugin.
    virtual void OnGameUnloaded()
    {
    }
};

}
