#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"

using std::string;

//this class is present button on the windows 
class ButtonLevel :public Button
{
public:
	ButtonLevel(sf::Vector2f loc, const sf::Texture& texture, float scale ,const sf::Texture& textureLock);
	void setPass(const bool pass);
	bool getPass();
	virtual void draw(sf::RenderWindow& window) const override;
	virtual sf::Sprite create() const override;

private:
	const sf::Texture& m_lockTexture;
	bool m_passLevel;
};