#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Level.h"

using std::vector;
using std::ifstream;
using std::string;
using std::fstream;

/*
this class is the file of the level in the game
*/
class HanldleFile
{
	//public function

public:
	HanldleFile();//constractor
	void closeFileOfLevels();
	void loadFromFile();
	vector<Level> getLevels() const;
	void setLevelPass(int level);
	
	//private members and function
private:
	vector<Level> m_levels;
	fstream m_fileOfLevels;//file to read level
};


