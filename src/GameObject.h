#pragma once

#include <iostream>
#include <unordered_map>
#include "IComponent.h"
#include "SFML/Graphics.hpp"

class GameObject
{
public:
	GameObject()
	{
	}
	void init();
	void update(float deltaTime);
	void removeComponent(std::string componentName);
	int getComponentCount();

	// Template for AddComponent, Targs is input paramenter for type T
	template<typename T, typename... Targs>
	void addComponent(std::string componentName, Targs&&... args)
	{
		static_assert(std::is_base_of<IComponent, T>::value);
		auto it = components.find(componentName);
		auto component = std::make_shared<T>(std::forward<Targs>(args)...);
		if (it == components.end())
		{
			components[componentName] = component;
		}
		else
		{
			std::cout << "Component already exists!" << std::endl;
			return;
		}
	}

	template<typename T>
	std::shared_ptr<T> getComponent(std::string componentName)
	{
		auto it = components.find(componentName);
		if (it != components.end())
		{
			static_assert(std::is_base_of<IComponent, T>::value);
			return std::dynamic_pointer_cast<T>(it->second);
		}
		else
		{
			return nullptr;
		}
	}

	template<typename T>
	std::shared_ptr<T> getComponent()
	{
		for (auto component : components)
		{
			auto casted = std::dynamic_pointer_cast<T>(component.second);
			if (casted)
			{
				return casted;
			}
		}
		return nullptr;
	}


private:
	std::unordered_map<std::string, std::shared_ptr<IComponent>> components;
};