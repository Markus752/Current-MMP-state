#pragma once

#include "IComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include <functional>

class Collision : public IComponent
{
public:
	Collision(sf::FloatRect shape, sf::RectangleShape debugGeometry)
		:m_Shape(shape)
		, m_DebugGeometry(debugGeometry)
	{

	}

	//Collision(sf::FloatRect shape, sf::RectangleShape debugGeometry, bool isTriggered, bool isInteractive, std::function<void> func)
	//	:m_Shape(shape)
	//	, m_DebugGeometry(debugGeometry)
	//	, m_IsTriggered(isTriggered)
	//	, m_IsInteractive(isInteractive)
	//	,m_func(func)
	//{

	//}

	sf::FloatRect& getShape();
	sf::RectangleShape getDebugShape();
	void init() override;
	void update(float delta) override;


protected:
	sf::FloatRect m_Shape;
	sf::RectangleShape m_DebugGeometry;
	//std::function<void> m_func;
	bool m_IsTriggered;
	bool m_IsInteractive;
};