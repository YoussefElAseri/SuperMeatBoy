#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "World.h"
#include "AbstractEntityFactory.h"
#include "AbstractPlayerFactory.h"
#include "Player.h"

World::World() : mSpawn(Vector(0, 0)), mHitGoal(false), mPlayerDied(false) {

}

void World::createPlayer(const std::weak_ptr<AbstractPlayerFactory>& factory, float posX, float posY, float width, float height) {
    PlayerCharacter player = factory.lock()->create(posX,posY, width, height);
    mPlayer = player;
    mSpawn.x = posX;
    mSpawn.y = posY;
}

void World::createEntity(const std::weak_ptr<AbstractEntityFactory>& factory, float posX, float posY, float width, float height) {
    Entity entity = factory.lock()->create(posX, posY, width, height);
    mEntities.emplace_back(entity);
//    mViewableEntities.emplace_back(entity);
}

std::vector<Entity> World::getEntities() const {
    return mEntities;
}



void World::jump() {
    mPlayer.first->setJump(true);
}

PlayerCharacter World::getPlayer() const {
    return mPlayer;
}

void World::moveLeft(bool moving) {
    mPlayer.first->moveLeft(moving);
}

void World::moveRight(bool moving) {
    mPlayer.first->moveRight(moving);
}

void World::clear() {
    mPlayer = {};
    mEntities.clear();
//    mViewableEntities.clear();
    mHitGoal = false;
}

bool World::RayVsRect(const Vector& origin, const Vector& direction, const Rectangle& entity, Vector& contactPoint,
               Vector& contactNormal, float& tHitNear) {

//    Relevant Video: https://www.youtube.com/watch?v=8JJ-4JgR7Dg

    contactNormal = {0, 0};
    contactPoint = {0, 0};

    Vector inverseDirection(1.f / direction.x, 1.f / direction.y);

    Vector tNear ((entity.mOrigin.x - origin.x) * inverseDirection.x,
                  (entity.mOrigin.y - origin.y) * inverseDirection.y);
    Vector tFar ((entity.mOrigin.x + entity.mWidth - origin.x) * inverseDirection.x,
                 (entity.mOrigin.y + entity.mHeight - origin.y) * inverseDirection.y);

    if (std::isnan(tFar.x) or std::isnan(tFar.y)) return false;
    if (std::isnan(tNear.x) or std::isnan(tNear.y)) return false;

    if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
    if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

    if (tNear.x > tFar.y or tNear.y > tFar.x) return false;

    tHitNear = std::max(tNear.x, tNear.y);

    float tHitFar = std::min(tFar.x, tFar.y);

    if (tHitFar < 0) return false;

    contactPoint.x = origin.x + tHitNear * direction.x;
    contactPoint.y = origin.y + tHitNear * direction.y;

    if (tNear.x > tNear.y) {
        if (inverseDirection.x < 0) {
            contactNormal = { 1, 0 };
        }
        else {
            contactNormal = { -1, 0 };
        }
    }
    else if (tNear.x < tNear.y) {
        if (inverseDirection.y < 0) {
            contactNormal = { 0, 1 };
        }
        else {
            contactNormal = { 0, -1 };
        }
    }

    return true;
}

bool World::DynamicRectVsRect(const EntityModel& entity, const float deltaTime, Vector& contactPoint,
                       Vector& contactNormal, float& contactTime) {
//    Check if Player is moving - player should not be in collision at the start
    if (mPlayer.first->getVelocity().x == 0 and mPlayer.first->getVelocity().y == 0) return false;

//    Make expanded entity rectangle
    Vector position(entity.getHitBoxLeft() - mPlayer.first->getDimensions().first / 2,
                    entity.getHitBoxTop() - mPlayer.first->getDimensions().second / 2);
    Vector size(mPlayer.first->getDimensions().first + entity.getDimensions().first,
                mPlayer.first->getDimensions().second + entity.getDimensions().second);
    Rectangle expandedEntity(position, size.x, size.y);

    Vector origin(mPlayer.first->getPosition().first, mPlayer.first->getPosition().second);
    Vector direction(mPlayer.first->getVelocity().x * deltaTime, mPlayer.first->getVelocity().y * deltaTime);

    if (RayVsRect(origin, direction, expandedEntity, contactPoint, contactNormal, contactTime)) {
        return (contactTime >= 0.f and contactTime <= 1.f);
    }
    return false;
}

bool World::ResolveDynamicRectVsRect(EntityModel& entity, float deltaTime) {
    Vector contactPoint(0,0), contactNormal(0,0);
    float contactTime = 0;
    bool touchTop {}, touchBottom {}, touchLeft {}, touchRight{};

    if (DynamicRectVsRect(entity, deltaTime, contactPoint, contactNormal, contactTime)) {
        if (contactNormal.y > 0) touchTop = true;
        else if (contactNormal.x < 0) touchLeft = true;
        else if (contactNormal.y < 0) touchBottom = true;
        else if (contactNormal.x > 0) touchRight = true;


        mPlayer.first->hitWall(touchLeft, touchRight, touchTop, touchBottom);
        Vector newVelocity = mPlayer.first->getVelocity() + contactNormal *
                Vector(std::abs(mPlayer.first->getVelocity().x), std::abs(mPlayer.first->getVelocity().y)) * (1 - contactTime);
        mPlayer.first->setVelocity(newVelocity);
        return true;
    }

    return false;
}

void World::movePlayer(float deltaTime) {
    Vector contactPoint(0, 0), contactNormal(0, 0);
    float t = 0;
    std::vector<std::pair<int, float>> z;
//  Collision needs to be resolved in order of closeness to the player, otherwise the player gets stuck on corners
// Work out collision point, add it to vector along with i
    for (int i = 0; i < mEntities.size(); ++i) {
        if (DynamicRectVsRect(*mEntities[i].first, deltaTime,contactPoint,
                              contactNormal, t)) {
            if (mEntities[i].first->goal()) {
                mHitGoal = true;
                return;
            }
            z.emplace_back( i, t );
        }
    }
// Do the sort
    std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
    {
        return a.second < b.second;
    });
//    See if Player touches a killing obstacle
    for (const auto& entity:mEntities) {
        if (intersects(*mPlayer.first, *entity.first) and entity.first->kill()) {
            killPlayer();
            return;
        }
    }
    // Now resolve the collision in correct order
    for (auto j : z)
        ResolveDynamicRectVsRect(*mEntities[j.first].first, deltaTime);
    mPlayer.first->updatePosition(deltaTime);
    mPlayer.first->updateVelocity(deltaTime);

}

bool World::getHitGoal() const {
    return mHitGoal;
}

bool World::intersects(const Player& player,const EntityModel& entity) {
    if (player.getHitBoxLeft() <= entity.getHitBoxRight() and player.getHitBoxRight() >= entity.getHitBoxLeft()
        and player.getHitBoxTop() <= entity.getHitBoxBottom() and player.getHitBoxBottom() >= entity.getHitBoxTop()) {
        return true;
    }
    return false;
}

bool World::playerDied() {
    if (mPlayerDied) {
        mPlayerDied = false;
        return true;
    }
    return false;
}

void World::killPlayer() {
    mPlayer.first->respawn(mSpawn.x, mSpawn.y);
    mPlayerDied = true;
}
