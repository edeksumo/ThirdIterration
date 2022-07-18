#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#pragma once
class PowerUp
{
public:
	//public enum
	enum class Type {
		Shield,
		MultiShot,
		FastShot
	};
private:
	//private variables
	sf::Sprite sprite;
	Type type;
	int currentFrame;
	bool _isColliding;
	int alpha;

	//private functions
	int getAlpha();
	void setAlpha(int val);
	void drawPowerUp(sf::RenderWindow& window);
	void animation();
	void frameTimer();

public:
	//constructor
	PowerUp() {
		type = Type::FastShot;
		currentFrame = -75;
		_isColliding = false;
		alpha = 0;
	}
	PowerUp(Type _type, int _currentFrame, bool __isColliding, int _alpha) :
		type(_type), currentFrame(_currentFrame), _isColliding(__isColliding), alpha(_alpha) {};

	//public functions
	sf::Sprite getSprite();

	void setTexture();

	void setPosition(sf::Vector2f val);

	bool isColliding(sf::Sprite _sprite);

	bool collision();

	void update(sf::RenderWindow& window);

	void setType(Type _type);

	Type getType();

	void setCurrentFrame(int val);

	bool isOnTheView(sf::View view);

	int getCurrentFrame();
};

