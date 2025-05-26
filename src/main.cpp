#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"

#include "Settings.h"
#include "rendering/RenderWindow.h"

#include "game_objects/WallTile.h"

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
        WallTile tile {
            0,
            window.loadTexture("./res/gfx/0.png"),
            0.0f,
            0.0f,
            Settings::tileScale 
        };
        WallTile tile_2 {
            3,
            window.loadTexture("./res/gfx/3.png"),
            Settings::tileScale * 2,
            Settings::tileScale,
            Settings::tileScale
        };
        // Main Game Loop
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
            tile.render();
            tile_2.render();
            window.display();
        }
    }
    SDL_Quit();
    return 0;
}
