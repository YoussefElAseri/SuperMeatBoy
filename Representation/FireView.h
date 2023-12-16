#ifndef SUPERMEATBOY_FIREVIEW_H
#define SUPERMEATBOY_FIREVIEW_H


#include "EntityView.h"

class FireView : public EntityView {
public:
    FireView(sf::Texture& texture, std::weak_ptr<sf::RenderWindow> window, float positionX, float positionY, float width, float height);

};


#endif //SUPERMEATBOY_FIREVIEW_H
