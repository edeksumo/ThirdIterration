#include<SFML/Graphics.hpp>
#include <iostream>
#pragma once
class FVX
{
	//private variables
	int cycles;
	int currentCycle;
	sf::Vector2f offset;
	sf::Vector2f size;
	sf::Sprite sprite;
	int currentFrame;
	int maxFrame;
	int startPosY;
	int frameCooldown;
	bool hasParent;
	sf::Sprite parent;
	void drawFVX(sf::RenderWindow& window);
	void animation();
	void moveWithParent();
	bool canBeKilled;
public:
	//constructor
	FVX() {
		size = sf::Vector2f(64, 64);
		cycles = 1;
		currentCycle = 0;
		currentFrame = 0;
		maxFrame = 10;
		startPosY = 250;
		frameCooldown = 0;
		hasParent = false;
		canBeKilled = false;
	}
	FVX(sf::Vector2f _size, int _cycles, int _currentCycle, int _currentFrame, int _maxFrame, int _startPosY, int _frameCooldown, bool _hasParent, bool _canBeKilled) :
			size(_size), cycles(_cycles), currentCycle(_currentCycle), currentFrame(_currentFrame), maxFrame(_maxFrame), startPosY(_startPosY), frameCooldown(_frameCooldown), hasParent(_hasParent), canBeKilled(_canBeKilled){}
	
	//public functions
	void setTexture();
	
	void setSize(sf::Vector2f val);

	sf::Vector2f getSize();

	void setOffset(sf::Vector2f val);

	sf::Vector2f getOffset();

	sf::Sprite getSprite();

	int getCycles();

	void setCycles(int val);

	void setRotation(int angle);

	void setPosition(sf::Vector2f val);

	void setPositionOffset(sf::Vector2f val);

	void setPosition(sf::Sprite _sprite);

	void setParent(sf::Sprite _sprite);

	sf::Sprite getParent();

	void setCanBeKilled(bool val);

	bool getCanBeKilled();

	int getCurrentCycle();

	void setCurrentCycle(int val);

	int getCurrentFrame();

	void setCurrentFrame(int val);

	int getMaxFrame();

	void setMaxFrame(int val);

	void setStartPosY(int val);

	int getStartPosY();

	int getFrameCooldown();

	void setFrameCooldown(int val);

	void frameCooldowTimer();

	bool getHasParent();

	void setHasParent(bool val);

	void update(sf::RenderWindow& window);
};

