#include "stdafx.h"
#include "Camera.h"
#include "Transform.h"

void Camera::init()
{
	m_View.setCenter(m_Position);
	m_View.zoom(m_Scale);
	m_Window.setView(m_View);
}

void Camera::update(float delta)
{
	// Normal behavior
	if (!m_IsRestrictedFromMap)
	{
		m_Position = m_Player->getComponent<Transform>("Transform")->getPosition();
	}
	else
	{
		// border of the tileMap
		m_TileMapBorder = MapLoader::getInstance().getMaxSizes();
		m_Position = m_Player->getComponent<Transform>("Transform")->getPosition();

		auto leftBorder = m_View.getSize().x / 2;
		auto rightBorder = m_TileMapBorder.first - m_View.getSize().x / 2;
		auto topBorder = m_View.getSize().y / 2;
		auto bottomBorder = m_TileMapBorder.second - m_View.getSize().y / 2;

		m_Position.x = std::clamp(m_Position.x, leftBorder, rightBorder);
		m_Position.y = std::clamp(m_Position.y, topBorder, bottomBorder);
	}

	m_View.setCenter(m_Position);
	m_Window.setView(m_View);
}

sf::Vector2f* Camera::getPosition()
{
	return &m_Position;
}

float* Camera::getScale()
{
	return &m_Scale;
}

float* Camera::getRotation()
{
	return &m_Angle;
}
