#pragma once

#include <memory>
#include <vector>

#include "Plugin.h"
#include "GameIdentity.h"

namespace KHMelonMix
{

class PluginManager
{
public:
    static PluginManager& Instance();

    bool Initialize();
    void Shutdown();
    void Reset();

    void RegisterPlugin(std::unique_ptr<Plugin> plugin);

    // Selects a plugin for the currently loaded ROM.
    // If no plugin supports it, melonDS continues normally.
    void OnGameLoaded(const GameIdentity& game);

    void OnGameUnloaded();

    Plugin* GetActivePlugin() const;
    const GameIdentity& GetCurrentGame() const;

private:
    PluginManager() = default;

    std::vector<std::unique_ptr<Plugin>> Plugins;

    Plugin* ActivePlugin = nullptr;
    GameIdentity CurrentGame;
};

}
