#pragma once
#include "TriggerCollision.h"
#include "IObserver.h"
#include "TGUI/TGUI.hpp"

class InteractiveCollision : public TriggerCollision, public IObserver
{
public:
	InteractiveCollision(sf::FloatRect shape, sf::RectangleShape debugGeometry, bool isTrigger, bool isInteractive, tgui::Gui& gui, bool& paused, std::string text)
		: TriggerCollision(shape, debugGeometry, isTrigger)
		, m_IsInteractive(isInteractive)
		, m_Gui(gui)
		, m_Paused(paused)
		, m_Text(text)
	{

	};
	
	
	void onInteract();
	void createTextBox(std::string text);
	bool isInteractive();
	void notify()override;

private:
	bool m_IsInteractive;
	bool& m_Paused;
	std::shared_ptr<tgui::TextBox> m_TextBox = nullptr;
	tgui::Gui& m_Gui;
	std::string m_Text;
	bool m_WasTriggered = false;
};
