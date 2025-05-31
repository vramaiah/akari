#include "Board.h"
#include "../rendering/RenderWindow.h"
#include "FloorTile.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_render.h"
#include "Tile.h"
#include "WallTile.h"
#include "../Settings.h"
#include "nlohmann/json.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <fstream>
#include <iostream>
#include <vector>

#include "SDL3/SDL.h"

Board::Board(std::string_view filePath)
: m_tiles {}
{
    // Create Textures
    std::array<SDL_Texture*, WallTile::numStates> texArr {};
    texArr[WallTile::notEnoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/0.png");
    texArr[WallTile::enoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/0g.png");
    texArr[WallTile::tooMuchLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/0r.png");
    m_wallTileTextures.push_back(
            texArr
    );
    texArr = {};
    texArr[WallTile::notEnoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/1.png");
    texArr[WallTile::enoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/1g.png");
    texArr[WallTile::tooMuchLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/1r.png");
    m_wallTileTextures.push_back(
            texArr
    );
    texArr = {};
    texArr[WallTile::notEnoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/2.png");
    texArr[WallTile::enoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/2g.png");
    texArr[WallTile::tooMuchLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/2r.png");
    m_wallTileTextures.push_back(
            texArr
    );
    texArr = {};
    texArr[WallTile::notEnoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/3.png");
    texArr[WallTile::enoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/3g.png");
    texArr[WallTile::tooMuchLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/3r.png");
    m_wallTileTextures.push_back(
            texArr
    );
    texArr = {};
    texArr[WallTile::notEnoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/4.png");
    texArr[WallTile::enoughLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/4g.png");
    texArr[WallTile::tooMuchLights] = 
        RenderWindow::getInstance().loadTexture("./res/gfx/4r.png");
    m_wallTileTextures.push_back(
            texArr
    );
    texArr = {};
    SDL_Texture* tex {
        RenderWindow::getInstance().loadTexture("./res/gfx/b.png")
    };
    texArr[WallTile::notEnoughLights] = tex; 
    texArr[WallTile::enoughLights] = tex; 
    texArr[WallTile::tooMuchLights] = tex; 
    m_wallTileTextures.push_back(
            texArr
    );
    m_floorTileTextures.push_back(
        nullptr
    );
    m_floorTileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/l.png") 
    );
    m_floorTileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/x.png") 
    );
    m_floorTileTextures.push_back(
        nullptr
    );
    for (int i {0}; i < Settings::gridSize; ++i)
    {
        std::vector<Tile*> vec(Settings::gridSize, nullptr);
        m_tiles.push_back(std::move(vec));
    }
    // Get level from file
    std::ifstream input_file(filePath);
    nlohmann::json puzzle_data {};
    input_file >> puzzle_data;
    for (const auto& feature : puzzle_data)
    {
        std::string type {feature.at("type").get<std::string>()};
        int row {feature.at("row").get<int>()};
        int col {feature.at("col").get<int>()};

        if (type == "clue")
        {
            int value {feature.at("value").get<int>()};
            WallTile* tile{ new WallTile {
                value,
                m_wallTileTextures[value],
                std::round(col * Settings::tileScale),
                std::round(row * Settings::tileScale),
                Settings::tileScale
            }};
            m_tiles[static_cast<std::size_t>(row)]
                [static_cast<std::size_t>(col)] = tile;
        }
        else
        {
            WallTile* tile{ new WallTile {
                WallTile::getBlankValue(),
                m_wallTileTextures[WallTile::getBlankValue()],
                std::round(col * Settings::tileScale),
                std::round(row * Settings::tileScale),
                Settings::tileScale
            }};
            m_tiles[static_cast<std::size_t>(row)]
                [static_cast<std::size_t>(col)] = tile;
        }
    }
    // Create FloorTile at all other spots
    for (
        std::size_t i {0}; 
        i < static_cast<std::size_t>(Settings::gridSize);
        ++i
    )
    {
        for (
            std::size_t j {0}; 
            j < static_cast<std::size_t>(Settings::gridSize);
            ++j
        )
        {
            if (!m_tiles[i][j])
            {
                FloorTile* ft { new FloorTile{
                    m_floorTileTextures[2],
                    m_floorTileTextures[1],
                    j * Settings::tileScale,
                    i * Settings::tileScale,
                    Settings::tileScale
                }};
                m_tiles[i][j] = ft;
            }
        }
    }
}

void Board::render() const
{
    for (const auto& row: m_tiles)
    {
        for (const auto& tile: row)
        {
            if (tile)
                tile->render();
        }
    }
    // Draw grid lines
    for (float f {1}; f <= Settings::gridSize; ++f)
    {
        RenderWindow::getInstance().renderLine(
            0,
            f * Settings::tileScale,
            Settings::tileScale * Settings::gridSize,
            f * Settings::tileScale
        );
        RenderWindow::getInstance().renderLine(
            f * Settings::tileScale,
            0,
            f * Settings::tileScale,
            Settings::tileScale * Settings::gridSize
        );
    }
}

void Board::update()
{
    // Make tiles in same row/col illuminated
    for (std::size_t row {0}; row < Settings::gridSize; ++row)
    {
        for (std::size_t col {0}; col < Settings::gridSize; ++col)
        {
            int numColLights {0};
            for (Tile* tile: getColNeighbors(row, col))
            {
                if (!tile)
                {
                    std::cout << "No tile for row: " << row << " col: ";
                    std::cout << col << " during Board::update()";
                }
                else if (tile->getStatus() == TileStatus::light)
                {
                    numColLights++;
                }
            }
            int numRowLights {0};
            for (Tile* tile: getRowNeighbors(row, col))
            {
                if ((tile->getStatus() == TileStatus::light) && tile)
                {
                    numRowLights++;
                }
            }
            Tile* tile {m_tiles.at(row).at(col)};
            if ((
                    (numColLights > 0) || (numRowLights > 0)) 
                    && (tile->getStatus() == TileStatus::light
                ))
                tile->setLightStatus(LightStatus::burnt);
            else if ((numColLights > 1) || (numRowLights > 1))
                tile->setLightStatus(LightStatus::burnt);
            else if ((numColLights == 1) || (numRowLights == 1))
                tile->setLightStatus(LightStatus::lit);
            else
                tile->setLightStatus(LightStatus::dark);
            // WallTile specific stuff
            WallTile* wall {dynamic_cast<WallTile*>(m_tiles[row][col])};
            if (!wall)
                continue;
            int nl {};
            try
            {
                if (m_tiles.at(row-1).at(col)->getStatus() == TileStatus::light)
                {
                    nl += 1;
                }
            } catch (std::out_of_range) {;}
            try
            {
                if (m_tiles.at(row+1).at(col)->getStatus() == TileStatus::light)
                {
                    nl += 1;
                }
            } catch (std::out_of_range) {;}
            try
            {
                if (m_tiles.at(row).at(col+1)->getStatus() == TileStatus::light)
                {
                    nl += 1;
                }
            } catch (std::out_of_range) {;}
            try
            {
                if (m_tiles.at(row).at(col-1)->getStatus() == TileStatus::light)
                {
                    nl += 1;
                }
            } catch (std::out_of_range) {;}
            wall->setNeighboringLights(nl);
        }
    }
}

Board::~Board()
{
    for (const auto& row: m_tiles)
    {
        for (const auto& tile: row)
        {
            delete tile;
        }
    }
}


void Board::handleEvent(const SDL_Event& e)
{
    if (e.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        float row {e.motion.x / (Settings::tileScale / 2)};
        float col {e.motion.y / (Settings::tileScale / 2)};
        Tile* tile {
            m_tiles[static_cast<std::size_t>(col)]
                [static_cast<std::size_t>(row)]
        };
        if ((e.button.button == SDL_BUTTON_RIGHT) && tile)
            tile->setStatus(TileStatus::x); 
        else if (tile)
            tile->click();
    }
}

std::vector<Tile*> Board::getColNeighbors(std::size_t p_row, std::size_t p_col)
{
    std::vector<Tile*> neighbors {};
    for (std::size_t row {p_row}; row >= 0; --row)
    {
        if (row > (std::ssize(m_tiles)))
            break;
        if (m_tiles.at(row).at(p_col)->getStatus() == TileStatus::wall)
            break;
        if ((row != p_row))
            neighbors.push_back(m_tiles.at(row).at(p_col));
    }
    for (std::size_t row {p_row}; row < Settings::gridSize; ++row)
    {
        if (m_tiles.at(row).at(p_col)->getStatus() == TileStatus::wall)
            break;
        if ((row != p_row))
            neighbors.push_back(m_tiles[row][p_col]);
    }
    return neighbors;
}

std::vector<Tile*> Board::getRowNeighbors(std::size_t p_row, std::size_t p_col)
{
    std::vector<Tile*> neighbors {};
    for (std::size_t col {p_col}; col < Settings::gridSize; ++col)
    {
        if (m_tiles.at(p_row).at(col)->getStatus() == TileStatus::wall)
            break;
        if ((col!= p_col))
            neighbors.push_back(m_tiles.at(p_row).at(col));
    }
    for (std::size_t col {p_col}; col >= 0; --col)
    {
        if (col > (std::ssize(m_tiles)))
            break;
        if (m_tiles.at(p_row).at(col)->getStatus() == TileStatus::wall)
            break;
        if ((col!= p_col))
            neighbors.push_back(m_tiles.at(p_row).at(col));
    }
    return neighbors;
}
