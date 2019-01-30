#include "stdafx.h"
#include "Transform.h"

void Transform::init()
{
	// Not yet needed
}

void Transform::update(float delta)
{
	// Not yet needed
}

sf::Vector2f& Transform::getPosition()
{
	return m_position;
}

void Transform::setPosition(sf::Vector2f position)
{
	m_position = position;
}


float& Transform::getRotation()
{
	return m_Angle;
}
