#ifndef SUPERMEATBOY_WORLD_H
#define SUPERMEATBOY_WORLD_H


#include <vector>
#include <memory>
#include <map>
#include "Rectangle.h"

class EntityModel;
class EntityView;
class Player;
class StateManager;
class AbstractEntityFactory;
class AbstractPlayerFactory;
using Entity = std::pair<std::shared_ptr<EntityModel>, std::shared_ptr<EntityView>>;
using PlayerCharacter = std::pair<std::shared_ptr<Player>, std::shared_ptr<EntityView>>;

class World {
private:
    PlayerCharacter mPlayer;
    std::vector<Entity> mEntities;
    Vector mSpawn;
    bool mHitGoal, mPlayerDied;

public:
    World();

    PlayerCharacter getPlayer() const;

    std::vector<Entity> getEntities() const;

    void createPlayer(const std::weak_ptr<AbstractPlayerFactory>& factory, float posX, float posY, float width, float height);

    void createEntity(const std::weak_ptr<AbstractEntityFactory>& factory, float posX, float posY, float width, float height);

    void movePlayer(float deltaTime);

    bool intersects(const Player& player,const EntityModel& entity);

    static bool RayVsRect(const Vector& origin, const Vector& direction, const Rectangle& entity, Vector& contactPoint,
                          Vector& contactNormal, float& tHitNear);

    bool DynamicRectVsRect(const EntityModel& entity, const float deltaTime, Vector& contactPoint,
                           Vector& contactNormal, float& contactTime);

    bool ResolveDynamicRectVsRect(EntityModel& entity, float deltaTime);

    void jump();

    void killPlayer();

    void moveLeft(bool moving);

    void moveRight(bool moving);

    bool getHitGoal() const;

    bool playerDied();

    void clear();

};

#endif //SUPERMEATBOY_WORLD_H
