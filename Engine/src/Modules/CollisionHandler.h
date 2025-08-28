//
// Created by Максим Процик on 20.08.2023.
//

#ifndef GAMETEST_COLLISIONHANDLER_H
#define GAMETEST_COLLISIONHANDLER_H

#include <unordered_map>
#include <set>

#include "Game/Scene.h"
#include "GameObject/Components/Colliding/Collider.h"
#include "GameObject/GameObject.h"

class CollisionHandler
{
public:
    static CollisionHandler* GetInstance();
    void OnUpdate(const std::vector<GameObject*>& objects);
    void DestroyObjects(const std::vector<GameObject*>& objects);
    void OnFinish();
    std::unordered_map<Collider*, Collider::Collision> GetActiveCollisions(Collider* collider) const;
private:
    static CollisionHandler* m_collidingHandler;
    CollisionHandler() = default;
    std::unordered_map<Collider*, std::unordered_map<Collider*, Collider::Collision>> m_collisions;
    using border_info_t = std::pair<Collider*, std::pair<Vector2D, Vector2D>>;
    std::unordered_map<Collider*, std::set<Collider*>> GetPossibleCollisions(std::vector<border_info_t>& borders,
                                                                             std::function<float(const Vector2D&)> measure) const;

    std::pair<bool, Collider::Collision> HandleCollision(const Collider* collider1,  const Collider* collider2) const;
};


#endif //GAMETEST_COLLISIONHANDLER_H
