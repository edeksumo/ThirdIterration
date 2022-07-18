#include "FVX.h"
//****************************************************
//Externals
//****************************************************
extern sf::Texture entitiesTexture;
//****************************************************
//Setting texture and drawing object 
//****************************************************
void FVX::setTexture() {
	sprite.setTexture(entitiesTexture);
}

void FVX::drawFVX(sf::RenderWindow& window) {
	window.draw(sprite);
}
//****************************************************
//Animatin of VFX
//****************************************************
void FVX::animation() {
	sprite.setTextureRect(sf::IntRect(getSize().x * getCurrentFrame(), getStartPosY(), getSize().x, getSize().y));
	if (getFrameCooldown() == 0) {
		setCurrentFrame(getCurrentFrame() + 1);
		setFrameCooldown(2);

		if (getCurrentFrame() == getMaxFrame()) {
			setCurrentCycle(getCurrentCycle() + 1);
			if (getCurrentCycle() == getCycles()) {
				setCanBeKilled(true);
				return;
			}
			setCurrentFrame(0);
		}
	}
}
//****************************************************
//Keep particle with parent 
//****************************************************
void FVX::moveWithParent() {
	if (getHasParent() == true) {
		sprite.setPosition(parent.getPosition());
		std::cout << parent.getPosition().x;
	}
}
//****************************************************
//Getters and setters
//****************************************************
sf::Sprite FVX::getSprite() {
	return sprite;
}

void FVX::setSize(sf::Vector2f val) {
	size = val;
}

sf::Vector2f FVX::getSize() {
	return size;
}

void FVX::setOffset(sf::Vector2f val) {
	offset = val;
}

sf::Vector2f FVX::getOffset() {
	return offset;
}

int FVX::getCycles() {
	return cycles;
}

void FVX::setCycles(int val) {
	cycles = val;
}

void FVX::setRotation(int angle) {
	sprite.setRotation(angle);
}

void FVX::setPosition(sf::Vector2f val) {
	sprite.setPosition(val);
}

void FVX::setPosition(sf::Sprite _sprite) {
	sprite.setPosition(_sprite.getPosition());
}

void FVX::setPositionOffset(sf::Vector2f val) {
	sprite.setPosition(val + offset);
}

sf::Sprite FVX::getParent() {
	return parent;
}

void FVX::setParent(sf::Sprite _sprite) {
	parent = _sprite;
}

void FVX::setCanBeKilled(bool val) {
	canBeKilled = val;
}

bool FVX::getCanBeKilled() {
	return canBeKilled;
}

int FVX::getCurrentCycle() {
	return currentCycle;
}

void FVX::setCurrentCycle(int val) {
	currentCycle = val;
}

void FVX::setCurrentFrame(int val) {
	currentFrame = val;
}

int FVX::getCurrentFrame() {
	return currentFrame;
}

int FVX::getMaxFrame() {
	return maxFrame;
}

void FVX::setMaxFrame(int val) {
	maxFrame = val;
}

void FVX::setStartPosY(int val) {
	startPosY = val;
}

int FVX::getStartPosY() {
	return startPosY;
}

int FVX::getFrameCooldown() {
	return frameCooldown;
}

void FVX::setFrameCooldown(int val) {
	frameCooldown = val;
}

bool FVX::getHasParent() {
	return hasParent;
}

void FVX::setHasParent(bool val) {
	hasParent = val;
}
//****************************************************
//Frame fixed timer
//****************************************************
void FVX::frameCooldowTimer() {
	if (getFrameCooldown() > 0)
		frameCooldown--;
}
//****************************************************
//Update function
//****************************************************
void FVX::update(sf::RenderWindow& window) {
	frameCooldowTimer();
	moveWithParent();
	animation();
	drawFVX(window);
}