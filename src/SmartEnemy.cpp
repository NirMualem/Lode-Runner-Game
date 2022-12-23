#include <SFML/Graphics.hpp>
#include "SmartEnemy.h"
#include "EnemyAbstract.h"
#include "Enums.h"
#include "Wall.h"
#include "Ladder.h"
#include "ConstForGame.h"

//class of smart enemy in the game

SmartEnemy::SmartEnemy(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol, float moveSpeed)
	: EnemyAbstract(loc, texture, symbol, moveSpeed), m_foundladder(false)
{}

//handle collision with game object
void SmartEnemy::handleCollision(ObjectAbstract& gameObject)
{
	//check if the same object then return
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

void SmartEnemy::handleCollision(Ladder& gameObject)
{
	//if find ladder update bool and change side to move
	if (m_foundladder)
	{
		if (m_sprite.getPosition().x - 10 < gameObject.getLocation().x
			&& m_sprite.getPosition().x + 10 > gameObject.getLocation().x)
		{
			m_foundladder = false;
			m_side = SideToMove::UP;
		}
	}
}

SideToMove SmartEnemy::searchLadder(sf::Vector2f playerLoc, const vector<unique_ptr<StaticObject>>& m_staticObect)
{
	StaticObject* ladder = NULL;
	sf::Vector2f loc(m_sprite.getPosition());//for check the location
	ladder = foundObjectInLocation(m_staticObect, loc);//check if there is ladder in the location

	//if the player in the right of the enemy 
	if (playerLoc.x > m_sprite.getPosition().x)
		for (int col = 0; !(dynamic_cast<Wall*> (ladder)); col++)
		{
			loc.x += IMAGE_SIZE;
			ladder = foundObjectInLocation(m_staticObect, loc);
			if (dynamic_cast<Ladder*> (ladder))
			{
				m_foundladder = true;
				return SideToMove::RIGHT;
			}

		}
	//if the player in the left of the enemy 
	if (playerLoc.x < m_sprite.getPosition().x)
		for (int col = 0; !(dynamic_cast<Wall*> (ladder)); col++)
		{
			loc.x -= IMAGE_SIZE;
			ladder = foundObjectInLocation(m_staticObect, loc);
			if (dynamic_cast<Ladder*> (ladder))
			{
				m_foundladder = true;
				return SideToMove::LEFT;
			}
		}
	return SideToMove::LEFT;
}

//update enemy locatioin according to the player location
void SmartEnemy::updateEnemyLocation(sf::Vector2f playerLoc, const float deltaTime, const vector<unique_ptr<StaticObject>>& m_staticObect)
{
	if (playerLoc.y < m_sprite.getPosition().y && !m_foundladder && m_side != SideToMove::UP)
	{
		StaticObject* myObj = foundObjectInLocation(m_staticObect, m_sprite.getPosition());
		if (!dynamic_cast<Ladder*> (myObj))
			m_side = searchLadder(playerLoc, m_staticObect);
	}

	//if the plawer down
	if (playerLoc.y > m_sprite.getPosition().y)
	{
		sf::Vector2f downPlace(m_sprite.getPosition());
		downPlace.y += IMAGE_SIZE;
		StaticObject* downObj = foundObjectInLocation(m_staticObect, downPlace);
		if (!dynamic_cast<Wall*> (downObj))
			m_side = SideToMove::DOWN;
	}
	if (playerLoc.y < m_sprite.getPosition().y + 10 && playerLoc.y > m_sprite.getPosition().y - 10)
	{
		if (playerLoc.x > m_sprite.getPosition().x)
			m_side = SideToMove::RIGHT;
		else
			m_side = SideToMove::LEFT;
	}

	//update the location according to the check.
	if (m_side == SideToMove::RIGHT)
		updateBySide(SideToMove::RIGHT, deltaTime);
	else if (m_side == SideToMove::LEFT)
		updateBySide(SideToMove::LEFT, deltaTime);
	else if (m_side == SideToMove::UP)
		updateBySide(SideToMove::UP, deltaTime);
	else if (m_side == SideToMove::DOWN)
		updateBySide(SideToMove::DOWN, deltaTime);

}

//handle collision with wall
void  SmartEnemy::handleCollision(Wall& gameObject)
{
	if (m_side == SideToMove::RIGHT || m_side == SideToMove::LEFT)
	{
		sf::Sprite checkSprite = m_sprite;
		checkSprite.setScale(1, float(0.8));//for check if go between two wall
		checkSprite.setPosition(checkSprite.getPosition().x, checkSprite.getPosition().y + 1);

		if (checkSprite.getGlobalBounds().intersects(gameObject.getsprite().getGlobalBounds()))
		{
			m_sprite.setPosition(m_lastLoc);
		}
	}
	else if (m_side == SideToMove::UP || m_side == SideToMove::DOWN)
	{
		sf::Sprite checkSprite = m_sprite;
		checkSprite.setScale(float(0.8), 1);//for check if go between two wall
		checkSprite.setPosition(checkSprite.getPosition().x, checkSprite.getPosition().y + 1);

		if (checkSprite.getGlobalBounds().intersects(gameObject.getsprite().getGlobalBounds()))
		{
			m_sprite.setPosition(m_lastLoc);
		}
	}
	else
		m_sprite.setPosition(m_lastLoc);//update to the last location
}

//if the enemy stay in the same location update the location to other location
void SmartEnemy::noMove(const sf::Vector2f& playerLoc, const float )
{
	if (m_side == SideToMove::UP)
	{
		if (playerLoc.x > m_sprite.getPosition().x)
			m_side = SideToMove::RIGHT;
		else
			m_side = SideToMove::LEFT;
	}
	if (m_side == SideToMove::DOWN)
	{
		if (playerLoc.x > m_sprite.getPosition().x)
			m_side = SideToMove::RIGHT;
		else
			m_side = SideToMove::LEFT;
	}
}
void  SmartEnemy::handleCollision(Pole& ) {}//ignore;