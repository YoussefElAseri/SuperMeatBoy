#include "StateManager.h"
#include "LevelState.h"
#include "MenuState.h"
#include "ConcretePlayerFactory.h"
#include "ConcreteWallFactory.h"
#include "ConcreteFireFactory.h"
#include "ConcreteGoalFactory.h"
#include "../Logic/Camera.h"
#include "../Logic/World.h"

StateManager::StateManager(const std::shared_ptr<sf::RenderWindow>& mWindow, std::string levelsDirectory) :
                            mLevelState(std::make_shared<LevelState>(mWindow->getSize().x,
                                                                     mWindow->getSize().y)),
                                                                     mWindow(mWindow)
                            {

    mTextureHolder = std::make_unique<TextureHolder>();
    mFontHolder = std::make_unique<FontHolder>();
    mTextureHolder->load(Textures::Meatboy,"../SpriteSheets/Animations/4bitmeatboyfinal.png");
    mTextureHolder->load(Textures::Earth,"../SpriteSheets/LevelPalettes/foresttiles01.png");
    mTextureHolder->load(Textures::Fire, "../SpriteSheets/LevelPalettes/obstacles.png");
    mTextureHolder->load(Textures::BandageGirl, "../SpriteSheets/LevelPalettes/robstacles.png");
    mFontHolder->load(Fonts::TitleScreen, "../Fonts/Blomberg.otf");
    auto gamePlayerFactory = std::make_shared<ConcretePlayerFactory>
            (ConcretePlayerFactory(mWindow, mTextureHolder->get(Textures::Meatboy)));
    auto gameWallFactory = std::make_shared<ConcreteWallFactory>
            (ConcreteWallFactory(mWindow, mTextureHolder->get(Textures::Earth)));
    auto gameFireFactory = std::make_shared<ConcreteFireFactory>
            (ConcreteFireFactory(mWindow, mTextureHolder->get(Textures::Fire)));
  auto gameGoalFactory = std::make_shared<ConcreteGoalFactory>
            (ConcreteGoalFactory(mWindow, mTextureHolder->get(Textures::BandageGirl)));
    mLevelState->mPlayerFactory = std::move(gamePlayerFactory);
    mLevelState->mWallFactory = std::move(gameWallFactory);
    mLevelState->mFireFactory = std::move(gameFireFactory);
    mLevelState->mGoalFactory = std::move(gameGoalFactory);
    mMenuState = std::make_shared<MenuState>(MenuState(levelsDirectory, mFontHolder->get(Fonts::TitleScreen),
                                                       mWindow->getSize().x, mWindow->getSize().y));
    mCurrentState = mMenuState;

}

void StateManager::handleInput(sf::Keyboard::Key key, bool isPressed) {
    mCurrentState.lock()->handleInput(*this, key, isPressed);
}

void StateManager::switchToLevel(const std::string &level) {
    mCurrentState = mLevelState;
    mLevelState->loadLevel("../Levels/" + level + ".txt");
}

void StateManager::update(float deltaTime) {
    mCurrentState.lock()->update(*this, deltaTime);
}

void StateManager::draw() {
    mWindow.lock()->setView(mCurrentState.lock()->getView());
    mCurrentState.lock()->draw(mWindow);
}

void StateManager::switchToMenu() {
    mCurrentState = mMenuState;
}
