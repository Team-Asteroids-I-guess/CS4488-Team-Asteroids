//Director: Aleksandar Petrovic
//Producer: Thomas Anderson
//Team Space Gaming
//Asteroid Building Blocks

//*********UPDATE 02-24-2022****************************************
//You'll need to include <cmath> for the angle calculations to work, using sin and cos.
//*********UPDATE 02-24-2022****************************************

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <list>


#define CIRCLE_SPEED 5

using namespace std;
//Set constant numbers for height and width
const int W = 1200;
const int H = 800;


//********************3/10/2022 Update TSA **************************************************
//Asteroid class
class asteroid
{
public:
	//Create asteroid and assign texture and size
	sf::Sprite shape;
	//sf::Texture *texture;
	asteroid(sf::Texture *texture, sf::Vector2u windowSize)
	{
		//set tecture of asteroid
		this->shape.setTexture(*texture);
		//set size of asteroid
		this->shape.setScale(0.2f, 0.2f);

		//Set spawn position of asteroid, using random y axis number
		this->shape.setPosition(/*rand() % */ windowSize.x - this->shape.getGlobalBounds().width, rand() % windowSize.y - this->shape.getGlobalBounds().height);

	}
	~asteroid(){}
};

//*********************************************************************************************


int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Title");
	window.setFramerateLimit(60);
	sf::Event event;

	//Create the shape with raidus and number of points
	sf::CircleShape circle(100, 30);
	circle.setFillColor(sf::Color(255, 0, 255));


	//*********UPDATE 02-24-2022****************************************
	//Make sure that your rocket.png is in the same file path as your main.cpp file.
	//Rocket
	sf::Texture rocketTexture;
	sf::Sprite rocket;

	rocketTexture.loadFromFile("rocket.png");
	rocket.setTexture(rocketTexture);
	rocket.setScale(0.1f, 0.1f);
	rocket.setRotation(0);
	rocket.setOrigin(rocket.getTexture()->getSize().x * 0.5, rocket.getTexture()->getSize().y * 0.5);

	//**********************************************************************************

	//********************3/10/2022 Update TSA **************************************************

	//implement texture for asteroids
	int asteroidspawn = 0;
	sf::Texture asteroidTexture;
	asteroidTexture.loadFromFile("rock.png");

	//Create asteroid from class
	vector<asteroid> asteroids;
	


	//********************************************************************************************



	//*********UPDATE 02-24-2022****************************************

	//This is for the initial position of the circle, used for the keystroke movement part.
	sf::Vector2f circlePosition(500, 350);

	//Sets the position of the object.
	//circle.setPosition(circlePosition);
	rocket.setPosition(circlePosition);

	//Circle Coordinates
	int x = window.getSize().x / 2;
	int y = window.getSize().y / 2;

	//These variables dictate how fast the circle moves in the x and y directions
	float xVelocity = 3;
	float yVelocity = 3;

	//Flags for key pressed
	bool upFlag = false;
	bool downFlag = false;
	bool leftFlag = false;
	bool rightFlag = false;

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
				default: break;
				}
			}
		}

		// Update coordinates

		//*********UPDATE 02-24-2022****************************************
		//This little bit is needed to make sure the up arrows make the rocket
		//go forward no matter what direction the rocket is facing
		double angleRads = (3.1415926536 / 180) * rocket.getRotation();
		double xAng = CIRCLE_SPEED * sin(angleRads);
		double yAng = CIRCLE_SPEED * -cos(angleRads);
		//if (leftFlag) x -= CIRCLE_SPEED;
		//This rotates the rocket when pressing on the left arrow key.
		//The -2 tells the rocket how many degrees to turn every time the page is refreshed.
		//If you want to make it turn faster then increase the number.
		if (leftFlag) rocket.setRotation(rocket.getRotation() - 2);
		//if (rightFlag) x += CIRCLE_SPEED;
		//This rotates the rocket when pressing on the right arrow key.
		//Same is true for the +2 here.
		if (rightFlag) rocket.setRotation(rocket.getRotation() + 2);
		//if (upFlag) y -= CIRCLE_SPEED;
		//This makes sure that the rocket goes forward using the calculated x and y
		//angles from above.
		if (upFlag) x += xAng, y += yAng;
		//if (downFlag) y += CIRCLE_SPEED;
		//This makes sure that the rocket goes backwards using the calculated x and y
		//angles from above.
		if (downFlag) x -= xAng, y -= yAng;
		//*********************************************************************

		//***********************UPDATE 2.24.22 TSA ***************************
		// Set screen boundries, If spaceship reaches certain point, wrap spaceship
		// to other side of the screen
		if (x < 0) x = W;
		if (x > W) x = 0;
		if (y < 0) y = H;
		if (y > H) y = 0;
		//*****************************************************************
		 


		//********************3/10/2022 Update TSA **************************************************

		//move asteroid
		//asteroid creator
		if(asteroidspawn < 15)
			asteroidspawn++;
		// Set a limit onhow many asteroids there can be on the screen at one time
		if (asteroidspawn >= 15)
		{
			asteroids.push_back(asteroid(&asteroidTexture, window.getSize()));
			asteroidspawn = 0; //reset count
		}
		//The movement of the asteroids
		// erase asteroids if they reach a certain edge of the screen.
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			asteroids[i].shape.move(-2.f, 0.f);

			if (asteroids[i].shape.getPosition().x <= 0 - asteroids[i].shape.getGlobalBounds().width)
				asteroids.erase(asteroids.begin() + i);

			if (asteroids[i].shape.getGlobalBounds().intersects(rocket.getGlobalBounds()))
				asteroids.erase(asteroids.begin() + i);
		}

		//*******************************************************************************************
	
		//The params for window.clear() are just to change the color to a dark grey...
		//Totally useless and can just be left blank if desired.
		window.clear(sf::Color(40, 40, 40));

		//draw player/rocket
		window.draw(rocket);
		rocket.setPosition(x, y);

		//********************3/10/2022 Update TSA **************************************************
		//draw asteroids
		// uses for loop to constantly spawn asteroids based on how many there are.
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			window.draw(asteroids[i].shape);
		}

		//********************************************************************************************
		//circle.setPosition(x, y);
		//window.draw(circle);

		window.display();
	}
	return 0;
}