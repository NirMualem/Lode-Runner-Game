#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Enums.h"
#include "Wall.h"
#include "Player.h"

//wall in the board class.

Wall::Wall(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol)
    : StaticObject(loc, texture, symbol)
{

}
void Wall::handleCollision(ObjectAbstract& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
void Wall::handleCollision(Player& player)
{
    player.handleCollision(*this);
}
void Wall::handleCollision(EnemyAbstract& enemy)
{
    enemy.handleCollision(*this);
}

void Wall::handleCollision(Wall& ) {}//ignore
void Wall::handleCollision(Hole& ) {}//ignore
void Wall::handleCollision(Coin& ) {}//ignore
void Wall::handleCollision(Gift& ) {}//ignore
void Wall::handleCollision(Ladder& ) {}//ignore
void Wall::handleCollision(Pole& ) {}//ignore