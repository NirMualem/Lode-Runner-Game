#pragma once
#include <vector>
#include <experimental/vector>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <memory.h>
#include "Controller.h"
#include "HanldleFile.h"
#include "ConstForGame.h"
#include "Enums.h"
#include "Menu.h"
#include "Player.h"
#include "RandomEnemy.h"
#include "BackForthEnemy.h"
#include "Hole.h"
#include "SmartEnemy.h"
#include "Gift.h"
#include "Coin.h"
#include "Wall.h"
#include "Ladder.h"
#include "Pole.h"
#include "ImageAndAudio.h"
#include <time.h>


using std::vector;
using std::make_unique;

int Controller::m_currLevel = 0;
int Controller::m_score = 0;
int Controller::m_numOfEnemy = 0;
int Controller::m_time = 0;

Controller::Controller(): m_window () , m_backgroundSprite(sf::Sprite()) , m_coinsInLevel(0)
{
	loadText();//load the text for window
	m_handleFile.loadFromFile();// load all level to vector
	m_backgroundSprite.setTexture(*ImageAndAudio::instance().getPic(BACKGROUND_GAME));//set backgrounde

	float loc = m_handleFile.getLevels()[m_currLevel].getWidth() * float(IMAGE_SIZE) / 4;
	m_text[2].setPosition(sf::Vector2f(loc, 5));
	m_text[3].setPosition(sf::Vector2f(loc + 100, 0));
	m_text[4].setPosition(sf::Vector2f(loc * 3, 5));
	m_text[5].setPosition(sf::Vector2f(loc * 2, 5));
	m_text[6].setPosition(sf::Vector2f((loc * 2) + 75, 0));
}

void Controller::runGame()
{	
	bool lose = false; //check player lose
	sf::Clock clock;//clock for hole
	sf::Clock clockTimeLevel;//clock for level
	sf::Time elapsed;//time to down from clock
	int LevelScore;//save the score in start level to recover if lose
	int enemyInLevel = 0;//save the mount that enemy in level (to add enemy)
	float deltaTime = 0;//move object by delta time 
	int life = START_LIFE;// save the of player life to check if down life
	
	ImageAndAudio::instance().playSound(Sound::GAME_MUSIC);

	while (true)//run the game
	{
		//handle game menu
		m_menu.openMenu();
		if (handleMenuPress(lose, life))
			break;

		loadLevelObject(LevelScore , enemyInLevel, clockTimeLevel, life);//load curr level object
		deltaTime = clock.restart().asSeconds();
		createWindow();//creat window by size
		m_window.setFramerateLimit(60);
		clockTimeLevel.restart();
		lose = false;
		while (m_window.isOpen())//while play in level
		{
			sf::Event event;
			while (!lose && m_window.pollEvent(event))
			{
				handleEvent(event);//handle press
			}
		
			deltaTime = clock.restart().asSeconds();
			holeUpdate(deltaTime);//update hole time
			playerMove(deltaTime);//move player
			addEnemyFromGift(enemyInLevel);//check if need add enemy
			if (lifeLose(life))//if life down
			{
				if (downPlayerLife(lose, LevelScore, enemyInLevel, clockTimeLevel,life))
					break;
			}
			drawGame();//draw game	
			if (!lose)//if no lose
			{
				if (enemyMove(lose, LevelScore, enemyInLevel, deltaTime ,clockTimeLevel,life))//move enemy
						break;
				deleteHole();
				elapsed = clockTimeLevel.getElapsedTime();
				handleTime(clockTimeLevel , elapsed, life);

				if (!lose)
				{
					drawGame();
					if (m_coinsInLevel ==  m_player->getcollectedCoin())//all coin in level collect
					{
						if (passLevel(clockTimeLevel, LevelScore, enemyInLevel,life))
							break;
					}
				
				}
			}
		}
	}
}

void Controller::handleEvent(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::KeyReleased:
		//create Hole when key released
		createHole(event.key.code);
		break;
	}
}

