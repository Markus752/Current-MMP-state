#pragma once
#include "GameObject.h"
#include <vector>

class AnimationsManager
{
public:
	static AnimationsManager& getInstance();
	void addObject(std::shared_ptr<GameObject> object);
	void update(float deltaTime);
private:
	AnimationsManager(void) = default;
	~AnimationsManager(void) = default;
	AnimationsManager(const AnimationsManager& p) = delete;
	AnimationsManager& operator=(AnimationsManager const&) = delete;

	std::vector<std::shared_ptr<GameObject>> objects;
};

