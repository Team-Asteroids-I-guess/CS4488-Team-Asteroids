//Director: Aleksandar Petrovic
//Team Space Gaming
//Asteroid Building Blocks

//*********UPDATE 02-24-2022****************************************
//You'll need to include <cmath> for the angle calculations to work, using sin and cos.
//*********UPDATE 02-24-2022****************************************

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include "ResourcePath.hpp"

#define ROCKET_SPEED 5

using namespace std;

class Bullet{
    float bulletSpeed = 20.0f;
    
public:
    sf::RectangleShape bulletShape;
    sf::Vector2f position;
    sf::Vector2f direction;
    Bullet(){
        
    }
    Bullet(sf::Vector2f position, float dirX, float dirY){
        this->position.x = position.x;
        this->position.y = position.y;
        this->direction.x = dirX;
        this->direction.y = dirY;
    }
    float getBulletSpeed(){
        return bulletSpeed;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Title");
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Clock Clock;
    float elapsed;
    int bulletCount = 0;

    //*********UPDATE 02-24-2022****************************************
    //Make sure that your rocket.png is in the same file path as your main.cpp file.
    //Rocket
    sf::Texture rocketTexture;
    sf::Sprite rocket;

    rocketTexture.loadFromFile("/Users/aleks/Documents/Xcode Files/MyFirstSFMLApp/MyFirstSFMLApp/rocket.png");
    rocket.setTexture(rocketTexture);
    rocket.setScale(0.2f, 0.2f);
    rocket.setRotation(0);
    rocket.setOrigin(rocket.getTexture()->getSize().x * 0.5, rocket.getTexture()->getSize().y * 0.5);
    //*********UPDATE 02-24-2022****************************************
    sf::Vector2f rocketPosition(window.getSize().x/2, window.getSize().y/2);

    //Sets the position of the object.
    rocket.setPosition(rocketPosition);

    //Rocket delta x and y for thrust
    int dx;
    int dy;
    
    //Bullets
    sf::RectangleShape bullets;
    bullets.setSize(sf::Vector2f(5, 20));
    bullets.setOutlineThickness(5);
    sf::Vector2f bulletPos(rocketPosition.x, rocketPosition.y);
    bullets.setPosition(bulletPos);
    bullets.setRotation(0);
    vector<sf::RectangleShape> myBullets;
    for (int i = 0;i<myBullets.size();i++){
        myBullets.erase(myBullets.begin() + i);
    }
    Bullet b1;
    b1.bulletShape.setPosition(rocketPosition.x, rocketPosition.y);
    b1.bulletShape.setOutlineThickness(5);

    //Flags for key pressed
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;
    bool spaceFlag = false;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            //If a key is pressed
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    //If escape key is pressed, close the application
                case sf::Keyboard::Escape: window.close(); break;

                //Process the up, down, left, and right keys
                case sf::Keyboard::Up: upFlag = true; break;
                case sf::Keyboard::Down: downFlag = true; break;
                case sf::Keyboard::Left: leftFlag = true; break;
                case sf::Keyboard::Right: rightFlag = true; break;
                case sf::Keyboard::Space: spaceFlag = true; break;
                default: break;
                }
            }

            //If a key is released
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                //Process the up, down, left and right keys
                case sf::Keyboard::Up: upFlag = false; break;
                case sf::Keyboard::Down: downFlag = false; break;
                case sf::Keyboard::Left: leftFlag = false; break;
                case sf::Keyboard::Right: rightFlag = false; break;
                case sf::Keyboard::Space: spaceFlag = false; break;
                default: break;
                }
            }
        }

        // Update coordinates

        //*********UPDATE 02-24-2022****************************************
        //This little bit is needed to make sure the up arrows make the rocket
        //go forward no matter what direction the rocket is facing
        double angleRads = (3.1415926536 / 180) * rocket.getRotation();
        double xAng = ROCKET_SPEED * sin(angleRads);
        double yAng = ROCKET_SPEED * -cos(angleRads);
        elapsed = Clock.getElapsedTime().asSeconds();
        Clock.restart();
        
        //New Attempt at Changing the position of the rocket
        //Steer
        if(leftFlag){
            rocket.setRotation(rocket.getRotation() - (200.0f * elapsed));
        }
        if(rightFlag){
            rocket.setRotation(rocket.getRotation() + (200.0f * elapsed));
        }
                               
        //Thrust
        if(upFlag){
            dx += sin(angleRads) * 200.0f * elapsed;
            dy += -cos(angleRads) * 200.0f * elapsed;
        }
        
            rocketPosition.x += dx * elapsed;
            rocketPosition.y += dy * elapsed;
        rocket.setPosition(rocketPosition);
        
        
        //Bullets
        if(spaceFlag){
            
            //myBullets.push_back(bullets);
            bullets.setRotation(rocket.getRotation());
            bullets.setPosition(rocketPosition);
         }
        /*
        bulletPos.x += dx * elapsed;
        bulletPos.y += dy * elapsed;
        bullets.setPosition(bulletPos);
        */

        //Check boundaries for the rocket using getGlobalBounds()
        if (rocketPosition.x + rocket.getGlobalBounds().width > window.getSize().x)
            rocketPosition.x = window.getSize().x - rocket.getGlobalBounds().width;
        if (rocketPosition.x < 0) rocketPosition.x = 0;
        if (rocketPosition.y < 0) rocketPosition.y = 0;
        if (rocketPosition.y + rocket.getGlobalBounds().height > window.getSize().y)
            rocketPosition.y = window.getSize().y - rocket.getGlobalBounds().height;

        //The params for window.clear() are just to change the color to a dark grey...
        //Totally useless and can just be left blank if desired.
        window.clear(sf::Color(40, 40, 40));
        window.draw(rocket);
        window.draw(bullets);
        window.display();
    }
    return 0;
}
