#include "PowerUp.h"
//****************************************************
//Externals
//****************************************************
extern sf::Texture entitiesTexture;
extern sf::Sound powerUpSound;
//****************************************************
//Setting up texture for power up obj
//****************************************************
void PowerUp::setTexture() {
	sprite.setTexture(entitiesTexture);
	
	switch (getType())
	{
	case Type::Shield:
		sprite.setTextureRect(sf::IntRect(672, 32, 32, 32));
		break;
	case Type::FastShot:
		sprite.setTextureRect(sf::IntRect(672, 64, 32, 32));
		break;
	case Type::MultiShot:
		sprite.setTextureRect(sf::IntRect(672, 0, 32, 32));
		break;
	}
	sprite.setOrigin((float)sprite.getTextureRect().width / 2, (float)sprite.getTextureRect().height / 2);
	sprite.setColor(sf::Color(255, 150, 150 , alpha));
}
//****************************************************
//getting current alpha
//****************************************************
int PowerUp::getAlpha() {
	return alpha;
}
//****************************************************
//setting alpha
//****************************************************
void PowerUp::setAlpha(int val) {
	alpha = alpha + val;
}
//****************************************************
//Draw function
//****************************************************
void PowerUp::drawPowerUp(sf::RenderWindow& window) {
	window.draw(sprite);
}
//****************************************************
//Checker that obj is visible 
//****************************************************
bool PowerUp::isOnTheView(sf::View view) {
	if ((view.getCenter().x - (view.getSize().x / 2) < sprite.getPosition().x + 50) && (view.getCenter().x + (view.getSize().x / 2) > sprite.getPosition().x)) {
		return true;
	}
	return false;
}
//****************************************************
//Timer for animation frames
//****************************************************
void PowerUp::frameTimer() {
	setCurrentFrame(getCurrentFrame() + 1);
	if (getCurrentFrame() < 0)
		setAlpha(1);
	//go back to begining
	if (getCurrentFrame() >= 50)
		setCurrentFrame(0);
}
//****************************************************
//Animations 
//****************************************************
void PowerUp::animation() {
	
	sprite.setColor(sf::Color(255, 150, 150, (alpha * 2) ));

	if (getCurrentFrame() == 0)
		powerUpSound.play();
	
	if ((getCurrentFrame() > 0) && (getCurrentFrame() < 10)) {
		sprite.setScale(sprite.getScale() + sf::Vector2f(0.02,0.02));
	}
	if ((getCurrentFrame() > 20) && (getCurrentFrame() < 30)) {
		sprite.setScale(sprite.getScale() + sf::Vector2f(0.02, 0.02));
	}
	if ((getCurrentFrame() > 30) && (getCurrentFrame() < 50)) {
		sprite.setScale(sprite.getScale() - sf::Vector2f(0.02, 0.02));
	}
}
//****************************************************
//getters and setters 
//****************************************************
sf::Sprite PowerUp::getSprite() {
	return sprite;
}

void PowerUp::setType(Type _type) {
	type = _type;
}

PowerUp::Type PowerUp::getType() {
	return type;
}

void PowerUp::setCurrentFrame(int val) {
	currentFrame = val;
}

int PowerUp::getCurrentFrame() {
	return currentFrame;
}

void PowerUp::setPosition(sf::Vector2f val) {
	sprite.setPosition(val);
}
//****************************************************
//Collision functions
//****************************************************
bool PowerUp::isColliding(sf::Sprite _sprite) {

	if (sprite.getGlobalBounds().intersects(_sprite.getGlobalBounds())) {
		_isColliding = true;
		return true;
	}

	return false;
}

bool PowerUp::collision() {
	if (_isColliding) {
		return true;
	}

	return false;
}
//****************************************************
//update functions
//****************************************************
void PowerUp::update(sf::RenderWindow& window) {
	if (!isOnTheView(window.getView())) {
		return;
	}
	frameTimer();
	animation();
	drawPowerUp(window);
	//reseting collision 
	_isColliding = false;
}