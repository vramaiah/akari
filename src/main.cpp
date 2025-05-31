#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_timer.h"

#include "Settings.h"
#include "game_objects/Board.h"
#include "rendering/RenderWindow.h"

#include <string>
#include <string_view>
#include <iostream>

int main()
{
    // Intro text
    std::cout << "Welcome to Akari!\n";
    std::cout << "In an Akari Puzzle, the goal is to place light bulbs";
    std::cout << " on a grid so all purple squares are lit.\n";
    std::cout << "    * A light bulb lights up all the purple squares in its row";
    std::cout << "and column until blocked by a wall.\n";
    std::cout << "    * No light bulb may light up another light bulb.\n";
    std::cout << "    * Black squares with a number indicate how many";
    std::cout << " squares with a light bulb share a side with that square.\n";
    std::cout << "\nTo start, enter the name of a level: ";
    std::string path {};
    std::cin >> path;

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
    RenderWindow& window {RenderWindow::getInstance()}; 
    // Logs current video driver
    SDL_Log(
            "Current video driver: %s", 
            SDL_GetCurrentVideoDriver()
    );
    // Creates a Grass Sprite
    // Main Game Loop
    Board board {"./res/levels/" + path + ".json"};
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
    if (solved)
    {
        SDL_Delay(Settings::solveDelay);
        SDL_Delay(100);
        std::cout << "Solved!\n";
    }
    SDL_Quit();
    return 0;
}
