#include "Player.h"
//****************************************************
//Externs
//****************************************************
extern sf::Texture entitiesTexture;
extern std::vector <FVX> FVXVector;
extern sf::Sound explosionSound;
extern sf::Sound shieldDownSound;
extern sf::SoundBuffer shotBuffer01;
//****************************************************
//Set Texture function
//****************************************************
bool Player::_setTexture() {
	//std::cout << "texture set n/";
	sprite.setTexture(entitiesTexture);
    shieldSprite.setTexture(entitiesTexture);
    shieldSprite.setTextureRect(sf::IntRect(60, 0, 60, 60));
	return 1;
}
//****************************************************
//Draw function
//****************************************************
void Player::drawPlayer(sf::RenderWindow& window) {
    if (iFramesTimer % 9 > 4) {
        return;
    }

    if (!isAlive()) {
        return;
    }

    if (!_setTexture()) {
        return;
    }
    if (checkPowerUp(PowerUp::Type::Shield))
        window.draw(shieldSprite);
    window.draw(sprite);
	//std::cout << "sprite";
}
//****************************************************
//Setting position
//****************************************************
void Player::setPosition(sf::Vector2f _pos) {
    float x, y;
    x = _pos.x;
    y = _pos.y - static_cast<float>(sprite.getTextureRect().height /2);   
	pos = sf::Vector2f(x,y);
    sprite.setPosition(pos);
}
//****************************************************
//Function for getting output and move player
//****************************************************
void Player::PlayerMoving(int offset_x_min, int offset_x_max, int offset_y, sf::View view, float speed_x, float speed_y, float cameraSpeed, sf::Clock clock) {

    float delta = clock.restart().asSeconds();

    if (!isAlive())
        return;

    if (sprite.getPosition().x <= view.getCenter().x - offset_x_min) {
            sprite.move(cameraSpeed,0);
            pos.x = sprite.getPosition().x;
    }
    
    //pos = viev.getCenter() - sf::Vector2f(offset_x, offset_y);

    if (_isColidingWTile) {
        if (lastPressedDown) {
            sprite.move(0, -speed_y);
            pos.y = sprite.getPosition().y;
        }
        else if (lastPressedUp) {
            sprite.move(0, speed_y);
            pos.y = sprite.getPosition().y;

        }
        if (lastPressedLeft) {
            sprite.move(speed_x, 0);
            pos.x = sprite.getPosition().x;
        }
        else if (lastPressedRight) {
            sprite.move(-speed_x, 0);
            pos.x = sprite.getPosition().x;
        }
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (sprite.getPosition().x > view.getCenter().x - offset_x_min))
    {
        // left key is pressed: move our character
        if (_isColidingWTile)
            if (lastPressedLeft)
                return;
        sprite.move(-speed_x, 0);
        lastPressedLeft = true;
        pos.x = sprite.getPosition().x;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (pos.x + (speed_x) <= view.getCenter().x - offset_x_max))
    {
        if (_isColidingWTile)
            if (lastPressedRight)
                return;
        sprite.move(speed_x, 0);
        lastPressedRight = true;
        pos.x = sprite.getPosition().x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // down key is pressed: move our character
        if (_isColidingWTile)
            if (lastPressedDown)
                return;

        sprite.move(0, speed_y);
        lastPressedDown = true;
        pos.y = sprite.getPosition().y;
        if (getFrameCooldown() == 0) {
            if (getCurrentFrame() > -4) {
                currentFrame--;
                setFrameCooldown(3);
            }
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
       if (_isColidingWTile)
            if (lastPressedUp) 
                return;
        lastPressedUp = true;
        sprite.move(0, -speed_y);
        pos.y = sprite.getPosition().y;
        if (getFrameCooldown() == 0) {
            if (getCurrentFrame() < 4) {
                currentFrame++;
                setFrameCooldown(3);
            }
        }
    }
}
//****************************************************
//Function for shooting
//****************************************************
void Player::PlayerShotting(sf::RenderWindow &window) {
    if (!isAlive())
        return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (getShotCooldownTimer() == shootCooldown()) {
            Bullet bullet;
            bullet.setTarget(sf::Vector2f(pos.x + 10000, pos.y + (getSprite().getTextureRect().height / 2) + 1));
            bullet.setPosition(sf::Vector2f(pos.x + sprite.getTextureRect().width + (bullet.getSprite().getTextureRect().width), pos.y + (sprite.getTextureRect().height / 2) - (bullet.getSprite().getTextureRect().height / 2)));
            bulletVec.push_back(bullet);
            setShotCooldownTimer(0);
            shootSound.play();
            if (checkPowerUp(PowerUp::Type::MultiShot)) {
                Bullet bullet1;
                bullet1.setTarget(sf::Vector2f(pos.x + 8000, pos.y + (getSprite().getTextureRect().height / 2) - 2000));
                bullet1.setPosition(sf::Vector2f(pos.x + sprite.getTextureRect().width + (bullet1.getSprite().getTextureRect().width), pos.y + (sprite.getTextureRect().height / 2) - (bullet1.getSprite().getTextureRect().height / 2)));
                Bullet bullet2;
                bullet2.setTarget(sf::Vector2f(pos.x + 8000, pos.y + (getSprite().getTextureRect().height / 2) + 2000));
                bullet2.setPosition(sf::Vector2f(pos.x + sprite.getTextureRect().width + (bullet2.getSprite().getTextureRect().width), pos.y + (sprite.getTextureRect().height / 2) - (bullet2.getSprite().getTextureRect().height / 2)));
                bulletVec.push_back(bullet1);
                bulletVec.push_back(bullet2);

            }
        
        }
    }
}
//****************************************************
//Setting lives and keep player alive
//****************************************************
void Player::setLives(int lives) {
    _lives = lives;
    if (_lives < 0) {
        _lives = 0;
    }

    if (_lives == 0) {
        if (!exploded) {
            FVX _fvx;
            _fvx.setPosition(sprite);
            _fvx.setTexture();
            explosionSound.play();
            FVXVector.push_back(_fvx);
            exploded = true;
        }
    }
};
//****************************************************
//Erasing all player bullets
//****************************************************
void Player::eraseBullets() {
    for (int i = 0; i < bulletVec.size(); i++) {
        bulletVec.erase(bulletVec.begin() + i);
    }
}
//****************************************************
//Collision functions
//****************************************************
bool Player::isColiding(Tile &_tile, sf::View _view) {

    sf::Sprite _sprite = _tile.tileGetSprite();
    if (isColiding(_sprite) && _tile.isSolid()) {
        if (iFramesTimer <=0) {     
            if (!checkPowerUp(PowerUp::Type::Shield)) {
                removePowerUp(PowerUp::Type::FastShot);
                removePowerUp(PowerUp::Type::MultiShot);
                setIFramesTimer(100);
                setLives(getLives() - 1);
                eraseBullets();
            }
            else {
                shieldDownSound.play();
                removePowerUp(PowerUp::Type::Shield);
            }
        }
        _isColidingWTile = true;
        return true;
    }
    return false;
}

