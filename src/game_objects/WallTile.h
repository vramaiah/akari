#pragma once

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Tile.h"

class WallTile: public Tile 
{
    private:
        int m_requiredLights {};
        SDL_Texture* m_texture {};
        SDL_FRect m_rect {};

    public:
        WallTile(int requiredLights, SDL_Texture* tex, float x, float y, float s);
        ~WallTile();
        bool isOpaque() const override {return true;}
        int requiredLights() const {return m_requiredLights;}
        void render() const override;
        void update() override;
};
