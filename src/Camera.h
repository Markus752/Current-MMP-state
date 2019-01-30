#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "MapLoader.h"

class Camera : public IComponent
{
public:
	Camera() = default;

	Camera(sf::View& view, sf::Vector2f position, float scale, float angle, sf::RenderWindow& window, std::shared_ptr<GameObject> player, bool isRestricted)
		: m_View(view)
		, m_Position(position)
		, m_Scale(scale)
		, m_Angle(angle)
		, m_Window(window)
		, m_Player(player)
		, m_IsRestrictedFromMap(isRestricted)
	{

	}

	void init() override;
	void update(float delta) override;
	sf::Vector2f* getPosition();
	float* getScale();
	float* getRotation();

private:
	sf::View& m_View;
	sf::Vector2f m_Position;
	float m_Scale;
	float m_Angle;
	sf::RenderWindow& m_Window;
	std::shared_ptr<GameObject> m_Player;
	
	bool m_IsRestrictedFromMap;
	std::pair<int, int> m_TileMapBorder;
};

