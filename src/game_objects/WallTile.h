#pragma once

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Tile.h"
#include <array>

class WallTile: public Tile 
{
    public:
        enum WallState
        {
            notEnoughLights,
            enoughLights,
            tooMuchLights,
            numStates
        };

    private:
        int m_requiredLights {};
        std::array<SDL_Texture*, numStates> m_textures {};
        SDL_FRect m_rect {};
        WallState m_lightState {WallState::notEnoughLights};
        inline static int s_blank {5};

    public:
        WallTile(
            int requiredLights,
            std::array<SDL_Texture*, 3> tex,
            float x,
            float y,
            float s
        );
        bool isOpaque() const override {return true;}
        int requiredLights() const {return m_requiredLights;}
        void render() const override;
        void update() override;
        static int getBlankValue() {return s_blank;}
        LightStatus lightStatus() const override {return LightStatus::dark;} 
        void setLightStatus(LightStatus status) override {;}
        void setStatus(TileStatus status) override {;}
        TileStatus getStatus() const override {return TileStatus::wall;}
        void click() override {};
        void setNeighboringLights(int nl);
};
