#include "stdafx.h"
#include "AnimationsManager.h"

AnimationsManager & AnimationsManager::getInstance()
{
	static AnimationsManager m_Instance;

	return m_Instance;
}

void AnimationsManager::addObject(std::shared_ptr<GameObject> object)
{
	objects.push_back(object);
}

void AnimationsManager::update(float deltaTime)
{
		
}
