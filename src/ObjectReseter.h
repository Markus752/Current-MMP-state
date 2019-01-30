#pragma once
#include "GameObject.h"
#include <vector>


class ObjectReseter
{
public:
	static ObjectReseter& getInstance();
	void addObserver(std::shared_ptr<GameObject> observer);
	void removeObserver(std::shared_ptr<GameObject> observer);
	void notifyObserver(std::shared_ptr<GameObject> object, std::shared_ptr<GameObject> hitObject, sf::Vector2f position);

	std::vector<std::shared_ptr<GameObject>>& getResetObserver();
private:
	ObjectReseter(void) = default;
	~ObjectReseter(void) = default;
	ObjectReseter(const ObjectReseter& p) = delete;
	ObjectReseter& operator=(ObjectReseter const&) = delete;

	std::vector<std::shared_ptr<GameObject>> m_ResetObservers;
};