void Controller::createWindow()
{
	m_window.create(sf::VideoMode((m_handleFile.getLevels()[m_currLevel].getWidth()) * IMAGE_SIZE, (m_handleFile.getLevels()[m_currLevel].getHight()) * IMAGE_SIZE), "LODE RUNNER");
	m_window.setFramerateLimit(60);
	m_window.clear();
	drawGame();
	m_window.display();
}

void Controller::holeUpdate(const float deltaTime)
{
	for (const auto& hole : m_holes)
	{
		hole->handleTime(deltaTime);//run on holes and update by delta time
	}
}

void Controller::playerMove(const float deltaTime)
{
	//move player and check vaild and collosion
	m_player->setLastLoc(m_player->getLocation());
	m_player->updatePlayerLocation(deltaTime);
	m_player->checkVaild(m_staticObect, deltaTime);
	handleCollisions(*m_player);
}

bool Controller::downPlayerLife(bool &lose , int &LevelScore , int &enemyInLevel , sf::Clock & clockTimeLevel, int &life)
{
	if (life == 0)//if player lose game
	{
		m_window.close();
		lose = true;
		ImageAndAudio::instance().playSound(Sound::LOSE);
		return true;
	}
	//if player down life
	m_score = LevelScore;
	loadLevelObject(LevelScore, enemyInLevel, clockTimeLevel, life);
	m_window.create(sf::VideoMode((m_handleFile.getLevels()[m_currLevel].getWidth()) * IMAGE_SIZE, (m_handleFile.getLevels()[m_currLevel].getHight()) * IMAGE_SIZE), "LODE RUNNER");
	return false;
}

bool Controller::enemyMove(bool &lose, int &LevelScore,int &enemyInLevel, const float deltaTime,sf::Clock &clockTimeLevel , int& life)
{
	bool checkFail = false;
	//move enemys and check vaild and collosion
	for (const auto& enemy : m_enemys)
	{
		enemy->setLastLoc(enemy->getLocation());
		enemy->updateEnemyLocation(m_player->getLocation(), deltaTime , m_staticObect);
		enemy->checkVaild(m_staticObect, deltaTime);
		handleCollisions(*enemy);
		if (enemy->getLocation() == enemy->getLastLoc())
		{
			enemy->noMove(m_player->getLocation(), deltaTime);
			enemy->checkVaild(m_staticObect, deltaTime);
			handleCollisions(*enemy);
		}
		if (lifeLose(life))
			if (downPlayerLife(lose, LevelScore, enemyInLevel, clockTimeLevel,life))
				checkFail = true;
	}
	return checkFail;
}

void Controller::handleTime(sf::Clock &clockTimeLevel , sf::Time elapsed, int &life)
{
	//update game clock
	if (m_handleFile.getLevels()[m_currLevel].getTimeOfLevel() != 0)
	{
		m_time = m_handleFile.getLevels()[m_currLevel].getTimeOfLevel() - int(elapsed.asSeconds());
		m_text[m_text.size() - 1].setString(std::to_string(m_time));
	}
	if (m_time < 0)
	{
		m_player->setLife(life - 1);
		ImageAndAudio::instance().playSound(Sound::ENEMY);
		clockTimeLevel.restart();
	}
}

bool Controller::passLevel(sf::Clock &clockTimeLevel, int& LevelScore, int& enemyInLevel, int& life)
{
	clockTimeLevel.restart();
	Controller::addScore(50);//add score of complete level
	m_currLevel++;
	if ((m_currLevel) ==  m_handleFile.getLevels().size())//if end game
	{
		youWin();//you win window
		Sleep(3000);
		m_window.close();
		return true;
	}
	ImageAndAudio::instance().playSound(Sound::NEXT_LEVEL);
	m_handleFile.setLevelPass(m_currLevel);
	m_menu.updateButtonLevel(m_currLevel);
	loadLevelObject(LevelScore, enemyInLevel, clockTimeLevel,life);
	m_window.create(sf::VideoMode((m_handleFile.getLevels()[m_currLevel].getWidth()) * IMAGE_SIZE, (m_handleFile.getLevels()[m_currLevel].getHight()) * IMAGE_SIZE), "LODE RUNNER");

	return false;
}

