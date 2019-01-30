#pragma once
#include <vector>
#include <iostream>
#include "GameObject.h"

class InteractionManager
{
public:
	static InteractionManager& getInstance();
	void addObserver(std::shared_ptr<GameObject> observer);
	void removeObserver(std::shared_ptr<GameObject> observer);
	void notifyObserver(std::shared_ptr<GameObject> object, std::shared_ptr<GameObject> objectToChange);
	void resetAllColliderTrigger();

	std::vector<std::shared_ptr<GameObject>>& getInteractionObservers();

private:
	InteractionManager(void) = default;
	~InteractionManager(void) = default;
	InteractionManager(const InteractionManager& p) = delete;
	InteractionManager& operator=(InteractionManager const&) = delete;

	std::vector<std::shared_ptr<GameObject>> m_InteractionObservers;
};


