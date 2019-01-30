#pragma once
#include "TriggerCollision.h"

class RoomTriggerCollision : public TriggerCollision
{
public:
	RoomTriggerCollision(sf::FloatRect shape, sf::RectangleShape debugGeometry, bool isTrigger, int roomId, sf::Vector2f changePosition)
		:TriggerCollision(shape, debugGeometry, isTrigger)
		, m_RoomId(roomId)
		, m_ChangePosition(changePosition)
	{

	}
	void onCollision(std::shared_ptr<GameObject> gameObject);

private:
	int m_RoomId;
	sf::Vector2f m_ChangePosition;
};

