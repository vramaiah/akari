#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class IEntity
{
    public:
        virtual void render() const = 0;
        virtual void update() = 0;
};

