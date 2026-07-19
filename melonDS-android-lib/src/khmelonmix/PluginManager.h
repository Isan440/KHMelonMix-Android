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
    void OnFrame(melonDS::NDS& nds);

    void RegisterPlugin(std::unique_ptr<Plugin> plugin);

    // Registers all built-in KHMelonMix game plugins.
    // Safe to call multiple times; registration only happens once.
    void RegisterBuiltInPlugins();

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

    // Number of active MelonInstance users of the global plugin subsystem.
    unsigned int InstanceCount = 0;

    // Prevent duplicate registration when multiple MelonInstance objects exist.
    bool BuiltInPluginsRegistered = false;
};

}
