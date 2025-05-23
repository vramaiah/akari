#include "RigidSprite.h"
#include "Entity.h"
#include "RenderWindow.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <utility>

RigidSprite::RigidSprite(
    SDL_Texture* tex, std::pair<float, float> origin, float scale)
: Entity {tex, {}, {}}
{
    if (!SDL_GetTextureSize(tex, &m_sourceRect.w, &m_sourceRect.h))
        SDL_Log("Failed to get texture size: %s", SDL_GetError());
    m_sourceRect.x = origin.first;
    m_sourceRect.y = origin.second;
    m_destRect.x = m_sourceRect.x;
    m_destRect.y = m_sourceRect.y;
    m_destRect.w = m_sourceRect.w * scale;
    m_destRect.h = m_sourceRect.h * scale;
}

void RigidSprite::render(RenderWindow& window) const
{
    window.renderTexture(m_texture, m_sourceRect, m_destRect);
}

void RigidSprite::update()
{
}

RigidSprite::~RigidSprite()
{
    Entity::~Entity();
}
