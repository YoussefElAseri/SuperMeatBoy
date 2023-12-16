#ifndef SUPERMEATBOY_ABSTRACTPLAYERFACTORY_H
#define SUPERMEATBOY_ABSTRACTPLAYERFACTORY_H


#include <memory>

class Player;
class EntityView;
using PlayerCharacter = std::pair<std::shared_ptr<Player>, std::shared_ptr<EntityView>>;

class AbstractPlayerFactory {
public:
    AbstractPlayerFactory() = default;

    virtual PlayerCharacter create(float positionX, float positionY, float width, float height) const = 0;
};


#endif //SUPERMEATBOY_ABSTRACTPLAYERFACTORY_H
