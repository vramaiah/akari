#pragma once

#include "SDL3/SDL_render.h"
#include "WallTile.h"
#include <string_view>
#include <vector>
class Board: public IEntity
{
    private:
        std::vector<WallTile> m_tiles {};
        std::vector<SDL_Texture*> m_tileTextures {};

    public:
        Board(std::string_view filePath);
        void render() const;
        void update();
};
