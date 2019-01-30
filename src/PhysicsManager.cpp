#pragma once
#include "stdafx.h"
#include "PhysicsManager.h"

PhysicsManager& PhysicsManager::getInstance()
{
	static PhysicsManager m_Instance;

	return m_Instance;
}

void PhysicsManager::addGameObject(std::shared_ptr<GameObject> object)
{
	m_ColliderObjects.push_back(object);
}

void PhysicsManager::addGameObjectStatic(std::shared_ptr<GameObject> object)
{
	m_ColliderObjects_Static.push_back(object);
}

void PhysicsManager::addGameObjectDynamic(std::shared_ptr<GameObject> object)
{
	m_ColliderObjects_Dynamic.push_back(object);
}

void PhysicsManager::removeGameObject(std::shared_ptr<GameObject> object)
{
	for (int it = 0; it < m_ColliderObjects.size(); it++)
	{
		if (m_ColliderObjects.at(it) == object) m_ColliderObjects.erase(m_ColliderObjects.begin() + it);
	}
}

void PhysicsManager::findCollision(float delta)
{
	bool hasNoCollision = true;

	for (auto& i : m_ColliderObjects_Dynamic)
	{
		for (auto& j : m_ColliderObjects_Static)
		{
			sf::Vector2f normal;
			float penetration;

			if (i != j && AABBvsAABB(getFloatRect(i), getFloatRect(j), normal, penetration))
			{

				playerTrigger(i, j, delta, hasNoCollision);

				auto roomCollision1 = i->getComponent<RoomTriggerCollision>("RoomTriggerCollision");
				auto roomCollsion2 = j->getComponent<RoomTriggerCollision>("RoomTriggerCollision");
				roomTrigger(roomCollision1, roomCollsion2, i, j);

				auto interactiveCollision = i->getComponent<InteractiveCollision>("InteractiveCollision");
				interactiveTrigger(interactiveCollision, j);
			}
			else if (hasNoCollision)
			{
				if (i->getComponent<MoveInput>("MoveInput")) resetPlayerMovement(i);

				else if (j->getComponent<MoveInput>("MoveInput")) resetPlayerMovement(j);
			}
		}
	}

	for (auto& i : m_ColliderObjects_Dynamic)
	{
		for (auto& j : m_ColliderObjects_Dynamic)
		{
			sf::Vector2f normal;
			float penetration;

			if (i != j && AABBvsAABB(getFloatRect(i), getFloatRect(j), normal, penetration))
			{

				playerTrigger(i, j, delta, hasNoCollision);

				auto roomCollision1 = i->getComponent<RoomTriggerCollision>("RoomTriggerCollision");
				auto roomCollsion2 = j->getComponent<RoomTriggerCollision>("RoomTriggerCollision");
				roomTrigger(roomCollision1, roomCollsion2, i, j);

				auto interactiveCollision = i->getComponent<InteractiveCollision>("InteractiveCollision");
				interactiveTrigger(interactiveCollision, j);
			}
			else if (hasNoCollision)
			{
				if (i->getComponent<MoveInput>("MoveInput")) resetPlayerMovement(i);

				else if (j->getComponent<MoveInput>("MoveInput")) resetPlayerMovement(j);
			}
		}
	}

	/*for (auto& i : m_ColliderObjects)
	{
		for (auto& j : m_ColliderObjects)
		{
			sf::Vector2f normal;
			float penetration;

			if (i->getComponent<RigidBody>("RigidBody")->isStatic() && j->getComponent<RigidBody>("RigidBody")->isStatic()) continue;

			if (i != j && AABBvsAABB(getFloatRect(i), getFloatRect(j), normal, penetration))
			{
				
				playerTrigger(i, j, delta, hasNoCollision);

				auto roomCollision1 = i->getComponent<RoomTriggerCollision>("RoomTriggerCollision");
				auto roomCollsion2 = j->getComponent<RoomTriggerCollision>("RoomTriggerCollision");
				roomTrigger(roomCollision1, roomCollsion2, i, j);
			
				auto interactiveCollision = i->getComponent<InteractiveCollision>("InteractiveCollision");
				interactiveTrigger(interactiveCollision, j);
			}
			else if (hasNoCollision)
			{
				if (i->getComponent<MoveInput>("MoveInput")) resetPlayerMovement(i);

				else if (j->getComponent<MoveInput>("MoveInput")) resetPlayerMovement(j);
			}
		}
	}*/
}

void PhysicsManager::roomTrigger(std::shared_ptr<RoomTriggerCollision> roomCollision1, std::shared_ptr<RoomTriggerCollision> roomCollision2, std::shared_ptr<GameObject> object1, std::shared_ptr<GameObject> object2)
{
	if (roomCollision1 && !roomCollision1->isTriggered())
	{
		RoomManager::getInstance().notifyObserver(object1, object2);
	}
	else if (roomCollision2 && !roomCollision2->isTriggered())
	{
		RoomManager::getInstance().notifyObserver(object2, object1);
	}
	else RoomManager::getInstance().resetAllColliderTrigger();
}

