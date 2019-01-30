#pragma once
#include "AbstractRender.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "MapLoader.h"

class Render : public AbstractRender
{
public:
	Render(std::string path, std::string fileName, sf::Vector2f& positionVec, float& angle, std::shared_ptr<GameObject> parent)
	: m_Path(path)
	, m_FileName(fileName)
	, m_PositionVec(positionVec)
	, m_Angle(angle)
	, m_LoadFromMap(false)
	, m_Parent(parent)
	{
		
	}

	Render(std::string fileName, sf::Vector2f& positionVec, float& angle, std::shared_ptr<GameObject> parent)
		: m_FileName(fileName)
		, m_PositionVec(positionVec)
		, m_Angle(angle)
		, m_LoadFromMap(true)
		, m_Parent(parent)
	{

	}

	void init() override;
	void update(float delta) override;
	void render(sf::RenderWindow& w) override;
	void setScale(float scaleX, float scaleY);

	bool& hasAnimation();

	std::string getFileName();
	sf::Texture& getTexture();

private:
	std::string m_Path;
	std::string m_FileName;
		
	bool m_TextureIsSet = false;
	bool m_HasAnimation = false;

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	bool m_LoadFromMap;

	// Position / angle of GameObject, aka Position given from Transform Component
	sf::Vector2f& m_PositionVec;
	float& m_Angle;

	//for animation
	std::shared_ptr<GameObject> m_Parent;
};

