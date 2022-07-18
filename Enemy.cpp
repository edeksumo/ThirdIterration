#include "Enemy.h"
//****************************************************
//Externs
//****************************************************
extern int tileSize;
extern sf::SoundBuffer shotBuffer01;
//****************************************************
//Setting texture depends on enemy type
//****************************************************
bool Enemy::setTexture(sf::Texture &_texture) {
    
    switch (getType())
    {
    case enemyType::Tower:
        sprite.setTextureRect(sf::IntRect(0,0,50,50));
        break;
    case enemyType::Ship:
        sprite.setTextureRect(sf::IntRect(0, 100, 54, 50));
        break;
    case enemyType::Bomb:
        sprite.setTextureRect(sf::IntRect(0, 50, 50, 50));
        break;
    default:
        break;
    }
    texture = _texture;
	sprite.setTexture(_texture);
	return 1;
}
//****************************************************
//Draw function
//****************************************************
void Enemy::drawEnemy(sf::RenderWindow& window) {

    window.draw(sprite);
}
//****************************************************
//Checher is obj visible 
//****************************************************
bool Enemy::isOnTheView(sf::View view) {
    if ((view.getCenter().x - (view.getSize().x / 2) < sprite.getPosition().x + 50) && (view.getCenter().x + (view.getSize().x / 2) > sprite.getPosition().x)) {
        return true;
    }
    return false;
}
//****************************************************
//Setters and getters
//****************************************************
void Enemy::setFrameCooldown(int val) {
    frameCooldown = val;
}

int Enemy::getFrameCooldown() {
    return frameCooldown;
}

int Enemy::getCurrentFrame() {
    return currentFrame;
}

void Enemy::frameCooldownTimer() {
    if (getFrameCooldown() > 0)
        frameCooldown--;
}


void Enemy::setPosition(sf::Vector2f _pos) {
    float x, y;
    
    if (getType() == enemyType::Tower) {
       x = _pos.x + (float)tileSize / 2;
       y = _pos.y + (float)tileSize / 2;
    }
    else if (getType() == enemyType::Bomb) {
        x = _pos.x + (float)tileSize / 2;
        y = _pos.y + (float)tileSize / 2;
    }
    else {
        x = _pos.x;
        y = _pos.y - (float)sprite.getTextureRect().height / 2;
    }
    pos = sf::Vector2f(x, y);
    sprite.setPosition(pos);
}

sf::Vector2f Enemy::GetPosition() {
    return pos;
 }

sf::Sprite Enemy::getSprite() {
    return sprite;
}

void Enemy::setDestroy(bool value) {
    destroy = value;
}

bool Enemy::getDestroy() {
    return destroy;
}

void Enemy::setType(enemyType _type) {
    switch (_type){
        case enemyType::Tower:
            type = enemyType::Tower;
            break;
        case enemyType::Ship:
            type = enemyType::Ship;
            break;
        case enemyType::Bomb:
            type = enemyType::Bomb;
            break;
    
    default:
        type = enemyType::Tower;
        break;
    }
}

void Enemy::setType(int _type) {
    switch (_type) {
    case 0:
        type = enemyType::Tower;
        break;
    case 1:
        type = enemyType::Ship;
        break;
    case 2:
        type = enemyType::Bomb;
        break;

    default:
        type = enemyType::Tower;
        break;
    }
}

void Enemy::setShotCooldownTimer(int a, int min, int max) {
    srand(time(NULL));
    int x = (std::rand() % max - min) + min;
    _shotCooldown = x + a;
}

void Enemy::setSound() {
    shootSound.setBuffer(shotBuffer01);
}

int Enemy::getShotCooldownTimer() {
    return _shotCooldown;
}

Enemy::enemyType Enemy::getType() {
    return type;
}
//****************************************************
//Collision functions
//****************************************************
bool Enemy::isColiding(sf::Sprite _sprite) {

    if (sprite.getGlobalBounds().intersects(_sprite.getGlobalBounds())) {
        _isColiding = true;
        return true;
    }

    return false;
}

