#pragma once
#include "GameObject.h"
#include "ComponentCreator.h"

class GameObjectFactory
{
public:
	std::shared_ptr<GameObject> createPlayer(std::string name, int playerIndex);
	std::shared_ptr<GameObject> createGameObjetBackground(std::string path, std::string filename, sf::Vector2f position, float angle, sf::View& window);
	std::shared_ptr<GameObject> createGameObjectCamera(sf::View& view, sf::Vector2f position, float scale, float angle, sf::RenderWindow& window, std::shared_ptr<GameObject> player, bool isRestrictedFromMap);
	std::shared_ptr<GameObject> createTileMap(std::string fileName, int roomId);
	std::shared_ptr<GameObject> createCollisionObject(std::string name);
	std::shared_ptr<GameObject> createRoomTrigger(std::string name);
	std::shared_ptr<GameObject> createAnimationObject(std::string name);
	std::shared_ptr<GameObject> createInteractionObject(std::string name, tgui::Gui& gui, bool& paused, std::string text);
	std::shared_ptr<GameObject> createNPC(std::string name);
	std::shared_ptr<GameObject> createEnemy(std::string name);
	std::shared_ptr<GameObject> createSprite(std::string path, std::string filename, sf::Vector2f position, float angle, sf::View& view);

private:
	ComponentCreator m_ComponentCreate;
};