bool Player::isColiding(sf::Sprite _sprite, bool isEnemy, sf::View _view) {

    if (isColiding(_sprite) && isEnemy && getIFramesTimer() <= 0) {
        //setPosition(sf::Vector2f(_view.getCenter().x - 200, _view.getCenter().y));
        if (!checkPowerUp(PowerUp::Type::Shield)) {
            removePowerUp(PowerUp::Type::FastShot);
            removePowerUp(PowerUp::Type::MultiShot);
            setIFramesTimer(100);
            setLives(getLives() - 1);
            eraseBullets();
        }
        else{
            shieldDownSound.play();
            removePowerUp(PowerUp::Type::Shield);
        }
        return true;
    }
    return false;
}

bool Player::isColiding(sf::Sprite _sprite) {

    if (sprite.getGlobalBounds().intersects(_sprite.getGlobalBounds())) {
        _isColiding = true;
        return true;
    }

    return false;
}
//****************************************************
//Checker if player is alive
//****************************************************
bool Player::isAlive() {
    if (getLives() <= 0) {
        return false;
    }
    return true;
}
//****************************************************
//IFrames counter
//****************************************************
int Player::_iFramesCounter(int a) {
    if (iFramesTimer > 0) {
        iFramesTimer = iFramesTimer - a;
    }
    return iFramesTimer;
}
//****************************************************
//Cooldown for shooting
//****************************************************
int Player::_shotCooldownTimer(int a) {
    if (_shotCooldown < shootCooldown()) {
        _shotCooldown = _shotCooldown + a;
    }
    if (_shotCooldown > shootCooldown())
        _shotCooldown = shootCooldown();
    return _shotCooldown;
}
//****************************************************
//Update function for bullets
//****************************************************
void Player::updateBullets(sf::RenderWindow &window) {
    sf::View view = window.getView();

   // std::cout << view.getCenter().x << " ";
    for (int i = 0; i < bulletVec.size(); i++) {
        if ((view.getCenter().x - (view.getSize().x / 2) < bulletVec[i].GetPosition().x) && (view.getCenter().x + (view.getSize().x / 2) > bulletVec[i].GetPosition().x)) {
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
//Fixed frame cooldown
//****************************************************
void Player::frameCooldownTimer() {
    if (getFrameCooldown() > 0)
        frameCooldown--;
}
//****************************************************
//Function that keeps player idle anim
//****************************************************
void Player::frameReseter() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return;
    if (getFrameCooldown() == 0) {
        if (getCurrentFrame() > 0) {
            currentFrame--;
            setFrameCooldown(3);
        }
        else if (getCurrentFrame() < 0) {
            currentFrame++;
            setFrameCooldown(3);
        }
    }
}
//****************************************************
//Animation 
//****************************************************
void Player::animation() {
    switch (getCurrentFrame())
    {
    case -1:
        sprite.setTextureRect(sf::IntRect(50, 200, 50, 50));
        break;
    case -2:
        sprite.setTextureRect(sf::IntRect(100, 200, 50, 50));
        break;
    case -3:
        sprite.setTextureRect(sf::IntRect(150, 200, 50, 50));
        break;
    case -4:
        sprite.setTextureRect(sf::IntRect(200, 200, 52, 50));
        break;
    case 0:
        sprite.setTextureRect(sf::IntRect(0, 150, 50, 50));
        break;
    case 1:
        sprite.setTextureRect(sf::IntRect(50, 150, 50, 50));
        break;
    case 2:
        sprite.setTextureRect(sf::IntRect(100, 150, 50, 50));
        break;
    case 3:
        sprite.setTextureRect(sf::IntRect(150, 150, 50, 50));
        break;
    case 4:
        sprite.setTextureRect(sf::IntRect(200, 150, 52, 50));
        break;
    default:
        sprite.setTextureRect(sf::IntRect(0, 150, 50, 50));
        break;
    }
}
//****************************************************
//Power up checker
//****************************************************
bool Player::checkPowerUp(PowerUp::Type type) {
    if ((type == PowerUp::Type::FastShot) && powerUpFastShoot) 
        return true;
    if ((type == PowerUp::Type::MultiShot) && powerUpMultiShoot)
        return true;
    if ((type == PowerUp::Type::Shield) && powerUpShield)
        return true;
    return false;
}
//****************************************************
//Adding new power up
//****************************************************
void Player::addPowerUp(PowerUp::Type type) {
    if (checkPowerUp(type))
        return;
    if (type == PowerUp::Type::FastShot)
        powerUpFastShoot = true;
    if (type == PowerUp::Type::MultiShot)
        powerUpMultiShoot = true;
    if (type == PowerUp::Type::Shield)
        powerUpShield = true;

}
//****************************************************
//Removing power ups
//****************************************************
void Player::removePowerUp(PowerUp::Type type) {
    if (!checkPowerUp(type))
        return;
    if (type == PowerUp::Type::FastShot)
        powerUpFastShoot = false;
    if (type == PowerUp::Type::MultiShot)
        powerUpMultiShoot = false;
    if (type == PowerUp::Type::Shield)
        powerUpShield = false;
}
//****************************************************
//Setter for max shoot cooldown
//****************************************************
int Player::shootCooldown() {
    auto i = 50;
    if (checkPowerUp(PowerUp::Type::FastShot))
        i = 30;
    return i;
}
//****************************************************
//Function for adding points
//****************************************************
void Player::addPoints(unsigned int val) {
    points = points + val;
}
//****************************************************
//Getters and Setters
//****************************************************
unsigned int Player::getPoints() {
    return points;
}
sf::Vector2f Player::getPosition() {
    return pos;
}

sf::Sprite Player::getSprite() {
    return sprite;
}

void Player::setSound() {
    shootSound.setBuffer(shotBuffer01);
}

int Player::getCurrentFrame() {
    return currentFrame;
}

int Player::getFrameCooldown() {
    return frameCooldown;
}

void Player::setFrameCooldown(int val) {
    frameCooldown = val;
}

void Player::setShotCooldownTimer(int a) {
    _shotCooldown = a;
}

int Player::getShotCooldownTimer() {
    return _shotCooldown;
}

void Player::setIFramesTimer(int a) {
    iFramesTimer = a;
}

int Player::getIFramesTimer() {
    return iFramesTimer;
}

int Player::getLives() {
    return _lives;
}
//****************************************************
//Update Function
//****************************************************
void Player::update() {
    
    _iFramesCounter(1);
    _shotCooldownTimer(1);
    frameCooldownTimer();
    animation();
    frameReseter();
    if (!_isColiding) {
        lastPressedUp = false;
        lastPressedDown = false;
        lastPressedLeft = false;
        lastPressedRight = false;
    }
    shieldSprite.setPosition(sf::Vector2f(sprite.getPosition().x - 5, sprite.getPosition().y - 5));
    _isColiding = false;
    _isColidingWTile = false;
}