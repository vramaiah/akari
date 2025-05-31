#pragma once

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"

#include "Tile.h"
#include "WallTile.h"

#include <array>
#include <cstddef>
#include <string_view>
#include <vector>
class Board: public IEntity
{
    private:
        std::vector<std::vector<Tile*>> m_tiles {};
        std::vector<SDL_Texture*> m_floorTileTextures {};
        std::vector<std::array<SDL_Texture*, WallTile::numStates>> 
            m_wallTileTextures {};
        std::vector<Tile*> getColNeighbors(std::size_t row, std::size_t col);
        std::vector<Tile*> getRowNeighbors(std::size_t row, std::size_t col);
        bool m_solved {};
        bool _isSolved() const;

    public:
        Board(std::string_view filePath);
        ~Board();
        void render() const;
        void update();
        void handleEvent(const SDL_Event& e);
        bool isSolved() const;
};
