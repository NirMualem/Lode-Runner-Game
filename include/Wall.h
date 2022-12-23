#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Enums.h"
#include "ObjectAbstract.h"

class Wall : public StaticObject
{
public:
	Wall(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol);//constractor
	void handleCollision(ObjectAbstract& gameObject)override;//double dispatch with game object 
	virtual void handleCollision(Wall& wall);//double dispatch with wall
	virtual void handleCollision(Player& player)override;//double dispatch with player
	virtual void handleCollision(EnemyAbstract& enemy)override;//double dispatch withenemy
	virtual void handleCollision(Hole& gameObject);//double dispatch with hole
	virtual void handleCollision(Coin& gameObject);//double dispatch with coin
	virtual void handleCollision(Gift& gameObject);//double dispatch with game object 
	virtual void handleCollision(Ladder& gameObject);//double dispatch with ladder 
	virtual void handleCollision(Pole& gameObject);//double dispatch with pole

};
