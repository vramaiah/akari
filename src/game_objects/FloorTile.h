#pragma once

#include "SDL3/SDL_rect.h"
#include "Tile.h"
#include "SDL3/SDL_render.h"
class FloorTile: public Tile
{
    private:
        SDL_Texture* m_lightTexture {};
        SDL_Texture* m_xTexture {};
        TileStatus m_status {};
        bool m_isLit {false};
        SDL_FRect m_rect {};
    
    public:
        FloorTile(
            SDL_Texture* xTex, SDL_Texture* lTex, float x, float y, float s);
        bool isOpaque() const override {return false;}
        bool isLit() const override {return m_isLit;}
        void render() const override;
        void update() override;
        void setStatus(TileStatus status) override;
        TileStatus getStatus() const override {return m_status;}
        void click() override;
};
