#include <filesystem>
#include <iostream>

#include "MenuState.h"
#include "StateManager.h"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;


MenuState::MenuState(const std::string& levelsDirectory, sf::Font& font, float windowWidth, float windowHeight) :
    mCurrentLevel(0) {
    mLevelText.setFont(font);
    mLevelText.setCharacterSize(28);

//    Directory volgorde is blijkbaar random

    for (const auto& level:recursive_directory_iterator("../Levels")) {
        std::string filePath {level.path()};
        std::string tempLevelName {};
        for (int i = 10; i < filePath.size() - 4; ++i) {
            tempLevelName += filePath[i];
        }
        mLevelNames.emplace_back(tempLevelName);
    }
    if (mLevelNames.empty()) {
        throw std::runtime_error("no levels available");
    }
    mLevelText.setString(mLevelNames[0]);
    mLevelText.setOrigin(mLevelText.getGlobalBounds().width/2, mLevelText.getLocalBounds().height/2);
    mLevelText.setPosition(240,320);
    mView->reset(sf::FloatRect(0, 0, windowWidth , windowHeight));

}

void MenuState::handleInput(StateManager& stateManager, sf::Keyboard::Key key, bool isPressed) {
    if (!isPressed) return;
    if (key == sf::Keyboard::Down) {
        if (mCurrentLevel > 0) {
            mCurrentLevel -= 1;
        }
    }
    if (key == sf::Keyboard::Up) {
        if (mCurrentLevel < mLevelNames.size()-1) {
            mCurrentLevel += 1;
        }
    }
    if (key == sf::Keyboard::Enter) {
        stateManager.switchToLevel(mLevelNames[mCurrentLevel]);
    }
}

void MenuState::update(StateManager& stateManager, float deltaTime) {
    mLevelText.setString(mLevelNames[mCurrentLevel]);
    mLevelText.setOrigin(mLevelText.getGlobalBounds().width/2, mLevelText.getLocalBounds().height/2);
    mLevelText.setPosition(240,320);
}

void MenuState::draw(std::weak_ptr<sf::RenderWindow>& window) {
    sf::RectangleShape rectangleShape(sf::Vector2f(50,50));
    rectangleShape.setFillColor(sf::Color::Blue);

    window.lock()->draw(mLevelText);
}


