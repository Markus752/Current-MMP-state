#include "stdafx.h"
#include "Collision.h"
#include "RoomManager.h"
#include "RigidBody.h"
#include "ImpulseInput.h"
#include "MapLoader.h"
#include "PhysicsManager.h"

sf::FloatRect& Collision::getShape()
{
	return m_Shape;
}

sf::RectangleShape Collision::getDebugShape()
{
	return m_DebugGeometry;
}

void Collision::init()
{
	// Not yet needed
}

void Collision::update(float delta)
{
	// Not yet needed
}
