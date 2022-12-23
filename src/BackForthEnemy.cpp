#include <SFML/Graphics.hpp>
#include "BackForthEnemy.h"
#include "EnemyAbstract.h"
#include "Enums.h"
#include "Wall.h"
BackForthEnemy::BackForthEnemy(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol, 
	float moveSpeed): EnemyAbstract(loc, texture, symbol, moveSpeed)
{}

void BackForthEnemy::updateEnemyLocation(sf::Vector2f , const float deltaTime, const vector<unique_ptr<StaticObject>>& )
{
	if (m_side == SideToMove::RIGHT)
		updateBySide(SideToMove::RIGHT, deltaTime);
	else if (m_side == SideToMove::LEFT)
		updateBySide(SideToMove::LEFT, deltaTime);
}

void BackForthEnemy::noMove(const sf::Vector2f& , const float )
{
	if (m_side == SideToMove::NO_MOVE)//first time choose side
	{
		m_side = SideToMove::LEFT;
	}
}

void BackForthEnemy::handleCollision(ObjectAbstract& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}
void BackForthEnemy::handleCollision(Wall& )
{
		m_sprite.setPosition(m_lastLoc);

	if (m_side == SideToMove::RIGHT)
		m_side = SideToMove::LEFT;
	else
		m_side = SideToMove::RIGHT;
}
void BackForthEnemy::handleCollision(Ladder& ) {}
void BackForthEnemy::handleCollision(Pole& ) {}

