#include <SFML/Graphics.hpp>
#include "Ladder.h"
#include "StaticObject.h"
#include "Enums.h"
#include "Player.h"

Ladder::Ladder(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol)
	: StaticObject(loc, texture, symbol)
{}

void Ladder::handleCollision(ObjectAbstract& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
void Ladder::handleCollision(Player& player)
{
    player.handleCollision(*this);
}
void Ladder::handleCollision(EnemyAbstract& enemy)
{
    enemy.handleCollision(*this);
}
void Ladder::handleCollision(Wall& ) {}//ignore
void Ladder::handleCollision(Hole& )  {}//ignore
void Ladder::handleCollision(Coin& )  {}//ignore
void Ladder::handleCollision(Gift& )  {}//ignore
void Ladder::handleCollision(Ladder& )  {}//ignore
void Ladder::handleCollision(Pole& ) {}//ignore