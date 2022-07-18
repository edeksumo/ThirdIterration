#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once

/*class Tile {
	int id;
	Object object;
public:
	Tile() {
		id = 0;
	}
	Tile(int _id) :
		id(_id){}
	
	Object getObject();
	void setId(int val);
	int getId();
	void setupTexture(sf::Texture& _texture);
};*/

class Tile {
	//private variables
	int id;
	int size_x;
	int size_y;
	sf::Vector2f pos;
	sf::Sprite sprite;
	bool solid;
	int curFrame;
	int frameCooldown;
	//private functions
	void frameCounter();

public:
	//construktor 
	Tile() {
		id = 0;
		size_x = 64;
		size_y = 64;
		pos = sf::Vector2f(0, 0);
		solid = false;
		curFrame = 0;
		frameCooldown = 0;
	}
	Tile(int _id, int _size_x, int _size_y, sf::Vector2f _pos, bool _solid, int _curFrame, int _frameCooldown)
			 :id(_id), size_x(_size_x), size_y(_size_y), pos(_pos), solid(_solid), curFrame(_curFrame), frameCooldown(_frameCooldown){
	}
	// public functions
	void setID(int val);
	
	int getID();
	
	void setSize(sf::Vector2f val);
	
	void setTexture(sf::Texture& _texture);
	
	void drawTile(sf::RenderWindow &window, sf::View &view);
	
	sf::Sprite tileGetSprite();
	
	bool isSolid();
	
	void setPos(sf::Vector2f val);
	
	sf::Vector2f getPos();
	
	void setSolid(int val);
	
	void update(sf::RenderWindow& window, sf::View& view);
};