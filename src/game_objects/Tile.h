#pragma once

#include "../rendering/Entity.h"

enum class TileStatus
{
    emptyFloor,
    light,
    x,
    wall,
    maxStatuses
};

class Tile: public IEntity
{
    public:
        virtual bool isOpaque() const = 0;
        virtual ~Tile() = default;
        virtual bool isLit() const = 0; 
        virtual void setStatus(TileStatus status) = 0;
        virtual TileStatus getStatus() const = 0; 
};

