#include <SFML/Graphics.hpp>
#include "Level.h"
#include "ObjectAbstract.h"

Level::Level(const int hight, const int width, const int time,  const vector<string> objectOfLevel)
	: m_hight(hight), m_width(width), m_objectOfLevel(objectOfLevel), m_time(time)
{
	m_levelComplete = false;//start level as no complete
}
int Level::getWidth()const
{
	return m_width;
}
int Level::getTimeOfLevel()const
{
	return m_time;
}

int Level::getHight()const
{
	return m_hight;
}

vector <string> Level::getCharLevel()const
{
	return m_objectOfLevel;
}
bool Level::getLevelComplete() const
{
	return m_levelComplete;
}
void Level::setLevelComplete(bool complete)
{
	m_levelComplete = complete;
}
