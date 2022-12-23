#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "EnemyAbstract.h"
#include "Enums.h"

//class of smart enemy in the game

class SmartEnemy : public EnemyAbstract
{
public:
	SmartEnemy(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol, float moveSpeed);//constractor
	~SmartEnemy() = default;
	virtual void handleCollision(ObjectAbstract& gameObject);//double dispatch with game object 
	virtual void handleCollision(Wall& wall);//double dispatch with wall
	virtual void handleCollision(Ladder& gameObject);//double dispatch with ladder
	virtual void handleCollision(Pole& gameObject);//double dispatch with pole


	SideToMove searchLadder(sf::Vector2f playerLoc,
		const vector<unique_ptr<StaticObject>>& m_staticObect);//function that check if there is ladder to go up or down
	void noMove(const sf::Vector2f& playerLoc, const float deltaTime);//check if cant move 
	void updateEnemyLocation(sf::Vector2f playerLoc, const float deltaTime,
		const vector<unique_ptr<StaticObject>>& m_staticObect) override;//update the enemy location.

private:
	bool m_foundladder;//check if found a ladder to go up
};