#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ObjectAbstract.h"

//this class is static object class in the board of the game.

class StaticObject : public ObjectAbstract
{
public:
	StaticObject(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol);
	~StaticObject() = default;
	bool checkIfTake() const;//check if take coin/gift ..
protected:
	bool m_taken;//check if take the static object
};