#include "WallTile.h"
#include "../rendering/RenderWindow.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL.h"
#include <string>

WallTile::WallTile(int requiredLights, SDL_Texture* tex, float x, float y, float s)
: m_requiredLights {requiredLights}
, m_texture {tex}
, m_rect {}
{
    m_rect.x = x;
    m_rect.y = y;
    float w {};
    float h {};
    if (!SDL_GetTextureSize(tex, &w, &h))
        SDL_Log("Failed to get texture size: %s", SDL_GetError());
    m_rect.w = s;
    m_rect.h = (s / w) * h;
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
