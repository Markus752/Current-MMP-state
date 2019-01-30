#include "stdafx.h"
#include "OverworldState.h"

void OverworldState::init()
{
	GameObjectFactory factory;

	auto map = factory.createTileMap("../assets/tiles/Room00", m_RoomId);
	map->init();
	m_GameObjectList.push_back(map);

	auto objects = MapLoader::getInstance().getObjects();
	for (auto it : objects)
	{
		if (it.first == "Player" && !m_Player)
		{
			auto object = factory.createPlayer(it.first, it.second->playerIndex);
			object->init();
			m_GameObjectList.push_back(object);

			m_ObjectDepth = it.second->depth;
			m_RenderManager.addRenderElement(object->getComponent<Render>("Render"), m_ObjectDepth);

			m_Player = object;
		}
		else if (it.first == "Animator")
		{
			auto object = factory.createAnimationObject(it.first);
			object->init();
			m_GameObjectList.push_back(object);

			m_RenderManager.addRenderElement(object->getComponent<Render>("Render"), it.second->depth);
		}
		else if (it.first.find("Wall") != std::string::npos || it.first.find("Object") != std::string::npos)
		{
			auto object = factory.createCollisionObject(it.first);
			object->init();
			m_GameObjectList.push_back(object);
		}
		else if (it.first.find("Trigger") != std::string::npos)
		{
			auto object = factory.createRoomTrigger(it.first);
			object->init();
			m_GameObjectList.push_back(object);
		}
		else if (it.first.find("Interactive") != std::string::npos)
		{
			auto object = factory.createInteractionObject(it.first, m_Gui, m_Paused, it.second->textBox);
			object->init();
			m_GameObjectList.push_back(object);
		}
		else if (it.first.find("NPC") != std::string::npos)
		{
			auto object = factory.createNPC(it.first);
			object->init();
			m_GameObjectList.push_back(object);

			int npcD = it.second->depth;
			m_RenderManager.addRenderElement(object->getComponent<Render>("Render"), npcD);
		}
		else if (it.first.find("Enemy") != std::string::npos)
		{
			auto object = factory.createEnemy(it.first);
			object->init();
			m_GameObjectList.push_back(object);

			int enemyD = it.second->depth;
			m_RenderManager.addRenderElement(object->getComponent<Render>("Render"), enemyD);
		}
	}

	// Send all to RenderManager
	int depthCounter = 0;
	for (int i = 0; i < map->getComponentCount(); i++)
	{
		// to skip the object layer - layers will be drawn in the correct order
		if (i == m_ObjectDepth) depthCounter++;

		m_RenderManager.addRenderElement(map->getComponent<LayerComponent>("LayerComponent" + std::to_string(i)), depthCounter);
		depthCounter++;
	}

	// Default Camera
	sf::View view;
	view.reset(sf::FloatRect(0, 0, m_Window.getSize().x, m_Window.getSize().y));
	m_View = view;

	// View, position, scale, angle, window, isRestrictedFromMap
	auto camera = factory.createGameObjectCamera(m_View, m_Player->getComponent<Transform>("Transform")->getPosition(), 0.17f, 0.0f, m_Window, m_Player, true);
	camera->init();
	m_GameObjectList.push_back(camera);

	// Music
	MusicManager::getInstance().changeRoomSong(m_RoomId, false);
}

void OverworldState::update(float deltaTime)
{
	if (!m_Paused)
	{
		for (auto i : m_GameObjectList)
		{
			i->update(deltaTime);
		}

		// Change states:		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			MusicManager::getInstance().stopPlaying();
			PhysicsManager::getInstance().setCurrentRoom(1);
			m_GameStateManager.setState("Menu");
			m_GameStateManager.getCurrentState()->init();
			m_Player = nullptr;
			m_RoomId = 1;
		}
		// For Room Changes
		if (m_RoomId != PhysicsManager::getInstance().getRoomId())
		{
			m_RoomId = PhysicsManager::getInstance().getRoomId();
			exit();
			m_GameObjectList.push_back(m_Player);
			m_RenderManager.addRenderElement(m_Player->getComponent<Render>("Render"), m_ObjectDepth);
			PhysicsManager::getInstance().addGameObject(m_Player);
			PhysicsManager::getInstance().addGameObjectDynamic(m_Player);
			init();
		}

		PhysicsManager::getInstance().update(deltaTime);
	}
}

void OverworldState::draw()
{
	m_RenderManager.render(m_Window);

	m_Gui.setTarget(m_Window);

	m_Gui.draw();
}


void OverworldState::exit()
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
	InteractionManager::getInstance().resetAllColliderTrigger();
}

std::shared_ptr<GameObject> OverworldState::getPlayer()
{
	return m_Player;
}

void OverworldState::setPlayer(std::shared_ptr<GameObject>& player)
{
	m_Player = player;
}

int OverworldState::getRoomId()
{
	return m_RoomId;
}
