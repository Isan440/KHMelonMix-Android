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
    for (auto& plugin : Plugins)
    {
        plugin->Shutdown();
    }
}

void PluginManager::Reset()
{
    for (auto& plugin : Plugins)
    {
        plugin->Reset();
    }
}

void PluginManager::RegisterPlugin(std::unique_ptr<Plugin> plugin)
{
    Plugins.push_back(std::move(plugin));
}

}
