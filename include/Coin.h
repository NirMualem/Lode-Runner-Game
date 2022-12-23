#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Enums.h"


class Coin : public StaticObject
{
public:
	Coin(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol);//constractor

	void handleCollision(ObjectAbstract& gameObject);//for double dispatch
	virtual void handleCollision(Player& gameObject);
	virtual void handleCollision(Wall& wall) ;//ignore
	virtual void handleCollision(EnemyAbstract& gameObject) ;//ignore
	virtual void handleCollision(Hole& gameObject);//ignore
	virtual void handleCollision(Coin& gameObject);//ignore
	virtual void handleCollision(Gift& gameObject);//ignore
	virtual void handleCollision(Ladder& gameObject);//ignore
	virtual void handleCollision(Pole& gameObject);//ignore
};
