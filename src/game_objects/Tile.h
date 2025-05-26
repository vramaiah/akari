#pragma once

#include "../rendering/Entity.h"

class Tile: public IEntity
{
    public:
        virtual bool isOpaque() const = 0;
        virtual ~Tile() {};
};
