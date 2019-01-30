#pragma once
#include "IComponent.h"
#include "InputManager.h"

enum Move
{
	moveUp,
	moveDown,
	moveLeft,
	moveRight,
	idle
};


class MoveInput : public IComponent
{
public:
	MoveInput(int playerIndex, sf::Vector2f& velocityUp, sf::Vector2f& velocitySide, sf::Vector2f& position)
	: m_PlayerIndex(playerIndex)
	, m_VelocityUp(velocityUp)
	, m_VelocitySide(velocitySide)
	, m_Position(position)
	{
	}
	void init();
	void update(float delta);
	Move& getDirection();

private:
	int m_PlayerIndex;
	sf::Vector2f& m_VelocityUp;
	sf::Vector2f& m_VelocitySide;
	sf::Vector2f& m_Position;
	Move direction = idle;
};