void Controller::drawGame()
{
	m_window.clear();
	m_window.draw(m_backgroundSprite);//draw background
	for (int i = 0; i < m_staticObect.size(); i++)
	{
		m_staticObect[i]->draw(m_window);//draw static object
	}

	for (int i = 0; i < m_holes.size(); i++)
	{
		m_holes[i]->draw(m_window);//draw the holes
	}

	for (int i = 0; i < m_enemys.size(); i++)
	{
		m_enemys[i]->draw(m_window);//draw enemys
	}

	(m_player)->draw(m_window);//draw the player

	//text draw
	m_text[1].setString(std::to_string(m_currLevel+1));
	m_text[3].setString(std::to_string(m_score));
	

	for (int i = 0; i < m_text.size()-2; i++)
	{
		m_window.draw(m_text[i]);//draw text
	}
	if (m_handleFile.getLevels()[m_currLevel].getTimeOfLevel() != 0)
	{
		m_window.draw(m_text[m_text.size() - 2]);
		m_window.draw(m_text[m_text.size() - 1]);
	}

	sf::Sprite heart;
	heart.setTexture(*ImageAndAudio::instance().getPic(HEART));//draw life remain
	for (int i = 0; i < m_player->getLife(); i++)
	{
		heart.setPosition(sf::Vector2f(m_text[4].getPosition().x+80 +i*40 , m_text[4].getPosition().y+4));
		m_window.draw(heart);
	}
	m_window.display();
}

bool Controller::handleMenuPress(bool lose,int &life )
{
	m_backgroundSprite.setTexture(*ImageAndAudio::instance().getPic(BACKGROUND_GAME));
	lose = false;
	m_score = 0;
	if (m_menu.getSelectLevel() == ButtonMenu::EXIT_GAME_PRESS)
	{
		return true;//if exit game
	}
	else if (m_menu.getSelectLevel() == ButtonMenu::PLAY_PRESS)
	{
		life = START_LIFE;
		m_currLevel = 0;//start from first level
	}
	else
	{
		life = START_LIFE;
		m_currLevel = m_menu.getSelectLevel();//start from selected level
		m_currLevel -= 1;
	}
	return false;
}

bool Controller::lifeLose(int& life)
{
	if (life != m_player->getLife())//if life change
	{
		if (life < m_player->getLife())//life up from gift
		{
			life = m_player->getLife();
			return false;
		}
		else//life down
		{
			life = m_player->getLife();
			return true;
		}
	}
	return false;
}

