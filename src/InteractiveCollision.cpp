#include "stdafx.h"
#include "InteractiveCollision.h"


void InteractiveCollision::onInteract()
{
	if (m_isTriggered && m_TextBox && m_TextBox->isVisible())
	{
		m_TextBox->setVisible(false);
		m_isTriggered = false;

		m_Paused = false;
		m_WasTriggered = true;

	}
	else if (m_isTriggered)
	{
		if (m_WasTriggered) return;
		
		if (!m_TextBox) createTextBox(m_Text);

		m_TextBox->setVisible(true);

		m_Paused = true;
	}
	else if (!m_isTriggered && m_TextBox && m_TextBox->isVisible())
	{
		m_TextBox->setVisible(false);
	}
}

void InteractiveCollision::createTextBox(std::string text)
{
	m_Gui.setFont("../assets/Font.ttf");

	m_TextBox = tgui::TextBox::create();
	m_TextBox->setPosition("10%", "80%");
	m_TextBox->getRenderer()->setBackgroundColor(sf::Color(300, 300, 300, 200));
	m_TextBox->getRenderer()->setTextColor(sf::Color::Black);
	m_TextBox->setSize("80%" , "15%");
	m_TextBox->setText(text);
	m_TextBox->setTextSize(35);
	m_TextBox->getRenderer()->setBorderColor(sf::Color::Transparent);
	m_TextBox->getRenderer()->setBackgroundColor(sf::Color::Transparent);
	m_TextBox->getRenderer()->setTextureBackground("../assets/TextB.png");
	m_Gui.add(m_TextBox);
}

bool InteractiveCollision::isInteractive()
{
	return m_IsInteractive;
}

void InteractiveCollision::notify()
{
	onInteract();
}

