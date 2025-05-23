#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_rect.h>
#include <cstddef>
#include <string_view>

#include "RenderWindow.h"

constexpr int windowLength {1280};
constexpr int windowHeight {720};
constexpr std::string_view windowName {"Akari [alpha]"};

RenderWindow::RenderWindow(
    std::string_view title,
    int width,
    int height
)
: m_window {nullptr}, m_renderer {nullptr}
{
    m_window = SDL_CreateWindow(
        title.data(),
        width,
        height,
        SDL_WINDOW_ALWAYS_ON_TOP 
    );
    // Checks if window was created or not
    if (!m_window)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "SDL_CreateWindow error: %s",
            SDL_GetError()
        );
        SDL_Quit();
    }
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer)
    {
        SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "SDL_CreateRendered error: %s",
                SDL_GetError()
        );
        SDL_Quit();
    }
    SDL_SetWindowPosition(m_window, 100, 100);
}

RenderWindow::~RenderWindow()
{
    SDL_DestroyWindow(m_window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(m_renderer);
}

void RenderWindow::display()
{
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
    SDL_Texture* texture, SDL_FRect src, SDL_FRect dest)
{
    SDL_RenderTexture(m_renderer, texture, &src, &dest);
}

RenderWindow& RenderWindow::getInstance()
{
    static RenderWindow instance {windowName, windowLength, windowHeight};
    return instance;
}
