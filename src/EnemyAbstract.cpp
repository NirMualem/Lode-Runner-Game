#include <SFML/Graphics.hpp>
#include "EnemyAbstract.h"
#include "MoveObjectAbstract.h"
#include "Player.h"
#include "Hole.h"
#include "ConstForGame.h"

EnemyAbstract::EnemyAbstract(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol,float moveSpeed)
	:MoveObjectAbstract(loc, texture, symbol, moveSpeed), m_side(SideToMove::NO_MOVE)
{
}

void EnemyAbstract::handleCollision(ObjectAbstract& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}
void EnemyAbstract::handleCollision(Hole& gameObject)//enemy enter hole
{
	if (gameObject.checkIfTake())
	{
		m_sprite.setScale(1, 1);
		m_sprite.setPosition(gameObject.getLocation().x, gameObject.getLocation().y - (IMAGE_SIZE-5));
	}
	else if (!gameObject.getFull())
	{
		gameObject.setFull(true);
		m_sprite.setPosition(gameObject.getLocation().x , gameObject.getLocation().y+(IMAGE_SIZE - 50));
	}
}
void EnemyAbstract::handleCollision(Player& ){}//ignore
void EnemyAbstract::handleCollision(EnemyAbstract& ) {}//ignore
void EnemyAbstract::handleCollision(Coin& ) {}//ignore
void EnemyAbstract::handleCollision(Gift& ) {}//ignore