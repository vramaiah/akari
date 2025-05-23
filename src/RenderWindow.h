#pragma once

#include "SDL3/SDL_rect.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <string_view>

class RenderWindow
{
    private:
        SDL_Window* m_window {nullptr};
        SDL_Renderer* m_renderer {nullptr};
        void destroy();

    protected:
        RenderWindow(
            std::string_view title, 
            int width, 
            int height
        );
    
    public:
        void operator=(const RenderWindow&) = delete;
        RenderWindow(RenderWindow&) = delete;
        RenderWindow(RenderWindow&&) = delete;
        
        static RenderWindow& getInstance();

        ~RenderWindow();
        void display();
        void clear();
        SDL_Texture* loadTexture(std::string_view filePath);
        void renderTexture(SDL_Texture* texture);
        void renderTexture(
            SDL_Texture* texture, SDL_FRect src, SDL_FRect dest);
};
