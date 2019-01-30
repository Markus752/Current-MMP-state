#pragma once
#include "IGameState.h"
#include <vector>
#include <iostream>
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "RenderManager.h"
#include "GamesStateManager.h"
#include "IMainStates.h"
#include "MainStateEnum.h"
#include "OverworldState.h"
#include "PauseState.h"
#include "BattleState.h"

class MainState : public IGameState, public IObserver
{
public:
	MainState(sf::RenderWindow& window, GameStateManager& gameStateManager, sf::View& view)
	: m_Window(window)
	, m_GameStateManager(gameStateManager)
	, m_View(view)
	{
			
	}

	void init();
	void update(float deltaTime);
	void draw();
	void exit();

	std::shared_ptr<IMainStates> getCurrentState();
	void notify() override;
	void addState(MainStatesEnum stateType, std::shared_ptr<IMainStates> state);

private:
	std::vector<std::shared_ptr<GameObject>> m_GameObjectList;
	RenderManager m_RenderManager;
	sf::RenderWindow& m_Window;
	GameStateManager& m_GameStateManager;
	sf::View& m_View;

	std::map<MainStatesEnum, std::shared_ptr<IMainStates>> m_MainStates;
	std::shared_ptr<IMainStates> m_CurrentState;

	// To keep the player during change
	std::shared_ptr<GameObject> m_Player;
};

