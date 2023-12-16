#include <iostream>
#include "Player.h"

Player::Player(float positionX, float positionY, float width, float height) : EntityModel(positionX, positionY, width *0.75f, height*0.75f),
                                                    mVelocity(0, 0), mTouchLeft(false), mJump(false),
                                                    mStanding(false), mMovingRight(false), mMovingLeft(false),
                                                    mTouchRight (false) {

}

void Player::moveLeft(bool moving) {
    mMovingLeft = moving;
    if (moving) {
        mTouchRight = false;
    }
}


void Player::moveRight(bool moving) {
    mMovingRight = moving;
    if (moving) {
        mTouchLeft = false;
    }
}

void Player::jump() {
    if (mStanding) {
        mVelocity.y = -terminalVelocity;
    }
    else if (mTouchLeft) {
        mVelocity.x = -terminalVelocity;
        mVelocity.y = -terminalVelocity;
    }
    else if (mTouchRight) {
        mVelocity.x = terminalVelocity;
        mVelocity.y = -terminalVelocity;
    }
    mStanding = false;
}

void Player::hitWall(bool left, bool right, bool top, bool bottom) {
    mTouchLeft = left;
    if (left) {
        mMovingLeft = false;
    }
    mTouchRight = right;
    if (right) {
        mMovingRight = false;
    }
    mStanding = bottom;
    if (top and mVelocity.y < 0) {
        mVelocity.y = 0;
    }
}

void Player::updateVelocity(float deltaTime) {
    if (mMovingLeft) {
        mVelocity.x -= acceleration * deltaTime;
    }
    else if (!mMovingLeft and mVelocity.x < 0) {
        mVelocity.x +=  acceleration * deltaTime;
        if (mVelocity.x > 0) {
            mVelocity.x = 0;
        }
    }
    if (mMovingRight) {
        mVelocity.x += acceleration * deltaTime;
    }
    else if (!mMovingRight and mVelocity.x > 0) {
        mVelocity.x -= acceleration * deltaTime;
        if (mVelocity.x < 0) {
            mVelocity.x = 0;
        }
    }
    mVelocity.y += gravity * deltaTime;
    mTouchRight = false;
    mTouchLeft = false;
    checkVelocity();
}

void Player::respawn(float newCenterX, float newCenterY) {
    positionX = newCenterX;
    positionY = newCenterY;
    mVelocity.x = 0;
    mVelocity.y = 0;
    mStanding = false;
    mMovingRight = false;
    mMovingLeft = false;
    mTouchRight = false;
    mTouchLeft = false;
    mJump = false;
    update();
}

void Player::hitGoal() {
    mVelocity.x = 0;
    mVelocity.y = 0;
}

void Player::updatePosition(float deltaTime) {
    if (mJump) {
        jump();
        mJump = false;
    }
    positionX += mVelocity.x * deltaTime;
    positionY += mVelocity.y * deltaTime;
    update();
}

Vector Player::getVelocity() const {
    return mVelocity;
}

void Player::setVelocity(Vector newVelocity) {
    mVelocity = newVelocity;
    checkVelocity();
}

void Player::checkVelocity() {
    if (mVelocity.y > terminalVelocity) {
        mVelocity.y = terminalVelocity;
    }
    else if (mVelocity.y < -terminalVelocity) {
        mVelocity.y = -terminalVelocity;
    }
    if (mVelocity.x > terminalVelocity) {
        mVelocity.x = terminalVelocity;
    }
    else if (mVelocity.x < -terminalVelocity) {
        mVelocity.x = -terminalVelocity;
    }
}

void Player::setJump(bool jump) {
    mJump = jump;
}

