#include "Bullet.h"
//****************************************************
//Externs
//****************************************************
extern sf::Texture entitiesTexture;
//****************************************************
//Set texture and draw function
//****************************************************
bool Bullet::_setTexture() {
	sprite.setTextureRect(sf::IntRect(50, 0, 10, 4));
	sprite.setTexture(entitiesTexture);
	return 1;
}

void Bullet::drawBullet(sf::RenderWindow& window) {
	if (!_setTexture()) {
		return;
	}
	window.draw(sprite);
}
//****************************************************
//Setters and getters
//****************************************************
void Bullet::setPosition(sf::Vector2f _pos) {
	float x, y;
	x = _pos.x;
	y = _pos.y - static_cast<float>(sprite.getTextureRect().height / 2);
	pos = sf::Vector2f(x, y);
	sprite.setPosition(pos);
}

void Bullet::setRotation(float rotation) {
	sprite.setRotation(rotation);
}

sf::Vector2f Bullet::GetPosition() {
	return pos;
}

void Bullet::setIFrames(int a) {
	iFrames = a;
}

int Bullet::getIFrames() {
	return iFrames;
}

sf::Sprite Bullet::getSprite() {
	return sprite;
}

void Bullet::setTarget(sf::Sprite _sprite) {
	if (pos == _sprite.getPosition()) {
		std::cout << "Wrong target position";
		return;
	}

	setTarget(_sprite.getPosition());
}

void Bullet::setTarget(sf::Vector2f _target) {
	if (pos == _target) {
		std::cout << "Wrong target position";
		return;
	}

	target = _target;
}
//****************************************************
//Fixed Iframes for collision detection
//****************************************************
void Bullet::updateIFrames(int a) {
	if(getIFrames() > 0)
		setIFrames(getIFrames() - a);
}
//****************************************************
//Collision functions
//****************************************************
bool Bullet::collision() {
	if (_isColiding) {
		return true;
	}

	return false;
}

bool Bullet::isColiding(Tile& _tile, sf::View _view) {

	sf::Sprite _sprite = _tile.tileGetSprite();
	if (isColiding(_sprite) && _tile.isSolid()) {
		return true;
	}
	return false;
}
bool Bullet::isColiding(sf::Sprite _sprite) {

	if (getIFrames() > 0)
		return false;
	if (sprite.getGlobalBounds().intersects(_sprite.getGlobalBounds())) {
		_isColiding = true;
		return true;
	}

	return false;
}

bool Bullet::isColiding(sf::Sprite _sprite, bool isEntity) {
	if (isColiding(_sprite) && isEntity) {
		return true;
	}
	return false;
}
//****************************************************
//Setting direction for bullet
//****************************************************
void Bullet::setDirection() {
	if (directionSet) {
		return;
	}
	float tx, ty, sx, sy, rx, ry;
	tx = target.x;
	ty = target.y;
	sx = pos.x;
	sy = pos.y;
	rx = tx - sx;
	ry = ty - sy;

	if (abs(rx) + abs(ry) > 2) {
		while (abs(rx) + abs(ry) > 2) {
			rx = rx / 2;
			ry = ry / 2;
		}
	}

	dir_x = rx;
	dir_y = ry;
	directionSet = true;
}
//****************************************************
//Moving bullet
//****************************************************
void Bullet::move() {
	sprite.move(dir_x * speed, dir_y * speed);
	pos.x = sprite.getPosition().x;
	pos.y = sprite.getPosition().y;
}
//****************************************************
//Collision reset function
//****************************************************
void Bullet::resetCollision() {
	_isColiding = false;
}
//****************************************************
//Update function
//****************************************************
void Bullet::update() {
	updateIFrames(1);
	setDirection();
	move();
}