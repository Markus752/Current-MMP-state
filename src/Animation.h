#pragma once
#include <iostream>
#include "IComponent.h"
#include "GameObject.h"

class Animation : public IComponent 
{
public:
	Animation(int width, int height, sf::Texture texture, std::shared_ptr<GameObject> parent, bool camMove = false)
		:m_Width(width)
		,m_Height(height)	
		,m_Texture(texture)
		, m_Parent(parent)
		,m_CanMove(camMove)
	{

	}

	void init();
	void update(float deltaTime);
	sf::Vector2f& gettexturePosition();
	int& getSizeX();
	int& getSizeY();
	void calculateSide();
	void calculatePositions();
	bool& getCanMove();
private:
	int m_Width;
	int m_Height;
	int m_SizeY;
	int m_SizeX;

	int side = 0;
	int down = 0;

	bool m_CanMove;
	std::shared_ptr<GameObject> m_Parent;
	float m_Counter = 0.1f;
	sf::Texture m_Texture;
	sf::Vector2f m_TexturePosition;
};

