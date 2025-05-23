#include "RigidSprite.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"

#include "RenderWindow.h"

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
        RigidSprite grass {
            window.loadTexture("./res/gfx/ground_grass_1.png"),
            {0, 0},
            10
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
            grass.render();
            window.display();
        }
    }
    SDL_Quit();
    return 0;
}
