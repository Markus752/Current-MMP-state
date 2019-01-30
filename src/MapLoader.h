#pragma once
#include "NLTmxMap.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>

class MapLoader
{
	struct Tile
	{
		sf::Texture texture;
		sf::Sprite sprite;
		std::vector<std::string> components;
		int depth;
		float movementSpeed;
		int playerIndex;
		
		// For Collision
		bool isTrigger = false;

		//For Trigger
		float posX;
		float posY;
		int roomId;

		//For TextBoxes
		std::string textBox;
	};

public:
	static MapLoader& getInstance();

	void loadMap(const string& filename, const sf::Vector2f& offset);
	std::shared_ptr<Tile> loadSprite(NLTmxMapObject* object);

	vector<vector<shared_ptr<sf::Sprite>>>& getLayers();
	std::unordered_map<std::string, shared_ptr<sf::Texture>>& getTexture();
	map<string, std::shared_ptr<Tile>>& getObjects();

	std::pair<int, int> getMaxSizes();

private:
	MapLoader(void) = default;
	~MapLoader(void) = default;
	MapLoader(const MapLoader& p) = delete;
	MapLoader& operator=(MapLoader const&) = delete;
	
	std::unordered_map<std::string, shared_ptr<sf::Texture>> m_TilesetTexture;
	const string m_ResourcePath = "../assets/tiles/";

	vector<vector<shared_ptr<sf::Sprite>>> m_Layers;
	map<string, std::shared_ptr<Tile>> m_Objects;

	std::pair<int, int> m_MaxTileMapSize = std::pair<int, int>(0, 0);
};

