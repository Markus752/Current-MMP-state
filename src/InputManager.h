#pragma once

#include <map>
#include <vector>
#include "GameObject.h"
#include "IObserver.h"

enum KeyInput
{
	move_up,
	move_down,
	move_left,
	move_right,

	space,
	escape
};

class InputManager
{
public:
	static InputManager& getInstance();
	bool isKeyDown(KeyInput action, int playerIndex);
	void bind(KeyInput action, int keyCode, int playerIndex);
	void unbind(KeyInput action, int playerIndex);
	std::map<KeyInput, int>& getMapAtPlayerIndex(int playerIndex);

	void processInput(sf::Window& window);

	void addObserver(sf::Keyboard::Key key, std::shared_ptr<IObserver> object);
	void removeObserver(std::shared_ptr<IObserver> object);
	void notify(sf::Keyboard::Key key, bool isPressed, int index);
	std::map<sf::Keyboard::Key, std::vector<std::shared_ptr<IObserver>>>& getObservers();

private:
	InputManager(void) = default;
	~InputManager(void) = default;
	InputManager(const InputManager& p) = delete;
	InputManager& operator=(InputManager const&) = delete;
	std::map<sf::Keyboard::Key, std::vector<std::shared_ptr<IObserver>>> m_Observers;

	std::vector<std::map<KeyInput, int>> keyMap;
};


