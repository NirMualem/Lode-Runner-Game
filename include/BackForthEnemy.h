#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "EnemyAbstract.h"
#include "Enums.h"


class BackForthEnemy : public EnemyAbstract
{
public:
	BackForthEnemy(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol,float moveSpeed);//constractor

	void updateEnemyLocation(sf::Vector2f playerLoc, const float deltaTime ,
		const vector<unique_ptr<StaticObject>>& m_staticObect) override;//update the new location of player
	virtual void noMove(const sf::Vector2f& playerLoc, const float deltaTime);//case enemy not move
	
	virtual void handleCollision(ObjectAbstract& gameObject);//for double dispatch
	virtual void handleCollision(Wall& wall);//collision with wall
	virtual void handleCollision(Ladder& gameObject);//collision with ladder
	virtual void handleCollision(Pole& gameObject);//collision with pole

};