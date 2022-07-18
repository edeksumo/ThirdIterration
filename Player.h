#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "Bullet.h"
#include "FVX.h"
#include "PowerUp.h"
#pragma once
class Player
{
	//private variables
	sf::Vector2f pos;
	std::string textureName;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Sprite shieldSprite;
	int iFramesTimer;
	bool _setTexture();
	int _iFramesCounter(int a);
	int _shotCooldownTimer(int a);
	bool _isColiding;
	bool _isColidingWTile;
	int _lives;
	int _shotCooldown;
	void eraseBullets();
	bool lastPressedUp;
	bool lastPressedDown;
	bool lastPressedLeft;
	bool lastPressedRight;
	bool exploded;
	sf::Sound shootSound;
	int frameCooldown;
	int currentFrame;
	void frameCooldownTimer();
	void animation();
	void frameReseter();
	bool powerUpShield;
	bool powerUpMultiShoot;
	bool powerUpFastShoot;
	unsigned int points;


public:
	//constructor
	Player() {
		pos = sf::Vector2f(0, 0);
		textureName = "player.png";
		iFramesTimer = 0;
		_isColiding = false;
		_isColidingWTile = false;
		_lives = 3;
		_shotCooldown = 50;
		points = 0;
		lastPressedUp = false;
		lastPressedDown = false;
		lastPressedLeft = false;
		lastPressedRight = false;
		frameCooldown = 0;
		currentFrame = 0;
		exploded = false;
		powerUpFastShoot = false;
		powerUpMultiShoot = false;
		powerUpShield = false;
	}

	Player(sf::Vector2f _pos, std::string _textureName, int _iFramesTimer, bool __isColiding, bool __isColidingWTile, int __lives, int __shotCooldown, bool _lastPressedDown, bool _lastPressedUp, bool _lastPressedLeft, bool _lastPressedRight, int _frameCooldown, int _currentFrame, bool _exploded, bool _powerUpShield, bool _powerUpMultiShoot, bool _powerUpFastShoot, unsigned int _points) :
						pos(_pos), textureName(_textureName), iFramesTimer(_iFramesTimer), _isColiding(__isColiding), _isColidingWTile(__isColidingWTile), _lives(__lives), _shotCooldown(__shotCooldown), lastPressedDown(_lastPressedDown), lastPressedUp(_lastPressedUp), lastPressedLeft(_lastPressedLeft), lastPressedRight(_lastPressedRight), frameCooldown(_frameCooldown), currentFrame(_currentFrame), exploded(_exploded), powerUpFastShoot(_powerUpFastShoot), powerUpMultiShoot(_powerUpMultiShoot), powerUpShield(_powerUpShield), points(_points){}
	
	//public functions
	std::vector <Bullet> bulletVec; //storing bullets

	int getFrameCooldown();

	void setFrameCooldown(int val);

	int getCurrentFrame();

	void setSound();

	void drawPlayer(sf::RenderWindow& window);
	
	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	sf::Sprite getSprite();
	
	void PlayerMoving(int offset_x_min, int offset_x_max, int offset_y, sf::View view, float speed_x, float speed_y, float cameraSpeed, sf::Clock clock);

	void PlayerShotting(sf::RenderWindow &window);
	
	bool isColiding(sf::Sprite _sprite);

	bool isColiding(Tile &_Tile, sf::View _view);

	bool isColiding(sf::Sprite _sprite, bool isEnemy, sf::View _view);
	
	bool isAlive();

	void setLives(int lives);

	int getLives();

	void setIFramesTimer(int a);

	int getIFramesTimer();

	void setShotCooldownTimer(int a);

	int getShotCooldownTimer();

	bool checkPowerUp(PowerUp::Type type);

	void addPowerUp(PowerUp::Type type);

	void removePowerUp(PowerUp::Type type);

	int shootCooldown();

	void addPoints(unsigned int val);

	unsigned int getPoints();

	void updateBullets(sf::RenderWindow &window);

	void update();
};


