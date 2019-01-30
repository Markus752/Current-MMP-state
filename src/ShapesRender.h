#pragma once
#include "IComponent.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "AbstractRender.h"

class ShapesRender : public AbstractRender
{
public:
	ShapesRender(sf::Vector2f size, float& angle, sf::Vector2f& position)
		:m_Size(size)
		, m_Angle(angle)
		, m_PositionVec(position)
	{

	}

	void init() override;
	void update(float delta) override;
	void render(sf::RenderWindow& w);
	
private:
	// Works for Rectangle only (yet)
	sf::RectangleShape m_Rectangle;
	sf::Vector2f m_Size;
	float& m_Angle;


	// Position of GameObject, aka Position given from Transform Component
	sf::Vector2f& m_PositionVec;
};

