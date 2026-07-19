#include "PluginManager.h"
#include "games/kingdom_hearts_days/KingdomHeartsDaysPlugin.h"

namespace KHMelonMix
{

PluginManager& PluginManager::Instance()
{
    static PluginManager instance;
    return instance;
}

bool PluginManager::Initialize()
{

    // Populate the global plugin registry once before initialization.
    RegisterBuiltInPlugins();

    // The plugin subsystem is global, while MelonInstance can have
    // multiple simultaneous instances. Initialize plugins only for
    // the first active MelonInstance.
    if (InstanceCount++ > 0)
        return true;

    for (auto& plugin : Plugins)
    {
        if (!plugin->Initialize())
        {
            InstanceCount = 0;
            return false;
        }
    }

    return true;
}

void PluginManager::Shutdown()
{
    if (InstanceCount == 0)
        return;

    // Keep the global plugin subsystem alive until the last
    // MelonInstance has been destroyed.
    if (--InstanceCount > 0)
        return;

    OnGameUnloaded();

    for (auto& plugin : Plugins)
        plugin->Shutdown();
}

void PluginManager::Reset()
{
    if (ActivePlugin)
        ActivePlugin->Reset();
}

void PluginManager::OnFrame(melonDS::NDS& nds)
{
    if (ActivePlugin)
        ActivePlugin->OnFrame(nds);
}

void PluginManager::RegisterPlugin(std::unique_ptr<Plugin> plugin)
{
    if (plugin)
        Plugins.push_back(std::move(plugin));
}

void PluginManager::OnGameLoaded(const GameIdentity& game)
{
    OnGameUnloaded();

    CurrentGame = game;

    for (auto& plugin : Plugins)
    {
        if (plugin->SupportsGame(game))
        {
            ActivePlugin = plugin.get();
            ActivePlugin->OnGameLoaded(game);
            break;
        }
    }
}

void PluginManager::OnGameUnloaded()
{
    if (ActivePlugin)
    {
        ActivePlugin->OnGameUnloaded();
        ActivePlugin = nullptr;
    }

    CurrentGame = {};
}

Plugin* PluginManager::GetActivePlugin() const
{
    return ActivePlugin;
}

const GameIdentity& PluginManager::GetCurrentGame() const
{
    return CurrentGame;
}

}

// Central registration point for built-in KHMelonMix plugins.
// Individual game plugins will be registered here.
void KHMelonMix::PluginManager::RegisterBuiltInPlugins()
{
    if (BuiltInPluginsRegistered)
        return;

    BuiltInPluginsRegistered = true;

    // Game-specific plugins will be registered here, for example:
    RegisterPlugin(std::make_unique<KingdomHeartsDaysPlugin>());
}
