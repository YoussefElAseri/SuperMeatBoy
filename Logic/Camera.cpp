#include <fstream>
#include <tuple>
#include <iostream>

#include "Camera.h"

using namespace std;

Camera::Camera(float viewWidth, float viewHeight) : mVerticalBorders(-1, 1), mCurrentlyVisible(-1, 1),
                  mViewWidth(viewWidth), mViewHeight(viewHeight), mLevelHeight() {

}

pair<vector<string>, float> Camera::loadLevel(string fileName) {
    vector<pair<char, Vector>> positions {};
    vector<string> completeLevel {};
    ifstream file;
    file.open(fileName);
    float offset {};
    float levelWidth {};

//    Read the file
    if (file.is_open()) {
        while (!file.eof()) {
            string level {};
            file >> level;
            completeLevel.emplace_back(level);
        }
    }
    else {
        throw runtime_error("Level file couldn't be found");
    }
    file.close();

    if (completeLevel.empty()) {
        throw runtime_error("Empty Level");
    }

    levelWidth = mViewWidth;
    mLevelHeight = ((float) (completeLevel.size() - 1) / (float) completeLevel[1].size()) * mViewWidth;
    mVerticalBorders.y = (mLevelHeight / (levelWidth / 2)) - 1;
    mCurrentlyVisible.y = (mViewHeight / (mViewWidth / 2)) - 1;
    offset = mViewWidth / (float) completeLevel[1].size();
    mTileDimension = offset;
    return {completeLevel, offset};
}

float Camera::updateView(float playerPosition) {
    float offset {};
    float playerInCamera = ((mLevelHeight - playerPosition) / (mViewWidth / 2)) - 1;
    float eightyPercentLine = ((mCurrentlyVisible.y - mCurrentlyVisible.x) * 0.8f) + mCurrentlyVisible.x;
     if (playerInCamera > eightyPercentLine and mCurrentlyVisible.y < mVerticalBorders.y) {
        offset = playerInCamera  - eightyPercentLine;
        mCurrentlyVisible.x += offset;
        mCurrentlyVisible.y += offset;
//        Translate to View pixels
        offset *= mViewWidth/2;
    }
//     Return -offset because higher values go down
    return -offset;
}

float Camera::getTileDimension() const {
    return mTileDimension;
}

void Camera::resetView() {
    mCurrentlyVisible.x = -1;
    mCurrentlyVisible.y = (mViewHeight / (mViewWidth / 2)) - 1;
}

bool Camera::playerVisible(float playerPosition) const {
    float playerInCamera = ((mLevelHeight - playerPosition) / (mViewWidth / 2)) - 1;
    if (playerInCamera <= mCurrentlyVisible.y and playerInCamera >= mCurrentlyVisible.x) {
        return true;
    }
    return false;
}

void Camera::updateCamera(float offset) {
    mCurrentlyVisible.x += offset / (mViewWidth / 2);
    mCurrentlyVisible.y += offset / (mViewWidth / 2);
}

bool Camera::reachedEnd() {
    if (mCurrentlyVisible.y >= mVerticalBorders.y) {
        float cameraDifference = mCurrentlyVisible.y - mCurrentlyVisible.x;
        mCurrentlyVisible.y = mVerticalBorders.y;
        mCurrentlyVisible.x = mCurrentlyVisible.y - cameraDifference;
        return true;
    }
    return false;
}
