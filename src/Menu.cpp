#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <string>
#include "Enums.h"
#include <windows.h>
#include <vector>
#include "Controller.h"
#include "Button.h"
#include "ButtonLevel.h"
#include "ConstForGame.h"
#include "ImageAndAudio.h"

using std::vector;

//this class is the start window to get from user the 
Menu::Menu():m_window(), m_backgroundSprite(sf::Sprite())
{
	//create button in the left of the windows. 
	createAllButton();//create the buttom

	m_backgroundSprite.setTexture(*ImageAndAudio::instance().getPicMenu(PicNameMenu::BACKGROUND_MENU));
	m_backgroundSprite.setPosition(sf::Vector2f(0, 0));
	m_typePlayer = PlayerType::GIRL;
}
PlayerType Menu::getType() const
{
	return m_typePlayer;//get type of player chose
}
void Menu::setType(PlayerType type)
{
	m_typePlayer = type;//set player choose
}

void Menu::openMenu()
{
	m_window.create(sf::VideoMode(900, 506), "lode runner menu");
	m_window.clear();
	//draw the members
	drawMenu();
	m_window.display();

	while (m_window.isOpen())
	{
		if (m_typePlayer == PlayerType::BOY)
		{
			m_button[ButtonMenu::BOY].setScale(float(1.1));
		}
		else if (m_typePlayer == PlayerType::GIRL)
		{
			m_button[ButtonMenu::GIRL].setScale(float(1.1));
		}

		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_buttonSelect = ButtonMenu::EXIT_GAME_PRESS;
				m_window.close();
				break;
			case sf::Event::MouseMoved:
			{
				handleMouseMove(float(event.mouseMove.x),float( event.mouseMove.y));
				break;
			}
			//if the mouse press handle.
			case sf::Event::MouseButtonReleased:
				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				handleClick(location);

				if (m_buttonSelect == ButtonMenu::PLAY_PRESS || m_buttonSelect == ButtonMenu::EXIT_GAME_PRESS)
				{
					m_window.close();
					break;
				}
				else if (m_buttonSelect == ButtonMenu::HELP_PRESS)
				{
					openInst();
				}
				else if (m_buttonSelect == ButtonMenu::BOY)
				{
					m_typePlayer = PlayerType::BOY;
				}
				else if (m_buttonSelect == ButtonMenu::GIRL)
				{
					m_typePlayer = PlayerType::GIRL;
				}
				else if (m_buttonSelect == ButtonMenu::SELECT_LEVEL_PRESS)
				{
					m_button[ButtonMenu::SELECT_LEVEL_PRESS].setScale(1);
					m_buttonSelect = drawSelectLevelWin();
					if (m_buttonSelect != 7)
					{
						m_window.close();
						break;
					}
					else
					{
						m_window.clear();
						//draw the members
						drawMenu();
						m_window.display();
					}
				}
			}

		}
	}
}

int Menu::drawSelectLevelWin()//when press select level handle select level window
{
	m_window.clear();
	m_window.draw(m_backgroundSprite);
	//buttons
	for (int i = 0; i < m_buttonLevel.size(); ++i)
	{
		m_buttonLevel[i].draw(m_window);
	}
	m_window.display();

	m_buttonSelect = -1;

	while (true)
	{
		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

				//if the mouse press handle.
			case sf::Event::MouseButtonReleased:
				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				handleClickLevelsWin(location);

				if (m_buttonSelect != -1)
				{
					return m_buttonSelect;
				}
			}
		}
	}
	return m_buttonSelect;
}
//this function change the mouse according the location.
void Menu::handleMouseMove(float x, float y)
{
	sf::Vector2f loc(x, y);
	//if on the menu in regular mouse 
	for (int i = 0; i < m_button.size(); ++i)
		{
			if (m_button[i].getSprite().getGlobalBounds().contains(loc))
					m_button[i].setScale(float(1.1));
			else
					m_button[i].setScale(1);
		}
	if (m_typePlayer == PlayerType::BOY)
	{
		m_button[ButtonMenu::BOY + 1].setChoose(false);
		m_button[ButtonMenu::GIRL+1].setChoose(true);

	}
	else if (m_typePlayer == PlayerType::GIRL)
	{
		m_button[ButtonMenu::BOY + 1].setChoose(true);
		m_button[ButtonMenu::GIRL + 1].setChoose(false);
	}
	m_window.clear();
	//draw the members
	drawMenu();
	m_window.display();
}

//this function handle click on the mouse
void Menu::handleClick(const sf::Vector2f& location)
{
	//check if click on buttons
	for (auto i = 0; i < m_button.size(); ++i)
	{
		if (m_button[i].handleClick(location))
		{
			m_buttonSelect = i-1;
			break;
		}
		//if push on no button in menu
		else
		{
			m_buttonSelect = -2 ;
		}
	}
	switch (m_buttonSelect)
	{
	case ButtonMenu::PLAY_PRESS:
		m_buttonSelect = 1;
		break;
	}
}

