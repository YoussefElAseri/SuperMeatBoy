#ifndef SUPERMEATBOY_PLAYER_H
#define SUPERMEATBOY_PLAYER_H


#include "EntityModel.h"
#include "Rectangle.h"


class Player : public EntityModel {
private:
    Vector mVelocity;
    const float terminalVelocity = 500, acceleration = 2000, gravity = 1250;
    bool mMovingLeft, mMovingRight, mStanding, mTouchLeft, mTouchRight, mJump;


public:
    Player(float positionX, float positionY, float width, float height);

    void moveLeft(bool moving);

    void moveRight(bool moving);

    void jump();

    void hitWall(bool left, bool right, bool top, bool bottom);

    void updatePosition(float deltaTime);

    void updateVelocity(float deltaTime);

    void checkVelocity();

    void respawn(float newCenterX, float newCenterY);

    void hitGoal();

    Vector getVelocity() const;

    void setVelocity(Vector newVelocity);

    void setJump(bool jump);

    ~Player() = default;
};


#endif //SUPERMEATBOY_PLAYER_H
