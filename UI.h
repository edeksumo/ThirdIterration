#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "PowerUp.h"
#pragma once

class UI
{
	// variables
	sf::Sprite UIBackground;
	sf::Sprite powerUps[3];
	sf::Sprite lives[3];
	sf::Sprite reloadBar;
	sf::Font font;
	sf::Text pointsCounter;
	sf::Text points;
	// functions
	void setBarScale(Player& player);
	void drawUI(sf::RenderWindow& window);
	void drawPowerUps(Player &player, sf::RenderWindow &window);
	void keepOnScreen(sf::RenderWindow &window);
	void drawLives(sf::RenderWindow &window, Player &player);
	void drawReloadBar(sf::RenderWindow& window, Player& player);
	void drawTexts(sf::RenderWindow& window, Player& player);
public:
	//functions
	void setTexture();
	void update(sf::RenderWindow &window, Player &player);
};

