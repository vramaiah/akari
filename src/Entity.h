#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "RenderWindow.h"

class Entity
{
    protected:
        SDL_Texture* m_texture {nullptr};
        SDL_FRect m_sourceRect {};
        SDL_FRect m_destRect {};

    public:
        Entity(
            SDL_Texture* tex,
            const SDL_FRect& sourceRect,
            const SDL_FRect& destRect
        )
        : m_texture {tex}, m_sourceRect {sourceRect}, m_destRect {destRect}
        {
        }

        virtual ~Entity()
        {
            SDL_DestroyTexture(m_texture);
        }

        virtual void render(RenderWindow& window) const = 0;
        virtual void update() = 0;
};

