#include "stdafx.h"
#include "GameObjectFactory.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <vector>

void ComponentCreator::createTransform(GameObject& object, string name)
{
	object.addComponent<Transform>("Transform", MapLoader::getInstance().getObjects()[name]->sprite.getPosition(), 0);
	std::cout << "Added Transform to " << name << std::endl;
}

void ComponentCreator::createRender(GameObject& object, string name, std::shared_ptr<GameObject> parent)
{
	object.addComponent<Render>("Render", name, object.getComponent<Transform>("Transform")->getPosition(),
		object.getComponent<Transform>("Transform")->getRotation(), parent);
	object.getComponent<Render>("Render")->init();
	auto scaleX = MapLoader::getInstance().getObjects()[name]->sprite.getScale().x;
	auto scaleY = MapLoader::getInstance().getObjects()[name]->sprite.getScale().y;
	object.getComponent<Render>("Render")->setScale(scaleX, scaleY);
}

void ComponentCreator::createAnimation(GameObject& object, string name, std::shared_ptr<GameObject> parent, bool canMove)
{
	object.addComponent<Animation>("Animation", 3, 4, object.getComponent<Render>("Render")->getTexture(), parent, canMove);
	object.getComponent<Animation>("Animation")->init();
	object.getComponent<Render>("Render")->hasAnimation() = true;
	auto scaleX = MapLoader::getInstance().getObjects()[name]->sprite.getScale().x;
	auto scaleY = MapLoader::getInstance().getObjects()[name]->sprite.getScale().y;
	object.getComponent<Render>("Render")->setScale(scaleX, scaleY);
}

void ComponentCreator::createMoveInput(GameObject& object, int playerIndex)
{
	object.addComponent<MoveInput>("MoveInput", playerIndex, object.getComponent<RigidBody>("RigidBody")->getRigBody()->velocityUp, object.getComponent<RigidBody>("RigidBody")->getRigBody()->velocitySide,
		object.getComponent<Transform>("Transform")->getPosition());
	InputManager::getInstance().bind(move_up, sf::Keyboard::W, playerIndex);
	InputManager::getInstance().bind(move_left, sf::Keyboard::A, playerIndex);
	InputManager::getInstance().bind(move_right, sf::Keyboard::D, playerIndex);
	InputManager::getInstance().bind(move_down, sf::Keyboard::S, playerIndex);
}

void ComponentCreator::createAiComponent(GameObject & object)
{
	object.addComponent<AiComponent>("AiComponent", object.getComponent<Transform>("Transform")->getPosition(), sf::Vector2f(50.0f, 50.0f), object.getComponent<Transform>("Transform")->getPosition());
}

void ComponentCreator::createRoomCollision(GameObject& object, string name, std::shared_ptr<GameObject> parent)
{
	RigBody body = { object.getComponent<Transform>("Transform")->getPosition() };
	float width = MapLoader::getInstance().getObjects()[name]->sprite.getScale().x;
	float height = MapLoader::getInstance().getObjects()[name]->sprite.getScale().y;
	sf::FloatRect aabb = { object.getComponent<Transform>("Transform")->getPosition().x, object.getComponent<Transform>("Transform")->getPosition().y, width, height };
	object.addComponent<RigidBody>("RigidBody", std::make_shared<RigBody>(body));
	object.addComponent<RoomTriggerCollision>("RoomTriggerCollision", aabb, sf::RectangleShape({ aabb.width, aabb.height }), true, MapLoader::getInstance().getObjects()[name]->roomId, sf::Vector2f(MapLoader::getInstance().getObjects()[name]->posX, MapLoader::getInstance().getObjects()[name]->posY));
	PhysicsManager::getInstance().addGameObject(parent);
	PhysicsManager::getInstance().addGameObjectStatic(parent);
	RoomManager::getInstance().addObserver(parent);
}

void ComponentCreator::createInteractionCollision(GameObject& object, string name, std::shared_ptr<GameObject> parent, tgui::Gui& gui, bool& paused, string text)
{
	RigBody body = { object.getComponent<Transform>("Transform")->getPosition() };
	float width = MapLoader::getInstance().getObjects()[name]->sprite.getScale().x;
	float height = MapLoader::getInstance().getObjects()[name]->sprite.getScale().y;
	sf::FloatRect aabb = { object.getComponent<Transform>("Transform")->getPosition().x, object.getComponent<Transform>("Transform")->getPosition().y, width, height };
	object.addComponent<RigidBody>("RigidBody", std::make_shared<RigBody>(body));
	object.addComponent<InteractiveCollision>("InteractiveCollision", aabb, sf::RectangleShape({ aabb.width, aabb.height }), false, true, gui, paused, text);
	PhysicsManager::getInstance().addGameObject(parent);
	PhysicsManager::getInstance().addGameObjectStatic(parent);
	InteractionManager::getInstance().addObserver(parent);
}

void ComponentCreator::createPlayerCollision(GameObject & object, string name, std::shared_ptr<GameObject> parent)
{
	sf::Vector2f movementVector = sf::Vector2f(MapLoader::getInstance().getObjects()[name]->movementSpeed, MapLoader::getInstance().getObjects()[name]->movementSpeed);
	RigBody body = { object.getComponent<Transform>("Transform")->getPosition(), movementVector, movementVector, MapLoader::getInstance().getObjects()[name]->movementSpeed };
	float scaleX = MapLoader::getInstance().getObjects()[name]->texture.getSize().x * MapLoader::getInstance().getObjects()[name]->sprite.getScale().x;
	float scaleY = MapLoader::getInstance().getObjects()[name]->texture.getSize().y * MapLoader::getInstance().getObjects()[name]->sprite.getScale().y;
	sf::FloatRect aabb = { object.getComponent<Transform>("Transform")->getPosition().x, object.getComponent<Transform>("Transform")->getPosition().y + 10, scaleX, scaleY };
	object.addComponent<RigidBody>("RigidBody", std::make_shared<RigBody>(body), false);
	object.addComponent<Collision>("Collision", aabb, sf::RectangleShape({ aabb.width, aabb.height }));
	PhysicsManager::getInstance().addGameObjectDynamic(parent);
	PhysicsManager::getInstance().addGameObject(parent);
}

void ComponentCreator::createObjectCollision(GameObject& object, string name, std::shared_ptr<GameObject> parent, bool isAnimation)
{
	RigBody body = { object.getComponent<Transform>("Transform")->getPosition() };
	float width = MapLoader::getInstance().getObjects()[name]->sprite.getScale().x;
	float height = MapLoader::getInstance().getObjects()[name]->sprite.getScale().y;
	sf::FloatRect aabb = { object.getComponent<Transform>("Transform")->getPosition().x, object.getComponent<Transform>("Transform")->getPosition().y, width, height };
	object.addComponent<RigidBody>("RigidBody", std::make_shared<RigBody>(body), isAnimation);
	object.addComponent<Collision>("Collision", aabb, sf::RectangleShape({ aabb.width, aabb.height }));
	PhysicsManager::getInstance().addGameObjectStatic(parent);
	PhysicsManager::getInstance().addGameObject(parent);
}