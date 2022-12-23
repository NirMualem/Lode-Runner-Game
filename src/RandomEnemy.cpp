#include <SFML/Graphics.hpp>
#include "RandomEnemy.h"
#include "EnemyAbstract.h"
#include "Enums.h"
#include <time.h>
#include "Wall.h"

//this class is random enemy in the board

RandomEnemy::RandomEnemy(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol,
	float moveSpeed)
	: EnemyAbstract(loc, texture, symbol, moveSpeed), m_timeMove(1), m_timesToMove(0)
{
}

void RandomEnemy::updateEnemyLocation(sf::Vector2f , const float deltaTime, const vector<unique_ptr<StaticObject>>& )
{
	m_timeMove++;//update the time that move
	if (m_timesToMove < m_timeMove)//check if need to update side
	{
		m_side = static_cast<SideToMove>(rand() % 2 + 3);//random up or down

		m_timesToMove = (rand() % 120) + 120;
		if (m_side == SideToMove::UP)
		{
			m_timeMove = -150;
		}
		else
			m_timeMove = 0;
	}
	//update the next location
	if (m_side == SideToMove::RIGHT)
		updateBySide(SideToMove::RIGHT, deltaTime);
	else if (m_side == SideToMove::LEFT)
		updateBySide(SideToMove::LEFT, deltaTime);
	else if (m_side == SideToMove::UP)
		updateBySide(SideToMove::UP, deltaTime);
	else if (m_side == SideToMove::DOWN)
		updateBySide(SideToMove::DOWN, deltaTime);
}

void RandomEnemy::noMove(const sf::Vector2f& , const float )
{
	m_side = static_cast<SideToMove>(rand() % 2 + 1);//update if not move to right or left
}
void RandomEnemy::handleCollision(ObjectAbstract& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

void RandomEnemy::handleCollision(Wall& gameObject)
{
	if (m_side == SideToMove::RIGHT || m_side == SideToMove::LEFT)
	{
		sf::Sprite checkSprite = m_sprite;
		checkSprite.setScale(1, float(0.8));//for check if between two walls
		checkSprite.setPosition(checkSprite.getPosition().x, checkSprite.getPosition().y + 4.f);
		if (checkSprite.getGlobalBounds().intersects(gameObject.getsprite().getGlobalBounds()))
			m_sprite.setPosition(m_lastLoc);
	}
	else
		m_sprite.setPosition(m_lastLoc);
}

void RandomEnemy::handleCollision(Ladder& ) {}//ignore;

void RandomEnemy::handleCollision(Pole& ) {}//ignore;