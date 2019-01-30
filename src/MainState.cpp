#include "stdafx.h"
#include "MainState.h"
#include "GameObjectFactory.h"
#include "SFML/System.hpp"
#include "MapLoader.h"
#include "PhysicsManager.h"
#include "RoomManager.h"
#include "MusicManager.h"
#include "InteractionManager.h"

void MainState::init()
{
	addState(MainStatesEnum::Overworld, std::make_shared<OverworldState>(m_Window, m_GameStateManager, m_View));

	auto pause = make_shared<PauseState>(m_Window, m_GameStateManager, m_View);
	addState(MainStatesEnum::Pause, std::make_shared<PauseState>(m_Window, m_GameStateManager, m_View));

	auto battle = make_shared<BattleState>(m_Window, m_GameStateManager, m_View);
	addState(MainStatesEnum::Battle, std::make_shared<BattleState>(m_Window, m_GameStateManager, m_View));

 	m_CurrentState = m_MainStates[MainStatesEnum::Overworld];
	m_CurrentState->init();
}

void MainState::update(float deltaTime)
{
	m_CurrentState->update(deltaTime);

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::B)) && (m_CurrentState = m_MainStates[MainStatesEnum::Overworld]))
	{
		m_Player = m_CurrentState->getPlayer();
		m_CurrentState = m_MainStates[MainStatesEnum::Battle];
		m_CurrentState->setPlayer(m_Player);
		m_CurrentState->init();
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::V)) && (m_CurrentState = m_MainStates[MainStatesEnum::Battle]))
	{
		m_Player = m_CurrentState->getPlayer();
		m_CurrentState = m_MainStates[MainStatesEnum::Overworld];
		m_CurrentState->setPlayer(m_Player);
		MusicManager::getInstance().stopPlaying();
		MusicManager::getInstance().changeRoomSong(10, false);
	}
}

void MainState::draw()
{
	m_CurrentState->draw();
}

void MainState::exit()
{
	m_GameObjectList.clear();
	m_RenderManager.clearList();
	MapLoader::getInstance().getLayers().clear();
	MapLoader::getInstance().getTexture().clear();
	MapLoader::getInstance().getObjects().clear();
	PhysicsManager::getInstance().getCollider().clear();
	PhysicsManager::getInstance().getDynamicCollider().clear();
	PhysicsManager::getInstance().getStaticCollider().clear();
	RoomManager::getInstance().getScoreObserver().clear();
}

void MainState::notify()
{
	if (m_CurrentState == m_MainStates[MainStatesEnum::Overworld])
	{
		m_Player = m_CurrentState->getPlayer();
		m_CurrentState = m_MainStates[MainStatesEnum::Pause];
		m_CurrentState->setPlayer(m_Player);
		m_CurrentState->init();
	}
	else if (m_CurrentState == m_MainStates[MainStatesEnum::Pause])
	{
		m_Player = m_CurrentState->getPlayer();
		m_CurrentState = m_MainStates[MainStatesEnum::Overworld];
		m_CurrentState->setPlayer(m_Player);
	}
}

void MainState::addState(MainStatesEnum stateType, std::shared_ptr<IMainStates> state)
{
	m_MainStates[stateType] = state;
}

