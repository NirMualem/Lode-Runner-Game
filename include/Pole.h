#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Enums.h"


class Pole : public StaticObject
{
public:
	Pole(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol);
	void handleCollision(ObjectAbstract& gameObject)override; // double dispatch with game object
	virtual void handleCollision(Wall& wall);// double dispatch with wall
	virtual void handleCollision(Player& gameObject)override;// double dispatch with player
	virtual void handleCollision(EnemyAbstract& gameObject) override;// double dispatch with enemy
	virtual void handleCollision(Hole& gameObject);// double dispatch with hole
	virtual void handleCollision(Coin& gameObject);// double dispatch with hole
	virtual void handleCollision(Gift& gameObject);// double dispatch with gift
	virtual void handleCollision(Ladder& gameObject);// double dispatch with ladder
	virtual void handleCollision(Pole& gameObject);// double dispatch with pole

};