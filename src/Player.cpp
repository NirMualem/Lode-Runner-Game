#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EnemyAbstract.h"
#include "StaticObject.h"
#include "Enums.h"
#include "ConstForGame.h"
#include <memory.h>
#include "Controller.h"
#include "MoveObjectAbstract.h"
#include "Wall.h"
#include "Coin.h"
#include "ImageAndAudio.h"

using std::vector;
using std::unique_ptr;

//this class if class of the player in the game

Player::Player(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol, float moveSpeed)
	: MoveObjectAbstract(loc, texture, symbol, moveSpeed), m_collectedCoin(0), m_life(START_LIFE)
{
	srand(time(NULL));
}

Player::~Player()
{
}
void Player::updatePlayerLocation(const float deltaTime)
{
	//go right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_directionLoc = sf::Vector2f(1, 0);
		updateBySide(SideToMove::RIGHT, deltaTime);
	}
	//go left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_directionLoc = sf::Vector2f(-1, 0);
		updateBySide(SideToMove::LEFT, deltaTime);
	}
	//go up
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_side = SideToMove::UP;
		m_directionLoc = sf::Vector2f(0, -1);
		updateBySide(SideToMove::UP, deltaTime);
	}
	//go down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_side = SideToMove::DOWN;
		m_directionLoc = sf::Vector2f(0, 1);
		updateBySide(SideToMove::DOWN, deltaTime);
	}
}


int Player::getcollectedCoin() const//get number of coin taken
{
	return m_collectedCoin;
}

int Player::getLife() const//get life
{
	return m_life;
}

void Player::setLife(int currLife)//set life if change 
{
	m_life = currLife;
}

void Player::handleCollision(ObjectAbstract& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

//if collision with enemy lose life
void Player::handleCollision(EnemyAbstract& gameObject)
{
	sf::Sprite checkSprite = gameObject.getsprite();
	checkSprite.setScale(0.8, 0.8);
	if (checkSprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
	{
		ImageAndAudio::instance().playSound(Sound::ENEMY);
		m_life--;
	}
}

//take coin
void Player::handleCollision(Coin& gameObject)
{
	ImageAndAudio::instance().playSound(Sound::COIN);

	m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getLocation().y);
	m_lastLoc.y = gameObject.getLocation().y;
	Controller::addScore(2);
	m_collectedCoin++;
}

//player collistion with hole update the location and the size
void Player::handleCollision(Hole& gameObject)
{
	if (gameObject.checkIfTake())
	{
		m_sprite.setScale(1, 1);
		m_sprite.setPosition(gameObject.getLocation().x, gameObject.getLocation().y - (IMAGE_SIZE - 5));
	}
	else if (!gameObject.getFull())
	{
		m_sprite.setScale(float(0.8), float(0.8));
		m_sprite.setPosition(gameObject.getLocation().x, gameObject.getLocation().y + (IMAGE_SIZE - 50));
	}
}
//player collistion with gift update to taken for erase  
//and random what to do 
void Player::handleCollision(Gift& gameObject)
{
	ImageAndAudio::instance().playSound(Sound::GIFT);

	m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getLocation().y);
	m_lastLoc.y = gameObject.getLocation().y;
	GiftGet gift = static_cast<GiftGet>(rand() % 4);
	if (gift == GiftGet::ADD_LIFE && m_life == MAX_LIFE)
		gift = static_cast<GiftGet>(rand() % 3 + 1);

	if (gift == GiftGet::ADD_TIME && Controller::m_time == 0)
		gift = static_cast<GiftGet>(rand() % 2 + 2);

	switch (gift)
	{
		//add life to the player
	case GiftGet::ADD_LIFE:
		m_life++;
		break;

		//add time 10 seconds
	case GiftGet::ADD_TIME:
		Controller::m_time += 10;
		break;

		//add 20 to the score
	case GiftGet::ADD_SCORE:
		Controller::addScore(20);
		break;

		//add enemy on the board
	case GiftGet::ADD_ENEMY:
		Controller::m_numOfEnemy++;
		break;
	}
}

//handle collision with wall
void Player::handleCollision(Wall& gameObject)
{
	//for check if beween two walls right or left
	if (m_side == SideToMove::RIGHT || m_side == SideToMove::LEFT)
	{
		sf::Sprite checkSprite = m_sprite;
		checkSprite.setScale(1, float(0.8));
		checkSprite.setPosition(checkSprite.getPosition().x, checkSprite.getPosition().y + 1);

		if (checkSprite.getGlobalBounds().intersects(gameObject.getsprite().getGlobalBounds()))
		{
			m_sprite.setPosition(m_lastLoc);
		}
	}
	//for check if beween two walls up or down
	else if (m_side == SideToMove::UP || m_side == SideToMove::DOWN)
	{
		sf::Sprite checkSprite = m_sprite;
		checkSprite.setScale(float(0.8), 1);
		checkSprite.setPosition(checkSprite.getPosition().x, checkSprite.getPosition().y + 1);

		if (checkSprite.getGlobalBounds().intersects(gameObject.getsprite().getGlobalBounds()))
		{
			m_sprite.setPosition(m_lastLoc);
		}
	}
	else
		m_sprite.setPosition(m_lastLoc);
}

void Player::handleCollision(Ladder& ) {}//ignore

void Player::handleCollision(Player& ) {}//ignore

void Player::handleCollision(Pole& ) {}//ignore