void Menu::handleClickLevelsWin(const sf::Vector2f& location)
{
	//check if click on buttons
	for (auto i = 0; i < m_buttonLevel.size(); ++i)
	{
		if (m_buttonLevel[i].handleClick(location))
		{
			if (m_buttonLevel[i].getPass())
			{
				m_buttonSelect = i + 1;
				break;
			}
		}
		//if push on no button in menu
		else
		{
			m_buttonSelect = -1;
		}
	}
}

void Menu::openInst()//instruction for game
{
	sf::RenderWindow inst;
	sf::Sprite instBack;
	instBack.setTexture(*ImageAndAudio::instance().getPicMenu(PicNameMenu::INST_BACKGROUND));
	instBack.setPosition(sf::Vector2f(0, 0));
	inst.create(sf::VideoMode(1004, 636), "lode runner instructions");
	inst.clear(); 
	inst.draw(instBack);
	inst.display();

	while (inst.isOpen())
	{
		for (auto event = sf::Event{}; inst.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				inst.close();
				break;
			}
		}
	}
}
//this function draw the members in the windows.
void Menu::drawMenu()
{

	m_window.draw(m_backgroundSprite);
	//buttons
	for (int i = 0; i < m_button.size(); ++i)
	{
		m_button[i].draw(m_window);
	}
}

int Menu::getSelectLevel() const
{
	return m_buttonSelect;
}

void Menu::updateButtonLevel(int level)
{
	m_buttonLevel[level].setPass(true);
}

//this function  create all button.
void Menu::createAllButton()
{
	//three button in the up of the page
	m_button.clear();
	sf::Vector2f l(70, 370);

	//exit
	Button EXIT_GAME(l, *ImageAndAudio::instance().getPicMenu(PicNameMenu::EXIT_GAME), 1);
	m_button.push_back(EXIT_GAME);
	l.y -= BUTTON_LOCATION;

	//select 
	Button select(l, *ImageAndAudio::instance().getPicMenu(PicNameMenu::SELECT_LEVEL), 1);
	l.y -= BUTTON_LOCATION;
	m_button.push_back(select);

	//play 
	Button PLAY(l, *ImageAndAudio::instance().getPicMenu(PicNameMenu::PLAY) , 1);
	m_button.push_back(PLAY);

	l = sf::Vector2f(30, 50);
	Button help(l, *ImageAndAudio::instance().getPicMenu(PicNameMenu::HELP), 1);
	m_button.push_back(help);

	l = sf::Vector2f(300, 160);
	Button boy(l, *ImageAndAudio::instance().getPicMenu(PicNameMenu::BOY_MENU), 1);
	m_button.push_back(boy);

	l = sf::Vector2f(500, 160);
	Button girl(l, *ImageAndAudio::instance().getPicMenu(PicNameMenu::GIRL_MENU), 1);
	m_button.push_back(girl);

	//levels menu buttons
	l = sf::Vector2f(200 , 200);

	ButtonLevel level1(l, *ImageAndAudio::instance().getPicLevels(1), 1 , *ImageAndAudio::instance().getPicLevels(0));
	level1.setPass(true);
	m_buttonLevel.push_back(level1);

	l.x += BUTTON_LEVEL_LOCATION;
	ButtonLevel level2(l, *ImageAndAudio::instance().getPicLevels(2), 1, *ImageAndAudio::instance().getPicLevels(0));
	m_buttonLevel.push_back(level2);

	l.x += BUTTON_LEVEL_LOCATION;
	ButtonLevel level3(l, *ImageAndAudio::instance().getPicLevels(3), 1, *ImageAndAudio::instance().getPicLevels(0));
	m_buttonLevel.push_back(level3);

	l.x = 200;
	l.y += BUTTON_LEVEL_LOCATION;
	ButtonLevel level4(l, *ImageAndAudio::instance().getPicLevels(4), 1, *ImageAndAudio::instance().getPicLevels(0));
	m_buttonLevel.push_back(level4);

	l.x += BUTTON_LEVEL_LOCATION;
	ButtonLevel level5(l, *ImageAndAudio::instance().getPicLevels(5), 1, *ImageAndAudio::instance().getPicLevels(0));
	m_buttonLevel.push_back(level5);

	l.x += BUTTON_LEVEL_LOCATION;
	ButtonLevel level6(l, *ImageAndAudio::instance().getPicLevels(6), 1, *ImageAndAudio::instance().getPicLevels(0));
	m_buttonLevel.push_back(level6);

	l = sf::Vector2f(20 , 300);
	ButtonLevel back(l, *ImageAndAudio::instance().getPicLevels(7), 1, *ImageAndAudio::instance().getPicLevels(7));
	back.setPass(true);
	m_buttonLevel.push_back(back);
}
