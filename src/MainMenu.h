#pragma once

#include "IGameState.h"
#include <vector>
#include <iostream>
#include "GameObject.h"
#include "RenderManager.h"
#include "GamesStateManager.h"
#include "TGUI/TGUI.hpp"
#include "IObserver.h"
#include "GameObjectFactory.h"

class MainMenu : public IGameState
{
public:
	MainMenu(sf::RenderWindow& window, GameStateManager& gameStateManager) 
	: m_Window(window)
	, m_GameStateManager(gameStateManager)
	{
	
	}
	void init();
	void update(float deltaTime);	
	void draw();	
	void exit();
	void menuControl(float deltaTime);
	void setActiveButton(int index);

	void createButtons(string name, int height, string percentage);
private:
	std::vector<std::shared_ptr<GameObject>> m_GameObjectList;
	RenderManager m_RenderManager;
	sf::RenderWindow& m_Window;
	GameStateManager& m_GameStateManager;

	tgui::Gui m_Gui;
	std::vector<std::shared_ptr<tgui::Button>> m_MenuButtons;
	int m_Index = 1;
	bool m_IsProtected = false;
	float counter = 0.35;
};

