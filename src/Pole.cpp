#include <SFML/Graphics.hpp>
#include "Pole.h"
#include "StaticObject.h"
#include "Enums.h"
#include "Player.h"

Pole::Pole(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol)
    : StaticObject(loc, texture, symbol)
{
}
void Pole::handleCollision(ObjectAbstract& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
void Pole::handleCollision(Player& player)
{
    player.handleCollision(*this);//send to player with pole
}
void Pole::handleCollision(EnemyAbstract& enemy)
{
    enemy.handleCollision(*this);
}
void Pole::handleCollision(Hole& ) {}// ignore
void Pole::handleCollision(Coin& ) {}// ignore
void Pole::handleCollision(Gift& ) {}// ignore
void Pole::handleCollision(Ladder& ) {}// ignore
void Pole::handleCollision(Pole& ) {}// ignore
void Pole::handleCollision(Wall& ) {};// ignore