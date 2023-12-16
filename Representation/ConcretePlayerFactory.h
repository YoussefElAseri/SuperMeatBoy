#ifndef SUPERMEATBOY_CONCRETEPLAYERFACTORY_H
#define SUPERMEATBOY_CONCRETEPLAYERFACTORY_H


#include "../Logic/AbstractPlayerFactory.h"
#include "SFML/Graphics.hpp"

class ConcretePlayerFactory : public AbstractPlayerFactory {
private:
    std::weak_ptr<sf::RenderWindow> mWindow;
    sf::Texture& mTexture;

public:
    ConcretePlayerFactory(std::weak_ptr<sf::RenderWindow> window, sf::Texture& texture);

    PlayerCharacter create(float positionX, float positionY, float width, float height) const;
};


#endif //SUPERMEATBOY_CONCRETEPLAYERFACTORY_H
