#ifndef SUPERMEATBOY_ABSTRACTENTITYFACTORY_H
#define SUPERMEATBOY_ABSTRACTENTITYFACTORY_H


#include <memory>

class EntityModel;
class EntityView;
using Entity = std::pair<std::shared_ptr<EntityModel>, std::shared_ptr<EntityView>>;

class AbstractEntityFactory {
public:
    AbstractEntityFactory() = default;

    virtual Entity create(float positionX, float positionY, float width, float height) const = 0;
};


#endif //SUPERMEATBOY_ABSTRACTENTITYFACTORY_H
