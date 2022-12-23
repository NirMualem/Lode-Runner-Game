#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Wall;
class Hole;
class Coin;
class Ladder;
class Pole;
class Gift;
class EnemyAbstract;
class Player;

class ObjectAbstract
{
public:
    ObjectAbstract(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol);//constractor
    virtual ~ObjectAbstract() = 0;
    char getchar();
    void draw(sf::RenderWindow& window) const;//draw the sprite
    sf::Vector2f getLocation();//get location
    sf::Sprite getsprite()const;//get the sprite
    void  operator=(ObjectAbstract* obj);
    bool checkCollision(const sf::FloatRect& rect) const;//check collision

    virtual void handleCollision(ObjectAbstract& gameObject) = 0; // double dispatch with object abstract
    virtual void handleCollision(Gift& Gift) = 0;// double dispatch with gift
    virtual void handleCollision(Wall& wall) = 0;// double dispatch with wall
    virtual void handleCollision(Player& gameObject) = 0;// double dispatch with player
    virtual void handleCollision(EnemyAbstract& gameObject) = 0;// double dispatch with enemy
    virtual void handleCollision(Hole& gameObject) = 0;// double dispatch with hole
    virtual void handleCollision(Coin& gameObject) = 0; // double dispatch with coin
    virtual void handleCollision(Ladder& gameObject) = 0;// double dispatch with ladder
    virtual void handleCollision(Pole& gameObject) = 0;// double dispatch with pole


protected:
    sf::Sprite m_sprite;
private:
    char m_symbol;
};