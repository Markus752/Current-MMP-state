#pragma once
#include "IGameState.h"
#include <vector>
#include <iostream>
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "RenderManager.h"
#include "GamesStateManager.h"
#include "MainState.h"
#include "GameObjectFactory.h"
#include "SFML/System.hpp"
#include "MapLoader.h"
#include "PhysicsManager.h"
#include "RoomManager.h"
#include "MusicManager.h"
#include "InteractionManager.h"
#include "IMainStates.h"

class PauseState : public IMainStates
{
public:
	PauseState(sf::RenderWindow& window, GameStateManager& gameStateManager, sf::View& view)
		: m_Window(window)
		, m_GameStateManager(gameStateManager)
		, m_View(view)
	{

	}

	void init() override;
	void update(float deltaTime) override;
	void draw() override;
	void exit() override;
	std::shared_ptr<GameObject> getPlayer() override;
	void setPlayer(std::shared_ptr<GameObject>& player) override;
	int getRoomId() override;

private:
	std::vector<std::shared_ptr<GameObject>> m_GameObjectList;
	RenderManager m_RenderManager;
	sf::RenderWindow& m_Window;
	GameStateManager& m_GameStateManager;
	sf::View& m_View;
	// To keep player between rooms
	std::shared_ptr<GameObject> m_Player;
};