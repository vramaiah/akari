#pragma once

#include "Entity.h"
#include <SDL3/SDL_render.h>

#include <utility>

class RigidSprite: public Entity
{
    private:
        float m_scale {1};
        std::pair<float, float> m_origin {0, 0};
    public:
        RigidSprite(
            SDL_Texture* tex, std::pair<float, float> origin, float scale=1);
        virtual void render() const override;
        void update() override;
        virtual ~RigidSprite();
};
