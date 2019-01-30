#include "stdafx.h"
#include "EventBus.h"

EventBus & EventBus::getInstance()
{
	static EventBus m_Instance;

	return m_Instance;
}

void EventBus::addObserver(EventTypes eventType, std::function<void()> func)
{
	m_Observers[eventType].push_back(func);
}

void EventBus::removeObserver(std::shared_ptr<GameObject> object)
{
	//not yet fixed
}

void EventBus::notify(EventTypes eventType)
{
	for (auto i : m_Observers[eventType])
	{
		i();
	}
}

