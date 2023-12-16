#ifndef SUPERMEATBOY_GAME_H
#define SUPERMEATBOY_GAME_H


#include <memory>

#include "SFML/Graphics.hpp"
#include "StateManager.h"

class Game {
private:
    friend class StateManager;
    std::unique_ptr<StateManager> mStateManager;
    std::shared_ptr<sf::RenderWindow> mWindow;
    float mFramerate;

    void processEvents();

    void render();

public:
    Game();

    void run();
};


#endif //SUPERMEATBOY_GAME_H
