#include <SFML/Graphics.hpp>
#include "ObjectAbstract.h"
#include "ConstForGame.h"

//this class is abstract for object

ObjectAbstract::ObjectAbstract(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol) : m_symbol(symbol)
{
	//update the texture
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getOrigin().x + IMAGE_MIDDLE, m_sprite.getOrigin().y));
	m_sprite.setPosition(sf::Vector2f(loc));
}

ObjectAbstract::~ObjectAbstract()
{}

//get the location
sf::Vector2f ObjectAbstract::getLocation()
{
	return m_sprite.getPosition();
}
//get the sprite
sf::Sprite ObjectAbstract::getsprite()const
{
	return m_sprite;
}

char ObjectAbstract::getchar()
{
	return m_symbol;
}

bool ObjectAbstract::checkCollision(const sf::FloatRect& rect) const
{
	return m_sprite.getGlobalBounds().intersects(rect);
}

void  ObjectAbstract::operator=(ObjectAbstract* obj)
{
	m_symbol = (*obj).m_symbol;
}

void ObjectAbstract::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}