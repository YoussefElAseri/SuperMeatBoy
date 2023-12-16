#ifndef SUPERMEATBOY_CAMERA_H
#define SUPERMEATBOY_CAMERA_H


#include <vector>
#include <string>

#include "Rectangle.h"

class Camera {
private:
//  Horizontal Borders aren't needed
    Vector mVerticalBorders;
    Vector mCurrentlyVisible;
    float mViewWidth, mViewHeight, mLevelHeight;
    float mTileDimension;

public:
    Camera(float viewWidth, float viewHeight);

    std::pair<std::vector<std::string>, float> loadLevel(std::string fileName);

    float updateView(float playerPosition);

    float getTileDimension() const;

    void resetView();

    void updateCamera(float offset);

    bool reachedEnd();

    bool playerVisible(float playerPosition) const;

    ~Camera() = default;
};


#endif //SUPERMEATBOY_CAMERA_H
