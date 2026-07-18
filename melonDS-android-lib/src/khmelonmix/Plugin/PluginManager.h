#pragma once

#include <memory>
#include <vector>

#include "Plugin.h"

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

private:
    PluginManager() = default;

    std::vector<std::unique_ptr<Plugin>> Plugins;
};

}
