// EngineProject.cpp : Defines the entry point for the console application.

// Schuster Andreas
// Klamer Markus

#include "stdafx.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "GamesStateManager.h"
#include "MainMenu.h"
#include "MainState.h"
#include "NLTmxMap.h"
#include "MapLoader.h"
#include "LayerComponent.h"
#include "PhysicsManager.h"

using namespace sf;

class Game
{
public:
	void Run()
	{
		if (!init())
			return;

		while (m_Window.isOpen())
		{
			/*Event event;
			while (m_Window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					m_Window.close();
			}*/
			static Clock clock;
			Time deltaTime = clock.restart();
			const float fDeltaTimeSeconds = deltaTime.asSeconds();

			update(fDeltaTimeSeconds);
			draw();
		}
		shutdown();
	}

private:
	
	bool init()
	{
		m_Window.create(VideoMode(1600, 900), "Our Game");

		auto menuState = std::make_shared<MainMenu>(m_Window, m_GameStateManager);
		m_GameStateManager.addState("Menu", menuState);

		auto mainState = std::make_shared<MainState>(m_Window, m_GameStateManager, m_View);
		m_GameStateManager.addState("Main", mainState);
		InputManager::getInstance().addObserver(sf::Keyboard::P, mainState);

		m_GameStateManager.setState("Menu");
		return true;
	}

	void update(const float fDeltaTimeSeconds)
	{
		InputManager::getInstance().processInput(m_Window);
		m_GameStateManager.update(fDeltaTimeSeconds);
	}

	void draw()
	{
		m_Window.clear();

		m_GameStateManager.draw();
		
		// Testing porpuse
		/*for (auto& i : PhysicsManager::getInstance().getCollider())
		{
			if (i->getComponent<Collision>("Collision"))
			{
				 auto body = i->getComponent<Collision>("Collision")->getDebugShape();
				 body.setPosition(i->getComponent<RigidBody>("RigidBody")->getRigBody()->position);
				 m_Window.draw(body);
			}
			else if (i->getComponent<TriggerCollision>("TriggerCollision"))
			{
				auto body = i->getComponent<TriggerCollision>("TriggerCollision")->getDebugShape();
				body.setPosition(i->getComponent<RigidBody>("RigidBody")->getRigBody()->position);
				m_Window.draw(body);
			}
			else if (i->getComponent<RoomTriggerCollision>("RoomTriggerCollision"))
			{
				auto body = i->getComponent<RoomTriggerCollision>("RoomTriggerCollision")->getDebugShape();
				body.setPosition(i->getComponent<RigidBody>("RigidBody")->getRigBody()->position);
				m_Window.draw(body);
			}
			else if (i->getComponent<InteractiveCollision>("InteractiveCollision"))
			{
				auto body = i->getComponent<InteractiveCollision>("InteractiveCollision")->getDebugShape();
				body.setPosition(i->getComponent<RigidBody>("RigidBody")->getRigBody()->position);
				m_Window.draw(body);
			}
		}*/
		m_Window.display();
	}
	   	 
	void shutdown()
	{
		// No 'new' in our code
		// Only memory left is from our singleton InputManager, get's deleted anyway on exit of program
		// Therefore no extra shutDown needed
 	}
	
	RenderWindow m_Window;
	GameStateManager m_GameStateManager;
	View m_View;
};

int main()
{
	Game game;
	game.Run();
	return 0;
}