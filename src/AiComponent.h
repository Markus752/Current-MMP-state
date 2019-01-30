#pragma once
#include "IComponent.h"

class AiComponent : public IComponent
{
public:
	AiComponent(sf::Vector2f& position, sf::Vector2f moveArea, sf::Vector2f startPos)
		:m_Position(position)
		,m_MoveArea(moveArea)
		,m_StartPos(startPos)
	{

	};

	void move();
	void init() override;
	void update(float delta) override;
	void findTarget();
	sf::Vector2f calcVelocity(sf::Vector2f targetPos, sf::Vector2f startPos);
	
private:
	sf::Vector2f& m_Position;
	sf::Vector2f m_StartPos;
	sf::Vector2f m_MoveArea;
	sf::Vector2f m_Target;
	sf::Vector2f m_Velocity;
	bool m_HasTarget = false;
};
