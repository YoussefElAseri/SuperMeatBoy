#ifndef SUPERMEATBOY_LEVELSTATE_H
#define SUPERMEATBOY_LEVELSTATE_H


#include "State.h"
#include "ResourceIdentifiers.h"

class World;
class Camera;
class ConcretePlayerFactory;
class ConcreteGoalFactory;
class ConcreteWallFactory;
class ConcreteFireFactory;

class LevelState : public State {
private:
    std::unique_ptr<World> mWorld;
    std::unique_ptr<Camera> mCamera;
    std::shared_ptr<ConcretePlayerFactory> mPlayerFactory;
    std::shared_ptr<ConcreteWallFactory> mWallFactory;
    std::shared_ptr<ConcreteFireFactory> mFireFactory;
    std::shared_ptr<ConcreteGoalFactory> mGoalFactory;
    /*
     * Check if space was released to jump again
     */
    bool mSpaceReleased;
    bool mPlayerLoaded, mAutoScroll;
    float mOriginalViewY;

    friend class StateManager;

public:
    LevelState(float windowWidth, float windowHeight);

    void handleInput(StateManager& stateManager, sf::Keyboard::Key key, bool isPressed) override;

    void loadLevel(const std::string& fileName);

    void update(StateManager& stateManager, float deltaTime) override;

    void draw(std::weak_ptr<sf::RenderWindow>& window) override;

};


#endif //SUPERMEATBOY_LEVELSTATE_H
