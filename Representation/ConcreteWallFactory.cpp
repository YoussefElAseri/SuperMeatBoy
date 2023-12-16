#include "ConcreteWallFactory.h"

#include <utility>
#include "../Logic/Wall.h"
#include "WallView.h"

ConcreteWallFactory::ConcreteWallFactory(std::weak_ptr<sf::RenderWindow> window,
                                         sf::Texture &texture) : mWindow(std::move(window)), mTexture(texture) {

}

Entity ConcreteWallFactory::create(float positionX, float positionY, float width, float height) const {
    std::shared_ptr<EntityModel> wall(new Wall(positionX, positionY, width, height));
    std::shared_ptr<EntityView> wallView(new WallView(mTexture,mWindow, positionX, positionY, width, height));
    wall->subscribe(wallView);
    return {wall, wallView};
}
