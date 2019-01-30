#include "stdafx.h"
#include "MoveInput.h"
#include "InputManager.h"

void MoveInput::init()
{
	// Not yet needed
}

void MoveInput::update(float delta)
{
	std::map<KeyInput, int> playerKeyMap = InputManager::getInstance().getMapAtPlayerIndex(m_PlayerIndex);

	for (auto i : playerKeyMap)
	{
		if (InputManager::getInstance().isKeyDown(move_up, m_PlayerIndex))
		{
			m_Position.y -= m_VelocityUp.x * delta;
			direction = moveUp;
		}

		if (InputManager::getInstance().isKeyDown(move_left, m_PlayerIndex))
		{
			m_Position.x -= m_VelocitySide.x * delta;
			direction = moveLeft;
		}

		if (InputManager::getInstance().isKeyDown(move_right, m_PlayerIndex))
		{
			m_Position.x += m_VelocitySide.y * delta;
			direction = moveRight;
		}

		if (InputManager::getInstance().isKeyDown(move_down, m_PlayerIndex))
		{
			m_Position.y += m_VelocityUp.y * delta;
			direction = moveDown;
		}

		if(!InputManager::getInstance().isKeyDown(move_up, m_PlayerIndex) && !InputManager::getInstance().isKeyDown(move_left, m_PlayerIndex)
			&& !InputManager::getInstance().isKeyDown(move_right, m_PlayerIndex) && !InputManager::getInstance().isKeyDown(move_down, m_PlayerIndex))
		{
			direction = idle;
		}
	}
}

Move & MoveInput::getDirection()
{
	return direction;
}
