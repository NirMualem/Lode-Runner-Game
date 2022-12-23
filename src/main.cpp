#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "HanldleFile.h"
#include "Controller.h"
#include "ImageAndAudio.h"

int main()
{
	srand((unsigned int)time(NULL));//for random the count to move.
	Controller con;
	con.runGame();//run the game
	return EXIT_SUCCESS;
}