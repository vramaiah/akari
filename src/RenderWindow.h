#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#include <string_view>

class RenderWindow
{
    private:
        SDL_Window* m_window {nullptr};
        SDL_Renderer* m_renderer {nullptr};

    public:
        RenderWindow(
            std::string_view title, 
            int width, 
            int height
        );
        ~RenderWindow();
        void display();
        void clear();
        SDL_Texture* loadTexture(std::string_view filePath);
        void renderTexture(SDL_Texture* texture);
};
