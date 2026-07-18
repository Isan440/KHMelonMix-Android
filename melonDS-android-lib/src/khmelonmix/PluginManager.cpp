#include "PluginManager.h"

namespace KHMelonMix
{

PluginManager& PluginManager::Instance()
{
    static PluginManager instance;
    return instance;
}

bool PluginManager::Initialize()
{
    for (auto& plugin : Plugins)
    {
        if (!plugin->Initialize())
            return false;
    }

    return true;
}

void PluginManager::Shutdown()
{
    OnGameUnloaded();

    for (auto& plugin : Plugins)
        plugin->Shutdown();
}

void PluginManager::Reset()
{
    if (ActivePlugin)
        ActivePlugin->Reset();
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
