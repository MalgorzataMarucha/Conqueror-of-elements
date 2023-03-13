#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "MapCreator.h"

class Player{
    private:
        sf::Texture texture;
        float speed = 300.f;
        sf::Vector2f velocity;
        sf::Vector2f objectVelocity;
        bool right= false;
        bool left = false;
        bool up = false;
        bool isOnGround = true;
        bool collisionMove = false;
        bool BoxBottomCollision = false;
        int prevPoints1 = 0;
        sf::Texture teksturka;
    public:
        sf::Sprite body;
        int points=0;
        int prevPoints2 = 0;
        int currentLevel=1;
        Player();
        ~Player();
        void Draw(sf::RenderWindow& window);
        void collisionScreen(sf::RenderWindow& window);
        void checkCollisions(float delta,std::vector<struct Obiekty*> level);
        void MotionUpdate(float delta,std::vector<struct Obiekty*> level,sf::RenderWindow& window);
        std::vector<struct Obiekty*> deleteObjects(std::vector<struct Obiekty*> level);
        std::vector<struct Obiekty*> ObjectsStateUpdate(std::vector<struct Obiekty*> level);

};
