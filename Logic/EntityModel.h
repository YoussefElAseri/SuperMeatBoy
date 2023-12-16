#ifndef SUPERMEATBOY_ENTITYMODEL_H
#define SUPERMEATBOY_ENTITYMODEL_H


#include "Subject.h"
#include "Rectangle.h"

class EntityModel : public Subject {
protected:
    float width, height, positionX, positionY;

public:
    EntityModel(float positionX, float positionY, float width, float height);

    EntityModel(EntityModel&) = delete;

    void operator=(const EntityModel&) = delete;

    void update();

    float getHitBoxTop() const;

    float getHitBoxBottom() const;

    float getHitBoxLeft() const;

    float getHitBoxRight() const;

    virtual bool kill();

    virtual bool goal();

    std::pair<float, float> getPosition() const;

    std::pair<float, float> getDimensions() const;
};


#endif //SUPERMEATBOY_ENTITYMODEL_H
