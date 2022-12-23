#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Enums.h"

class Ladder : public StaticObject
{
public:
	Ladder(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol);//constractor

	virtual void handleCollision(ObjectAbstract& gameObject) override;
	virtual void handleCollision(Player& gameObject)override;
	virtual void handleCollision(EnemyAbstract& gameObject)override;
	virtual void handleCollision(Wall& gameObject)override ;//ignore
	virtual void handleCollision(Hole& gameObject) override;//ignore
	virtual void handleCollision(Coin& gameObject) override;//ignore
	virtual void handleCollision(Gift& gameObject) override;//ignore
	virtual void handleCollision(Ladder& gameObject) override;//ignore
	virtual void handleCollision(Pole& gameObject)override;//ignore
};
