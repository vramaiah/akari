#pragma once

#include "SDL3/SDL_rect.h"
#include "Tile.h"
#include "SDL3/SDL_render.h"
class FloorTile: public Tile
{
    private:
        SDL_Texture* m_lightTexture {};
        SDL_Texture* m_xTexture {};
        TileStatus m_status {TileStatus::emptyFloor};
        LightStatus m_lightStatus {LightStatus::dark};
        SDL_FRect m_rect {};
    
    public:
        FloorTile(
            SDL_Texture* xTex, SDL_Texture* lTex, float x, float y, float s);
        bool isOpaque() const override {return false;}
        LightStatus lightStatus() const override {return m_lightStatus;}
        void setLightStatus(LightStatus status) override;
        void render() const override;
        void update() override;
        void setStatus(TileStatus status) override;
        TileStatus getStatus() const override {return m_status;}
        void click() override;
};
