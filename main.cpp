#include<iostream>
#include "SFML/Graphics.hpp"
#include "ghost.h"
#include "globals.h"
#include<math.h>
int radius = 15;
using namespace std;

//enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(1000, 1000), "PacMan"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("map.png");
    sf::Sprite wall;
    wall.setTexture(brick);

    ghost Knuckles;
    Knuckles.initGhost(400, 644, 1, 0, 1, sf::Color(200,0,0));
    ghost Tails;
    Tails.initGhost(200, 644, 1, 0, 1, sf::Color(255,100,0));
    ghost Luigi;
    Luigi.initGhost(100, 644, 1, 0, 1, sf::Color(0, 200, 100));
    ghost LilPurp;
    LilPurp.initGhost(550, 644, 1, 0, 1, sf::Color(106, 13, 173));

    int map[28][28] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1,0,1,
        1,0,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,1,1,1,0,1,
        1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,
        1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1,1,1,
        0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,
        1,1,1,1,1,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,
        0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,
        0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,
        1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,
        1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,
        1,0,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,1,0,1,
        1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
        1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
        1,1,0,0,1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,1,0,0,1,1,
        1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,
        1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };

    //player setup
    int xpos = 50;
    int ypos = 50;
    int vx = 0;
    int vy = 0;
    sf::CircleShape player(15);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };

    //dot
    sf::CircleShape dot(5);
    dot.setFillColor(sf::Color(250, 250, 250)); //using RGB value for color here (hex also works)
    dot.setPosition(0, 0);

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;


        }//end event loop---------------------------------------------------------------

        //warp zone
        if (xpos < -15 && ypos >= 435 && ypos < 495)
            xpos = 970;
        if (xpos > 970 && ypos >= 435 && ypos < 495)
            xpos = -15;
        
        //call ghost chaser functions
        Luigi.chase1(xpos, ypos, map);
        Knuckles.chase2(xpos, ypos, map);
        Tails.chase3(xpos, ypos, map);
        LilPurp.chase4(xpos, ypos, map);

         //move Mr. Pac
        if (keys[LEFT] == true)
            vx = -5;

        else if (keys[RIGHT] == true)
            vx = 5;
        else vx = 0;
        if (keys[DOWN] == true)
            vy = 5;

        else if (keys[UP] == true)
            vy = -5;

        else vy = 0;


        //right collision
        if (vx > 0 && map[(ypos) / 36][(xpos + radius * 2 + 5) / 36] == 1) {
            vx = 0;
        }
        //left collision
        if (vx < 0 && map[(ypos) / 36][(xpos - 5) / 36] == 1) {
            vx = 0;
        }
        //down collision
        if (vy > 0 && map[(ypos + radius * 2 + 5) / 36][(xpos) / 36] == 1) {
            vy = 0;
        }
        //up collision
        if (vy < 0 && map[(ypos - 5) / 36][(xpos) / 36] == 1) {
            vy = 0;
        }

        if (map[(ypos) / 36][(xpos) / 36] == 0)
            map[(ypos) / 36][(xpos) / 36] = 2;
        cout << xpos << " , " << ypos << endl;

        //update player position
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear
       // screen.draw(&screen);
        //draw map
        for (int rows = 0; rows < 28; rows++)
            for (int cols = 0; cols < 28; cols++) {
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 36, rows * 36);
                    screen.draw(wall);
                }
                if (map[rows][cols] == 0) {
                    dot.setPosition(cols * 36 + 18, rows * 36 + 18);
                    screen.draw(dot);

                }
            }
        Luigi.drawGhost(screen);
        Knuckles.drawGhost(screen);
        Tails.drawGhost(screen);
        LilPurp.drawGhost(screen);
        screen.draw(player); //draw player
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main
