#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_timer.h"

#include "Settings.h"
#include "game_objects/Board.h"
#include "rendering/RenderWindow.h"

#include <string_view>
#include <iostream>

int main()
{
    SDL_SetLogPriorities(SDL_LogPriority::SDL_LOG_PRIORITY_ERROR);
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION, 
            "Failed to initialize SDL: %s",
            SDL_GetError()
        );
        return 1;
    }
    bool solved {false};
    {
        RenderWindow& window {RenderWindow::getInstance()}; 
        // Logs current video driver
        SDL_Log(
                "Current video driver: %s", 
                SDL_GetCurrentVideoDriver()
        );
        // Creates a Grass Sprite
        // Main Game Loop
        Board board {"./res/levels/easy_1.json"};
        SDL_Event event {};
        bool quit {false};
        while (!quit) 
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                    quit = true;
                else
                    board.handleEvent(event);
            }
            window.clear();
            board.update();
            if (board.isSolved())
            {
                quit = true;
                solved = true;
            }
            board.render();
            window.display();
        }
    }
    if (solved)
    {
        SDL_Delay(Settings::solveDelay);
        std::cout << "Solved!\n";
    }
    SDL_Quit();
    return 0;
}
