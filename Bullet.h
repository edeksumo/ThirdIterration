#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#pragma once
class Bullet
{
	//variables
	sf::Vector2f pos;
	std::string textureName;
	sf::Texture texture;
	sf::Sprite sprite;
	bool _setTexture();
	bool _isColiding;
	sf::Vector2f target;
	float speed;
	float dir_x;
	float dir_y;
	bool directionSet;
	void setDirection();
	void move();
	int iFrames;
	void updateIFrames(int a);

public:
	//constructor
	Bullet() {
		pos = sf::Vector2f(0, 0);
		textureName = "bullet.png";
		_isColiding = false;
		target = sf::Vector2f(1,1);
		speed = 7;
		dir_x = 5;
		dir_y = 0;
		directionSet = false;
		iFrames = 6;
	}
	Bullet(sf::Vector2f _pos, std::string _textureName, bool __isColiding, sf::Vector2f _target, float _speed, float _dir_x, float _dir_y, bool _directionSet, int _iFrames) :
						pos(_pos), textureName(_textureName), _isColiding(__isColiding), target(_target), speed(_speed), dir_x(_dir_x), dir_y(_dir_y), directionSet(_directionSet), iFrames(_iFrames)  {}
	//functions
	void setIFrames(int a);

	int getIFrames();
	
	void drawBullet(sf::RenderWindow& window);

	void setPosition(sf::Vector2f pos);

	void setRotation(float rotation);

	sf::Vector2f GetPosition();

	bool isColiding(Tile& _Tile, sf::View _view);

	bool isColiding(sf::Sprite _sprite);

	bool isColiding(sf::Sprite _sprite, bool isEntity);

	bool collision();

	sf::Sprite getSprite();

	void setTarget(sf::Sprite _sprite);

	void setTarget(sf::Vector2f _target);

	void resetCollision();

	void update();
};

