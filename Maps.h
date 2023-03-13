#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "MapCreator.h"

Obiekty* CreateObject(sf::Vector2f rozmiar, std::string tekstura, int pos_x, int pos_y,bool isCollectible, bool isMoveable, bool isPassable,bool delete1, bool delete2, bool islever,bool iscave);
std::vector<Obiekty*> level1();
std::vector<Obiekty*> level2();
std::vector<Obiekty*> level3();
std::vector<Obiekty*> level4();

