#ifndef SUPERMEATBOY_CONCRETEGOALFACTORY_H
#define SUPERMEATBOY_CONCRETEGOALFACTORY_H


#include "../Logic/AbstractEntityFactory.h"
#include "SFML/Graphics.hpp"

class ConcreteGoalFactory : public AbstractEntityFactory {
private:
    std::weak_ptr<sf::RenderWindow> mWindow;
    sf::Texture& mTexture;

public:
    ConcreteGoalFactory(std::weak_ptr<sf::RenderWindow> window, sf::Texture& texture);

    Entity create(float positionX, float positionY, float width, float height) const;
};


#endif //SUPERMEATBOY_CONCRETEGOALFACTORY_H
