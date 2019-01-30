#include "stdafx.h"
#include "ShapesRender.h"
#include "GameObject.h"
#include "Transform.h"
#include <iostream>

void ShapesRender::init()
{
	m_Rectangle.setPosition(m_PositionVec);
	m_Rectangle.setSize(m_Size);
	m_Rectangle.setRotation(m_Angle);

	// Set Pivot of Rectangle to make it look better (Not needed)
	m_Rectangle.setOrigin(7.5f, 7);
}

void ShapesRender::update(float delta)
{
	m_Rectangle.setPosition(m_PositionVec);
	m_Rectangle.setRotation(m_Angle);
}

void ShapesRender::render(sf::RenderWindow& w)
{
	w.draw(m_Rectangle);
}