bool Enemy::isColiding(sf::Sprite _sprite, bool isPlayer) {

    if (isColiding(_sprite) && isPlayer) {
        return true;
    }

    return false;
}

bool Enemy::collision() {
    if (_isColiding) {
        return true;
    }

    return false;
}
//****************************************************
//Timer for shot cooldown
//****************************************************
int Enemy::_shotCooldownTimer(int a) {
    if (_shotCooldown > 0) {
        _shotCooldown = _shotCooldown - a;
    }
    return _shotCooldown;
}
//****************************************************
//Shooting into player
//****************************************************
void Enemy::shooting(Player player) {
    if (getShotCooldownTimer() == 0) {
        Bullet bullet;
        bullet.setTarget(sf::Vector2f(player.getPosition().x + (player.getSprite().getTextureRect().width / 2), player.getPosition().y + (player.getSprite().getTextureRect().height / 2)));
        bullet.setPosition(sf::Vector2f(pos.x, pos.y));
        bullet.setRotation(currentTg * 180.0 / 3.14);
        bulletVec.push_back(bullet);
        setShotCooldownTimer(100, 1, 30);
        shootSound.play();
    }
}
//****************************************************
//Shooting into position
//****************************************************
void Enemy::shooting(sf::Vector2f _pos) {
    if (getShotCooldownTimer() == 0) {
        Bullet bullet;
        bullet.setTarget(sf::Vector2f(_pos.x, _pos.y));
        bullet.setPosition(sf::Vector2f(pos.x + (sprite.getTextureRect().width / 2), pos.y + (sprite.getTextureRect().height / 2)));
        bulletVec.push_back(bullet);
        setShotCooldownTimer(100, 1, 30);
        shootSound.play();
    }
}
//****************************************************
//Update function for bullets kept in vector
//****************************************************
void Enemy::updateBullets(sf::RenderWindow& window) {
    sf::View view = window.getView();

    // std::cout << view.getCenter().x << " ";
    for (int i = 0; i < bulletVec.size(); i++) {
        if ((view.getCenter().x - (view.getSize().x / 2) < bulletVec[i].GetPosition().x) && (view.getCenter().x + (view.getSize().x / 2) - 100 > bulletVec[i].GetPosition().x)) {
            bulletVec[i].drawBullet(window);
            bulletVec[i].update();
            if (bulletVec[i].collision()) {
                bulletVec.erase(bulletVec.begin() + i);
                return;
            }
            bulletVec[i].resetCollision();

        }
        else {
            bulletVec.erase(bulletVec.begin() + i);
            //std::cout << "erase";
        }
    }
}
//****************************************************
//Init function for dummy obj
//****************************************************
void Enemy::createEnemies(int x, int y, int _type, sf::RenderWindow &window, sf::Texture &texture) {
    if (!enemiesInit) {
        Enemy _enemy;
        _enemy.setType(_type);
        _enemy.setTexture(texture);
        _enemy.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
        int x = (std::rand() % 60 - 10) + 10;
        _enemy.setShotCooldownTimer(100, 1, x);
        _enemy.setSound();
        enemyVec.push_back(_enemy);
        //std::cout << "enemy created ";
    }
}
//****************************************************
//Moving and animation controler for ship enemy
//****************************************************
void Enemy::moving(sf::Vector2f velocity) {
    int x, y, r;
    x = -velocity.x;
    y = velocity.y;
    srand(time(NULL));
    float z = (std::rand() % 5 - 1) + 1;
    r = (std::rand() % 3 - 1) + 1;
    if (r < 1) {
        z = -z;
        if (getFrameCooldown() == 0) {
            if (getCurrentFrame() > -3) {
                currentFrame--;
                setFrameCooldown(3);
            }
        }
    }
    else if (r > 1) {
        if (getFrameCooldown() == 0) {
            if (getCurrentFrame() < 3) {
                currentFrame++;
                setFrameCooldown(3);
            }
        }
    }
    else if (r == 1) {
        z = 0;
        if (getFrameCooldown() == 0) {
            if (getCurrentFrame() < 0) {
                currentFrame++;
                setFrameCooldown(3);
            } else if (getCurrentFrame() > 0) {
                currentFrame--;
                setFrameCooldown(3);
            }
        }
    }
    switch (getType())
    {
    case enemyType::Ship:
        sprite.move(x * (speed + (z / 10)), y + (z / 20) * speed);
        pos.x = sprite.getPosition().x;
        pos.y = sprite.getPosition().y;
        break;
    case enemyType::Bomb:
        sprite.setOrigin(static_cast<float>(-sprite.getTextureRect().width / 2), (sprite.getTextureRect().height / 2));
        sprite.rotate(4 + (z/3));
        break;
    }
}
//****************************************************
//Defaut moving func
//****************************************************
void Enemy::moving() {
    moving(sf::Vector2f(0, 0));
}
//****************************************************
//Tacking player for tower enemy
//****************************************************
void Enemy::playerTracing(Player player) {
    float p_x, p_y, e_x, e_y;
    p_x = player.getPosition().x + (player.getSprite().getTextureRect().width /2);
    p_y = player.getPosition().y + (player.getSprite().getTextureRect().height / 2);
    e_y = pos.y;
    e_x = pos.x;
    sprite.setOrigin((sprite.getTextureRect().width / 2), (sprite.getTextureRect().height / 2));
    currentTg = std::atan2(p_y - e_y, p_x - e_x);
    sprite.setRotation(currentTg * 180.0 / 3.14);
}
//****************************************************
//Animation function
//****************************************************
void Enemy::animation() {
    switch (getCurrentFrame())
    {
    case 1:
        sprite.setTextureRect(sf::IntRect(216, 100, 54, 50));
        break;
    case 2:
        sprite.setTextureRect(sf::IntRect(270, 100, 54, 50));
        break;
    case 3:
        sprite.setTextureRect(sf::IntRect(324, 100, 54, 50));
        break;
    case 0:
        sprite.setTextureRect(sf::IntRect(0, 100, 54, 50));
        break;
    case -1:
        sprite.setTextureRect(sf::IntRect(54, 100, 54, 50));
        break;
    case -2:
        sprite.setTextureRect(sf::IntRect(108, 100, 54, 50));
        break;
    case -3:
        sprite.setTextureRect(sf::IntRect(162, 100, 54, 50));
        break;
    default:
        sprite.setTextureRect(sf::IntRect(0, 100, 54, 50));
        break;
    }
}
//****************************************************
//FVX for enemy init function
//****************************************************
void Enemy::setUpFVX() {
    fvx.setStartPosY(314);
    fvx.setCycles(100);
    fvx.setMaxFrame(7);
    fvx.setRotation(270);
    fvx.setSize(sf::Vector2f(12, 48));
    fvx.setTexture();
    fvx.setOffset(sf::Vector2f(sprite.getTextureRect().width - 15, sprite.getTextureRect().height/ 2 + 6));
}
//****************************************************
//FVX update function
//****************************************************
void Enemy::FVXUpdate(sf::RenderWindow &window) {
    fvx.setPositionOffset(sprite.getPosition());
    fvx.update(window);
}
//****************************************************
//Update function
//****************************************************
void Enemy::update(sf::RenderWindow &window, Player player) {
    if (!isOnTheView(window.getView())) {
        return;
    }
    //updating difrent component by enemy type
    switch (getType()) {
    case enemyType::Tower:
        playerTracing(player);
        shooting(player);
        updateBullets(window);
        break;
    case enemyType::Ship:
        if (!FVXSetUp)
            setUpFVX();
        moving(sf::Vector2f(1, 0));
        shooting(sf::Vector2f(pos.x - 200, pos.y + (sprite.getTextureRect().height / 2)));      //shooting straight
        updateBullets(window);
        animation();
        frameCooldownTimer();
        FVXUpdate(window);
        break;
    case enemyType::Bomb:
        moving();
        break;
    }
    _isColiding = false;            //reseting collision 
    _shotCooldownTimer(1);
    drawEnemy(window);
}