#pragma once
#include "IComponent.h"

class Transform : public IComponent
{
public:
	Transform(sf::Vector2f position, float angle)
	: m_position(position)
	, m_Angle(angle)
	{

	}
	void init() override;
	void update(float delta) override;
	sf::Vector2f& getPosition();
	void setPosition(sf::Vector2f position);
	float& getRotation();

private:
	sf::Vector2f m_position;
	float m_Angle;
};

