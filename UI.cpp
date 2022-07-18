#include "UI.h"
//****************************************************
//Externals
//****************************************************
extern sf::Texture UITexture;
//****************************************************
//Initial texture and sprites set up
//****************************************************
void UI::setTexture() {

	if (!font.loadFromFile("assets/kenvector_future_thin.ttf"))
	{
		return;
	}

	//setting up points counter
	pointsCounter.setFont(font);
	pointsCounter.setCharacterSize(25);
	pointsCounter.setPosition(sf::Vector2f(730, 628));

	//setting up points TEXT
	points.setFont(font);
	points.setCharacterSize(25);
	points.setPosition(sf::Vector2f(700, 590));
	points.setString("POINTS: ");

	//setting up background
	UIBackground.setTexture(UITexture);
	UIBackground.setTextureRect(sf::IntRect(0, 0, 1280, 150));
	UIBackground.setPosition(sf::Vector2f(-1, 570));

	//setting up lives 
	for (int i = 0; i < (sizeof(lives) / sizeof(lives[0])); i++) {
		lives[i].setTexture(UITexture);
		lives[i].setTextureRect(sf::IntRect(120, 150, 40, 40));
		lives[i].setPosition(sf::Vector2f(30, 581 + (43 * i)));
	}

	//setting up power ups
	for (int i = 0; i < (sizeof(powerUps) / sizeof(powerUps[0])); i++) {
		powerUps[i].setTexture(UITexture);
		powerUps[i].setTextureRect(sf::IntRect(40 * i, 150, 40, 40));
		powerUps[i].setPosition(sf::Vector2f(90, 581 + (i * 44)));
	}

	//seting up reload bar
	reloadBar.setTexture(UITexture);
	reloadBar.setTextureRect(sf::IntRect(160, 150, 151, 19));
	reloadBar.setPosition(sf::Vector2f(160, 637));
}
//****************************************************
//Function to keep UI elements on screen
//****************************************************
void UI::keepOnScreen(sf::RenderWindow& window) {

	// background
	UIBackground.setPosition(window.getView().getCenter().x - (window.getView().getSize().x / 2) + 1, (window.getView().getCenter().y + (window.getView().getSize().y / 2) - 150));
	// power ups icons
	for (int i = 0; i < (sizeof(powerUps) / sizeof(powerUps[0])); i++) {
		powerUps[i].setPosition(window.getView().getCenter().x - (window.getView().getSize().x / 2) + 92, (window.getView().getCenter().y + (window.getView().getSize().y / 2) - (139 - (i * 44))));
	}
	// lives display
	for (int i = 0; i < (sizeof(lives) / sizeof(lives[0])); i++) {
		lives[i].setPosition(window.getView().getCenter().x - (window.getView().getSize().x / 2) + 31, (window.getView().getCenter().y + (window.getView().getSize().y / 2) - (138 - (i * 44))));
	}
	// bar display
	reloadBar.setPosition(window.getView().getCenter().x - (window.getView().getSize().x / 2) + 160, (window.getView().getCenter().y + (window.getView().getSize().y / 2) - 84));
	// points display
	pointsCounter.setPosition(window.getView().getCenter().x - (window.getView().getSize().x / 2) + 731, (window.getView().getCenter().y + (window.getView().getSize().y / 2) - 92));
	// points text display
	points.setPosition(window.getView().getCenter().x - (window.getView().getSize().x / 2) + 701, (window.getView().getCenter().y + (window.getView().getSize().y / 2) - 130));
}
//****************************************************
//Setting realod bar scale
//****************************************************
void UI::setBarScale(Player& player) {
	double a = player.getShotCooldownTimer();
	double b = player.shootCooldown();
	double c = a / b;

	if (c > 1)
		c = 1;
	reloadBar.setScale(sf::Vector2f(c, 1));
}
//****************************************************
//Draw functions
//****************************************************
void UI::drawUI(sf::RenderWindow& window) {
	window.draw(UIBackground);
}

void UI::drawPowerUps(Player &player, sf::RenderWindow &window) {
	if (player.checkPowerUp(PowerUp::Type::MultiShot)) {
		window.draw(powerUps[0]);
	}
	if (player.checkPowerUp(PowerUp::Type::Shield)) {
		window.draw(powerUps[1]);
	}
	if (player.checkPowerUp(PowerUp::Type::FastShot)) {
		window.draw(powerUps[2]);
	}
}

void UI::drawLives(sf::RenderWindow &window, Player &player) {
	for (int i = 0; i < player.getLives(); i++) {
		window.draw(lives[i]);
	}
}

void UI::drawReloadBar(sf::RenderWindow& window, Player& player) {
	setBarScale(player);
	window.draw(reloadBar);
}

void UI::drawTexts(sf::RenderWindow& window, Player& player) {
	std::string a = std::to_string(player.getPoints());
	pointsCounter.setString(a);
	window.draw(pointsCounter);
	window.draw(points);
}
//****************************************************
//Update Function
//****************************************************
void UI::update(sf::RenderWindow& window, Player &player) {
	drawUI(window);
	drawPowerUps(player, window);
	drawLives(window, player);
	drawReloadBar(window, player);
	drawTexts(window, player);
	keepOnScreen(window);
}