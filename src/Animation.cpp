#include "stdafx.h"
#include "Animation.h"
#include "MoveInput.h"

void Animation::init()
{
	m_SizeY = m_Texture.getSize().y / m_Height;
	m_SizeX = m_Texture.getSize().x / m_Width;

	m_TexturePosition.x = side * m_SizeX;
	m_TexturePosition.y = down * m_SizeY;
}

void Animation::update(float deltaTime)
{
	m_Counter -= deltaTime;

	if (!m_CanMove)
	{
		if (m_Counter <= 0)
		{
			m_Counter = 0.1f;
			side += 1;
			calculatePositions();
		}
	}
	else
	{
		if (m_Parent->getComponent<MoveInput>("MoveInput"))
		{
			if (m_Counter <= 0)
			{
				if (m_Parent->getComponent<MoveInput>("MoveInput")->getDirection() == moveDown) down = 0;
				
				if (m_Parent->getComponent<MoveInput>("MoveInput")->getDirection() == moveLeft) down = 1;

				if (m_Parent->getComponent<MoveInput>("MoveInput")->getDirection() == moveRight) down = 2;

				if (m_Parent->getComponent<MoveInput>("MoveInput")->getDirection() == moveUp) down = 3;
								
				m_Counter = 0.1f;

				if (m_Parent->getComponent<MoveInput>("MoveInput")->getDirection() == idle)
				{
					side = 1;
				}
				else
				{
					side += 1;
					calculateSide();
				}
			}
		}
		else
		{
			// For enemies etc
		}
	}

	m_TexturePosition.x = side * m_SizeX;
	m_TexturePosition.y = down * m_SizeY;
}

sf::Vector2f& Animation::gettexturePosition()
{
	return m_TexturePosition;
}

int& Animation::getSizeX()
{
	return m_SizeX;
}

int& Animation::getSizeY()
{
	return m_SizeY;
}

void Animation::calculateSide()
{
	if (side == m_Width)
	{
		side = 0;	
	}
}

void Animation::calculatePositions()
{
	if (side == m_Width)
	{
		side = 0;
		down += 1;
	}

	if (down == m_Height)
	{
		down = 0;
		side = 0;
	}	
}

bool& Animation::getCanMove()
{
	return m_CanMove;
}
