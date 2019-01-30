#pragma once
#include "GameObject.h"

class IMainStates
{
public:
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void exit() = 0;
	virtual std::shared_ptr<GameObject> getPlayer() { return nullptr; };
	virtual void setPlayer(std::shared_ptr<GameObject>& player) = 0;
	virtual int getRoomId() = 0;
};
