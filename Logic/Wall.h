#ifndef SUPERMEATBOY_WALL_H
#define SUPERMEATBOY_WALL_H


#include "EntityModel.h"

class Wall : public EntityModel {
public:
    Wall(float positionX, float positionY, float width, float height);
};


#endif //SUPERMEATBOY_WALL_H
