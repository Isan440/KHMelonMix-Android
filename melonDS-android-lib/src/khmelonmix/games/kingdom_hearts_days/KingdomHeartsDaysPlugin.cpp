#include "KingdomHeartsDaysPlugin.h"
#include <android/log.h>
#include "Platform.h"
#include "PlatformAndroid.h"

namespace KHMelonMix
{

namespace
{

void WriteRuntimeProbe(const char* message)
{
    auto* file = melonDS::Platform::OpenInternalFile(
        "khmelonmix_runtime_probe.txt",
        melonDS::Platform::FileMode::Append
    );

    if (!file)
        return;

    melonDS::Platform::FileWriteFormatted(file, "%s\\n", message);
    melonDS::Platform::CloseFile(file);
}

}

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

    static bool FirstFrameLogged = false;
    if (!FirstFrameLogged)
    {
        __android_log_print(
            ANDROID_LOG_INFO,
            "KHMelonMix",
            "[KHMelonMix] Kingdom Hearts 358/2 Days first OnFrame reached");
        FirstFrameLogged = true;
        WriteRuntimeProbe("FIRST_FRAME");
    }

    // Runtime bridge established.
    // Memory access will be added only after this callback is wired
    // safely from MelonInstance::runFrame().
    (void)nds;
}

void KingdomHeartsDaysPlugin::OnGameLoaded(const GameIdentity& game)
{
    __android_log_print(
        ANDROID_LOG_INFO,
        "KHMelonMix",
        "[KHMelonMix] Kingdom Hearts 358/2 Days OnGameLoaded GameCode='%s'",
        game.GameCode.c_str());

    GameLoaded = true;

    WriteRuntimeProbe("GAME_LOADED YKGE");
}

void KingdomHeartsDaysPlugin::OnGameUnloaded()
{
    GameLoaded = false;
}

void KingdomHeartsDaysPlugin::OnTextureObserved(const TextureObservation& texture)
{
    if (!GameLoaded)
        return;

    // Diagnostic only. Keep bounded to avoid flooding logcat.
    static unsigned int LoggedTextures = 0;
    if (LoggedTextures >= 32)
        return;

    if (LoggedTextures == 0)
        WriteRuntimeProbe("FIRST_TEXTURE_OBSERVED");

    __android_log_print(
        ANDROID_LOG_INFO,
        "KHMelonMix",
        "[KHMelonMix][Texture] %ux%u fmt=%u "
        "texHash0=%016llX texHash1=%016llX palHash=%016llX",
        texture.Width,
        texture.Height,
        texture.Format,
        texture.TextureHash0,
        texture.TextureHash1,
        texture.PaletteHash);

    ++LoggedTextures;
}

}
