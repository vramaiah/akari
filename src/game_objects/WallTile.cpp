#include "WallTile.h"
#include "../rendering/RenderWindow.h"
#include "SDL3/SDL_render.h"
#include "../Settings.h"
#include "SDL3/SDL.h"
#include <string>

WallTile::WallTile(int requiredLights, SDL_Texture* tex, float x, float y, float s)
: m_requiredLights {requiredLights}
, m_texture {tex}
, m_rect {}
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = Settings::tileScale;
    m_rect.h = Settings::tileScale;
}

void WallTile::render() const
{
    RenderWindow::getInstance().renderTexture(m_texture, m_rect);
}

void WallTile::update()
{
}

WallTile::~WallTile()
{
}
