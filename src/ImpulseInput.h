#pragma once
#include "IComponent.h"
#include "RigidBody.h"


class ImpulsInput : public IComponent
{
public:
	ImpulsInput(int playerIndex, sf::Vector2f impuls, std::shared_ptr<RigBody> body)
		: m_PlayerIndex(playerIndex)
		, m_Impuls(impuls)
		, m_Body(body)
	{
			
	}
	void init();
	void update(float delta);
	bool& resetImpulse();

private:
	int m_PlayerIndex;
	sf::Vector2f m_Impuls;
	std::shared_ptr<RigBody> m_Body;
	bool m_GotImpulse = false;
};

