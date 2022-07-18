#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "FVX.h"
#include <iostream>
#include <math.h>
#include <time.h>
#pragma once
class Enemy
{
public:
	//public enum for defining type of enemy 
	enum class enemyType {
		Tower, //static, rotating, shoting enemy
		Ship,  //flying , shoting enemy 
		Bomb   //circling enemy
	};
private:
	//private variables
	FVX fvx;
	sf::Vector2f pos;
	sf::Sprite sprite;
	bool _isColiding;
	bool isOnTheView(sf::View view);
	void setType(enemyType type);
	void setType(int type);
	enemyType type;
	void playerTracing(Player player);
	void moving(sf::Vector2f velocity);
	void moving();
	sf::Texture texture;
	float speed;
	sf::Sound shootSound;
	int _shotCooldown;
	bool setTexture(sf::Texture& _texture);
	float currentTg;
	int _shotCooldownTimer(int a);
	void shooting(Player player);
	void shooting(sf::Vector2f _pos);
	bool destroy;
	void setSound();
	int currentFrame;
	int frameCooldown;
	void setFrameCooldown(int val);
	int getFrameCooldown();
	int getCurrentFrame();
	void animation();
	void frameCooldownTimer();
	void setUpFVX();
	bool FVXSetUp;
	void FVXUpdate(sf::RenderWindow &window);

public:
	//construktor
	Enemy() {
		pos = sf::Vector2f(0, 0);
		_isColiding = false;
		type = enemyType::Tower;
		enemiesInit = false;
		_shotCooldown = 100;
		destroy = false;
		currentTg = 0;
		speed = 2;
		currentFrame = 0;
		frameCooldown = 0;
		FVXSetUp = false;
	}
	
	Enemy(sf::Vector2f _pos, bool __isColiding, enemyType _type, bool _init, int __shootCooldown, float _currentTg, bool _destroy, float _speed, int _currentFrame, int _frameCooldown, bool _FVXSetUp) :
		pos(_pos), _isColiding(__isColiding), type(_type), enemiesInit(_init), _shotCooldown(__shootCooldown), currentTg(_currentTg), destroy(_destroy), speed(_speed), currentFrame(_currentFrame), frameCooldown(_frameCooldown), FVXSetUp(_FVXSetUp) {}
	
	//public funtions
	bool enemiesInit;

	std::vector <Enemy> enemyVec;

	std::vector <Bullet> bulletVec;

	void updateBullets(sf::RenderWindow& window);

	void drawEnemy(sf::RenderWindow& window);

	void setPosition(sf::Vector2f pos);

	sf::Vector2f GetPosition();

	enemyType getType();

	sf::Sprite getSprite();

	bool isColiding(sf::Sprite _sprite);

	bool isColiding(sf::Sprite _sprite, bool isPlayer);

	bool collision();

	void setShotCooldownTimer(int a, int min, int max);

	void setDestroy(bool value);

	bool getDestroy();

	int getShotCooldownTimer();

	void createEnemies(int x, int y, int _type, sf::RenderWindow &window, sf::Texture &texture);

	void update(sf::RenderWindow &window, Player player);
};

