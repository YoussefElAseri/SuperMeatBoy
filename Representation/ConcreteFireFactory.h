#ifndef SUPERMEATBOY_CONCRETEFIREFACTORY_H
#define SUPERMEATBOY_CONCRETEFIREFACTORY_H


#include "../Logic/AbstractEntityFactory.h"
#include "SFML/Graphics.hpp"

class ConcreteFireFactory : public AbstractEntityFactory {
private:
    std::weak_ptr<sf::RenderWindow> mWindow;
    sf::Texture& mTexture;

public:
    ConcreteFireFactory(std::weak_ptr<sf::RenderWindow> window, sf::Texture& texture);

    Entity create(float positionX, float positionY, float width, float height) const;
};


#endif //SUPERMEATBOY_CONCRETEFIREFACTORY_H