void PhysicsManager::interactiveTrigger(std::shared_ptr<InteractiveCollision> interactiveCollision, std::shared_ptr<GameObject> object)
{
	if (!interactiveCollision)
		interactiveCollision = object->getComponent<InteractiveCollision>("InteractiveCollision");

	if (interactiveCollision && !interactiveCollision->isTriggered())
	{
		interactiveCollision->setIsTriggered(true);
	}
	//else if (interactiveCollision) {
	//	interactiveCollision->setIsTriggered(false);
	//}
}

void PhysicsManager::playerTrigger(std::shared_ptr<GameObject> object1, std::shared_ptr<GameObject> object2, float delta, bool& hasNoCollision)
{
	if (object1->getComponent<MoveInput>("MoveInput") && object2->getComponent<Collision>("Collision"))
	{
		resolveCollisionsPlayer(object1, object2, delta);
		hasNoCollision = false;
	}
	else if (object2->getComponent<MoveInput>("MoveInput") && object1->getComponent<Collision>("Collision"))
	{
		resolveCollisionsPlayer(object2, object1, delta);
		hasNoCollision = false;
	}
}

void PhysicsManager::resetPlayerMovement(std::shared_ptr<GameObject> player)
{
	auto comp = player->getComponent<RigidBody>("RigidBody")->getRigBody();

	float defaultSpeed = comp->movementSpeed;

	if (!(comp->velocityUp == sf::Vector2f(defaultSpeed, defaultSpeed) && comp->velocitySide == sf::Vector2f(defaultSpeed, defaultSpeed)))
	{
		comp->velocityUp.x = defaultSpeed;
		comp->velocityUp.y = defaultSpeed;
		comp->velocitySide.x = defaultSpeed;
		comp->velocitySide.y = defaultSpeed;
	}
}

sf::FloatRect & PhysicsManager::getFloatRect(std::shared_ptr<GameObject> object)
{
	auto collisionComponent = object->getComponent<Collision>();

	return collisionComponent->getShape();
}

bool PhysicsManager::AABBvsAABB(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration)
{
	auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
	{
		return sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);
	};
	sf::Vector2f n = getCenter(b) - getCenter(a);
	float a_extent = a.width * 0.5f;
	float b_extent = b.width * 0.5f;
	float x_overlap = a_extent + b_extent - abs(n.x);

	if (x_overlap > 0) {
		float a_extent = a.height * 0.5f;
		float b_extent = b.height * 0.5f;
		float y_overlap = a_extent + b_extent - abs(n.y);

		if (y_overlap > 0)
		{
			if (x_overlap < y_overlap)
			{
				if (n.x < 0)
					normal = sf::Vector2f(1.0f, 0.0f);
				else
					normal = sf::Vector2f(-1.0f, 0.0f);
				penetration = x_overlap;
				return true;
			}
			else
			{
				if (n.y < 0)
					normal = sf::Vector2f(0, 1);
				else
					normal = sf::Vector2f(0, -1);
				penetration = y_overlap;
				return true;
			}
		}
	}
	return false;
}

void PhysicsManager::resolveCollisionsPlayer(std::shared_ptr<GameObject> body1, std::shared_ptr<GameObject> body2, float deltaTime)
{
	auto body1Pos = body1->getComponent<Collision>("Collision")->getShape();
	auto body2Pos = body2->getComponent<Collision>("Collision")->getShape();

	// To the Right
	if (body1Pos.left > body2Pos.left + body2Pos.width - 200 * deltaTime)
	{
		body1->getComponent<RigidBody>("RigidBody")->getRigBody()->velocitySide.x = 0.0f;
	}
	// To the Bottom
	if (body1Pos.top > body2Pos.top + body2Pos.height - 200 * deltaTime)
	{
		body1->getComponent<RigidBody>("RigidBody")->getRigBody()->velocityUp.x = 0.0f;
	}
	// To the Left
	if (body1Pos.left + body1Pos.width - 200 * deltaTime < body2Pos.left)
	{
		body1->getComponent<RigidBody>("RigidBody")->getRigBody()->velocitySide.y = 0.0f;
	}
	// To the Top
	if (body1Pos.top + body1Pos.height - 200 * deltaTime < body2Pos.top)
	{
		body1->getComponent<RigidBody>("RigidBody")->getRigBody()->velocityUp.y = 0.0f;
	}
}

void PhysicsManager::update(float deltaTime)
{
	for (auto it : m_ColliderObjects)
	{
		auto col = it->getComponent<Collision>("Collision");
		if (col)
		{
			col->getShape().left = it->getComponent<RigidBody>("RigidBody")->getRigBody()->position.x;
			col->getShape().top = it->getComponent<RigidBody>("RigidBody")->getRigBody()->position.y;
		}
	}
	findCollision(deltaTime);
}

std::vector<std::shared_ptr<GameObject>>& PhysicsManager::getCollider()
{
	return m_ColliderObjects;
}

std::vector<std::shared_ptr<GameObject>>& PhysicsManager::getStaticCollider()
{
	return m_ColliderObjects_Static;
}

std::vector<std::shared_ptr<GameObject>>& PhysicsManager::getDynamicCollider()
{
	return m_ColliderObjects_Dynamic;
}

void PhysicsManager::setCurrentRoom(int value)
{
	m_RoomId = value;
}

int & PhysicsManager::getRoomId()
{
	return m_RoomId;
}
