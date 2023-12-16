#include "Goal.h"

Goal::Goal(float positionX, float positionY, float width, float height) :  EntityModel(positionX, positionY, width, height) {

}

bool Goal::goal() {
    return true;
}
