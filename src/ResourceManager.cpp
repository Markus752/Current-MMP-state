#include "stdafx.h"
#include "ResourceManager.h"
#include "SFML/Graphics.hpp"

ResourceManager & ResourceManager::getInstance()
{
	static ResourceManager m_Instance;

	return m_Instance;
}

void ResourceManager::loadTexture(std::string path, std::string textureName)
{
	auto it = m_TextureMap.find(textureName);
	if (it != m_TextureMap.end()) return;

	sf::Image originImage;
	sf::Texture texture;

	if (!originImage.loadFromFile(path))
	{
		sf::err() << "Could not loaded Image.";
		return;
	}

	originImage.createMaskFromColor(sf::Color(255, 128, 255));

	if (!texture.loadFromImage(originImage))
	{
		sf::err() << "Texture not loaded.";
		return;
	}

	m_TextureMap[textureName] = texture;
}

sf::Texture ResourceManager::getTexture(std::string textureName)
{
	return m_TextureMap[textureName];
}
