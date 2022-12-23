#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using std::string;

//this class is present button on the windows 
class Button
{
public:
    Button(sf::Vector2f loc, const sf::Texture& texture, float scale);//constractor
    void setScale(float scale);
    void setChoose(bool choose);
    bool getChoose() const;
    bool handleClick(const sf::Vector2f& location) const;//check if click on button

    sf::Sprite getSprite()const;//return sprite
   
    virtual sf::Sprite create() const;//create sprite
    virtual void draw(sf::RenderWindow& window) const;//draw the button
  
protected:
    sf::Vector2f m_location;//location of the sprite
    const sf::Texture& m_texture;//texture

private:
    float m_scale;//scale of button
    bool m_choose;//save if button choos
};


