#include "stdafx.h"
#include "AiComponent.h"
#include <random>

void AiComponent::move()
{

}

void AiComponent::init()
{

}

void AiComponent::update(float delta)
{
	if (!m_HasTarget)
	{
		findTarget();
		m_Velocity = calcVelocity(m_Target, m_StartPos);
	}
	if (m_HasTarget)
	{
		if(!(std::abs(m_Position.x - m_Target.x) < 5 && std::abs(m_Position.y - m_Target.y) < 5))
		{			
			m_Position += m_Velocity * 20.0f * delta;	
		}	
		else if(m_Target != m_StartPos)
		{
			m_Target = m_StartPos;
			m_Velocity = calcVelocity(m_StartPos, m_Position);
		}
		else
		{
			m_HasTarget = false;
		}
	}
}

void AiComponent::findTarget()
{
	std::random_device seeder;
	std::ranlux48 gen(seeder());
	std::uniform_int_distribution<int> rand(-m_MoveArea.x, m_MoveArea.x);
	int newXPos = rand(gen);

	std::random_device seeder2;
	std::ranlux48 gen2(seeder2());
	std::uniform_int_distribution<int> rand2(-m_MoveArea.y, m_MoveArea.y);
	int newYPos = rand2(gen2);

	m_Target = sf::Vector2f(m_StartPos.x - newXPos, m_StartPos.y - newYPos);

	m_HasTarget = true;
}

sf::Vector2f AiComponent::calcVelocity(sf::Vector2f targetPos, sf::Vector2f startPos)
{
	sf::Vector2f distance = sf::Vector2f(targetPos.x - startPos.x , targetPos.y - startPos.y);

	float length = std::sqrtf(distance.x * distance.x + distance.y * distance.y);

	return distance / length;
}
