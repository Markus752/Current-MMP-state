#pragma once

#include "SFML/Graphics.hpp"
#include "AbstractRender.h"
#include <unordered_map>

class LayerComponent : public AbstractRender
{
public:
	LayerComponent(std::vector<std::shared_ptr<sf::Sprite>> layer)
	: m_Layer(layer)
	{
	}

	void init() override;
	void update(float delta) override;
	// Needed to make it possible for layerComponent to derive from abstractRender
	void render(sf::RenderWindow& w) override;

private:
	void drawLayer(sf::RenderWindow& window);
	
	std::vector<std::shared_ptr<sf::Sprite>> m_Layer;
};


