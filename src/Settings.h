#pragma once

#include "SDL3/SDL_pixels.h"
#include <string_view>

namespace Settings
{
    inline constexpr std::string_view windowName {"Akari [alpha]"};
    inline constexpr float tileScale {150.0f};
    inline constexpr int gridSize {7}; 
    inline constexpr double windowWidth {(150 * gridSize) / 2 + 10};
    inline constexpr double windowHeight {windowWidth};
    inline constexpr SDL_Color backgroundColor {106, 99, 168, 255}; 
    inline constexpr SDL_Color litColor {194, 183, 219, 255}; 
}
