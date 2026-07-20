#pragma once

#include "../../Plugin.h"

namespace KHMelonMix
{

class KingdomHeartsDaysPlugin final : public Plugin
{
public:
    std::string GetName() const override;

    bool SupportsGame(const GameIdentity& game) const override;

    bool Initialize() override;
    void Shutdown() override;
    void Reset() override;
    void OnFrame(melonDS::NDS& nds) override;

    void OnGameLoaded(const GameIdentity& game) override;
    void OnGameUnloaded() override;
    void OnTextureObserved(const TextureObservation& texture) override;

private:
    bool GameLoaded = false;
};

}
