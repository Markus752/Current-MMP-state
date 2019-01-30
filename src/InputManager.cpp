#include "stdafx.h"
#include "InputManager.h"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "InteractiveCollision.h"

InputManager& InputManager::getInstance()
{
	static InputManager m_Instance;

	return m_Instance;
}

bool InputManager::isKeyDown(KeyInput action, int playerIndex)
{
	auto foundBinding = keyMap[playerIndex].find(action);
	if (foundBinding != keyMap[playerIndex].end())
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)foundBinding->second))
		{
			return true;
		}
	}
	return false;
}

void InputManager::bind(KeyInput action, int keyCode, int playerIndex)
{
	std::map<KeyInput, int> mapInVector;
	keyMap.push_back(mapInVector);
	
	keyMap[playerIndex][action] = keyCode;
}

void InputManager::unbind(KeyInput action, int playerIndex)
{
	auto it = keyMap[playerIndex].find(action);
	if (it == keyMap[playerIndex].end()) 
	{
		std::cout << "No valid playerIndex.";
		return;
	}
	keyMap[playerIndex].erase(action);
}

std::map<KeyInput, int>&InputManager::getMapAtPlayerIndex(int playerIndex)
{
	return keyMap[playerIndex];
}

void InputManager::processInput(sf::Window & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				notify(sf::Keyboard::Key::Num1, true, 0);
			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				notify(sf::Keyboard::Key::Num2, true, 1);
			}
			if (event.key.code == sf::Keyboard::E)
			{
				notify(sf::Keyboard::Key::E, true, 1);
			}
			if (event.key.code == sf::Keyboard::P)
			{
				notify(sf::Keyboard::Key::P, true, 1);
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}

void InputManager::addObserver(sf::Keyboard::Key key, std::shared_ptr<IObserver> object)
{
 	m_Observers[key].push_back(object);
}

void InputManager::removeObserver(std::shared_ptr<IObserver> object)
{
	//TODO
}

void InputManager::notify(sf::Keyboard::Key key, bool isPressed, int index)
{
	
	for (auto i : m_Observers[key])
	{	
		i->notify();
	}
}

std::map<sf::Keyboard::Key, std::vector<std::shared_ptr<IObserver>>>& InputManager::getObservers()
{
	return m_Observers;
}


