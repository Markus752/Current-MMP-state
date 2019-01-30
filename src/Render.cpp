#include "stdafx.h"
#include "Render.h"
#include "GameObject.h"
#include "Transform.h"
#include <iostream>
#include "ResourceManager.h"
#include "Animation.h"

void Render::init()
{
	if (m_TextureIsSet) return;

	if (m_LoadFromMap)
	{
		m_Texture = MapLoader::getInstance().getObjects().at(m_FileName)->texture;
	}
	else
	{
		ResourceManager::getInstance().loadTexture(m_Path, m_FileName);
		m_Texture = ResourceManager::getInstance().getTexture(m_FileName);
	}

	m_Texture.setSmooth(false);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setPosition(m_PositionVec);
	m_Sprite.setRotation(m_Angle);
	  
	m_TextureIsSet = true;
}

void Render::update(float delta)
{
	m_Sprite.setPosition(m_PositionVec);
	m_Sprite.setRotation(m_Angle);

	if (m_HasAnimation)
	{
		int left = m_Parent->getComponent<Animation>("Animation")->gettexturePosition().x;
		int top = m_Parent->getComponent<Animation>("Animation")->gettexturePosition().y;

		m_Sprite.setTextureRect(sf::IntRect(left, top, m_Parent->getComponent<Animation>("Animation")->getSizeX(), m_Parent->getComponent<Animation>("Animation")->getSizeY()));
	
		// Special offset for player / npc only
		if (m_Parent->getComponent<Animation>("Animation")->getCanMove())
		{
			m_Sprite.setPosition(m_PositionVec.x - 4, m_PositionVec.y - 15);
			m_Sprite.setScale(0.8f, 0.8f);
		}
		else m_Sprite.setScale(1, 1);
	}
}

std::string Render::getFileName()
{
	return m_FileName;
}

sf::Texture& Render::getTexture()
{
	return m_Texture;
}

void Render::render(sf::RenderWindow& window)
{
	window.draw(m_Sprite);	
}

void Render::setScale(float scaleX, float scaleY)
{
	m_Sprite.setScale(scaleX, scaleX);
}

bool & Render::hasAnimation()
{
	return m_HasAnimation;
}
