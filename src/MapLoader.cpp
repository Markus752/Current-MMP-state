#include "stdafx.h"
#include "MapLoader.h"
#include <map>
#include <iostream>

using namespace sf;

MapLoader & MapLoader::getInstance()
{
	static MapLoader m_Instance;

	return m_Instance;
}

void MapLoader::loadMap(const string & filename, const sf::Vector2f & offset)
{
	FileInputStream mapStream;
	if (!mapStream.open(filename))
	{
		err() << "loadMap: could not open file " << filename << endl;
		return;
	}

	// convert FileInputStream to char* mapBuffer
	char* mapBuffer = new char[mapStream.getSize() + 1];
	mapStream.read(mapBuffer, mapStream.getSize());
	mapBuffer[mapStream.getSize()] = '\0';

	// now lets load a NLTmxMap
	NLTmxMap* tilemap = NLLoadTmxMap(mapBuffer);
	delete mapBuffer;

	err() << "Load tilemap with size: " << tilemap->width << ", "
		<< tilemap->height << " and tilesize: " << tilemap->tileWidth
		<< ", " << tilemap->tileHeight << std::endl;

	// load textures for every tileset
	for (auto tileset : tilemap->tilesets)
	{
		err() << "Load tileset: " << tileset->name << " width filename: "
			<< tileset->filename << " and tilesize: " << tileset->tileWidth
			<< ", " << tileset->tileHeight << std::endl;

		auto texture = make_shared<Texture>();
		if (!texture->loadFromFile(m_ResourcePath + tileset->filename))
			err() << "Could not load texture " << m_ResourcePath + tileset->filename << endl;
		m_TilesetTexture[tileset->name] = texture;
	}

	// go through all layers
	m_Layers.resize(tilemap->layers.size());
	
	for (int layerIdx = 0; layerIdx < (int)tilemap->layers.size(); layerIdx++)
	{
		NLTmxMapLayer* layer = tilemap->layers[layerIdx];
		err() << "Load layer: " << layer->name << " with width: "
			<< layer->width << " and height: " << layer->height << std::endl;

		int size = layer->width * layer->height;

		// go over all elements in the layer
		for (int i = 0; i < size; i++)
		{
			int grid = layer->data[i];

			if (grid == 0)
			{
				// 0 means there is no tile at this grid position		
				continue;
			}

			// get tileset and tileset texture
			NLTmxMapTileset* tileset = tilemap->getTilesetForGrid(grid);
			Vector2i tileSize(tilemap->tileWidth, tilemap->tileHeight);
			Texture& texture = *m_TilesetTexture[tileset->name];

			// horizontal tile count in tileset texture
			int tileCountX = texture.getSize().x / tileSize.x;

			// calcualte position of tile
			Vector2f position;
			position.x = (i % layer->width) * (float)tileSize.x;
			position.y = (i / layer->width) * (float)tileSize.y;
			position += offset;

			// calculate 2d idx of tile in tileset texture
			int idx = grid - tileset->firstGid;
			int idxX = idx % tileCountX;
			int idxY = idx / tileCountX;

			// calculate source area of tile in tileset texture
			IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

			auto sprite = make_shared<Sprite>();
			sprite->setTexture(texture);
			sprite->setTextureRect(source);
			sprite->setPosition(position.x, position.y);

			m_Layers[layerIdx].push_back(sprite);

			// set max Size of a layers
			m_MaxTileMapSize.first = tilemap->width * tilemap->tileWidth;
			m_MaxTileMapSize.second = tilemap->height * tilemap->tileHeight;
		}
	}

	 //go through all object layers
	for (auto group : tilemap->groups)
	{
		// go over all objects per layer
		for (auto object : group->objects)
		{			
			if (object->type == "GameObject")
			{				
				auto sprite = loadSprite(object);
				m_Objects[object->name] = sprite;
			}
		}
	}
	delete tilemap;
}

std::shared_ptr<MapLoader::Tile> MapLoader::loadSprite(NLTmxMapObject * object)
{
	auto gameObject = make_shared<Tile>();

	IntRect textureRect{};
	textureRect.width = object->width;
	textureRect.height = object->height;
	for (auto property : object->properties)
	{
		auto name = property->name;
		if (name == "Texture" && 
			!gameObject->texture.loadFromFile(m_ResourcePath + property->value))
		{
			err() << "loadSprite: Could not load texture for sprite: " <<
				m_ResourcePath + property->value << endl;
		}
		else if (name == "TextureRectLeft")
		{
			textureRect.left = stoi(property->value);
		}
		else if (name == "TextureRectTop")
		{
			textureRect.top = stoi(property->value);
		}
		else if (name == "ObjectDepth")
		{
			gameObject->depth = stoi(property->value);
		}
		else if (name == "MovementSpeed")
		{
			gameObject->movementSpeed = stoi(property->value);
		}
	
		else if (name == "PlayerIndex")
		{
			gameObject->playerIndex = stoi(property->value);
		}
		else if (name == "IsTrigger")
		{
			if (property->value == "1") gameObject->isTrigger = true;
		}
		else if (property->value == "component")
		{
			gameObject->components.push_back(name);
		}
		else if (name == "posX")
		{
			gameObject->posX = stof(property->value);
		}
		else if (name == "posY")
		{
			gameObject->posY = stof(property->value);
		}
		else if (name == "roomId")
		{
			gameObject->roomId = stoi(property->value);
		}
		else if (name == "TextureS")
		{
			gameObject->texture.loadFromFile(m_ResourcePath + property->value);
		}
		else if (name == "Text")
		{
			gameObject->textBox = property->value;
		}
	}
	gameObject->sprite.setTexture(gameObject->texture);
	gameObject->sprite.setTextureRect(textureRect);
	gameObject->sprite.setPosition(object->x, object->y);
	
	if ((float)gameObject->texture.getSize().x > 0 && (float)gameObject->texture.getSize().y > 0)
	{
		gameObject->sprite.setScale(object->width / (float)gameObject->texture.getSize().x, object->height / (float)gameObject->texture.getSize().y);
	}
	else gameObject->sprite.setScale(object->width, object->height);
		
	err() << "Object loaded: " << object->name << std::endl;
	return gameObject;
}

vector<vector<shared_ptr<sf::Sprite>>>& MapLoader::getLayers()
{
	return m_Layers;
}

std::unordered_map<std::string, shared_ptr<sf::Texture>>& MapLoader::getTexture()
{
	return m_TilesetTexture;
}

map<string, std::shared_ptr<MapLoader::Tile>>& MapLoader::getObjects()
{
	return m_Objects;
}

std::pair<int, int> MapLoader::getMaxSizes()
{
	return m_MaxTileMapSize;
}
