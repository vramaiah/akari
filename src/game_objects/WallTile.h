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
        inline static int s_blank {5};

    public:
        WallTile(
            int requiredLights, SDL_Texture* tex, float x, float y, float s);
        bool isOpaque() const override {return true;}
        int requiredLights() const {return m_requiredLights;}
        void render() const override;
        void update() override;
        static int getBlankValue() {return s_blank;}
        bool isLit() const override {return false;} 
        void setStatus(TileStatus status) override {;}
        TileStatus getStatus() const override {return TileStatus::wall;} 
};
