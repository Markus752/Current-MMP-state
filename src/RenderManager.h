#pragma once

#include <iostream>
#include <vector>
#include "Render.h"
#include "ShapesRender.h"
#include "SFML/Graphics.hpp"
#include "IGameState.h"

class RenderManager
{
public:
	RenderManager()
	{

	}
	void render(sf::RenderWindow& window);
	void addRenderElement(std::shared_ptr<AbstractRender>, int zLayer);
	std::vector<std::pair<std::shared_ptr<AbstractRender>, int>>& getRenderElements();
	// Exit for switch between gameStates
	void clearList();

private:
	RenderManager(const RenderManager& p) = delete;
	RenderManager& operator=(RenderManager const&) = delete;

	std::vector<std::pair<std::shared_ptr<AbstractRender>, int>> m_renderList;
};