void Controller::addScore(int addScore)
{
	m_score += addScore* (Controller::m_currLevel+1);//function add score multuply by level 
	
}
void Controller::createHole(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Z)
	{
		m_player->changeSideSprite(SideToMove::LEFT);
		//check vaild
		if(checkCreateHole(sf::Vector2f(float(m_player->getLocation().x - float(IMAGE_SIZE)),float( m_player->getLocation().y + (float(IMAGE_SIZE) -5))) , key))
		{ 
			sf::Vector2f HoleLoc(float(m_player->getLocation().x - float(IMAGE_SIZE)),float( m_player->getLocation().y + float(IMAGE_SIZE) * 1.5));
			ObjectAbstract* objWhereHole = m_player->foundObjectInLocation(m_staticObect, HoleLoc);
			if(objWhereHole != NULL)
		    m_holes.push_back(
			make_unique <Hole>(sf::Vector2f(float(m_player->getLocation().x - float(IMAGE_SIZE)),float( objWhereHole->getLocation().y - 5 )),
			*ImageAndAudio::instance().getPic(PicNameGame::HOLE), HOLE_CHAR));
			return;
		}
		return;
	}
	else if (key == sf::Keyboard::X)
	{
		m_player->changeSideSprite(SideToMove::RIGHT);
		if (checkCreateHole(sf::Vector2f(float(m_player->getLocation().x + float(IMAGE_SIZE)),float( m_player->getLocation().y + (float(IMAGE_SIZE) - 5))), key))
		{
			sf::Vector2f HoleLoc(float(m_player->getLocation().x + float(IMAGE_SIZE)),float( m_player->getLocation().y + float(IMAGE_SIZE) * 1.5));
			ObjectAbstract* objWhereHole = m_player->foundObjectInLocation(m_staticObect, HoleLoc);
			if (objWhereHole != NULL)
			m_holes.push_back(
			make_unique <Hole>(sf::Vector2f(float(m_player->getLocation().x + float(IMAGE_SIZE)), float(objWhereHole->getLocation().y - 5)),
			*ImageAndAudio::instance().getPic(PicNameGame::HOLE), HOLE_CHAR));
			return;
		}
	}
	return;
}

bool Controller::checkCreateHole(sf::Vector2f location , sf::Keyboard::Key key)
{
	sf::Vector2f rightLoc = sf::Vector2f(location.x - IMAGE_MIDDLE, location.y + (IMAGE_SIZE - 5));
	sf::Vector2f leftLoc = sf::Vector2f(location.x + IMAGE_MIDDLE, location.y + (IMAGE_SIZE - 5));
	bool left = false;
	bool right = false;

	for (auto& unmovable : m_staticObect)
	{
		if (unmovable->getchar() == WALL_CHAR)
		{
			if (unmovable->getsprite().getGlobalBounds().contains(rightLoc))
				right = true;
			if (unmovable->getsprite().getGlobalBounds().contains(leftLoc))
				left = true;
		}
	}
	for (auto& hole : m_holes)
	{
		if (hole->getsprite().getGlobalBounds().contains(rightLoc))
			right = false;
		if (hole->getsprite().getGlobalBounds().contains(leftLoc))
			left = false;
	}
	if (key == sf::Keyboard::X)
	{
		rightLoc = sf::Vector2f(float(m_player->getLocation().x + (float(IMAGE_SIZE) *1.5)),float( m_player->getLocation().y + (float(IMAGE_SIZE) - 5)));
		if (m_player->foundObjectInLocation(m_staticObect, rightLoc) != NULL)
			return false;
		rightLoc = sf::Vector2f(float(m_player->getLocation().x + (float(IMAGE_SIZE) / 2 +1)), float( m_player->getLocation().y + (float(IMAGE_SIZE) - 5)));
		if (m_player->foundObjectInLocation(m_staticObect, rightLoc) != NULL)
			return false;
	}
	else if (key == sf::Keyboard::Z)
	{
		leftLoc = sf::Vector2f(float(m_player->getLocation().x - (float(IMAGE_SIZE) * 1.5)), float( m_player->getLocation().y + (float(IMAGE_SIZE) - 5)));
		if (m_player->foundObjectInLocation(m_staticObect, leftLoc) != NULL)
			return false;
		leftLoc = sf::Vector2f(m_player->getLocation().x - (IMAGE_SIZE / 2 + 1), m_player->getLocation().y + (IMAGE_SIZE - 5));
		if (m_player->foundObjectInLocation(m_staticObect, leftLoc) != NULL)
			return false;
	}

	if (right && left)//check if hole in vaild locatin by hole edges
		return true;
	return false;
}
void Controller::deleteHole()
{
	std::experimental::erase_if(m_holes, [](unique_ptr <Hole>& hole)
		{
			return hole->checkIfTake();//delete hole when time end
		});
}
void Controller::addEnemyFromGift(int &enemyInLevel)
{
	if (m_numOfEnemy != enemyInLevel)//enemy number increase
	{
		for (int row = 0; row < m_handleFile.getLevels()[m_currLevel].getHight(); row++)
		{
			for (int col = 0; col < m_handleFile.getLevels()[m_currLevel].getWidth(); col++)
			{
				if (m_handleFile.getLevels()[m_currLevel].getCharLevel()[row][col] == ENEMY_CHAR)
				{
					addEnemyByRandom(row, col);//add enemy
					enemyInLevel++;
					return;
				}
			}
		}
	}
}

