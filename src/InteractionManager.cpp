#include "stdafx.h"
#include "InteractionManager.h"
#include "InteractiveCollision.h"

InteractionManager & InteractionManager::getInstance()
{
	static InteractionManager m_Instance;
	return m_Instance;
}

void InteractionManager::addObserver(std::shared_ptr<GameObject> observer)
{
	m_InteractionObservers.push_back(observer);
}

void InteractionManager::removeObserver(std::shared_ptr<GameObject> observer)
{
	for (int it = 0; it < m_InteractionObservers.size(); it++)
	{
		if (m_InteractionObservers.at(it) == observer) m_InteractionObservers.erase(m_InteractionObservers.begin() + it);
	}
}

void InteractionManager::notifyObserver(std::shared_ptr<GameObject> object, std::shared_ptr<GameObject> objectToChange)
{
	for (auto i : m_InteractionObservers)
	{
		if (i == object) i->getComponent<InteractiveCollision>("InteractiveCollision")->onInteract();
	}
}

void InteractionManager::resetAllColliderTrigger()
{
	for (auto i : m_InteractionObservers)
	{
		i->getComponent<InteractiveCollision>("InteractiveCollision")->resetIsTriggered() = false;
	}
}

std::vector<std::shared_ptr<GameObject>>& InteractionManager::getInteractionObservers()
{
	return m_InteractionObservers;
}
