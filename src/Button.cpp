#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>

using std::string;

//constrctor
Button::Button(sf::Vector2f loc, const sf::Texture& texture, float scale)
	:m_location(loc), m_texture(texture), m_scale(scale), m_choose(false)
{
}
//return sprite
sf::Sprite Button::getSprite()const
{
	return create();
}

//check if click on the button
bool Button::handleClick(const sf::Vector2f& location) const
{
	if (create().getGlobalBounds().contains(location))
	{
		return true;
	}

	return false;
}

//draw the button
 void Button::draw(sf::RenderWindow& window) const
{
	window.draw(create());
}

//create 
sf::Sprite Button::create() const
{
	auto result = sf::Sprite(m_texture);
	result.setPosition(sf::Vector2f(m_location.x, m_location.y));
	result.setScale(m_scale,m_scale);
	if (m_choose)
	{
		result.setColor(sf::Color(255, 255, 255, 128));
	}
	else
		result.setColor(sf::Color(255, 255, 255));
	return result;
}


void Button::setScale(float scale)
{
	m_scale = scale;
}

void Button::setChoose(bool choose)
{
	m_choose = choose;
}

bool Button::getChoose() const
{
	return m_choose;
}