void Controller::addEnemyByRandom(const int &row ,const int &col)
{
	int enemyType = static_cast<typeOfEnemy>(rand() % 3);//random choose enemy
	if (enemyType == typeOfEnemy::randomEnemy)
	{
		m_enemys.push_back(
			make_unique <RandomEnemy>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)),
				*ImageAndAudio::instance().getPic(PicNameGame::ENEMY_RANDOM), ENEMY_CHAR, 100.f));
	}
	else if (enemyType == typeOfEnemy::backForthEnemy)
	{
		m_enemys.push_back(
			make_unique <BackForthEnemy>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)),
				*ImageAndAudio::instance().getPic(PicNameGame::ENEMY_BACK_FORTH), ENEMY_CHAR,120.f));
	}
	else
	{
		m_enemys.push_back(
			make_unique <SmartEnemy>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)),
				*ImageAndAudio::instance().getPic(PicNameGame::ENEMY_SMART), ENEMY_CHAR, 110.f));
	}
}

void Controller::handleCollisions(ObjectAbstract& obj)
{
	for (auto& movable : m_enemys)//handle collision with enemys
	{
		if (obj.checkCollision(movable->getsprite().getGlobalBounds()))
		{
			obj.handleCollision(*movable);
		}
	}
	if (obj.checkCollision(m_player->getsprite().getGlobalBounds()))//handle collision with player
	{
		obj.handleCollision(*m_player);
	}

	for (auto& unmovable : m_staticObect)//handle collision with static object
	{
		if (obj.checkCollision(unmovable->getsprite().getGlobalBounds()))
		{
			obj.handleCollision(*unmovable);
		}
	}
	for (auto& hole : m_holes)//handle collision with holes
	{
		if (obj.checkCollision(hole->getsprite().getGlobalBounds()))
		{
			obj.handleCollision(*hole);
		}
	}

	std::experimental::erase_if(m_staticObect, [] (unique_ptr <StaticObject>& unmovable)
	{
		return unmovable->checkIfTake();//erase static object taken by player
	});
}

void Controller::youWin()
{
	sf::Text score("", *ImageAndAudio::instance().getFont(), 34);
	score.setString(m_text[3].getString());
	score.setPosition(300, 250);
	m_window.create(sf::VideoMode(512, 296), "LODE RUNNER");
	m_window.clear();
	m_backgroundSprite.setTexture(*ImageAndAudio::instance().getPic(WIN_BACK));
	m_window.draw(m_backgroundSprite);
	m_window.draw(score);
	m_window.display();
}

