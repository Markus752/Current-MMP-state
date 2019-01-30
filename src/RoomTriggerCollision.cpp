#include "stdafx.h"
#include "RoomTriggerCollision.h"
#include "functional"
#include "PhysicsManager.h"

void RoomTriggerCollision::onCollision(std::shared_ptr<GameObject> gameObject)
{



	if (!m_isTriggered)
	{
		PhysicsManager::getInstance().setCurrentRoom(m_RoomId);
		gameObject->getComponent<Transform>("Transform")->setPosition(m_ChangePosition);
	}
}
