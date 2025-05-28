#include "Board.h"
#include "../rendering/RenderWindow.h"
#include "SDL3/SDL_render.h"
#include "WallTile.h"
#include "../Settings.h"
#include "nlohmann/json.hpp"
#include <optional>
#include <string_view>
#include <fstream>

Board::Board(std::string_view filePath)
: m_tiles {}
{
    // Create Textures
    m_tileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/0.png")
    );
    m_tileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/1.png")
    );
    m_tileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/2.png")
    );
    m_tileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/3.png")
    );
    m_tileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/4.png")
    );
    m_tileTextures.push_back(
        RenderWindow::getInstance().loadTexture("./res/gfx/b.png")
    );
    //
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
                m_tileTextures[value],
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
                m_tileTextures[WallTile::getBlankValue()],
                col * Settings::tileScale,
                row * Settings::tileScale,
                Settings::tileScale
            }};
            m_tiles[row][col] = tile;
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
