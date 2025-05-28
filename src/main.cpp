#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "Settings.h"
#include "game_objects/Board.h"
#include "nlohmann/json_fwd.hpp"
#include "rendering/RenderWindow.h"
#include "game_objects/WallTile.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <string_view>
#include <vector>
#include <filesystem>

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION, 
            "Failed to initialize SDL: %s",
            SDL_GetError()
        );
        return 1;
    }
    {
        RenderWindow& window {RenderWindow::getInstance()}; 
        // Logs current video driver
        SDL_Log(
                "Current video driver: %s", 
                SDL_GetCurrentVideoDriver()
        );
        // Creates a Grass Sprite
        // Main Game Loop
        Board board {"./res/levels/normal_1.json"};
        SDL_Event event {};
        bool quit {false};
        while (!quit) 
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                    quit = true;
            }
            window.clear();
            board.update();
            board.render();
            window.display();
        }
    }
    SDL_Quit();
    return 0;
}
