#ifndef SUPERMEATBOY_CONCRETEWALLFACTORY_H
#define SUPERMEATBOY_CONCRETEWALLFACTORY_H


#include "../Logic/AbstractEntityFactory.h"
#include "SFML/Graphics.hpp"

class ConcreteWallFactory : public AbstractEntityFactory {
private:
    std::weak_ptr<sf::RenderWindow> mWindow;
    sf::Texture& mTexture;

public:
    ConcreteWallFactory(std::weak_ptr<sf::RenderWindow> window, sf::Texture& texture);

    Entity create(float positionX, float positionY, float width, float height) const;
};


#endif //SUPERMEATBOY_CONCRETEWALLFACTORY_H
