#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "player.h"

struct Obiekty{
    bool isMoveable;
    bool isCollectible;
    sf::RectangleShape* obiekt;
    bool isPassable;
    bool delete1;
    bool delete2;
    bool islever;
    bool isplate;
    bool iscave;
};
sf::RectangleShape* obiekt(sf::Vector2f rozmiar, std::string tekstura, int pos_x, int pos_y);

void updateText(int points);
void displayPoints(int points, sf::RenderWindow& window);
void start(int& gamestate,int &ifleave,sf::Event,sf::RenderWindow& window);
void tutorial(int& gamestate,int &ifleave,sf::Event,sf::RenderWindow& window);
void ending(int& gamestate,sf::Event event,sf::RenderWindow& window,int &Points,int &currentLevel);
void updateLevel(float delta, sf::RenderWindow &window, Player &player, std::vector<Obiekty*> &level);
