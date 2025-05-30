#pragma once

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "Tile.h"
#include "WallTile.h"
#include <memory>
#include <string_view>
#include <vector>
class Board: public IEntity
{
    private:
        std::vector<std::vector<Tile*>> m_tiles {};
        std::vector<SDL_Texture*> m_floorTileTextures {};
        std::vector<SDL_Texture*> m_wallTileTextures {};

    public:
        Board(std::string_view filePath);
        ~Board();
        void render() const;
        void update();
        void handleEvent(const SDL_Event& e);
};
