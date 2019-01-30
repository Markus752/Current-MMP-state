#include "stdafx.h"
#include "ObjectReseter.h"
#include "Collision.h"
#include "RoomManager.h"

ObjectReseter & ObjectReseter::getInstance()
{
	static ObjectReseter m_Instance;

	return m_Instance;
}

void ObjectReseter::addObserver(std::shared_ptr<GameObject> observer)
{
	m_ResetObservers.push_back(observer);
}

void ObjectReseter::removeObserver(std::shared_ptr<GameObject> observer)
{
	for (int it = 0; it < m_ResetObservers.size(); it++)
	{
		if (m_ResetObservers.at(it) == observer) m_ResetObservers.erase(m_ResetObservers.begin() + it);
	}
}

void ObjectReseter::notifyObserver(std::shared_ptr<GameObject> object, std::shared_ptr<GameObject> hitObject, sf::Vector2f position)
{
	for (auto i : m_ResetObservers)
	{

		if (i == object)
		{
			i->getComponent<Collision>("Collision")->reset(hitObject, position);
			RoomManager::getInstance().resetScore();
		}
	}
}

std::vector<std::shared_ptr<GameObject>>& ObjectReseter::getResetObserver()
{
	return m_ResetObservers;
}

