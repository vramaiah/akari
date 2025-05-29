#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_rect.h>
#include <cstddef>
#include <string_view>

#include "../Settings.h"
#include "SDL3/SDL_pixels.h"

#include "RenderWindow.h"


RenderWindow::RenderWindow(
    std::string_view title,
    int width,
    int height
)
: m_window {nullptr}, m_renderer {nullptr}
{
    bool created {SDL_CreateWindowAndRenderer(
            title.data(),
            width,
            height,
            SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP,
            &m_window, &m_renderer)
    };
    if (!created)
    {
        SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "SDL_CreateWindowAndRenderer error: %s",
                SDL_GetError()
        );
        SDL_Quit();
    }
    SDL_SetWindowPosition(m_window, 100, 100);
    SDL_SetRenderVSync(m_renderer, 1);
    clear();
    display();
}

RenderWindow::~RenderWindow()
{
}

void RenderWindow::destroy()
{
    SDL_DestroyWindow(m_window);
    for (SDL_Texture* texture: m_textures)
        SDL_DestroyTexture(texture);
}

void RenderWindow::clear()
{
    SDL_RenderClear(m_renderer);
}

void RenderWindow::display()
{
    SDL_SetRenderDrawColor(
            m_renderer,
            Settings::backgroundColor.r,
            Settings::backgroundColor.g, 
            Settings::backgroundColor.b,
            Settings::backgroundColor.a);
    SDL_RenderPresent(m_renderer);
}

SDL_Texture* RenderWindow::loadTexture(std::string_view filePath)
{
    SDL_Texture* texture {nullptr};
    texture = IMG_LoadTexture(m_renderer, filePath.data());
    if (!texture)
        SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION, 
                "Failed to load a texture: %s",
                SDL_GetError()
        );
    return texture;
}

void RenderWindow::renderTexture(SDL_Texture* texture)
{
    SDL_RenderTexture(m_renderer, texture, NULL, NULL);
}

void RenderWindow::renderTexture(
    SDL_Texture* texture, const SDL_FRect& dest)
{
    SDL_RenderTexture(m_renderer, texture, NULL, &dest);
}

RenderWindow& RenderWindow::getInstance()
{
    static RenderWindow instance {
        Settings::windowName,
        static_cast<int>(Settings::windowWidth),
        static_cast<int>(Settings::windowHeight)
    };
    return instance;
}

void RenderWindow::renderLine(
    float x1, float y1, float x2, float y2, const SDL_Color& color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    if(!SDL_RenderLine(m_renderer, x1, y1, x2, y2))
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "SDL_RenderLine error: %s",
            SDL_GetError()
        );
    }
}
