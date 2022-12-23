#pragma once
//this enum for the image option
enum PicNameMenu {
	BACKGROUND_MENU = 0, PLAY = 1, SELECT_LEVEL = 2, EXIT_GAME = 3, HELP = 4, INST_BACKGROUND= 5,BOY_MENU = 6, GIRL_MENU = 7
};

enum PicNameGame {
	BACKGROUND_GAME = 0, WALL = 1, PLAYER_BOY = 2, PLAYER_GIRL = 3 ,ENEMY_RANDOM = 4 , ENEMY_BACK_FORTH = 5, ENEMY_SMART = 6,  COIN = 7 ,
	LADDER = 8 , POLE = 9 , GIFT = 10  ,HEART = 11 , HOLE = 12, WIN_BACK = 13, SPACE = 14 
};

enum ButtonMenu {
	 EXIT_GAME_PRESS = -1 , SELECT_LEVEL_PRESS = 0 , PLAY_PRESS = 1 , HELP_PRESS = 2 , BOY = 3, GIRL = 4
};


enum typeOfEnemy {
	randomEnemy = 0,
	backForthEnemy = 1,
	smartEnemy = 2
};
enum class SideToMove {
	NO_MOVE = 0,
	RIGHT = 1,
	LEFT = 2,
	UP = 3,
	DOWN = 4
};

enum class Sound
{
	GAME_MUSIC = 0,
	COIN = 1,
	GIFT = 2,
	ENEMY = 3, 
	WALL = 4,
	NEXT_LEVEL = 5,
	LOSE = 6,
	WIN = 7
};

enum class GiftGet
{
	ADD_LIFE = 0,
	ADD_TIME = 1,
	ADD_SCORE = 2,
	ADD_ENEMY = 3,
};


enum class PlayerType
{
	BOY = 0,
	GIRL = 1,

};