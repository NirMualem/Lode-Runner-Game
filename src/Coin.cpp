#include <SFML/Graphics.hpp>
#include "Coin.h"
#include "StaticObject.h"
#include "Enums.h"
#include "Player.h"

Coin::Coin(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol)
	: StaticObject(loc, texture, symbol) 
{
    m_sprite.setScale(float(0.8),1);//coin scale
}

void Coin::handleCollision(ObjectAbstract& gameObject)
{
    if (&gameObject == this) return;
   
    // double dispatch
    gameObject.handleCollision(*this);
}
void Coin::handleCollision(Player& player)
{
    m_taken = true;//mark coin as taken when collosion with player
    player.handleCollision(*this);
}
void Coin::handleCollision(Wall& ) {};//ignore
void Coin::handleCollision(EnemyAbstract& ) {};//ignore
void Coin::handleCollision(Hole& ) {};//ignore
void Coin::handleCollision(Coin& ) {};//ignore
void Coin::handleCollision(Gift& ) {};//ignore
void Coin::handleCollision(Ladder& ) {};//ignore
void Coin::handleCollision(Pole& ) {};//ignore