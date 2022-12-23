#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enums.h"
#include <vector>

using std::vector;
//signleton load image and sound once
class ImageAndAudio {
public:
	~ImageAndAudio() {};
	static ImageAndAudio& instance();
	//void show() const;

	sf::Texture* getPic(int picName);
	sf::Texture* getPicMenu(int picName);
	sf::Texture* getPicLevels(int picName);
	sf::Font *getFont();
	void playSound(Sound sound);
private:
	ImageAndAudio();
	ImageAndAudio(const ImageAndAudio&) = default;
	ImageAndAudio& operator=(const ImageAndAudio&) = default;
	void loadPictures();
	void loadPicturesForMenu();
	void loadAudio();
	vector <sf::Texture> m_image;//vector of image
	vector <sf::Texture> m_imageForMenu;//vector of image menu
	vector <sf::Texture> m_imageLevel;//vector of image levels
	sf::Font m_font;
	vector <sf::Sound> m_sound;
	vector <sf::SoundBuffer> m_soundBuffer;
};
