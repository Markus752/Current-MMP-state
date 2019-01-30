#pragma once

#include <map>;
#include "SFML/Graphics.hpp"

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	void loadTexture(std::string path, std::string fileName);
	sf::Texture getTexture(std::string textureName);
	
private:
	ResourceManager(void) = default;
	~ResourceManager(void) = default;
	ResourceManager(const ResourceManager& p) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	std::map<std::string, sf::Texture> m_TextureMap;
};