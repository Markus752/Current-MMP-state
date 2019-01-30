#include "stdafx.h"
#include "MainMenu.h"
#include "GameObjectFactory.h"
#include "RenderManager.h"
#include "MusicManager.h"

void MainMenu::init()
{
	// Default Camera
	sf::View view;
	view.reset(sf::FloatRect(0, 0, m_Window.getSize().x, m_Window.getSize().y));
	m_Window.setView(view);

	GameObjectFactory factory;
	auto background = factory.createGameObjetBackground("..\\assets\\mainMenu.jpg", "MenuBackground", sf::Vector2f(0.0f, 0.0f), 0, view);
	background->init();
	m_GameObjectList.push_back(background);
	m_RenderManager.addRenderElement(background->getComponent<Render>("Render"), 0);

	// Music
	MusicManager::getInstance().loadSong("../assets/music/MainMenu.wav");
	MusicManager::getInstance().playCurrentSong();

	// GUI
	m_MenuButtons.clear();

	m_Gui.setTarget(m_Window);
	m_Gui.setFont("../assets/Font.ttf");
	
	auto title = tgui::Button::create();
	title->setText("Overworld Royal");
	title->setTextSize(70);
	title->setSize("65%", "25%");
	title->setPosition("20%", "15%");
	title->getRenderer()->setBorderColor(sf::Color::Transparent);
	title->getRenderer()->setBackgroundColor(sf::Color::Transparent);
	title->getRenderer()->setBorderColorFocused(sf::Color::Transparent);
	title->getRenderer()->setTexture("../assets/ButtonB.png");
	m_Gui.add(title, "Title");

	createButtons("New Game", m_Window.getSize().y / 2 - 50, "50%");
	createButtons("Controls", m_Window.getSize().y / 2 + 100, "65%");
	createButtons("Exit", m_Window.getSize().y - 200, "80%");

	auto textBox = tgui::TextBox::create();
	textBox->setText("Schuster Andreas, Klamer Markus");
	textBox->setTextSize(30);
	textBox->setPosition("50%", "95%");
	textBox->setSize("60%", "10%");
	m_Gui.add(textBox);
	
	auto eule = factory.createSprite("../assets/Eule.png", "Eule", sf::Vector2f(0.0f,0.0f), 0.0f, view);
	eule->init();
	m_GameObjectList.push_back(eule);
	m_RenderManager.addRenderElement(eule->getComponent<Render>("Render"), 1);
}


void MainMenu::update(float deltaTime)
{
	for (auto i : m_GameObjectList)
	{
		i->update(deltaTime);		
	}
	
	menuControl(deltaTime);
	setActiveButton(m_Index - 1);
}

void MainMenu::draw()
{
	m_RenderManager.render(m_Window);
	m_Gui.draw();
}

void MainMenu::exit()
{
	m_Gui.removeAllWidgets();
	m_GameObjectList.clear();
	m_RenderManager.clearList();
	MusicManager::getInstance().stopPlaying();
	m_MenuButtons.clear();
}

void MainMenu::menuControl(float deltaTime)
{
	if (!m_IsProtected)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_IsProtected = true;
			m_Index--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_IsProtected = true;
			m_Index++;
		}
	}
	else
	{
		counter = counter - deltaTime;
		if (counter <= 0)
		{
			m_IsProtected = false;
			counter = 0.35;
		}
	}

	if (m_Index < 1) m_Index = 3;
	if (m_Index > 3) m_Index = 1;

	if (m_Index == 1 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)))
	{
		m_GameStateManager.setState("Main");
	}
	else if (m_Index == 2 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)))
	{
		std::cout << "Controls" << std::endl;
	}
	else if (m_Index == 3 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::E)))
	{
		m_Window.close();
	}
}

void MainMenu::setActiveButton(int index)
{
 	for (auto it : m_MenuButtons)
	{
		if (it->getRenderer()->getTexture() != "../assets/ButtonB.png") it->getRenderer()->setTexture("../assets/ButtonB.png");
		if (it == m_MenuButtons[index]) it->getRenderer()->setTexture("../assets/ButtonD.png");
	}
}

void MainMenu::createButtons(string name, int height, string percentage)
{
	auto playButton = tgui::Button::create();
	playButton->setText(name);
	playButton->setTextSize(45);
	playButton->setSize("30%", "10%");
	playButton->setPosition("35%", percentage);
	playButton->getRenderer()->setBorderColor(sf::Color::Transparent);
	playButton->getRenderer()->setBackgroundColor(sf::Color::Transparent);
	playButton->getRenderer()->setBorderColorFocused(sf::Color::Transparent);
	playButton->getRenderer()->setTexture("../assets/ButtonB.png");

	m_Gui.add(playButton, name);
	m_MenuButtons.push_back(playButton);
}
