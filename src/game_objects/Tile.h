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

enum class LightStatus
{
    dark,
    lit,
    burnt,
    maxStatuses
};

class Tile: public IEntity
{
    public:
        virtual bool isOpaque() const = 0;
        virtual ~Tile() = default;
        virtual LightStatus lightStatus() const = 0; 
        virtual void setLightStatus(LightStatus status) = 0;
        virtual void setStatus(TileStatus status) = 0;
        virtual TileStatus getStatus() const = 0;
        virtual void click() = 0;
};

