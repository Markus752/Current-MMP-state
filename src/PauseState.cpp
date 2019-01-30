#include "stdafx.h"
#include "PauseState.h"

void PauseState::init()
{
	GameObjectFactory factory;
	float calcX = m_View.getCenter().x - m_View.getSize().x / 2;
	float calcY = m_View.getCenter().y - m_View.getSize().y / 2;
	auto background = factory.createGameObjetBackground("..\\assets\\Pause.png", "Pause", sf::Vector2f(calcX, calcY), 0, m_View);
	background->init();
	m_GameObjectList.push_back(background);
	m_RenderManager.addRenderElement(background->getComponent<Render>("Render"), 0);
}

void PauseState::update(float deltaTime)
{	
}

void PauseState::draw()
{
	m_RenderManager.render(m_Window);
}

void PauseState::exit()
{
	m_GameObjectList.clear();
	m_RenderManager.clearList();
	MapLoader::getInstance().getLayers().clear();
	MapLoader::getInstance().getTexture().clear();
	MapLoader::getInstance().getObjects().clear();
	PhysicsManager::getInstance().getCollider().clear();
	RoomManager::getInstance().getScoreObserver().clear();
}

std::shared_ptr<GameObject> PauseState::getPlayer()
{
	return m_Player;
}

void PauseState::setPlayer(std::shared_ptr<GameObject>& player)
{
	m_Player = player;
}

int PauseState::getRoomId()
{
	return 0;
}