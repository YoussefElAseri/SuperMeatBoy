#ifndef SUPERMEATBOY_GOAL_H
#define SUPERMEATBOY_GOAL_H


#include "EntityModel.h"

class Goal : public EntityModel {
public:
    Goal(float positionX, float positionY, float width, float height);

    bool goal() override;
};


#endif //SUPERMEATBOY_GOAL_H
