#pragma once

#include <utility>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "Entity.h"

class RigidSprite: public IEntity 
{
    private:
        float m_scale {1};
        std::pair<float, float> m_origin {0, 0};
        SDL_Texture* m_texture {nullptr};
        SDL_FRect m_sourceRect {};
        SDL_FRect m_destRect {};

    public:
        RigidSprite(
            SDL_Texture* tex, std::pair<float, float> origin, float scale=1);
        virtual void render() const override;
        void update() override;
        virtual ~RigidSprite();
};
