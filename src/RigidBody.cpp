#include "stdafx.h"
#include "RigidBody.h"

std::shared_ptr<RigBody>& RigidBody::getRigBody()
{
	return m_Rig;
}

void RigidBody::addCollisionComponents(std::shared_ptr<Collision> collision)
{
	m_CollisionComponents.push_back(collision);
}

bool RigidBody::isStatic()
{
	return m_IsStatic;
}

void RigidBody::init()
{
	// Not yet needed
}

void RigidBody::update(float delta)
{
	// Not yet needed
}
