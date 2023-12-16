#ifndef SUPERMEATBOY_ENTITYVIEW_H
#define SUPERMEATBOY_ENTITYVIEW_H

#include <memory>
#include "SFML/Graphics.hpp"

#include "ResourceIdentifiers.h"
#include "../Logic/Observer.h"

class EntityView : public Observer, private sf::NonCopyable {
protected:
    sf::Sprite mSprite;
    sf::Texture& mTexture;
    sf::IntRect mTextureRect;
    std::weak_ptr<sf::RenderWindow> mWindow;

public:
    EntityView(sf::Texture& texture, std::weak_ptr<sf::RenderWindow> window);

    void draw();

    void update(float posX, float posY) override;

};


#endif //SUPERMEATBOY_ENTITYVIEW_H
