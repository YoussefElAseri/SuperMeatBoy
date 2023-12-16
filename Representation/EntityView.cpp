#include "EntityView.h"

EntityView::EntityView(sf::Texture& texture, std::weak_ptr<sf::RenderWindow> window)
    : mWindow(std::move(window)), mTexture(texture) {
    mSprite = sf::Sprite(texture);
}

void EntityView::update(float posX, float posY) {
    mSprite.setPosition(posX, posY);
}

void EntityView::draw() {
    mWindow.lock()->draw(mSprite);
}

