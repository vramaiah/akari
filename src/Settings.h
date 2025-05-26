#pragma once

#include "SDL3/SDL_pixels.h"
#include <string_view>

namespace Settings
{
    inline constexpr std::string_view windowName {"Akari [alpha]"};
    inline constexpr int windowWidth {1280};
    inline constexpr int windowHeight {720};
    inline constexpr float tileScale {150.0f};
    inline constexpr SDL_Color backgroundColor {106, 99, 168, 255}; 
}
