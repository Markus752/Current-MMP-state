#pragma once
#include "stdafx.h"
#include "GameObjectFactory.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <vector>

std::shared_ptr<GameObject> GameObjectFactory::createPlayer(std::string name, int playerIndex)
{
	auto player = std::make_shared<GameObject>();

	m_ComponentCreate.createTransform(*player, name);
	m_ComponentCreate.createRender(*player, name, player);
	m_ComponentCreate.createPlayerCollision(*player, name, player);
	m_ComponentCreate.createAnimation(*player, name, player, true);
	m_ComponentCreate.createMoveInput(*player, playerIndex);

	return player;
}


std::shared_ptr<GameObject> GameObjectFactory::createCollisionObject(std::string name)
{
	auto object = std::make_shared<GameObject>();

	m_ComponentCreate.createTransform(*object, name);
	m_ComponentCreate.createObjectCollision(*object, name, object, false);

	return object;
}

std::shared_ptr<GameObject> GameObjectFactory::createRoomTrigger(std::string name)
{
	auto trigger = std::make_shared<GameObject>();

	m_ComponentCreate.createTransform(*trigger, name);
	m_ComponentCreate.createRoomCollision(*trigger, name, trigger);

	return trigger;
}

std::shared_ptr<GameObject> GameObjectFactory::createAnimationObject(std::string name)
{
	auto anim = std::make_shared<GameObject>();

	m_ComponentCreate.createTransform(*anim, name);
	m_ComponentCreate.createRender(*anim, name, anim);
	m_ComponentCreate.createAnimation(*anim, name, anim, false);

	return anim;
}

std::shared_ptr<GameObject> GameObjectFactory::createInteractionObject(std::string name, tgui::Gui& gui, bool& paused, string text)
{
	auto interacter = std::make_shared<GameObject>();

	m_ComponentCreate.createTransform(*interacter, name);
	m_ComponentCreate.createInteractionCollision(*interacter, name, interacter, gui, paused, text);
	InputManager::getInstance().addObserver(sf::Keyboard::Key::E, interacter->getComponent<InteractiveCollision>("InteractiveCollision"));
	return interacter;
}

std::shared_ptr<GameObject> GameObjectFactory::createNPC(std::string name)
{
	auto npc = std::make_shared<GameObject>();

	m_ComponentCreate.createTransform(*npc, name);
	m_ComponentCreate.createRender(*npc, name, npc);

	return npc;
}

std::shared_ptr<GameObject> GameObjectFactory::createEnemy(std::string name)
{
	auto enemy  = std::make_shared<GameObject>();

	m_ComponentCreate.createTransform(*enemy, name);
	m_ComponentCreate.createRender(*enemy, name, enemy);
	//m_ComponentCreate.createPlayerCollision(*enemy, name, enemy);
	//m_ComponentCreate.createAnimation(*enemy, name, enemy, true);
	m_ComponentCreate.createAiComponent(*enemy);

	return enemy;
}








std::shared_ptr<GameObject> GameObjectFactory::createSprite(std::string path, std::string filename, sf::Vector2f position, float angle, sf::View & view)
{
	auto sprite = std::make_shared<GameObject>();
	sprite->addComponent<Transform>("Transform", position, angle);
	sprite->addComponent<Render>("Render", path, filename, sprite->getComponent<Transform>("Transform")->getPosition(),
		sprite->getComponent<Transform>("Transform")->getRotation(), sprite);

	sprite->getComponent<Render>("Render")->init();
	float textureSizeX = sprite->getComponent<Render>("Render")->getTexture().getSize().x;
	float textureSizeY = sprite->getComponent<Render>("Render")->getTexture().getSize().y;
	sprite->getComponent<Render>("Render")->setScale(0.6f, 0.6f);

	return sprite;
}

std::shared_ptr<GameObject> GameObjectFactory::createGameObjetBackground(std::string path, std::string filename, sf::Vector2f position, float angle, sf::View& view)
{
	auto background = std::make_shared<GameObject>();
	background->addComponent<Transform>("Transform", position, angle);
	background->addComponent<Render>("Render", path, filename, background->getComponent<Transform>("Transform")->getPosition(),
		background->getComponent<Transform>("Transform")->getRotation(), background);

	background->getComponent<Render>("Render")->init();
	float textureSizeX = background->getComponent<Render>("Render")->getTexture().getSize().x;
	float textureSizeY = background->getComponent<Render>("Render")->getTexture().getSize().y;
	background->getComponent<Render>("Render")->setScale(view.getSize().x / textureSizeX, view.getSize().y / textureSizeY);

	return background;
}

std::shared_ptr<GameObject> GameObjectFactory::createGameObjectCamera(sf::View& view, sf::Vector2f position, float scale, float angle,
	sf::RenderWindow& window, std::shared_ptr<GameObject> player, bool isRestrictedMap)
{
	auto camera = std::make_shared<GameObject>();
	camera->addComponent<Camera>("Camera", view, position, scale, angle, window, player, isRestrictedMap);
	camera->addComponent<Transform>("Transform", position, angle);

	return camera;
}

std::shared_ptr<GameObject> GameObjectFactory::createTileMap(std::string fileName, int roomId)
{
	auto tileMap = std::make_shared<GameObject>();

	MapLoader::getInstance().loadMap(fileName + std::to_string(roomId) + ".tmx", sf::Vector2f(0, 0));
	for (int i = 0; i < MapLoader::getInstance().getLayers().size(); i++)
	{
		std::vector<std::shared_ptr<sf::Sprite>>& layer = MapLoader::getInstance().getLayers().at(i);
		tileMap->addComponent<LayerComponent>("LayerComponent" + std::to_string(i), layer);
	}
	return tileMap;
}