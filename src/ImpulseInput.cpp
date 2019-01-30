#include "stdafx.h"
#include "ImpulseInput.h"
#include "InputManager.h"

void ImpulsInput::init()
{
}

void ImpulsInput::update(float delta)
{
	std::map<KeyInput, int> playerKeyMap = InputManager::getInstance().getMapAtPlayerIndex(m_PlayerIndex);

	for (auto i : playerKeyMap)
	{
		if (InputManager::getInstance().isKeyDown(impulse_up, m_PlayerIndex) && !m_GotImpulse)
		{
			//m_Body->impulses.push_back(m_Impuls);
			m_Body->velocity = sf::Vector2f(m_Impuls.x, m_Impuls.y);
			m_GotImpulse = true;

			// Gravity
			m_Body->forces.push_back(sf::Vector2f(0.0f, 900.0f));
		}
	}
}

bool & ImpulsInput::resetImpulse()
{
	return m_GotImpulse;
}
