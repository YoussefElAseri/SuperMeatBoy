#ifndef SUPERMEATBOY_STATEMANAGER_H
#define SUPERMEATBOY_STATEMANAGER_H


#include <memory>
#include "SFML/Graphics.hpp"
#include "../Logic/ResourceHolder.h"
#include "ResourceIdentifiers.h"


class Game;
class State;
class LevelState;
class MenuState;
class AbstractEntityFactory;
class AbstractPlayerFactory;

class StateManager {
private:
    std::unique_ptr<TextureHolder> mTextureHolder;
    std::unique_ptr<FontHolder> mFontHolder;
    std::shared_ptr<LevelState> mLevelState;
    std::shared_ptr<MenuState> mMenuState;
    std::weak_ptr<State> mCurrentState;
    std::weak_ptr<sf::RenderWindow> mWindow;

    friend class MenuState;
    friend class LevelState;

    void switchToLevel(const std::string& level);

    void switchToMenu();

public:
    StateManager(const std::shared_ptr<sf::RenderWindow>& mWindow, std::string levelsDirectory);

    void handleInput(sf::Keyboard::Key key, bool isPressed);

    void update(float deltaTime);

    void draw();
};


#endif //SUPERMEATBOY_STATEMANAGER_H
