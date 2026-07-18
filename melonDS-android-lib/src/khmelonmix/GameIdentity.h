#pragma once

#include <string>

namespace KHMelonMix
{

struct GameIdentity
{
    std::string Title;
    std::string GameCode;
    std::string MakerCode;

    bool IsValid() const
    {
        return !GameCode.empty();
    }
};

}
