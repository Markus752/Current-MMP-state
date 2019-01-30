#include "stdafx.h"
#include "LayerComponent.h"
#include <iostream>

void LayerComponent::init()
{
}

void LayerComponent::update(float delta)
{
}

void LayerComponent::drawLayer(sf::RenderWindow& window)
{
	for (auto& sprite : m_Layer)
	{
		window.draw(*sprite);
	}
}

void LayerComponent::render(sf::RenderWindow & w)
{	
	drawLayer(w);	
}
