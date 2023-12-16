#include "ConcreteFireFactory.h"

#include <utility>
#include "../Logic/Fire.h"
#include "FireView.h"

ConcreteFireFactory::ConcreteFireFactory(std::weak_ptr<sf::RenderWindow> window,
                                         sf::Texture &texture) : mWindow(std::move(window)), mTexture(texture) {

}

Entity ConcreteFireFactory::create(float positionX, float positionY, float width, float height) const {
    std::shared_ptr<EntityModel> fire(new Fire(positionX, positionY, width, height));
    std::shared_ptr<EntityView> fireView(new FireView(mTexture,mWindow, positionX, positionY, width, height));
    fire->subscribe(fireView);
    return {fire, fireView};
}
