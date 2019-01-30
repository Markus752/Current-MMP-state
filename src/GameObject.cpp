#include "stdafx.h"
#include "GameObject.h"
#include "Render.h"

void GameObject::init()
{
	for (auto i : components)
	{
		i.second->init();
	}
}

void GameObject::update(float deltaTime)
{
	for (auto i : components)
	{
		i.second->update(deltaTime);
	}
}

void GameObject::removeComponent(std::string componentName)
{
	auto it = components.find(componentName);

	if (it != components.end())
	{
		components.erase(componentName);
	}
	else  std::cout << "Can't remove component, could not find it." << std::endl;
	
}

int GameObject::getComponentCount()
{
	return components.size();
}