void Controller::loadLevelObject(int &LevelScore , int &enemyInLevel , sf::Clock &clockTimeLevel, int &life)
{
	
	//clear level data
	m_enemys.clear();
	m_staticObect.clear();
	m_player.release();
	m_holes.clear();
	m_coinsInLevel = m_numOfEnemy = enemyInLevel = 0 ;
	clockTimeLevel.restart();
	LevelScore = m_score;
	m_time = m_handleFile.getLevels()[m_currLevel].getTimeOfLevel();
	m_text[m_text.size() - 1].setString(std::to_string(m_handleFile.getLevels()[m_currLevel].getTimeOfLevel()));
	//run on the new level char and load object
	for (int row = 0; row < m_handleFile.getLevels()[m_currLevel].getHight(); row++)
	{
		for (int col = 0; col < m_handleFile.getLevels()[m_currLevel].getWidth(); col++)
		{
			switch (m_handleFile.getLevels()[m_currLevel].getCharLevel()[row][col])
			{
			case WALL_CHAR:
			{
				m_staticObect.push_back(
					make_unique <Wall>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)), *ImageAndAudio::instance().getPic(PicNameGame::WALL), WALL_CHAR));
				break;
			}
			case POLE_CHAR:
			{
				m_staticObect.push_back(
					make_unique <Pole>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)), *ImageAndAudio::instance().getPic(PicNameGame::POLE), POLE_CHAR));
				break;
			}
			case LADDER_CHAR:
			{

				m_staticObect.push_back(
					make_unique <Ladder>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)), *ImageAndAudio::instance().getPic(PicNameGame::LADDER), LADDER_CHAR));
				break;
			}
			case GIFT_CHAR:
			{
				m_staticObect.push_back(
					make_unique <Gift>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)), *ImageAndAudio::instance().getPic(PicNameGame::GIFT), GIFT_CHAR));
				break;
			}
			case COIN_CHAR:
			{
				m_staticObect.push_back(
					make_unique <Coin>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE) +6, (row * float(IMAGE_SIZE)) ), *ImageAndAudio::instance().getPic(PicNameGame::COIN), COIN_CHAR));
				m_coinsInLevel++;
				break;
			}
			case ENEMY_CHAR:
			{
				addEnemyByRandom(row, col);
				m_numOfEnemy++;
				break;
			}
			case PLAYER_CHAR:
			{
				if(m_menu.getType() == PlayerType::BOY)
					m_player = make_unique<Player>(sf::Vector2f((col * float(IMAGE_SIZE))+ float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)), *ImageAndAudio::instance().getPic(PicNameGame::PLAYER_BOY),
					PLAYER_CHAR,150.f);
				else
					m_player = make_unique<Player>(sf::Vector2f((col * float(IMAGE_SIZE)) + float(IMAGE_MIDDLE), row * float(IMAGE_SIZE)), *ImageAndAudio::instance().getPic(PicNameGame::PLAYER_GIRL),
						PLAYER_CHAR, 150.f);
				break;
			}
			}
		}
	}
	enemyInLevel = m_numOfEnemy;
	m_player->setLife(life);
}

void Controller::loadText()//load text of the windows
{
	m_text.push_back(sf::Text("LEVEL:", *ImageAndAudio::instance().getFont(), 34));
	m_text[0].setPosition(sf::Vector2f(5,5));
	m_text[0].setFillColor(sf::Color(255,255,168));

	m_text.push_back(sf::Text("", *ImageAndAudio::instance().getFont(),40));
	m_text[1].setPosition(sf::Vector2f(100, 0));
	m_text[1].setFillColor(sf::Color(255, 255, 168));

	m_text.push_back(sf::Text("SCORE:", *ImageAndAudio::instance().getFont(), 34));
	m_text[2].setPosition(sf::Vector2f(405,5));
	m_text[2].setFillColor(sf::Color(255, 255, 168));

	m_text.push_back(sf::Text("", *ImageAndAudio::instance().getFont(), 40));
	m_text[3].setPosition(sf::Vector2f(505, 0));
	m_text[3].setFillColor(sf::Color(255, 255, 168));

	m_text.push_back(sf::Text("LIFE:", *ImageAndAudio::instance().getFont(), 34));
	m_text[4].setPosition(sf::Vector2f(805,5));
	m_text[4].setFillColor(sf::Color(255, 255, 168));

	m_text.push_back(sf::Text("TIME:", *ImageAndAudio::instance().getFont(), 34));
	m_text[5].setPosition(sf::Vector2f(205, 5));
	m_text[5].setFillColor(sf::Color(255, 255, 168));

	m_text.push_back(sf::Text("", *ImageAndAudio::instance().getFont(), 40));
	m_text[6].setPosition(sf::Vector2f(280, 0));
	m_text[6].setFillColor(sf::Color(255, 255, 168));
}