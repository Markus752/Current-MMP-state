#pragma once

#include "SFML/Graphics.hpp"
#include "IComponent.h"

class AbstractRender : public IComponent
{

public:
	virtual void init() = 0;
	virtual void update(float delta) = 0;
	virtual void render(sf::RenderWindow& w) = 0;

private:
};