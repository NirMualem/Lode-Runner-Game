#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "ObjectAbstract.h"

//this class is static object class in the board of the game.

StaticObject::StaticObject(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol)
	: ObjectAbstract(loc, texture, symbol), m_taken(false)
{
}

bool StaticObject::checkIfTake() const
{
	return m_taken;
}