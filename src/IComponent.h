#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class IComponent
{
public:
	virtual void init() = 0;
	virtual void update(float delta) = 0;
};
