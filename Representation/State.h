#ifndef SUPERMEATBOY_STATE_H
#define SUPERMEATBOY_STATE_H


#include <memory>

#include "SFML/Graphics.hpp"

class StateManager;

class State {
protected:
    std::unique_ptr<sf::View> mView;

public:
    State() : mView(std::make_unique<sf::View>()) {}

    virtual void handleInput(StateManager& stateManager, sf::Keyboard::Key key, bool isPressed) = 0;

    virtual void update(StateManager& stateManager, float deltaTime) = 0;

    virtual void draw(std::weak_ptr<sf::RenderWindow>& window) = 0;

    sf::View& getView() {
        return *mView;
    }

};


#endif //SUPERMEATBOY_STATE_H
