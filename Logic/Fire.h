#ifndef SUPERMEATBOY_FIRE_H
#define SUPERMEATBOY_FIRE_H


#include "EntityModel.h"

class Fire : public EntityModel {
public:
    Fire(float positionX, float positionY, float width, float height);

    bool kill() override;
};


#endif //SUPERMEATBOY_FIRE_H
