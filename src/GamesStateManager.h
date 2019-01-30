#pragma once

#include "IGameState.h"
#include <map>
#include <iostream>

class GameStateManager
{
public:
	GameStateManager() :currentState(nullptr) {}
	void update(float delta);
	void draw();
	
	std::shared_ptr<IGameState> getCurrentState()const;
	void setState(std::string stateName);
	void addState(std::string stateName, std::shared_ptr<IGameState> state);
	GameStateManager(const GameStateManager& p) = delete;
	GameStateManager& operator=(GameStateManager const&) = delete;
private:
	std::shared_ptr<IGameState> currentState;
	std::map<std::string, std::shared_ptr<IGameState>> stateMap;
};