#pragma once

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <string_view>
#include <vector>

class RenderWindow
{
    private:
        SDL_Window* m_window {nullptr};
        SDL_Renderer* m_renderer {nullptr};
        std::vector<SDL_Texture*> m_textures {};
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
            SDL_Texture* texture, const SDL_FRect& dest);
        void renderLine(
            float x1, float y1, float x2, float y2,
            const SDL_Color& color={0,0,0,255});
        void renderFillRect(const SDL_FRect& rect, const SDL_Color& color);
};
