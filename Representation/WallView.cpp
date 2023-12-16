#include "WallView.h"

WallView::WallView(sf::Texture &texture, std::weak_ptr<sf::RenderWindow> window, float positionX, float positionY, float width, float height)
    : EntityView(texture, window) {
    mTextureRect = sf::IntRect(120,60,59,59);
    mSprite.setTextureRect(mTextureRect);
    mSprite.setScale(width/59,height/59);
    mSprite.setOrigin(29.5, 29.5);
    mSprite.setPosition(positionX, positionY);

}
