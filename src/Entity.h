#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

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
        );
        virtual ~Entity();
        virtual void render() const = 0;
        virtual void update() = 0;
};

