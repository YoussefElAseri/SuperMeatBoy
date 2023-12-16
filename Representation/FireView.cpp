#include "FireView.h"

FireView::FireView(sf::Texture &texture, std::weak_ptr<sf::RenderWindow> window, float positionX, float positionY, float width, float height)
    : EntityView(texture, window) {
    mTextureRect = sf::IntRect(326,364,74,73);
    mSprite.setTextureRect(mTextureRect);
    mSprite.setScale(width / 74,height / 73);
    mSprite.setOrigin(37, 36.5);
    mSprite.setPosition(positionX, positionY);
}
