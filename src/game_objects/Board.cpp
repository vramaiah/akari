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
#include <cstddef>
#include <optional>
#include <string_view>
#include <fstream>
#include <iostream>

#include "SDL3/SDL.h"

Board::Board(std::string_view filePath)
: m_tiles {}
{
    // Create Textures
    m_wallTileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/0.png")
    );
    m_wallTileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/1.png")
    );
    m_wallTileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/2.png")
    );
    m_wallTileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/3.png")
    );
    m_wallTileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/4.png")
    );
    m_wallTileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/b.png")
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
    for (int i {1}; i <= Settings::gridSize; ++i)
    {
        std::vector<Tile*> vec(Settings::gridSize);
        m_tiles.push_back(vec);
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
                col * Settings::tileScale,
                row * Settings::tileScale,
                Settings::tileScale
            }};
            m_tiles[row][col] = tile;
        }
        else
        {
            WallTile* tile{ new WallTile {
                WallTile::getBlankValue(),
                m_wallTileTextures[WallTile::getBlankValue()],
                col * Settings::tileScale,
                row * Settings::tileScale,
                Settings::tileScale
            }};
            m_tiles[row][col] = tile;
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
            auto& tile {m_tiles[i][j]};
            if (!tile)
                tile = new FloorTile{
                    m_floorTileTextures[2],
                    m_floorTileTextures[1],
                    i * Settings::tileScale,
                    j * Settings::tileScale,
                    Settings::tileScale
                };

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
        float col {e.motion.x / (Settings::tileScale / 2)};
        float row {e.motion.y / (Settings::tileScale / 2)};
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
