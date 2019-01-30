#pragma once
#include "IComponent.h"
#include "InputManager.h"

class FlipperInput : public IComponent
{
public:
	FlipperInput(int playerIndex, float& angle, float defaultAngle, float rotationAngle, sf::Vector2f& position, bool& isInteractive)
		: m_PlayerIndex(playerIndex)
		, m_Angle(angle)
		, m_DefautlAngle(defaultAngle)
		, m_RotationAngle(rotationAngle)
		, m_Position(position)
		, m_IsInteractive(isInteractive)
	{

	}

	void init();
	void update(float delta);

private:
	int m_PlayerIndex;
	float& m_Angle;
	float m_DefautlAngle;
	float m_RotationAngle;
	sf::Vector2f& m_Position;
	bool& m_IsInteractive;
};
