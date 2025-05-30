#include "FloorTile.h"

#include "../rendering/RenderWindow.h"
#include "../Settings.h"

#include "SDL3/SDL_render.h"
#include "Tile.h"

FloorTile::FloorTile(SDL_Texture* xTex, SDL_Texture* lTex, float x, float y, float s)
: m_lightTexture {lTex}
, m_xTexture {xTex}
, m_isLit {}
, m_rect {}
, m_status {TileStatus::emptyFloor}
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = s;
    m_rect.h = s;
}

void FloorTile::render() const
{
    if (m_isLit)
        RenderWindow::getInstance().renderFillRect(m_rect, Settings::litColor);
    switch (m_status) {
        case TileStatus::light:
        {
            RenderWindow::getInstance().renderTexture(m_lightTexture, m_rect);
            break;
        }
        case TileStatus::x:
        {
            RenderWindow::getInstance().renderTexture(m_xTexture, m_rect);
            break;
        }
        default:
            ;
    }
}

void FloorTile::update()
{
}

void FloorTile::setStatus(TileStatus status)
{
    if ((status != TileStatus::maxStatuses) && (status != TileStatus::wall))
        m_status = status;
}
