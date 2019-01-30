#include "stdafx.h"
#include "TriggerCollision.h"

bool TriggerCollision::isTrigger()
{
	return m_IsTrigger;
}

bool& TriggerCollision::isTriggered()
{
	return m_isTriggered;
}
void TriggerCollision::setIsTriggered(bool value)
{
	m_isTriggered = value;
}


bool& TriggerCollision::resetIsTriggered()
{
	return m_isTriggered;
}

