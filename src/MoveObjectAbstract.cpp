#include <SFML/Graphics.hpp>
#include "MoveObjectAbstract.h"
#include "ObjectAbstract.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Wall.h"
#include "Pole.h"
#include "Ladder.h"
#include "EnemyAbstract.h"
#include "ConstForGame.h"
#include <memory.h>

using std::vector;
using std::unique_ptr;

//this class is absract of move object in the game

//constractor
MoveObjectAbstract::MoveObjectAbstract(const sf::Vector2f loc, const sf::Texture& texture,
	const char& symbol, float moveSpeed)
	: ObjectAbstract(loc, texture, symbol), m_moveSpeed(moveSpeed), m_lastLoc(loc)
{

	m_side = SideToMove::RIGHT;
	m_directionLoc = sf::Vector2f(1, 0);

}

//set the last location
void MoveObjectAbstract::setLastLoc(sf::Vector2f last)
{
	m_lastLoc = last;
}

//set position
void MoveObjectAbstract::setPosition(sf::Vector2f last)
{
	m_sprite.setPosition(last);
}

//check if the next place is vaild
void MoveObjectAbstract::checkVaild(const vector<unique_ptr<StaticObject>>& m_staticObect, const float deltaTime)
{
	SideToMove side;
	side = getSide();
	StaticObject* objInPlace = foundObjectInLocation(m_staticObect, m_sprite.getPosition());

	if (dynamic_cast<Pole*> (objInPlace))
	{
		m_sprite.setPosition(m_sprite.getPosition().x, objInPlace->getLocation().y);
	}

	switch (side)
	{
		//go up
	case SideToMove::UP:
	{
		if (objInPlace == NULL)
			m_sprite.setPosition(m_lastLoc);
		break;
	}

	//go down
	case SideToMove::DOWN:
	{
		if (dynamic_cast<Pole*> (objInPlace))
		{
			fall(m_staticObect);

		}
		else if (dynamic_cast<Ladder*> (objInPlace))
		{
			sf::Vector2f next(m_sprite.getPosition());
			next.y += 60.f + m_moveSpeed * deltaTime;
			if (foundObjectInLocation(m_staticObect, next) == NULL)
			{
				next.y = m_sprite.getPosition().y + IMAGE_MIDDLE;
				m_sprite.setPosition(foundObjectInLocation(m_staticObect, next)->getLocation());
			}
		}
		break;
	}
	}
	handleHalf(m_staticObect, m_sprite.getOrigin(), side);
}

//handle half situation of move object
void MoveObjectAbstract::handleHalf(const vector<unique_ptr<StaticObject>>& m_staticObect, sf::Vector2f ,
	SideToMove side)
{
	StaticObject* nextobj;
	StaticObject* lastobj;
	nextobj = foundObjectInLocation(m_staticObect, m_sprite.getPosition());
	lastobj = foundObjectInLocation(m_staticObect, m_lastLoc);

	if (side == SideToMove::UP)
	{
		if (lastobj == NULL && nextobj != NULL)
		{
			m_sprite.setPosition(m_lastLoc);
		}
		if (dynamic_cast<Wall*>(nextobj) && dynamic_cast<Pole*>(lastobj))
		{
			m_sprite.setPosition(m_sprite.getPosition().x, m_lastLoc.y);
		}
	}

	//check if the point in the object in left != right and fix the location
	if (side == SideToMove::UP || side == SideToMove::DOWN)
	{
		sf::Vector2f rightEdge(m_sprite.getPosition().x + (IMAGE_MIDDLE - 2), m_sprite.getPosition().y + IMAGE_MIDDLE);
		sf::Vector2f leftEdge(m_sprite.getPosition().x - (IMAGE_MIDDLE - 2), m_sprite.getPosition().y + IMAGE_MIDDLE);
		
		if (foundObjectInLocation(m_staticObect, rightEdge) != foundObjectInLocation(m_staticObect, leftEdge))
		{
			sf::Vector2f loc(m_sprite.getPosition().x, m_sprite.getPosition().y + IMAGE_MIDDLE);
			nextobj = foundObjectInLocation(m_staticObect, loc);
			if (nextobj != NULL)
			{
				m_sprite.setPosition(nextobj->getLocation());
			}
		}
	}
	//check if need to fall 
	if (side == SideToMove::RIGHT || side == SideToMove::LEFT)
	{
		if (nextobj == NULL && lastobj != NULL)
		{
			fall(m_staticObect);
			return;
		}

		//for check if the player little bit in the wall 
		if (foundObjectInLocation(m_staticObect, m_sprite.getPosition()) != NULL &&
			dynamic_cast<Wall*> (foundObjectInLocation(m_staticObect, m_sprite.getPosition())))
		{
			//check if in hole
			sf::Vector2f InHole(m_sprite.getPosition().x, m_sprite.getPosition().y + 10);
			if (foundObjectInLocation(m_staticObect, m_sprite.getPosition()) == NULL)
				fall(m_staticObect);
		}

		//go from wall to pole or ladder
		sf::Vector2f lastLoc(m_lastLoc.x, m_sprite.getPosition().y + IMAGE_SIZE + 2);
		sf::Vector2f nextLoc(m_sprite.getPosition().x, m_sprite.getPosition().y + IMAGE_SIZE + 2);
		lastobj = foundObjectInLocation(m_staticObect, lastLoc);
		nextobj = foundObjectInLocation(m_staticObect, nextLoc);
		if (dynamic_cast<Wall*>(lastobj)
			&& dynamic_cast<Ladder*>(nextobj) || dynamic_cast<Pole*>(nextobj))
		{
			if (foundObjectInLocation(m_staticObect, m_sprite.getPosition()) == NULL && nextobj != NULL)
			{
				m_sprite.setPosition(nextobj->getLocation());
			}
		}

		nextLoc = sf::Vector2f(m_sprite.getPosition().x + IMAGE_SIZE, m_sprite.getPosition().y);
		sf::Vector2f FallFromWall(m_sprite.getPosition().x, m_sprite.getPosition().y + IMAGE_SIZE);
		lastLoc = sf::Vector2f(m_lastLoc.x, m_lastLoc.y + IMAGE_SIZE);
		if (dynamic_cast<Wall*>(foundObjectInLocation(m_staticObect, lastLoc)) &&
			foundObjectInLocation(m_staticObect, FallFromWall) == NULL)
		{
			if (dynamic_cast<Pole*>(foundObjectInLocation(m_staticObect, nextLoc)))
			{
				return;
			}

			if (side == SideToMove::LEFT)
				m_sprite.setPosition(lastLoc.x + IMAGE_MIDDLE, m_sprite.getPosition().y);
			else
				m_sprite.setPosition(lastLoc.x - IMAGE_MIDDLE, m_sprite.getPosition().y);
			fall(m_staticObect);
		}
	}
}

