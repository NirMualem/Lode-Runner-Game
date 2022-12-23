#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory.h>
#include "MoveObjectAbstract.h"
#include "EnemyAbstract.h"
#include "StaticObject.h"
#include "Enums.h"
#include "Gift.h"
using std::vector;
using std::unique_ptr;

//this class if class of the player in the game

class Player : public MoveObjectAbstract
{
public:
	Player(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol, float moveSpeed);
	~Player();
	int getcollectedCoin() const;
	int getLife() const;
	void setLife(int currLife);

	void handleCollision(ObjectAbstract& gameObject);//double dispatch with game object 
	void handleCollision(Player& gameObject);//double dispatch with player not do anything
	void handleCollision(EnemyAbstract& gameObject);//double dispatch with enemy lose life
	void handleCollision(Hole& gameObject);//double dispatch with hole
	void handleCollision(Ladder& gameObject);//double dispatch with ladder
	void handleCollision(Pole& gameObject);//double dispatch with pole 
	void handleCollision(Wall& wall);//double dispatch with wall
	void handleCollision(Gift& gameObject);//double dispatch gift take gift
	void handleCollision(Coin& gameObject);///double dispatch coin take gift

	//update player location according to the key press
	void updatePlayerLocation(const float deltaTime);

private:
	int m_collectedCoin;//coin taken
	int m_life;//life of the player
};