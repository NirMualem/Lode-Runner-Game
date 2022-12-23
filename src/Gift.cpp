#include <SFML/Graphics.hpp>
#include "Gift.h"
#include "StaticObject.h"
#include "Enums.h"
#include "Player.h"

Gift::Gift(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol)
	: StaticObject(loc, texture, symbol)
{}
void Gift::handleCollision(ObjectAbstract& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
void Gift::handleCollision(Player& player)
{
    m_taken = true;//mark gift as taken
    player.handleCollision(*this);
}
 void Gift::handleCollision(EnemyAbstract& ) {};//ignore
 void Gift::handleCollision(Hole& ) {};//ignore
 void Gift::handleCollision(Coin& ) {};//ignore
 void Gift::handleCollision(Gift& ) {};//ignore
 void Gift::handleCollision(Ladder& ) {};//ignore
 void Gift::handleCollision(Pole& ) {};//ignore
 void Gift::handleCollision(Wall& ) {};//ignore