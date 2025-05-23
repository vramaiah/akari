#include "RigidSprite.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"

#include "RenderWindow.h"
#include "SDL3/SDL_render.h"

constexpr int windowLength {1280};
constexpr int windowHeight {720};


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
        RenderWindow window {
            "Akari [Alpha]", windowLength, windowHeight
        };
        // Load a texture
        SDL_Texture* grassTexture {
            window.loadTexture("./res/gfx/ground_grass_1.png")
        };
        // Logs current video driver
        SDL_Log(
                "Current video driver: %s", 
                SDL_GetCurrentVideoDriver()
        );
        RigidSprite grass {
            grassTexture,
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
            grass.render(window);
            window.display();
        }
    }
    SDL_Quit();
    return 0;
}
