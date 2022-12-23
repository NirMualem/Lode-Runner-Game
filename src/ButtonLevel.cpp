#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>
#include "ButtonLevel.h"
#include <iostream>

using std::string;

//constrctor
ButtonLevel::ButtonLevel(sf::Vector2f loc, const sf::Texture& texture, float scale, const sf::Texture& textureLock)
							:Button(loc,texture,scale), m_lockTexture(textureLock)
{
	m_passLevel = false; 
}

void ButtonLevel::setPass(const bool pass)
{
	m_passLevel = pass;
}

bool ButtonLevel::getPass()
{
	return m_passLevel;
}
//draw the button
void ButtonLevel::draw(sf::RenderWindow& window) const
{
	window.draw(create());
}

//create 
sf::Sprite ButtonLevel::create() const
{
	if (!m_passLevel)
	{
		auto result = sf::Sprite(m_lockTexture);
		result.setPosition(sf::Vector2f(m_location.x, m_location.y));
		return result;
	}
	else
	{
		auto result = sf::Sprite(m_texture);
		result.setPosition(sf::Vector2f(m_location.x, m_location.y));
		return result;
	}
}
