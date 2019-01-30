#pragma once
#include <vector>
#include <iostream>
#include "GameObject.h"
#include "RigidBody.h"
#include "Collision.h"
#include "RoomManager.h"
#include "MoveInput.h"
#include "InteractionManager.h"
#include "TriggerCollision.h"
#include "InteractiveCollision.h"


class PhysicsManager
{
public:
	static PhysicsManager& getInstance();
	void addGameObject(std::shared_ptr<GameObject> object);
	void addGameObjectStatic(std::shared_ptr<GameObject> object);
	void addGameObjectDynamic(std::shared_ptr<GameObject> object);
	void removeGameObject(std::shared_ptr<GameObject> object);
	bool AABBvsAABB(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration);
	void resolveCollisionsPlayer(std::shared_ptr<GameObject> body1, std::shared_ptr<GameObject> body2, float delta);
	void update(float deltaTime);
	std::vector<std::shared_ptr<GameObject>>& getCollider();
	std::vector<std::shared_ptr<GameObject>>& getStaticCollider();
	std::vector<std::shared_ptr<GameObject>>& getDynamicCollider();
	void setCurrentRoom(int value);
	int& getRoomId();

private:
	void findCollision(float delta);
	PhysicsManager(void) = default;
	~PhysicsManager(void) = default;
	PhysicsManager(const PhysicsManager& p) = delete;
	PhysicsManager& operator=(PhysicsManager const&) = delete;

	void roomTrigger(std::shared_ptr<RoomTriggerCollision> roomCollision1, std::shared_ptr<RoomTriggerCollision> roomCollision2, std::shared_ptr<GameObject> object1, std::shared_ptr<GameObject> object2);
	void interactiveTrigger(std::shared_ptr<InteractiveCollision> interactiveCollision, std::shared_ptr<GameObject> object);
	void playerTrigger(std::shared_ptr<GameObject> object1, std::shared_ptr<GameObject> object2, float delta, bool& hasNoCollision);
	void resetPlayerMovement(std::shared_ptr<GameObject> player);

	std::vector<std::shared_ptr<GameObject>> m_ColliderObjects;

	std::vector<std::shared_ptr<GameObject>> m_ColliderObjects_Static;
	std::vector<std::shared_ptr<GameObject>> m_ColliderObjects_Dynamic;
	sf::Vector2f m_DefaultVelocity;

	sf::FloatRect& getFloatRect(std::shared_ptr<GameObject> object);

	int m_RoomId = 1;
};

