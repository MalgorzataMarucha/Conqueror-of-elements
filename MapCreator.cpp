#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "MapCreator.h"
#include "Maps.h"
#include "player.h"

sf::Text text;
sf::Text text2;
sf::Font font;
sf::Font font2;

void updateText(int points) {
    text.setString("Points: " + std::to_string(points));
}
void updateLevel(float delta,sf::RenderWindow &window, Player &player, std::vector<Obiekty*> &level) {
    level = player.deleteObjects(level);
    level = player.ObjectsStateUpdate(level);
    player.MotionUpdate(delta,level,window);

    for (size_t i = 0; i < level.size(); i++) {
        window.draw(*level[i]->obiekt);
    }
}
sf::RectangleShape* obiekt(sf::Vector2f rozmiar, std::string tekstura, int pos_x, int pos_y){
    sf::Texture *element_texture;
    sf::RectangleShape *element;
    element_texture = new sf::Texture;
    element = new sf::RectangleShape;
    element_texture->loadFromFile(tekstura);
    element->setSize(rozmiar);
    element->setTexture(element_texture);
    element->setPosition(pos_x, pos_y);
    return element;
}


void displayPoints(int points, sf::RenderWindow& window) {
    static bool firstRun = true;
    if (firstRun) {
        if (!font.loadFromFile("Images/OpenSansBold.ttf")){
            std::ifstream file("Images/OpenSansBold.ttf", std::ios::binary);
            if (!file){
                std::cout << "Nie można znalezc czcionki OpenSansBold.ttf" << std::endl;
            }
            file.close();
        }
        else {
            text.setFont(font);
        }
        text.setCharacterSize(25);
        text.setPosition(15, 15);
        firstRun = false;
    }
    updateText(points);
    window.draw(text);
}
void start(int& gamestate,int &ifleave,sf::Event event,sf::RenderWindow& window){
    sf::RectangleShape* start=obiekt(sf::Vector2f(200,100),"Images/Menu/start.png",500,300);
    sf::RectangleShape* exit=obiekt(sf::Vector2f(200,100),"Images/Menu/exit.png",500,600);
    sf::RectangleShape* tutorial=obiekt(sf::Vector2f(200,100),"Images/Menu/tutorial.png",500,450);
    sf::RectangleShape* background=obiekt(sf::Vector2f(1200,800),"Images/Menu/background.png",0,0);
    font2.loadFromFile("Images/OpenSansBold.ttf");
    text2.setCharacterSize(50);
    text2.setFont(font2);
    text2.setPosition(300, 150);
    text2.setString("Conqueror of elements:");
    text2.setFillColor(sf::Color::White);
    text2.setOutlineThickness(2);
    while (window.pollEvent(event))
    {
        if (event.type == event.MouseButtonReleased && event.mouseButton.button==sf::Mouse::Left){
            sf::Vector2i mouseBounds=sf::Mouse::getPosition(window);
            sf::FloatRect startBounds=start->getGlobalBounds();
            sf::FloatRect exitBounds=exit->getGlobalBounds();
            sf::FloatRect tutorialBounds=tutorial->getGlobalBounds();
            if(startBounds.contains(mouseBounds.x,mouseBounds.y)){
                gamestate=2;
            }
            else if(tutorialBounds.contains(mouseBounds.x,mouseBounds.y)){
                ifleave=1;
            }
            else if(exitBounds.contains(mouseBounds.x,mouseBounds.y)){
                window.close();
            }
        }
    }
    window.draw(*background);
    window.draw(*start);
    window.draw(*tutorial);
    window.draw(*exit);
    window.draw(text2);
}
void tutorial(int& gamestate,int &ifleave,sf::Event event,sf::RenderWindow& window){
    sf::RectangleShape* background=obiekt(sf::Vector2f(1200,800),"Images/Menu/tutorialbackground.png",0,0);
    sf::RectangleShape* return_button=obiekt(sf::Vector2f(200,100),"Images/Menu/return.png",500,600);
    while (window.pollEvent(event))
    {
        if (event.type == event.MouseButtonReleased && event.mouseButton.button==sf::Mouse::Left){
            sf::Vector2i mouseBounds=sf::Mouse::getPosition(window);
            sf::FloatRect returnBounds=return_button->getGlobalBounds();
            if(returnBounds.contains(mouseBounds.x,mouseBounds.y)){
                ifleave = 2;
            }
        }
    }
    window.draw(*background);
    window.draw(*return_button);
    window.draw(text);
    window.display();
}
void ending(int& gamestate,sf::Event event,sf::RenderWindow& window,int &Points,int &currentLevel){
     sf::RectangleShape* background=obiekt(sf::Vector2f(1200,800),"Images/Menu/background.png",0,0);
     sf::RectangleShape* exit =obiekt(sf::Vector2f(200,100),"Images/Menu/exit.png",500,600);
     sf::RectangleShape* playagain=obiekt(sf::Vector2f(200,100),"Images/Menu/playagain.png",500,450);
     text2.setCharacterSize(50);
     text2.setFont(font);
     text2.setPosition(350, 250);
     text2.setString("Zdobyto: "+std::to_string(Points)+" punktow");
     text2.setFillColor(sf::Color::White);
     text2.setOutlineThickness(2);
     while (window.pollEvent(event))
    {
        if (event.type == event.MouseButtonReleased && event.mouseButton.button==sf::Mouse::Left){
            sf::Vector2i mouseBounds=sf::Mouse::getPosition(window);
            sf::FloatRect exitBounds=exit->getGlobalBounds();
            sf::FloatRect playBounds=playagain->getGlobalBounds();
            if(exitBounds.contains(mouseBounds.x,mouseBounds.y)){
                window.close();
            }
            else if(playBounds.contains(mouseBounds.x,mouseBounds.y)){
                gamestate=2;
                currentLevel = 1;
                Points = 0;
            }
        }
    }
    window.draw(*background);
    window.draw(*exit);
    window.draw(*playagain);
    window.draw(text2);
}
