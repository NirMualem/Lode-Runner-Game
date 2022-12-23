#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ButtonLevel.h"
#include "Enums.h"
using std::vector;

class Menu
{
public:
    // run();

    Menu();
    void openMenu();

    void updateButtonLevel(int level);
    int getSelectLevel() const;
    PlayerType getType() const;
    void setType(PlayerType type);

private:
    //members
    sf::RenderWindow m_window;
    sf::Sprite m_backgroundSprite;
    vector<Button> m_button;//vector of button
    vector<ButtonLevel> m_buttonLevel;//vector of button
    PlayerType m_typePlayer;
    int m_buttonSelect; 
    int m_numOfLevel; 
    

    void handleMouseMove(float x, float y);
    void drawMenu();
    void createAllButton();
    void openInst();
    int  drawSelectLevelWin();
    void handleClick(const sf::Vector2f& location);
    void handleClickLevelsWin(const sf::Vector2f& location);

};

