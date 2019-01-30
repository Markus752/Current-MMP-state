#include "stdafx.h"
#include "GamesStateManager.h"

void GameStateManager::update(float delta)
{
	currentState->update(delta);
}

void GameStateManager::draw()
{
	currentState->draw();
}


std::shared_ptr<IGameState> GameStateManager::getCurrentState() const
{
	return currentState;
}

void GameStateManager::setState(std::string stateName)
{
	auto it = stateMap.find(stateName);
	
	if (it == stateMap.end())
	{
		std::cout << "State not found!" << std::endl;
		return;
	}

	// Terminates old state to set new one 
	if (currentState) currentState->exit();
	currentState = stateMap[stateName];
	if (currentState) currentState->init();
}

void GameStateManager::addState(std::string stateName, std::shared_ptr<IGameState> state)
{
	auto it = stateMap.find(stateName);

	if (it == stateMap.end())
	{
		stateMap[stateName] = state;
	}
	else std::cout << "State already exists!" << std::endl;
}
