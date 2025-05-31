#include "WallTile.h"
#include "../rendering/RenderWindow.h"
#include "SDL3/SDL_render.h"

WallTile::WallTile(
    int requiredLights, std::array<SDL_Texture*, 3> tex, float x, float y, float s)
: m_requiredLights {requiredLights}
, m_textures {tex}
, m_rect {}
, m_lightState {notEnoughLights}
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = s;
    m_rect.h = s;
}

void WallTile::render() const
{
    RenderWindow::getInstance().renderTexture(
        m_textures[m_lightState], m_rect);
}

void WallTile::update()
{
}

void WallTile::setNeighboringLights(int nl)
{
    if (nl == m_requiredLights)
        m_lightState = WallState::enoughLights;
    else if (nl < m_requiredLights)
        m_lightState = WallState::notEnoughLights;
    else if (nl > m_requiredLights)
        m_lightState = WallState::tooMuchLights;
}
