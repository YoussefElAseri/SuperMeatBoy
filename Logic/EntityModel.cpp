#include "EntityModel.h"
#include "Observer.h"

EntityModel::EntityModel(float posX, float posY, float width, float height) : width(width), height(height),
                                                                                positionX(posX), positionY(posY) {
    update();
}

void EntityModel::update() {
    for (const auto& observer:mObservers) {
        observer->update(positionX, positionY);
    }
}

float EntityModel::getHitBoxTop() const {
    return positionY - (height / 2);
}

float EntityModel::getHitBoxBottom() const {
    return positionY + (height / 2);
}

float EntityModel::getHitBoxLeft() const {
    return positionX - (width / 2);
}

float EntityModel::getHitBoxRight() const {
    return positionX + (width / 2);
}

std::pair<float, float> EntityModel::getDimensions() const {
    return {width, height};
}

std::pair<float, float> EntityModel::getPosition() const {
    return {positionX, positionY};
}

bool EntityModel::kill() {
    return false;
}

bool EntityModel::goal() {
    return false;
}