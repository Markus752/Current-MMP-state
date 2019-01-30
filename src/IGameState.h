#pragma once

class IGameState
{
public:
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void exit() = 0;
};
