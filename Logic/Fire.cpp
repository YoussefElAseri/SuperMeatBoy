#include "Fire.h"

Fire::Fire(float positionX, float positionY, float width, float height) :  EntityModel(positionX, positionY, width, height*0.8f) {
}

bool Fire::kill() {
    return true;
}
