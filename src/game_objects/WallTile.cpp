#include "WallTile.h"
#include "../rendering/RenderWindow.h"
#include "SDL3/SDL_render.h"
#include "Tile.h"

WallTile::WallTile(
    int requiredLights, SDL_Texture* tex, float x, float y, float s)
: m_requiredLights {requiredLights}
, m_texture {tex}
, m_rect {}
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = s;
    m_rect.h = s;
}

void WallTile::render() const
{
    RenderWindow::getInstance().renderTexture(m_texture, m_rect);
}

void WallTile::update()
{
}

