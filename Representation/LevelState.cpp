#include <fstream>
#include <iostream>

#include "LevelState.h"
#include "../Logic/World.h"
#include "../Logic/Camera.h"
#include "StateManager.h"
#include "ConcretePlayerFactory.h"
#include "ConcreteWallFactory.h"
#include "ConcreteFireFactory.h"
#include "ConcreteGoalFactory.h"
#include "../Logic/Player.h"
#include "EntityView.h"

using namespace std;

LevelState::LevelState(float windowWidth, float windowHeight) : mWorld(make_unique<World>()), mPlayerLoaded(false), mPlayerFactory(), mWallFactory(),
                            mSpaceReleased(true), mCamera(make_unique<Camera>(Camera(windowWidth, windowHeight))),
                            mOriginalViewY(), mAutoScroll(false) {
    mView->reset(sf::FloatRect(0, 0, windowWidth , windowHeight));
}

void LevelState::loadLevel(const string &fileName) {
    mWorld->clear();
    pair<vector<string>, float> cameraOutput = mCamera->loadLevel(fileName);
    vector<string> level = cameraOutput.first;
    float width {mCamera->getTileDimension()}, height {mCamera->getTileDimension()};
    float offset = cameraOutput.second;
    float positionX {(offset / 2) - offset}, positionY {offset / 2};
    for (const auto& symbolRow:level) {
        if (symbolRow == "auto") {
            mAutoScroll = true;
            continue;
        }
        else if (symbolRow == "not-auto") {
            continue;
        }
        for (const auto& symbol:symbolRow) {
            positionX += offset;
            if (symbol == '-') {
                continue;
            }
            else if (symbol == 'p') {
                mWorld->createPlayer(mPlayerFactory, positionX, positionY, width, height);
                mPlayerLoaded = true;
            }
            else if (symbol == 'w') {
                mWorld->createEntity(mWallFactory, positionX, positionY, width, height);
            }
            else if (symbol == 'f') {
                mWorld->createEntity(mFireFactory, positionX, positionY, width, height);
            }
            else if (symbol == 'g') {
                mWorld->createEntity(mGoalFactory, positionX, positionY, width, height);
            }
            else {
                throw std::runtime_error("Level character does not exist");
            }
        }
        positionY += offset;
        positionX = (offset / 2) - offset;
    }
    mOriginalViewY = level.size()/level[1].size() * mView->getSize().x;
    mView->setCenter(mView->getCenter().x, mOriginalViewY);
}

void LevelState::handleInput(StateManager &stateManager, sf::Keyboard::Key key, bool isPressed) {
    if (!mPlayerLoaded) return;
    if (key == sf::Keyboard::A or key == sf::Keyboard::Left) {
        mWorld->moveLeft(isPressed);
    }
    else if (key == sf::Keyboard::D or key == sf::Keyboard::Right) {
        mWorld->moveRight(isPressed);
    }
    else if (key == sf::Keyboard::Space) {
        if (isPressed and mSpaceReleased) {
            mWorld->jump();
            mSpaceReleased = false;
        }
        else if (!isPressed) {
            mSpaceReleased = true;
        }
    }
    else if (key == sf::Keyboard::Escape) {
        mWorld->clear();
        stateManager.switchToMenu();
    }
}

void LevelState::update(StateManager& stateManager, float deltaTime) {
    if (mWorld->playerDied()) {
        mView->setCenter(mView->getCenter().x, mOriginalViewY);
        mCamera->resetView();
    }
    if (!mCamera->playerVisible(mWorld->getPlayer().first->getPosition().second)) {
        mWorld->killPlayer();
        mCamera->resetView();
    }
    if (mWorld->getHitGoal()) {
        stateManager.switchToMenu();
    }
    if (mAutoScroll and !mCamera->reachedEnd()) {
        mView->move(0, -1);
        mCamera->updateCamera(1);
    }
    if (mPlayerLoaded) {
        mWorld->movePlayer(deltaTime);
        float offset = mCamera->updateView(mWorld->getPlayer().first->getPosition().second);
        mView->move(0, offset);
    }
}

void LevelState::draw(weak_ptr<sf::RenderWindow>& window) {
    window.lock()->setView(*mView);
    for (const auto& entity:mWorld->getEntities()) {
        entity.second->draw();

    }
    if (mPlayerLoaded) {
        mWorld->getPlayer().second->draw();
    }
}