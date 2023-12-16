#include "GoalView.h"

GoalView::GoalView(sf::Texture &texture, std::weak_ptr<sf::RenderWindow> window, float positionX, float positionY, float width, float height) :
                    EntityView(texture, window) {
    mTextureRect = sf::IntRect(720,265,47,41);
    mSprite.setTextureRect(mTextureRect);
    mSprite.setOrigin(23.5, 20.5);
    mSprite.setPosition(positionX, positionY);
    mSprite.setScale(width / 47,height / 41);
}