//go down until cant 
void MoveObjectAbstract::fall(const vector<unique_ptr<StaticObject>>& m_staticObect)
{
	sf::Vector2f fall(m_sprite.getPosition().x, m_sprite.getPosition().y + IMAGE_MIDDLE);
	StaticObject* nextPlace = NULL;

	while (nextPlace == NULL)
	{
		m_lastLoc = sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 1.f);
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + 1.f);
		fall.y += 1.f;
		nextPlace = foundObjectInLocation(m_staticObect, fall);
	}
	if (dynamic_cast<Wall*>(nextPlace))
	{
		fall.y = nextPlace->getLocation().y - IMAGE_SIZE;
		m_lastLoc.y = nextPlace->getLocation().y - IMAGE_SIZE;
	}
	else
	{
		fall.y = nextPlace->getLocation().y;
		m_lastLoc.y = nextPlace->getLocation().y;
	}
	handleCollision(*this);
	m_sprite.setPosition(fall);
}

//get the side of the object according the last location and the new location
SideToMove MoveObjectAbstract::getSide() const
{
	if (m_lastLoc.x > m_sprite.getPosition().x)
		return SideToMove::RIGHT;
	else if (m_lastLoc.x < m_sprite.getPosition().x)
		return SideToMove::LEFT;
	else if (m_lastLoc.y > m_sprite.getPosition().y)
		return SideToMove::UP;
	else if (m_lastLoc.y < m_sprite.getPosition().y)
		return SideToMove::DOWN;

	return SideToMove::NO_MOVE;
}

//found which static object in the input location 
StaticObject* MoveObjectAbstract::foundObjectInLocation(const vector<unique_ptr<StaticObject>>& m_staticObect,
	const sf::Vector2f& nextlocation)
{
	int index;
	for (index = 0; index < m_staticObect.size(); index++)
	{
		if (m_staticObect[index]->getsprite().getGlobalBounds().contains(nextlocation))
		{
			return &(*m_staticObect[index]);
		}
	}
	return NULL;
}

//change side of sprite
void MoveObjectAbstract::changeSideSprite(SideToMove side)
{
	if (side == SideToMove::RIGHT)
	{
		m_sprite.setScale(1, 1);
		m_side = SideToMove::RIGHT;
	}
	if (side == SideToMove::LEFT)
	{
		m_sprite.setScale(-1, 1);
		m_side = SideToMove::LEFT;
	}
}

//update thr side of the sprite the member and the sprite to the correct side.
void MoveObjectAbstract::updateBySide(const SideToMove side, const float deltaTime)
{
	switch (side)
	{
	case SideToMove::RIGHT:
	{
		changeSideSprite(SideToMove::RIGHT);
		m_directionLoc = sf::Vector2f(1, 0);
		m_sprite.move(m_directionLoc * m_moveSpeed * deltaTime);
		break;
	}
	case SideToMove::LEFT:
	{
		changeSideSprite(SideToMove::LEFT);
		m_directionLoc = sf::Vector2f(-1, 0);
		m_sprite.move(m_directionLoc * m_moveSpeed * deltaTime);

		break;
	}
	case SideToMove::UP:
	{
		m_directionLoc = sf::Vector2f(0, -1);
		m_sprite.move(m_directionLoc * m_moveSpeed * deltaTime);

		break;
	}
	case SideToMove::DOWN:
	{
		m_directionLoc = sf::Vector2f(0, 1);
		m_sprite.move(m_directionLoc * m_moveSpeed * deltaTime);
		break;
	}
	}
}

sf::Vector2f MoveObjectAbstract::getLastLoc() const
{
	return m_lastLoc;
}


float MoveObjectAbstract::getspeed()const
{
	return m_moveSpeed;
}