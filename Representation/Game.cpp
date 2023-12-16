#include "Game.h"
#include "../Logic/Stopwatch.h"


using namespace sf;

Game::Game() : mFramerate(60),
 mWindow(std::make_shared<RenderWindow> (VideoMode(480,640), "Super Meat Boy", Style::Default))  {

    mStateManager = std::make_unique<StateManager>(StateManager(mWindow, "../Levels"));
}

void Game::run() {
    std::shared_ptr<Stopwatch> stopWatch = Stopwatch::getInstance();
    while (mWindow->isOpen()) {
        stopWatch->Tick();
        processEvents();
        if (stopWatch->DeltaTime() >= 1 / mFramerate) {
            float deltaTime = stopWatch->DeltaTime();
            stopWatch->Reset();
            processEvents();
            mStateManager->update(deltaTime);
        }
        render();
    }
}

void Game::processEvents() {
    Event event {};
    while (mWindow->pollEvent(event)) {
        switch (event.type) {
            case Event::KeyPressed:
                mStateManager->handleInput(event.key.code, true);
                break;
            case Event::KeyReleased:
                mStateManager->handleInput(event.key.code, false);
                break;
            case Event::Closed:
                mWindow->close();
                break;
        }

    }
}

void Game::render() {
    mWindow->clear();
    mStateManager->draw();
    mWindow->display();
}