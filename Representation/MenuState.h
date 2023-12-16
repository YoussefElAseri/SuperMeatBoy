#ifndef SUPERMEATBOY_MENUSTATE_H
#define SUPERMEATBOY_MENUSTATE_H


#include "State.h"

class StateManager;

class MenuState : public State {
private:
    sf::Text mLevelText;
    std::vector<std::string> mLevelNames;
    int mCurrentLevel;

public:
    MenuState(const std::string& levelsDirectory, sf::Font& font, float windowWidth, float windowHeight);

    void handleInput(StateManager& stateManager, sf::Keyboard::Key key, bool isPressed) override;

    void update(StateManager& stateManager, float deltaTime) override;

    void draw(std::weak_ptr<sf::RenderWindow>& window) override;
};


#endif //SUPERMEATBOY_MENUSTATE_H
