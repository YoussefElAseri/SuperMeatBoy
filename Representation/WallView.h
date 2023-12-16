#ifndef SUPERMEATBOY_WALLVIEW_H
#define SUPERMEATBOY_WALLVIEW_H


#include "EntityView.h"

class WallView : public EntityView {
public:
    WallView(sf::Texture& texture, std::weak_ptr<sf::RenderWindow> window, float positionX, float positionY, float width, float height);
};


#endif //SUPERMEATBOY_WALLVIEW_H
