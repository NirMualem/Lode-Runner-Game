#include <SFML/Graphics.hpp>
#include "Hole.h"
#include "StaticObject.h"
#include "Enums.h"
#include "ConstForGame.h"
#include "Player.h"

Hole::Hole(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol)
	: StaticObject(loc, texture, symbol) , m_full(false) , m_timer(TIME_FOR_HOLE)
{}
void Hole::handleCollision(ObjectAbstract& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
void Hole::handleCollision(Player& player)
{
    player.handleCollision(*this);
}
void Hole::handleCollision(EnemyAbstract& enemy)
{
    enemy.handleCollision(*this);
}

void Hole::handleTime(float deltaTime)
{
    m_timer -= deltaTime;
    if(m_timer < 0 )
        m_taken = true;//delete hole when time end
}

bool Hole::getFull() const
{
    return m_full;
}
void Hole::setFull(bool full)
{
    m_full = full;//set hole to full
}

void Hole::handleCollision(Wall& ) {};//ignore
void Hole::handleCollision(Hole& )  {};//ignore
void Hole::handleCollision(Gift& ) {};//ignore
void Hole::handleCollision(Coin& )  {};//ignore
void Hole::handleCollision(Ladder& )  {};//ignore
void Hole::handleCollision(Pole& ) {};//ignore