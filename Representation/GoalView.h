#ifndef SUPERMEATBOY_GOALVIEW_H
#define SUPERMEATBOY_GOALVIEW_H


#include "EntityView.h"

class GoalView : public EntityView {
public:
    GoalView(sf::Texture &texture, std::weak_ptr<sf::RenderWindow> window, float positionX, float positionY, float width, float height);

};


#endif //SUPERMEATBOY_GOALVIEW_H
