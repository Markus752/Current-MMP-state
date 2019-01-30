#pragma once
#include <list>
#include "Collision.h"
#include <vector>
#include "IComponent.h"

struct RigBody
{
	sf::Vector2f& position;
	sf::Vector2f velocityUp;
	sf::Vector2f velocitySide;
	float movementSpeed = 0.0f;
};


class RigidBody : public IComponent
{
public:
	RigidBody(std::shared_ptr<RigBody> rig, bool isStatic = true)
		:m_Rig(rig)	
		,m_IsStatic(isStatic)
	{
		
	}

	std::shared_ptr<RigBody>& getRigBody();
	void addCollisionComponents(std::shared_ptr<Collision> collision);
	bool isStatic();
	void init() override;
	void update(float delta) override;

private:
	std::shared_ptr<RigBody> m_Rig;
	std::vector<std::shared_ptr<Collision>> m_CollisionComponents;
	bool m_IsStatic;
};

