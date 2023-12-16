#include "ConcretePlayerFactory.h"

#include <utility>
#include "../Logic/Player.h"
#include "PlayerView.h"

ConcretePlayerFactory::ConcretePlayerFactory(std::weak_ptr<sf::RenderWindow> window,
                                             sf::Texture& texture) : mWindow(std::move(window)),
                                             mTexture(texture) {

}

PlayerCharacter ConcretePlayerFactory::create(float positionX, float positionY, float width, float height) const {
    std::shared_ptr<Player> player(new Player(positionX, positionY, width, height));
    std::shared_ptr<PlayerView> playerView(new PlayerView(mTexture,mWindow, positionX, positionY, width, height));
    player->subscribe(playerView);
    return {player, playerView};
}

