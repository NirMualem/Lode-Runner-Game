#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Enums.h"
#include "ImageAndAudio.h"
#include <vector>

using std::vector;

ImageAndAudio::ImageAndAudio()
{
	loadPictures();
	loadPicturesForMenu();
	m_font.loadFromFile("font.TTF");
	loadAudio();
}

ImageAndAudio& ImageAndAudio::instance() {
	static ImageAndAudio inst;
	return inst;
}

//this function load the picture once to use in other places.
void ImageAndAudio::loadPictures() 
{
	sf::Texture texture;
	m_image.clear();

	texture.loadFromFile("backgroundGame.png");
	m_image.push_back(texture);

	texture.loadFromFile("wallImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("playerImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("playerImage1.png");
	m_image.push_back(texture);

	texture.loadFromFile("randomEnemy.png");
	m_image.push_back(texture);

	texture.loadFromFile("enemyImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("enemySmart.png");
	m_image.push_back(texture);

	texture.loadFromFile("coinImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("ladderImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("poleImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("giftImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("heartImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("HoleImage.png");
	m_image.push_back(texture);

	texture.loadFromFile("winBack.png");
	m_image.push_back(texture);

}
void ImageAndAudio::loadPicturesForMenu()
{
	sf::Texture texture;
	m_imageForMenu.clear();

	texture.loadFromFile("backgroundMenu.png");
	m_imageForMenu.push_back(texture);

	texture.loadFromFile("play.png");
	m_imageForMenu.push_back(texture);

	texture.loadFromFile("selectLevel.png");
	m_imageForMenu.push_back(texture);

	texture.loadFromFile("exit.png");
	m_imageForMenu.push_back(texture);

	texture.loadFromFile("helpImage.png");
	m_imageForMenu.push_back(texture);

	texture.loadFromFile("InstImage.png");
	m_imageForMenu.push_back(texture);

	texture.loadFromFile("boyImage.png");
	m_imageForMenu.push_back(texture);

	texture.loadFromFile("girlmage.png");
	m_imageForMenu.push_back(texture);

	texture.loadFromFile("lock.png");
	m_imageLevel.push_back(texture);

	texture.loadFromFile("1.png");
	m_imageLevel.push_back(texture);

	texture.loadFromFile("2.png");
	m_imageLevel.push_back(texture);

	texture.loadFromFile("3.png");
	m_imageLevel.push_back(texture);

	texture.loadFromFile("4.png");
	m_imageLevel.push_back(texture);

	texture.loadFromFile("5.png");
	m_imageLevel.push_back(texture);

	texture.loadFromFile("6.png");
	m_imageLevel.push_back(texture);

	texture.loadFromFile("back.png");
	m_imageLevel.push_back(texture);

}
sf::Texture* ImageAndAudio::getPic(int picName) 
{
	return &m_image[picName];
}
sf::Texture* ImageAndAudio::getPicMenu(int picName)
{
	return &m_imageForMenu[picName];
}
sf::Texture* ImageAndAudio::getPicLevels(int picName)
{
	return &m_imageLevel[picName];
}
sf::Font* ImageAndAudio::getFont()
{
	return &m_font;
}

void ImageAndAudio::loadAudio()
{
	
	//GAME MUSIC
	sf::SoundBuffer gameMusic;
	if (!gameMusic.loadFromFile("resources/gameMusic.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	
	sf::Sound gameSound(gameMusic);
	gameSound.setLoop(true);
	gameSound.setVolume(80);
	m_sound.push_back(sf::Sound(gameSound));

	//COIN
	if (!gameMusic.loadFromFile("resources/moneySound.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	m_sound.push_back(sf::Sound(gameMusic));

	//GIFT
	if (!gameMusic.loadFromFile("resources/giftSound.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	m_sound.push_back(sf::Sound(gameMusic));

	//ENEMY
	if (!gameMusic.loadFromFile("resources/downLifeSound.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	m_sound.push_back(sf::Sound(gameMusic));

	//WALL
	if (!gameMusic.loadFromFile("resources/giftSound.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	m_sound.push_back(sf::Sound(gameMusic));
	
	//NEXT LEVEL
	if (!gameMusic.loadFromFile("resources/levelPassSound.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	m_sound.push_back(sf::Sound(gameMusic));

	//LOSE
	if (!gameMusic.loadFromFile("resources/loseGameSound.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	m_sound.push_back(sf::Sound(gameMusic));

	//WIN
	if (!gameMusic.loadFromFile("resources/loseGameSound.wav"))
	{
		return;
	}
	m_soundBuffer.push_back(gameMusic);
	m_sound.push_back(sf::Sound(gameMusic));

}

void ImageAndAudio::playSound(Sound sound)
{
	m_sound[int(sound)].setBuffer(m_soundBuffer[int(sound)]);
	m_sound[int(sound)].play();
}