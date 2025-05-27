#include "Board.h"
#include "../rendering/RenderWindow.h"
#include "WallTile.h"
#include "../Settings.h"
#include "nlohmann/json.hpp"
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
    // Get level from file
    // TODO: Make tiles dynamically allocated
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
            WallTile tile{
                value,
                m_tileTextures[value],
                col * Settings::tileScale,
                row * Settings::tileScale,
                Settings::tileScale
            };
            m_tiles.push_back(
                tile
            );
        }
        else
        {
            WallTile tile{
                WallTile::getBlankValue(),
                m_tileTextures[WallTile::getBlankValue()],
                col * Settings::tileScale,
                row * Settings::tileScale,
                Settings::tileScale
            };
            m_tiles.push_back(
                tile
            );
        }
    }
}

void Board::render() const
{
    for (auto& tile: m_tiles)
        tile.render();
}

void Board::update()
{
}
