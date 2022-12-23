#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MoveObjectAbstract.h"
#include "Enums.h"

class EnemyAbstract : public MoveObjectAbstract
{
public:
	EnemyAbstract(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol, float moveSpeed);
	 ~EnemyAbstract()  = default;

	virtual void updateEnemyLocation(sf::Vector2f playerLoc, const float deltaTime, const vector<unique_ptr<StaticObject>>& m_staticObect) = 0;
	virtual void noMove(const sf::Vector2f& playerLoc, const float deltaTime) = 0;//if enemy no move

	virtual void handleCollision(ObjectAbstract& gameObject) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(Ladder& gameObject) = 0;
	virtual void handleCollision(Pole& gameObject) = 0;
	virtual void handleCollision(Player& gameObject) ;
	virtual void handleCollision(Hole& gameObject);
	virtual void handleCollision(EnemyAbstract& gameObject);//ignore
	virtual void handleCollision(Coin& gameObject);//ignore
	virtual void handleCollision(Gift& gameObject) ;//ignore

protected:
	SideToMove m_side;//side move
};