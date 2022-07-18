#include "Tile.h"
//****************************************************
//Externs
//****************************************************
extern int tileSize;

//****************************************************
//Setting texture by id 
//****************************************************
void Tile::setTexture(sf::Texture& _texture) {
	switch (getID())
	{
	case 0:
		sprite.setTextureRect(sf::IntRect(0,0, 48, 48));
		break;
	case 1:
		sprite.setTextureRect(sf::IntRect(48, 0, 48, 48));
		break;
	case 2:
		sprite.setTextureRect(sf::IntRect(96, 0, 48, 48));
		break;
	case 3:
		sprite.setTextureRect(sf::IntRect(144, 0, 48, 48));
		break;
	case 4:
		sprite.setTextureRect(sf::IntRect(192, 0, 48, 48));
		break;
	case 5:
		sprite.setTextureRect(sf::IntRect(240, 0, 48, 48));
		break;
	case 6:
		sprite.setTextureRect(sf::IntRect(0, 48, 48, 48));
		break;
	case 7:
		sprite.setTextureRect(sf::IntRect(48, 48, 48, 48));
		break;
	case 8:
		sprite.setTextureRect(sf::IntRect(96, 48, 48, 48));
		break;
	case 9:
		sprite.setTextureRect(sf::IntRect(144, 48, 48, 48));
		break;
	case 10:
		sprite.setTextureRect(sf::IntRect(192, 48, 48, 48));
		break;
	case 11:
		sprite.setTextureRect(sf::IntRect(240, 48, 48, 48));
		break;
	case 12:
		sprite.setTextureRect(sf::IntRect(0, 96, 48, 48));
		break;
	case 13:
		sprite.setTextureRect(sf::IntRect(48, 96, 48, 48));
		break;
	case 14:
		sprite.setTextureRect(sf::IntRect(96, 96, 48, 48));
		break;
	case 15:
		sprite.setTextureRect(sf::IntRect(144, 96, 48, 48));
		break;
	case 16:
		sprite.setTextureRect(sf::IntRect(192, 96, 48, 48));
		break;
	case 17:
		sprite.setTextureRect(sf::IntRect(240, 96, 48, 48));
		break;
	case 18:
		sprite.setTextureRect(sf::IntRect(0, 144, 48, 48));
		break;
	case 19:
		sprite.setTextureRect(sf::IntRect(48, 144, 48, 48));
		break;
	case 20:
		sprite.setTextureRect(sf::IntRect(96, 144, 48, 48));
		break;
	case 21:
		sprite.setTextureRect(sf::IntRect(144, 144, 48, 48));
		break;
	case 22:
		sprite.setTextureRect(sf::IntRect(192, 144, 48, 48));
		break;
	case 23:
		sprite.setTextureRect(sf::IntRect(240, 144, 48, 48));
		break;
	case 24:
		sprite.setTextureRect(sf::IntRect(0, 192, 48, 48));
		break;
	case 25:
		sprite.setTextureRect(sf::IntRect(48, 192, 48, 48));
		break;
	case 26:
		sprite.setTextureRect(sf::IntRect(96, 192, 48, 48));
		break;
	case 27:
		sprite.setTextureRect(sf::IntRect(144, 192, 48, 48));
		break;
	case 28:
		sprite.setTextureRect(sf::IntRect(192, 192, 48, 48));
		break;
	case 100:
		sprite.setTextureRect(sf::IntRect(288, 0, 32, 144));
		break;
	case 101:
		sprite.setTextureRect(sf::IntRect(288, 144, 32, 144));
		break;
	case 102:
		sprite.setTextureRect(sf::IntRect(0, 608, 144, 32));
		break;
	case 103:
		sprite.setTextureRect(sf::IntRect(144, 604, 108, 36));
		break;
	default:
		sprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
		break;
	}

	//sprite.setTextureRect(sf::IntRect(0, (row - 1) * tileSize, tileSize, tileSize));
	sprite.setTexture(_texture);

}
//****************************************************
//Counter for animation
//****************************************************
void Tile::frameCounter() {
	sprite.setTextureRect(sf::IntRect(curFrame * size_x, (getID() - 200) * 96, size_x, size_y));
	frameCooldown++;
	if (frameCooldown >= 5) {
		curFrame++;
		frameCooldown = 0;
	}
	if (curFrame == 10)
		curFrame = 0;
}
//****************************************************
//Draw Function
//****************************************************
void Tile::drawTile(sf::RenderWindow& window, sf::View& view) {
	
	if (getID() >= 200)
		frameCounter();
	
	sprite.setPosition(pos);
	if((view.getCenter().x - (view.getSize().x / 2) < sprite.getPosition().x + 100) && (view.getCenter().x + (view.getSize().x / 2) > sprite.getPosition().x)) {
		window.draw(sprite);
	}
}
//****************************************************
//Getters and setters
//****************************************************
sf::Sprite Tile::tileGetSprite() {
	return sprite;
}

void Tile::setSolid(int val) {
	if (val > 1)
		if (val < 0)
			return;
	solid = val;
}

bool Tile::isSolid() {
	return solid;
}

void Tile::setID(int val) {
	id = val;
}

int Tile::getID() {
	return id;
}

void Tile::setPos(sf::Vector2f val) {
	pos = val;
}

sf::Vector2f Tile::getPos() {
	return pos;
}

void Tile::setSize(sf::Vector2f val) {
	size_x = val.x;
	size_y = val.y;
}
//****************************************************
//Update funtion
//****************************************************
void Tile::update(sf::RenderWindow& window, sf::View& view) {
	drawTile(window, view);
}