//#include "animationIdentifiers.h"
#include "PlayerView.h"

PlayerView::PlayerView(sf::Texture& texture, std::weak_ptr<sf::RenderWindow> window,
                       float positionX, float positionY, float width, float height) : EntityView(texture, window) {
    mTextureRect = sf::IntRect (200, 61, 46, 45);
    mSprite.setTextureRect(mTextureRect);
    mSprite.setScale((width / 46) * 0.75f,(height / 45) * 0.75f);
    mSprite.setOrigin(23, 22.5);
    mSprite.setPosition(positionX, positionY);
}
