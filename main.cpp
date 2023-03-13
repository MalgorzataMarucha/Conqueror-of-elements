#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Maps.h"
#include "player.h"
#include "MapCreator.h"


int main(){
    int gamestate=1;
    int ifleave = 0;
    sf::Time deltaTime;
    sf::Clock clock;
    sf::Music music;
    music.openFromFile("Images/music.ogg");
    music.setLoop(true);
    music.setVolume(20.f);
    music.play();
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Conqueror of elements");
    Player player;
    std::vector<Obiekty*> level_1=level1();
    std::vector<Obiekty*> level_2=level2();
    std::vector<Obiekty*> level_3=level3();
    std::vector<Obiekty*> level_4=level4();
    sf::RectangleShape* question = obiekt(sf::Vector2f(50,50),"Images/help.png",1050,0);
    sf::RectangleShape* restart = obiekt(sf::Vector2f(50,50),"Images/again.png",1120,0);
    while (window.isOpen())
    {
        float delta = clock.getElapsedTime().asSeconds();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                    window.close();
            }
            if (event.type == event.MouseButtonReleased && event.mouseButton.button==sf::Mouse::Left){
                sf::Vector2i mouseBounds=sf::Mouse::getPosition(window);
                sf::FloatRect helpBounds=question->getGlobalBounds();
                sf::FloatRect restartBounds=restart->getGlobalBounds();
                if(helpBounds.contains(mouseBounds.x,mouseBounds.y)){
                    ifleave = 1;
                }
                else if(restartBounds.contains(mouseBounds.x,mouseBounds.y)){
                    player.body.setPosition(175,585);
                    player.points = player.prevPoints2;
                    if(player.currentLevel == 1){
                        level_1=level1();
                    }
                    else if(player.currentLevel == 2){
                        level_2=level2();
                    }
                    else if(player.currentLevel == 3){
                        level_3=level3();
                    }
                    else if(player.currentLevel == 4){
                        level_4=level4();
                    }
                }

            }
        }
        window.clear();
        while(ifleave==1){
            tutorial(gamestate,ifleave,event,window);
        }
        if(gamestate==1){
            start(gamestate,ifleave,event,window);
        }
        if(gamestate==2){
            if(player.currentLevel==1){
                updateLevel(delta,window,player,level_1);
            }
            else if(player.currentLevel==2){
                updateLevel(delta,window,player,level_2);
            }
            else if(player.currentLevel==3){
                updateLevel(delta,window,player,level_3);
            }
            else if(player.currentLevel==4){
                updateLevel(delta,window,player,level_4);
            }
            else{
                gamestate=4;
            }
            player.Draw(window);
            displayPoints(player.points, window);
            window.draw(*question);
            window.draw(*restart);
        }

        if(gamestate==4){
            ending(gamestate,event,window,player.points,player.currentLevel);
        }
        window.display();
    }

    return 0;
}
