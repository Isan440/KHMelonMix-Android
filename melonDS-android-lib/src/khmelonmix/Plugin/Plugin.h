#pragma once

#include <string>

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

    virtual bool Initialize() = 0;

    virtual void Shutdown() = 0;

    virtual void Reset() = 0;

    // Called once after each emulated frame.
    virtual void OnFrame(melonDS::NDS& nds) { (void)nds; }
};

}
