#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "EnemyAbstract.h"
#include "Enums.h"

//this class is random enemy in the board
class RandomEnemy : public EnemyAbstract
{
public:
	RandomEnemy(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol,
		float moveSpeed);//constractor

	virtual void handleCollision(ObjectAbstract& gameObject);//double dispatch with game object 
	virtual void handleCollision(Wall& wall);//double dispatch with wall
	virtual void handleCollision(Ladder& gameObject);//double dispatch with game object 
	virtual void handleCollision(Pole& gameObject);//double dispatch with pole
	void noMove(const sf::Vector2f& playerLoc, const float deltaTime); //update next location if not move
	void updateEnemyLocation(sf::Vector2f playerLoc, const float deltaTime,
		const vector<unique_ptr<StaticObject>>& m_staticObect) override;//update the next location of the enemy

private:
	int m_timesToMove;//how much to move
	int m_timeMove;//how much moved
};