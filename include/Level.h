#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ObjectAbstract.h"
using std::string;
using std::vector;

//this class is level in the game 
class Level
{
public:
	Level(const int hight ,const int width, const int time, const vector<string> objectOfLevel);//constructor

	int getWidth() const ;//get width of level
	int getHight()const;//get hight of level
	int getTimeOfLevel()const;//get time of level
	bool getLevelComplete() const;//get if level complete
	void setLevelComplete(bool complete);//set if level complite
	vector <string> getCharLevel()const;//get the vector char of level


private:
	int m_width;//width of level
	int m_hight;//hight of level
	int m_time;// time of level
	vector<string> m_objectOfLevel;//char of level
	bool m_levelComplete;//if level pass
};



