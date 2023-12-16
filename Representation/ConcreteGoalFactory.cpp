#include "ConcreteGoalFactory.h"
#include "GoalView.h"
#include "../Logic/Goal.h"

ConcreteGoalFactory::ConcreteGoalFactory(std::weak_ptr<sf::RenderWindow> window, sf::Texture &texture)
                                            : mWindow(std::move(window)), mTexture(texture) {

}

Entity ConcreteGoalFactory::create(float positionX, float positionY, float width, float height) const {
    std::shared_ptr<EntityModel> goal(new Goal(positionX, positionY, width, height));
    std::shared_ptr<EntityView> goalView(new GoalView(mTexture,mWindow, positionX, positionY, width, height));
    goal->subscribe(goalView);
    return {goal, goalView};
}