#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Enums.h"

class Gift : public StaticObject
{
public:
	Gift(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol);
	void handleCollision(ObjectAbstract& gameObject)override;
	virtual void handleCollision(Player& gameObject)override;
	virtual void handleCollision(EnemyAbstract& gameObject);
	virtual void handleCollision(Hole& gameObject);//ignore
	virtual void handleCollision(Coin& gameObject);//ignore
	virtual void handleCollision(Gift& gameObject);//ignore
	virtual void handleCollision(Ladder& gameObject);//ignore
	virtual void handleCollision(Pole& gameObject);//ignore
	virtual void handleCollision(Wall& gameObject);//ignore
};
