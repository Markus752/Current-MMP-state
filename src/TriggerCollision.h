#pragma once
#include "Collision.h"

class TriggerCollision : public Collision
{
public:
	TriggerCollision(sf::FloatRect shape, sf::RectangleShape debugGeometry, bool isTrigger) 
		: Collision(shape, debugGeometry)
		, m_IsTrigger(isTrigger)
	{

	};

	bool isTrigger();
	bool& isTriggered();
	void setIsTriggered(bool value);
	bool& resetIsTriggered();
	
protected:
	bool m_IsTrigger;
	bool m_isTriggered = false;
};

