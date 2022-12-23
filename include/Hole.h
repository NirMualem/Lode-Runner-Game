#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Enums.h"


class Hole : public StaticObject
{
public:
	Hole(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol);

	bool getFull() const;//get if the hole is full
	void setFull(bool full);//set hole full
	void handleTime(float deltaTime);//change life time of hole

	virtual void handleCollision(ObjectAbstract& gameObject)override;//for double patch
	virtual void handleCollision(Player& gameObject)override;
	virtual void handleCollision(EnemyAbstract& gameObject)override;
	virtual void handleCollision(Wall& wall) override ;//ignore
	virtual void handleCollision(Hole& gameObject) override ;//ignore
	virtual void handleCollision(Gift& gameObject) ;//ignore
	virtual void handleCollision(Coin& gameObject) override ;//ignore
	virtual void handleCollision(Ladder& gameObject) override ;//ignore
	virtual void handleCollision(Pole& gameObject)override ;//ignore

private:
	float m_timer;//time left for clock
	bool m_full;//if hole is full
};
