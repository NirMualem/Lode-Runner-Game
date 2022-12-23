#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "HanldleFile.h"
#include "Menu.h"
#include "EnemyAbstract.h"
#include "Player.h"
#include "Hole.h"
#include "StaticObject.h"
#include <memory>
using std::unique_ptr;
using std::vector;

class Controller
{
public:
	Controller();//constructor
	void runGame();//run the game
	static void addScore(int addScore);// static func that add score

	static int m_numOfEnemy;//save the numbers oof enemy
	static int m_time;//save the time

private:
	int m_coinsInLevel;//save how many coins in level
	static int m_currLevel;//save curr level
	static int m_score;//save the score

	HanldleFile m_handleFile;//get the level from board.txt 
	Menu m_menu;//menu of the game
	vector<sf::Text> m_text;//text show on screen

	sf::Sprite m_backgroundSprite;
	sf::RenderWindow m_window; 

	unique_ptr<Player> m_player;//player
	vector<unique_ptr<EnemyAbstract>> m_enemys;//enemys
	vector<unique_ptr<StaticObject>>m_staticObect;//static object in level
	vector<unique_ptr<Hole>>m_holes;//hole 

	void drawGame();//draw the window
	void loadText();//load text for level
	void deleteHole();//delete hole if time pass
	void youWin();//when player complete the game
	void handleEvent(sf::Event event);//handle event
	void createWindow();//creat the window for game
	void holeUpdate(const float deltaTime);//update hole pass time
	void createHole(sf::Keyboard::Key key);//creat hole if press z/x
	void playerMove(const float deltaTime);//move player
	void addEnemyFromGift(int& enemyInLevel);//add enemy 
	void handleCollisions(ObjectAbstract& obj);//handle collosion by double patch
	void addEnemyByRandom(const int& row, const int& col) ;//add enemy (random kind)
	void handleTime(sf::Clock& clockTimeLevel, sf::Time elapsed, int& life);//update game time
	void loadLevelObject(int& LevelScore, int& enemyInLevel, sf::Clock& clockTimeLevel, int& life);//load curr level 
	bool lifeLose(int& life);//check life lose
	bool checkCreateHole(sf::Vector2f location, sf::Keyboard::Key key);//check if hole in vaild position
	bool downPlayerLife(bool& lose, int& LevelScore, int& enemyInLevel, sf::Clock& clockTimeLevel, int& life);//player down life
	bool enemyMove(bool& lose, int& LevelScore,int& enemyInLevel,const float deltaTime, sf::Clock& clockTimeLevel, int& life);//move enemy
	bool passLevel(sf::Clock &clockTimeLevel, int& LevelScore, int& enemyInLevel, int& life);//whem pass level
	bool handleMenuPress(bool lose, int& life);//handle press in menu
};