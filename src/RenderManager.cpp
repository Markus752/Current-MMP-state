#include "stdafx.h"
#include "RenderManager.h"

void RenderManager::render(sf::RenderWindow& window)
{	
	for (auto it : m_renderList)
	{
		it.first->render(window);
	}
}

void RenderManager::addRenderElement(std::shared_ptr<AbstractRender> newElement, int zLayer)
{
	std::pair<std::shared_ptr<AbstractRender>, int> newPair;
	newPair.first = newElement;
	newPair.second = zLayer;
	
	m_renderList.push_back(newPair);

	// Sort by Value of Pair, aka Order List by ZLayer -> Depth / Drawing Order
	std::sort(m_renderList.begin(), m_renderList.end(), [](auto &left, auto &right) {
		return left.second < right.second;
	});
}

std::vector<std::pair<std::shared_ptr<AbstractRender>, int>>& RenderManager::getRenderElements()
{
	return m_renderList;
}

void RenderManager::clearList()
{
	m_renderList.clear();
}
