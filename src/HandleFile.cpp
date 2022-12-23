#include<iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "HanldleFile.h"
#include "Level.h"

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
/*
this class we create the board of the game for each level
save the file to read the levels.
members description in the board header file.
*/

//in the oo1_ex05 folder.
const string NAME_OF_FILE = "..\\..\\..\\Board.txt";// board.txt location in main folder

//constractor
HanldleFile::HanldleFile()
{
	m_fileOfLevels.open(NAME_OF_FILE);
	if (m_fileOfLevels.fail())//no sucsses open file
	{
		closeFileOfLevels();
	}
	else
	{
		loadFromFile();//load all level by char to vector of levels
	}
}

//this function update all the locations of the player enemy and coins
void HanldleFile::loadFromFile()
{
	int lenght = 0;
	int width = 0;
	int time = 0;
	char symbol = ' ';

	vector <string> levelChars;
	string line;

 	while (!m_fileOfLevels.eof())
	{
		m_fileOfLevels >> lenght;//leanth of level
		m_fileOfLevels >> width;//width of level
		m_fileOfLevels >> time;//time of level
		//take the enter char.

		 m_fileOfLevels.get(symbol);
		while (symbol != '\n')
		{
			m_fileOfLevels.get(symbol);
		}

		//go over the map and update with get line
		for (int i = 0; i < lenght; i++)
		{
			getline(m_fileOfLevels, line);
			levelChars.push_back(line);
		}
		getline(m_fileOfLevels, line);
		Level level(lenght, width, time, levelChars);
		levelChars.clear();
		m_levels.push_back(level);
	}
	getline(m_fileOfLevels, line);
}
vector<Level> HanldleFile::getLevels() const
{
	return m_levels;//return the levels
}

void HanldleFile::setLevelPass(int level)
{
	m_levels[level].setLevelComplete(true);//mark if pass level
}

//close file in the end of the game
void HanldleFile::closeFileOfLevels()
{
	m_fileOfLevels.close();
}