#pragma once
#include <map>
#include "IEvent.h"
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "EventTypes.h"
#include <functional>

class EventBus
{
public:
	static EventBus& getInstance();
	void addObserver(EventTypes eventType, std::function<void()> func);
	void removeObserver(std::shared_ptr<GameObject> object);
	void notify(EventTypes eventType);

private:
	EventBus(void) = default;
	~EventBus(void) = default;
	EventBus(const EventBus& p) = delete;
	EventBus& operator=(EventBus const&) = delete;

	std::map <EventTypes, std::vector<std::function<void()>>> m_Observers;


};