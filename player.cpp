#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Maps.h"
#include "MapCreator.h"
#include "MapRotation.h"
#include "player.h"


Player::Player(){
    texture.loadFromFile("Images/Player/player.png");
    teksturka.loadFromFile("Images/leverFlip.png");
    body.setTexture(texture);
    body.setScale(45/body.getLocalBounds().width,65/body.getLocalBounds().height);
    body.setPosition(175,585);

}
Player::~Player(){
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(body);
}
void Player::collisionScreen(sf::RenderWindow& window){
    sf::Vector2u windowSize = window.getSize();
    if (body.getPosition().y < 0) {
        body.setPosition(body.getPosition().x, 0);
        velocity.y = 0;
    }
    else if (body.getPosition().y + body.getGlobalBounds().height > windowSize.y) {
        body.setPosition(body.getPosition().x, windowSize.y - body.getGlobalBounds().height);
        velocity.y = 0;
        isOnGround = true;
    }
}
void Player::checkCollisions(float delta,std::vector<Obiekty*> level){
    bool collisionRight = false;
    bool collisionLeft = false;
    bool collisionDown = false;
    sf::FloatRect playerBounds = body.getGlobalBounds();
    sf::FloatRect nextMove;
    for (size_t i = 0; i < level.size(); i++){
        sf::RectangleShape object = *level[i]->obiekt;
        sf::FloatRect objectBounds = object.getGlobalBounds();
        nextMove = playerBounds;
        nextMove.top += velocity.y*2;
        nextMove.left += velocity.x*2;
        if(!(level[i]->isPassable)){
            if(objectBounds.intersects(nextMove)){
                if(level[i]->isMoveable){
                    if((playerBounds.left < objectBounds.left&&
                       playerBounds.left+playerBounds.width < objectBounds.left&&
                       playerBounds.left + playerBounds.width < objectBounds.left+objectBounds.width&&
                       objectBounds.top + objectBounds.height > playerBounds.top &&
                       objectBounds.top < playerBounds.top + playerBounds.height)||
                       (playerBounds.left > objectBounds.left&&
                       playerBounds.left > objectBounds.left+objectBounds.width&&
                       playerBounds.left + playerBounds.width > objectBounds.left+objectBounds.width&&
                       objectBounds.top + objectBounds.height > playerBounds.top &&
                       objectBounds.top < playerBounds.top + playerBounds.height)){
                        collisionMove = false;
                        for (size_t j = 0; j < level.size(); j++) {
                            if (i != j) {
                                sf::RectangleShape otherObject = *level[j]->obiekt;
                                sf::FloatRect otherObjectBounds = otherObject.getGlobalBounds();
                                sf::FloatRect movedObjectBounds = objectBounds;
                                movedObjectBounds.left += velocity.x;
                                movedObjectBounds.top += velocity.y;
                                if (movedObjectBounds.intersects(otherObjectBounds) && !level[j]->isPassable){
                                    if(movedObjectBounds.top < otherObjectBounds.top &&
                                   movedObjectBounds.top + movedObjectBounds.height < otherObjectBounds.top + otherObjectBounds.height&&
                                   movedObjectBounds.left < otherObjectBounds.left + otherObjectBounds.width &&
                                   movedObjectBounds.left + movedObjectBounds.width > otherObjectBounds.left){
                                        continue;
                                    }
                                    if(movedObjectBounds.left>otherObjectBounds.left || movedObjectBounds.left<otherObjectBounds.left+otherObjectBounds.width){
                                        if(level[j]->isplate){
                                            level[i]->obiekt->setPosition(otherObjectBounds.left+otherObjectBounds.width/4,otherObjectBounds.top-movedObjectBounds.height);
                                        }
                                        collisionMove = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if (!collisionMove) {
                            object.move(velocity.x,0);
                            level[i]->obiekt->setPosition(object.getPosition());
                        }
                    }
                }
               if(playerBounds.left < objectBounds.left&&
               playerBounds.left+playerBounds.width < objectBounds.left&&
               playerBounds.left + playerBounds.width < objectBounds.left+objectBounds.width&&
               objectBounds.top + objectBounds.height > playerBounds.top &&
               objectBounds.top < playerBounds.top + playerBounds.height){
                velocity.x=0.f;
                collisionRight = true;
                }
                else{
                    collisionRight = false;
                }
                if(playerBounds.left > objectBounds.left&&
                   playerBounds.left > objectBounds.left+objectBounds.width&&
                   playerBounds.left + playerBounds.width > objectBounds.left+objectBounds.width&&
                   objectBounds.top + objectBounds.height > playerBounds.top &&
                   objectBounds.top < playerBounds.top + playerBounds.height){
                    velocity.x=0.f;
                    collisionLeft = true;
                }
                else{
                    collisionLeft = false;
                }
                if(playerBounds.top < objectBounds.top &&
                   playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height&&
                   playerBounds.left < objectBounds.left + objectBounds.width &&
                   playerBounds.left + playerBounds.width > objectBounds.left){
                    velocity.y=0.f;
                    collisionDown = true;
                    isOnGround = true;
                }
                else{
                    collisionDown = false;
                    isOnGround = false;
                }
                if(playerBounds.top > objectBounds.top &&
                   playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height&&
                   playerBounds.left < objectBounds.left + objectBounds.width &&
                   playerBounds.left + playerBounds.width > objectBounds.left){
                    velocity.y=0.f;
                    collisionDown = false;
                }
                else{
                    collisionDown = true;
                }
            }
        }
    }
    if (right==true && collisionRight==false) {
        texture.loadFromFile("Images/Player/playerright.png");
    }
    if (left==true && collisionLeft==false) {
        texture.loadFromFile("Images/Player/playerleft.png");
    }
    if (up && right){
        texture.loadFromFile("Images/Player/rightjump.png");
    }
    if (up && left){
        texture.loadFromFile("Images/Player/leftjump.png");
    }
    if (right == false && left == false){
        texture.loadFromFile("Images/Player/player.png");
    }
    if (up == false && collisionDown==false && playerBounds.top<585){
        velocity.y += speed * delta* 0.001;
        body.move(velocity);
    }
}
std::vector<Obiekty*> Player::deleteObjects(std::vector<Obiekty*> level){
    prevPoints1 = points;
    sf::FloatRect playerBounds = body.getGlobalBounds();
    sf::FloatRect nextMove;
    for (size_t i = 0; i < level.size(); i++){
        sf::RectangleShape object = *level[i]->obiekt;
        sf::FloatRect objectBounds = object.getGlobalBounds();
        nextMove = playerBounds;
        nextMove.top += velocity.y*2;
        nextMove.left += velocity.x*2;
        if(!(level[i]->isPassable)){
            if(objectBounds.intersects(nextMove)){
                if(level[i]->islever){
                    if(playerBounds.left < objectBounds.left&&
                    playerBounds.left+playerBounds.width < objectBounds.left&&
                    playerBounds.left + playerBounds.width < objectBounds.left+objectBounds.width&&
                    objectBounds.top + objectBounds.height > playerBounds.top &&
                    objectBounds.top < playerBounds.top + playerBounds.height){
                        level[i]->obiekt->setTexture(&teksturka);
                        for(size_t j=0;j<level.size();j++){
                            if(level[j]->delete1){
                                level.erase(level.begin()+j);
                            }
                        }
                    }
                }
                else if(level[i]->isCollectible){
                    if((playerBounds.left < objectBounds.left&&
                    playerBounds.left+playerBounds.width < objectBounds.left&&
                    playerBounds.left + playerBounds.width < objectBounds.left+objectBounds.width&&
                    objectBounds.top + objectBounds.height > playerBounds.top &&
                    objectBounds.top < playerBounds.top + playerBounds.height)||
                    (playerBounds.left > objectBounds.left&&
                    playerBounds.left > objectBounds.left+objectBounds.width&&
                    playerBounds.left + playerBounds.width > objectBounds.left+objectBounds.width&&
                    objectBounds.top + objectBounds.height > playerBounds.top &&
                    objectBounds.top < playerBounds.top + playerBounds.height) ||
                    (playerBounds.top < objectBounds.top &&
                    playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height&&
                    playerBounds.left < objectBounds.left + objectBounds.width &&
                    playerBounds.left + playerBounds.width > objectBounds.left)||
                    (playerBounds.top > objectBounds.top &&
                    playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height&&
                    playerBounds.left < objectBounds.left + objectBounds.width &&
                    playerBounds.left + playerBounds.width > objectBounds.left)){
                        points +=1;
                        if(points != prevPoints1){
                            updateText(points);
                            prevPoints1 = points;
                        }
                        level.erase(level.begin()+i);
                    }
                }
                else if(level[i]->iscave){
                    if((playerBounds.left < objectBounds.left&&
                    playerBounds.left+playerBounds.width < objectBounds.left&&
                    playerBounds.left + playerBounds.width < objectBounds.left+objectBounds.width&&
                    objectBounds.top + objectBounds.height > playerBounds.top &&
                    objectBounds.top < playerBounds.top + playerBounds.height)||
                    (playerBounds.left > objectBounds.left&&
                    playerBounds.left > objectBounds.left+objectBounds.width&&
                    playerBounds.left + playerBounds.width > objectBounds.left+objectBounds.width&&
                    objectBounds.top + objectBounds.height > playerBounds.top &&
                    objectBounds.top < playerBounds.top + playerBounds.height)){
                        currentLevel+=1;
                        body.setPosition(175,585);
                        prevPoints2 = points;
                    }
                }
            }
        }
        if(level[i]->isplate){
            for(size_t j=0;j<level.size();j++){
                if(level[j]->isMoveable){
                    sf::RectangleShape movedObject = *level[j]->obiekt;
                    sf::FloatRect plateObjectBounds = objectBounds;
                    sf::FloatRect movedObjectBounds = movedObject.getGlobalBounds();
                    movedObjectBounds.left += velocity.x;
                    movedObjectBounds.top += velocity.y;
                    if(movedObjectBounds.intersects(plateObjectBounds)){
                        for(size_t k=0; k<level.size();k++){
                            if(level[k]->delete2){
                                level.erase(level.begin()+k);
                            }
                        }
                    }
                }
            }
        }
    }
    return level;
}

std::vector<Obiekty*> Player::ObjectsStateUpdate(std::vector<Obiekty*> level){
    for(size_t i = 0; i < level.size(); i++){
        if(level[i]->isMoveable){
            sf::RectangleShape object = *level[i]->obiekt;
            sf::FloatRect objectBounds = object.getGlobalBounds();
            for(size_t j = 0; j < level.size(); j++){
                if(j != i &&  !level[j]->isPassable){
                    sf::RectangleShape otherObject = *level[j]->obiekt;
                    sf::FloatRect otherObjectBounds = otherObject.getGlobalBounds();
                    if(otherObjectBounds.intersects(objectBounds)){
                        object.setPosition(object.getPosition().x, objectBounds.top);
                        *level[i]->obiekt = object;
                        break;
                    }
                    else{
                        object.setPosition(object.getPosition().x, object.getPosition().y+0.05);
                        *level[i]->obiekt = object;
                    }
                }
            }
        }
    }
    return level;
}

void Player::MotionUpdate(float delta, std::vector<Obiekty*> level,sf::RenderWindow& window){
    velocity.y += 9.8f * delta;
    velocity.x = 0.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        right = true;
        velocity.x += speed * delta;
    }
    else{
        right = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        left = true;
        velocity.x += -speed * delta;
    }
    else{
        left=false;
    }
    if(isOnGround){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            up = true;
            velocity.y = -3.5f;
            isOnGround = false;
        }
        else{
            up=false;
        }
    }
    collisionScreen(window);
    checkCollisions(delta,level);
    body.move(velocity);
}
