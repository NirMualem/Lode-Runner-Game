#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "ObjectAbstract.h"
#include "StaticObject.h"
#include <memory.h>

//this class is absract of move object in the game
using std::vector;
using std::unique_ptr;
class MoveObjectAbstract : public ObjectAbstract
{
public:
	MoveObjectAbstract(const sf::Vector2f loc, const sf::Texture& texture, const char& symbol, float moveSpeed);//constractor
	~MoveObjectAbstract() = default;
	float getspeed() const;//get speed of object
	void checkVaild(const vector <unique_ptr<StaticObject>>& m_staticObect, const float deltaTime);//check if the next place vaild
	SideToMove getSide() const;//get side of the move object
	sf::Vector2f getLastLoc()const;//get the last location
	void setLastLoc(sf::Vector2f last);//set the last location
	void setPosition(sf::Vector2f last);//set position of the sprite
	void changeSideSprite(SideToMove side);//change the side of the sprite
	StaticObject* foundObjectInLocation(const vector<unique_ptr<StaticObject>>& m_staticObect,
		const sf::Vector2f& nextlocation);//found the object in the next location
protected:
	float m_moveSpeed;//move speed of the object
	SideToMove m_side;//side of the object
	sf::Vector2f m_lastLoc;//the last location of the object
	sf::Vector2f m_directionLoc;//side of the sprite

	void updateBySide(const SideToMove side, const float deltaTime);//update the location according to the time and side
	void fall(const vector<unique_ptr<StaticObject>>& m_staticObect);//fall down until object
	void handleHalf(const vector<unique_ptr<StaticObject>>& m_staticObect, sf::Vector2f loc,
		SideToMove side);//handle with situation that the move object on half of object

};