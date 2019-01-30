#include "stdafx.h"
#include "RoomManager.h"

void RoomManager::addObserver(std::shared_ptr<GameObject> observer)
{
	m_RoomObservers.push_back(observer);
}

void RoomManager::removeObserver(std::shared_ptr<GameObject> observer)
{
	for (int it = 0; it < m_RoomObservers.size(); it++)
	{
		if (m_RoomObservers.at(it) == observer) m_RoomObservers.erase(m_RoomObservers.begin() + it);
	}
}

void RoomManager::notifyObserver(std::shared_ptr<GameObject> object, std::shared_ptr<GameObject> objectToChange)
{

	for (auto i : m_RoomObservers)
	{
		if(i == object) i->getComponent<RoomTriggerCollision>("RoomTriggerCollision")->onCollision(objectToChange);
	}
}

void RoomManager::resetAllColliderTrigger()
{
	for (auto i : m_RoomObservers)
	{
		i->getComponent<RoomTriggerCollision>("RoomTriggerCollision")->resetIsTriggered() = false;
	}
}

std::vector<std::shared_ptr<GameObject>>& RoomManager::getScoreObserver()
{
	return m_RoomObservers;
}


RoomManager& RoomManager::getInstance()
{
	static RoomManager m_Instance;
	return m_Instance;
}