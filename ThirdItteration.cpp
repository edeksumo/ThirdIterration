#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "FVX.h"
#include <iostream>
#include "PowerUp.h"
#include "UI.h"
//****************************************************
//Global variables
//****************************************************
int tileSize = 48;

float cameraSpeed = 1.3;

sf::Texture textureMap;
sf::Texture animTexture;
sf::Texture background_01;
sf::Texture background_Stars;
sf::Texture entitiesTexture;
sf::Texture UITexture;

sf::Sprite backgroundSprite;
sf::Sprite backgroundSpriteStars;

sf::SoundBuffer shotBuffer01;
sf::SoundBuffer explosionBuffer01;
sf::SoundBuffer powerUpBuffer;
sf::SoundBuffer powerUpGetBuffer;
sf::SoundBuffer shieldDownBuffer;
sf::Sound shieldDownSound;
sf::Sound explosionSound;
sf::Sound powerUpSound;
sf::Sound powerUpGetSound;

std::vector <Tile> tileArr;
std::vector <FVX> FVXVector;
std::vector <PowerUp> PowerUpVector;

bool mapBuild = false;
bool backgroundCreated = false;
//****************************************************
//Map Array
//****************************************************
int map[12][120] = { 
  /*        0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119*/
  /* 0*/  { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7},
  /* 1*/  {22,22,22,22,22,22,22,22,22,22,22,22,13,22,22,22,22,22,22,22,13,22,22,22,22,22,22,13,22,22,22,22,13,13,22,22, 7,22,22,22,22,22, 7, 7, 7, 7,22,22, 7,22,22,22,22, 7,22,22,13,22,22,22,22,22, 7,22, 7,22,22,22,22,22,22,13,22, 7,22,22, 7, 7, 7, 7,13,22,22,22, 7,22,22,22, 7, 7, 7, 7, 7,22,22,22,13,22,22,22, 22, 22, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 22, 22, 22},
  /* 2*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4,-1,-1,-1,-1,-1,26, 7, 7, 8,-1,-1,10,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1, 6, 7, 7,27,-1,-1,-1,-1, 4,-1,-1,-1,12,13,13,22,14,-1,-1,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /* 3*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4,-1,-1,-1,-1,-1,-1,26, 7, 8,-1,-1,10,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1, 6, 7,27,-1,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /* 4*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,26,14,22,22,22,22,22,22,22,13,13,13,22,22,22,22,22,22,22,13,22,13,22,22,22,22,13,13,22,22,22,22,22,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /* 5*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20, 1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /* 6*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 6, 9,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /* 7*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,26,13, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /* 8*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20, 1,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20, 2,15,16,17,15,15,15,15,15,15, 1,15,15,15,15,15,17, 1,15,15,15,15,15,15,15,15,15, 1, 1,15,17,15,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 2,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /* 9*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20, 7, 7, 7,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20, 7, 8,-1,-1,10,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1, 6, 7,21,-1,-1,-1,-1,-1,28,-1,-1,-1,-1,-1,-1,-1, 6, 9, 8,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /*10*/  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20, 7, 7, 7, 7, 7,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20, 7, 7, 8,-1,-1,10,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1, 6, 7, 7,21,-1,-1,-1,-1, 4,-1,-1,-1,-1,-1,-1,-1,12,13,14,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  /*11*/  {15,15,15,15,15,15,15,15, 1,15,15,15,15,16,15,15,15, 1,15,15,17,15,15,15,15, 7, 7, 7, 7, 7, 7, 7,16,15,15,15,15,15, 1,15,15,15, 7, 7, 7, 7,15,15, 7,15,15,15,15, 7,15,15,15,15,15,15,15,15, 7,15, 7,15,15,15,15,15,15,15,15, 7,15,15, 7, 7, 7, 7,15,16,15,15, 7,15,15,17,15,15,15,15,15,15,15,15,15,15,15,15, 15, 15, 17, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}
};
//****************************************************
//Array for placing sprites on map 
//****************************************************
int mapSprites[44][6] = {
    //pos x       pos y   id      solid  //size x  //size y
      {1040,      400,    100,      1},
      {978,       368,    102,      1},
      {620,        52,    101,      1},
      {680,        32,    101,      1},
      {740,        42,    101,      1},
      {1810,      430,    100,      1},
      {1902,      430,    100,      1},
      {900,        96,    103,      0},
      {2400,      240,    103,      0},
      {1800,      430,    102,      1},
      {2208,      432,    200,      1,      96,         96},
      {2208,       96,    200,      1,      96,         96},
      {2352,      432,    200,      1,      96,         96},
      {2448,      432,    200,      1,      96,         96},
      {2352,       96,    200,      1,      96,         96},
      {2448,       96,    200,      1,      96,         96},
      {2592,      432,    200,      1,      96,         96},
      {2688,      432,    200,      1,      96,         96},
      {2592,       96,    200,      1,      96,         96},
      {2688,       96,    200,      1,      96,         96},
      {2784,      432,    200,      1,      96,         96},
      {2880,      432,    200,      1,      96,         96},
      {2784,       96,    200,      1,      96,         96},
      {2880,       96,    200,      1,      96,         96},
      {2976,      432,    200,      1,      96,         96},
      {2976,       96,    200,      1,      96,         96},
      {3072,      432,    200,      1,      96,         96},
      {3168,      432,    200,      1,      96,         96},
      {3264,      432,    200,      1,      96,         96},
      {3360,      432,    200,      1,      96,         96},
      {3072,       96,    200,      1,      96,         96},
      {3168,       96,    200,      1,      96,         96},
      {3264,       96,    200,      1,      96,         96},
      {3360,       96,    200,      1,      96,         96},
      {3456,      432,    200,      1,      96,         96},
      {3456,       96,    200,      1,      96,         96},
      {3552,      432,    200,      1,      96,         96},
      {3552,       96,    200,      1,      96,         96},
      {3200,      240,    103,      0},
      {4060,       96,    103,      0},
      {3888,       63,    101,      1},
      {4210,      460,    100,      1},
      {4302,      460,    100,      1},
      {4200,      460,    102,      1},
};
//****************************************************
//Array for placing enemies on map
//****************************************************
int enemies[16][3] = {
    //pos x   pos y   type
      {28,    5,      1},
      {36,    4,      0},
      {44,    6,      2},
      {40,    6,      1},
      {54,    6,      1},
      {58,    6,      2},
      {70,    6,      1},
      {76,    6,      2},
      {79,    6,      1},
      {84,    3,      0},
      {84,    9,      0},
      {98,    2,      1},
      {100,   4,      1},
      {102,   6,      1},
      {104,   8,      1},
      {106,  10,      1},
};
//****************************************************
//Background init function
//****************************************************
void createBackground() {

    background_01.setRepeated(true);
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, 10024, 560));
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setTexture(background_01);
    background_Stars.setRepeated(true);
    backgroundSpriteStars.setTextureRect(sf::IntRect(0, 0, 10024, 560));
    backgroundSpriteStars.setPosition(0, 0);
    backgroundSpriteStars.setTexture(background_Stars);
    backgroundCreated = true;

}
//****************************************************
//Background update function
//****************************************************
void backgroundUpdate(float speed, sf::RenderWindow &window, Player &player, sf::Sprite &sprite) {
    if(player.isAlive())
        sprite.move(speed, 0);
    window.draw(sprite);
}
//****************************************************
//Setting player initial pos 
//****************************************************
void setPlayerInitPos(Player &player, sf::Vector2f pos) {
    player.setPosition(pos);
}
//****************************************************
//Camera moving function
//****************************************************
void cameraMoving(sf::View &view, sf::RenderWindow &window, Player player) {
    if (player.isAlive()) {
        view.move(cameraSpeed, 0.f);
    }
}
//****************************************************
//Creating not tile objects
//****************************************************
void buildmap() {

    for (int i = 0; i < (sizeof(map[0]) / sizeof(int)); i++) {
        for (int j = 0; j < (sizeof(map) / sizeof(map[0])); j++) {
            if (map[j][i] != -1) {
                //Tile tile(map[j][i], tileSize, tileSize, sf::Vector2f(tileSize * i, tileSize * j), true, 0);
                Tile tile;
                tile.setPos(sf::Vector2f(tileSize * i, tileSize * j));
                tile.setID(map[j][i]);
                tile.setSize(sf::Vector2f(tileSize, tileSize));
                tile.setSolid(true);
                tile.setTexture(textureMap);
                tileArr.push_back(tile);
            }
        }
    }
    std::cout << "[GAME] Map Build!\n";
    mapBuild = true;
}
//****************************************************
//Creating tile set objects
//****************************************************
void buildmapTiles() {
    for (int i = 0; i < (sizeof(mapSprites) / sizeof(mapSprites[0])); i++) {
        Tile tile(mapSprites[i][2], tileSize, tileSize, sf::Vector2f(mapSprites[i][0], mapSprites[i][1]), mapSprites[i][3], 0, 0);
        if (tile.getID() < 200) {
            tile.setTexture(textureMap);
        }
        else {
            tile.setTexture(animTexture);
            tile.setSize(sf::Vector2f(mapSprites[i][4], mapSprites[i][5]));
        }
        tileArr.push_back(tile);
    }
    std::cout << "[GAME] Map Build Tiles!\n";
    mapBuild = true;
}
//****************************************************
//Creating enemies from array
//****************************************************
void initEnemies(Enemy& enemy, sf::RenderWindow& window) {

    if (!enemy.enemiesInit) {
        for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++) {
            enemy.createEnemies(enemies[i][0], enemies[i][1], enemies[i][2], window, entitiesTexture);
        }
        enemy.enemiesInit = true;
        std::cout << "[GAME] Enemies created!\n";
    }
}
//****************************************************
//Creating power up by type
//****************************************************
void createPowerUp(PowerUp::Type type, Enemy &enemy) {
    for (int i = 0; i < PowerUpVector.size(); i++) {
        if (PowerUpVector[i].getType() == type)
            return;
    }
    PowerUp powerUp;
    powerUp.setType(type);
    powerUp.setTexture();
    powerUp.setPosition(enemy.GetPosition() + sf::Vector2f(enemy.getSprite().getTextureRect().width / 2, enemy.getSprite().getTextureRect().width / 2));
    PowerUpVector.push_back(powerUp);
}
//****************************************************
//Creating power up on enemy dead
//****************************************************
void powerUpsInit(Enemy &enemy, Player &player) {
    if (enemy.getType() == Enemy::enemyType::Tower)
        return;

    srand(time(NULL));
    auto p = (std::rand() % 10 - 1) + 1;
    if (p > 3) {
        auto t = (std::rand() % 3 - 1) + 1;
        if ((t < 1)&& (!player.checkPowerUp(PowerUp::Type::FastShot))) {
            createPowerUp(PowerUp::Type::FastShot, enemy);
        }
        if ((t == 1) && (!player.checkPowerUp(PowerUp::Type::MultiShot))) {
            createPowerUp(PowerUp::Type::MultiShot, enemy);
        }
        if ((t > 1) && (!player.checkPowerUp(PowerUp::Type::Shield))) {
            createPowerUp(PowerUp::Type::Shield, enemy);
        }
    }
}
//****************************************************
//Main collision checer function
//****************************************************
void collsionChecker(sf::View& view, Player& player, Enemy& enemy) {
    if (!player.isAlive())
        return;

    for (int i = 0; i < PowerUpVector.size(); i++) {
        if (player.isColiding(PowerUpVector[i].getSprite())) {
            player.addPowerUp(PowerUpVector[i].getType());
            powerUpGetSound.play();
            player.addPoints(1000);
            PowerUpVector.erase(PowerUpVector.begin() + i);
        }
    }
    
    for (int i = 0; i < enemy.enemyVec.size(); i++) {
        for (int j = 0; j < enemy.enemyVec[i].bulletVec.size(); j++) {
            //collision player with enemy bullet
            if (player.getIFramesTimer() <= 0) {
                if (enemy.enemyVec[i].bulletVec[j].isColiding(player.getSprite(), true)) {
                    if (!player.checkPowerUp(PowerUp::Type::Shield))
                        explosionSound.play();
                    player.isColiding(enemy.enemyVec[i].bulletVec[j].getSprite(), true, view);
                
                }
            }
        }
        for (int j = 0; j < player.bulletVec.size(); j++) {
            //collision player bullet with enemy
            if (player.bulletVec[j].isColiding(enemy.enemyVec[i].getSprite(), true)) {
                enemy.enemyVec[i].setDestroy(true);
                FVX _fvx;
                _fvx.setPosition(sf::Vector2f(player.bulletVec[j].getSprite().getPosition().x, player.bulletVec[j].getSprite().getPosition().y- 32));
                _fvx.setTexture();
                FVXVector.push_back(_fvx);
                powerUpsInit(enemy.enemyVec[i], player);
                explosionSound.play();
                player.addPoints(100);
            }
        }
        if (player.isColiding(enemy.enemyVec[i].getSprite(), true, view) || enemy.enemyVec[i].getDestroy()) {
            //collision player with enemy
            enemy.enemyVec.erase(enemy.enemyVec.begin() + i);
            explosionSound.play();
        }
    }
}
//****************************************************
//Draw function and contine collision checker
//****************************************************
void drawMap(sf::RenderWindow& window, sf::View& view, Player& player, Enemy& enemy) {
    for (int i = 0; i < tileArr.size(); i++) {
        tileArr[i].drawTile(window, view);
        //Player collision with map
        if (player.isColiding(tileArr[i], view)) {
            //explosionSound.play();
        }
        //Players bullet collision with map
        for (int k = 0; k < player.bulletVec.size(); k++) {
            player.bulletVec[k].isColiding(tileArr[i], view);
        }
        for (int k = 0; k < enemy.enemyVec.size(); k++) {
            for (int l = 0; l < enemy.enemyVec[k].bulletVec.size(); l++) {
                //enemy bullet collision with map
                enemy.enemyVec[k].bulletVec[l].isColiding(tileArr[i], view);
            }
        }
    }
}
//****************************************************
//Main update for enemies
//****************************************************
void updateEnemies(Enemy &enemy, sf::RenderWindow &window, Player player) {
    for (int i = 0; i < enemy.enemyVec.size(); i++) {
        enemy.enemyVec[i].update(window, player);
    }
}
//****************************************************
//Main update for Visual Efects
//****************************************************
void updateFVX(sf::RenderWindow &window) {
    for (int i = 0; i < FVXVector.size(); i++) {
        FVXVector[i].update(window);
        if (FVXVector[i].getCanBeKilled()) {
            FVXVector.erase(FVXVector.begin() + i);
        }
    }
}
//****************************************************
//Main update for power ups
//****************************************************
void updatePowerUps(sf::RenderWindow& window) {
    for (int i = 0; i < PowerUpVector.size(); i++) {
        PowerUpVector[i].update(window);
        if (!PowerUpVector[i].isOnTheView(window.getView())) {
            PowerUpVector.erase(PowerUpVector.begin() + i);
        }
    }
}
//****************************************************
//Main update function for game 
//****************************************************
void update(sf::RenderWindow &window, sf::View &view, sf::Clock &clock, Player &player, Enemy &enemy, UI &ui) {
    if (!mapBuild) {
        buildmapTiles();
        buildmap();
        createBackground();
    }
    player.update();
    window.clear();
   
    backgroundUpdate(0.7, window, player, backgroundSprite);
    backgroundUpdate(0.6, window, player, backgroundSpriteStars);
    drawMap(window, view, player, enemy);
    collsionChecker(view, player, enemy);
    initEnemies(enemy, window);
    if (player.isAlive()) {
        updateEnemies(enemy, window, player);
    }
    player.updateBullets(window);
    player.PlayerMoving(600, 100, 0, view, 3, 2.5, cameraSpeed, clock);
    player.PlayerShotting(window);
    player.drawPlayer(window);
    updatePowerUps(window);
    updateFVX(window);
    ui.update(window, player);
    cameraMoving(view, window, player);
    window.setView(view);
    window.display();
}
//****************************************************
//Sound init function
//****************************************************
bool initSoundBuffers() {
    if (!shotBuffer01.loadFromFile("assets/shoot.wav"))
        return false;
    if (!explosionBuffer01.loadFromFile("assets/explosion.wav"))
        return false;
    if (!powerUpBuffer.loadFromFile("assets/powerUp.ogg"))
        return false;
    if (!powerUpGetBuffer.loadFromFile("assets/powerUpGet.ogg"))
        return false;
    if (!shieldDownBuffer.loadFromFile("assets/shieldDown.ogg"))
        return false;
    shieldDownSound.setBuffer(shieldDownBuffer);
    explosionSound.setBuffer(explosionBuffer01);
    powerUpSound.setBuffer(powerUpBuffer);
    powerUpGetSound.setBuffer(powerUpGetBuffer);
    return true;
}
//****************************************************
//Texture init function
//****************************************************
bool textureMenager() {
    if (!textureMap.loadFromFile("assets/textures.png", sf::IntRect(0, 0, 320, 640))) {
        return false;
    }
    if (!animTexture.loadFromFile("assets/animTextures.png", sf::IntRect(0, 0, 960, 960))) {
        return false;
    }
    if (!background_01.loadFromFile("assets/background.png", sf::IntRect(0, 0, 1024, 1024))) {
        return false;
    }
    if (!background_Stars.loadFromFile("assets/backgroundStars.png", sf::IntRect(0, 0, 1024, 1024))) {
        return false;
    }
    if (!entitiesTexture.loadFromFile("assets/entities.png", sf::IntRect(0, 0, 704, 1000))) {
        entitiesTexture.setSmooth(true);
        return false;
    }
    if (!UITexture.loadFromFile("assets/UI.png", sf::IntRect(0, 0, 1280, 200))) {
        return false;
    }
    return true;
}
//****************************************************
//Main
//****************************************************
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ufo Journey v.0.0.1");
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
    
    Player player;
    Enemy enemy;
    UI userInterface;
    userInterface.setTexture();



    sf::Clock clock;
    setPlayerInitPos(player, sf::Vector2f(view.getCenter().x - 200, view.getCenter().y - 75));
    player.setSound();
    sf::Music music;
    if (!music.openFromFile("assets/mainTheme.ogg"))
        return -1;
    music.play();
    if (!initSoundBuffers())
        return -1;
    if (!textureMenager())
        return -1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.draw(backgroundSprite);
        update(window, view, clock, player, enemy, userInterface);

    }

    return 0;
}