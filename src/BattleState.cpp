#include "stdafx.h"
#include "BattleState.h"
#include "MusicManager.h"

void BattleState::init()
{
	GameObjectFactory factory;
	float calcX = m_View.getCenter().x - m_View.getSize().x / 2;
	float calcY = m_View.getCenter().y - m_View.getSize().y / 2;
	auto background = factory.createGameObjetBackground("..\\assets\\BattleBackground.png", "BG", sf::Vector2f(calcX, calcY), 0, m_View);
	background->init();
	m_GameObjectList.push_back(background);
	m_RenderManager.addRenderElement(background->getComponent<Render>("Render"), 0);

	MusicManager::getInstance().changeRoomSong(1, true);
}

void BattleState::update(float deltaTime)
{
}

void BattleState::draw()
{
	m_RenderManager.render(m_Window);
}

void BattleState::exit()
{
	m_GameObjectList.clear();
	m_RenderManager.clearList();
	MapLoader::getInstance().getLayers().clear();
	MapLoader::getInstance().getTexture().clear();
	MapLoader::getInstance().getObjects().clear();
	PhysicsManager::getInstance().getCollider().clear();
	RoomManager::getInstance().getScoreObserver().clear();
}

std::shared_ptr<GameObject> BattleState::getPlayer()
{
	return m_Player;
}

void BattleState::setPlayer(std::shared_ptr<GameObject>& player)
{
	m_Player = player;
}

int BattleState::getRoomId()
{
	return 0;
}
