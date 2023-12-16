#ifndef SUPERMEATBOY_PLAYERVIEW_H
#define SUPERMEATBOY_PLAYERVIEW_H


#include "EntityView.h"

class Player;

class PlayerView : public EntityView {
public:
    PlayerView(sf::Texture& texture, std::weak_ptr<sf::RenderWindow> window, float positionX, float positionY, float width, float height);
};


#endif //SUPERMEATBOY_PLAYERVIEW_H
