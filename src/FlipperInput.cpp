#include "stdafx.h"
#include "FlipperInput.h"

void FlipperInput::init()
{
	// Not yet needed
}

void FlipperInput::update(float delta)
{
	std::map<KeyInput, int> playerKeyMap = InputManager::getInstance().getMapAtPlayerIndex(m_PlayerIndex);

	for (auto i : playerKeyMap)
	{
		if (InputManager::getInstance().isKeyDown(flipper_left, m_PlayerIndex))
		{
			m_Angle = -m_DefautlAngle - m_RotationAngle;
			m_IsInteractive = true;
		}
		else if (InputManager::getInstance().isKeyDown(flipper_right, m_PlayerIndex))
		{
			m_Angle = -m_DefautlAngle + m_RotationAngle;
			m_IsInteractive = true;
		}
		else
		{
			m_Angle = m_DefautlAngle;
			m_IsInteractive = false;
		}
	}
}
