#include "Entity.h"

Entity::Entity(
    SDL_Texture* tex,
    const SDL_FRect& sourceRect,
    const SDL_FRect& destRect
)
: m_texture {tex}, m_sourceRect {sourceRect}, m_destRect {destRect}
{
}

Entity::~Entity()
{
    SDL_DestroyTexture(m_texture);
}

