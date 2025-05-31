#include "FloorTile.h"

#include "../rendering/RenderWindow.h"
#include "../Settings.h"

#include "SDL3/SDL_render.h"
#include "Tile.h"

FloorTile::FloorTile(
    SDL_Texture* xTex, SDL_Texture* lTex, float x, float y, float s)
: m_lightTexture {lTex}
, m_xTexture {xTex}
, m_lightStatus {LightStatus::dark}
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
    if (!m_solved)
    {
        if (m_lightStatus == LightStatus::lit)
            RenderWindow::getInstance().renderFillRect(m_rect, Settings::litColor);
        if (m_lightStatus == LightStatus::burnt)
            RenderWindow::getInstance().renderFillRect(
                m_rect, Settings::burntColor);
    }
    switch (m_status) {
        case TileStatus::light:
        {
            if (!(m_lightStatus == LightStatus::burnt) && !m_solved)
                RenderWindow::getInstance().renderFillRect(
                    m_rect, Settings::litColor);
            if (m_solved)
                RenderWindow::getInstance().renderFillRect(
                    m_rect, Settings::solvedColor);
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
    if (m_status == TileStatus::light)
        m_lightStatus = LightStatus::lit;
}

void FloorTile::click()
{
    switch (m_status)
    {
        case TileStatus::emptyFloor:
        {
            m_status = TileStatus::light;
            break;
        }
        case TileStatus::light:
        {
            m_status = TileStatus::x;
            m_lightStatus = LightStatus::lit;
            break;
        }
        case TileStatus::x:
        {
            m_status = TileStatus::emptyFloor;
            break;
        }
        default:
            break;
    }
}

void FloorTile::setLightStatus(LightStatus status)
{
    if ((status != LightStatus::maxStatuses))
        m_lightStatus = status;
}

void FloorTile::setSolved(bool s)
{
    m_solved = s;
}
