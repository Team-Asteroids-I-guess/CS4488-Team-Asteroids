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
#include <vector>
#include <math.h>


#define ROCKET_SPEED 5

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
	asteroid(sf::Texture* texture, sf::Vector2u windowSize)
	{
		//set tecture of asteroid
		this->shape.setTexture(*texture);
		//set size of asteroid
		this->shape.setScale(0.2f, 0.2f);

		//Set spawn position of asteroid, using random y axis number
		this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % windowSize.y - this->shape.getGlobalBounds().height);

	}
	~asteroid() {}
};

//*********************************************************************************************

class Bullet
{
public:
	sf::CircleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;

	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(sf::Color::Red);
	}
};




int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Title");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock Clock;
	float elapsed;
	

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
	//***********
	sf::Vector2f rocketPosition(window.getSize().x / 2, window.getSize().y / 2);

	rocket.setPosition(rocketPosition);

	//Thrust
	int dx = 0;
	int dy = 0;



	//**********************************************************************************

	//********************3/10/2022 Update TSA **************************************************

	//implement texture for asteroids
	int asteroidspawn = 0;
	sf::Texture asteroidTexture;
	asteroidTexture.loadFromFile("rock.png");

	//Create asteroid from class
	vector<asteroid> asteroids;

	//********************************************************************************************
	
	//Bullets
	Bullet b1;
	std::vector<Bullet> bullets;


	//Vectors
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	float Sqt = 0;

	//*********UPDATE 02-24-2022****************************************

	//Flags for key pressed
	bool upFlag = false;
	bool downFlag = false;
	bool leftFlag = false;
	bool rightFlag = false;
	//bool spaceFlag = false;

	while (window.isOpen()) 
	{
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
				//case sf::Keyboard::Space: spaceFlag = true; break;
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
				//case sf::Keyboard::Space: spaceFlag = false; break;
				default: break;
				}
			}
		}

		//updating vectors for shooting
		playerCenter = sf::Vector2f(rocket.getPosition());
		mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		Sqt = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		aimDirNorm = aimDir / Sqt;

		float PI = 3.14159265f;
		float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
		// Update coordinates

		//*********UPDATE 02-24-2022****************************************
		//This little bit is needed to make sure the up arrows make the rocket
		//go forward no matter what direction the rocket is facing
		double angleRads = (3.1415926536 / 180) * rocket.getRotation();
		double xAng = ROCKET_SPEED * sin(angleRads);
		double yAng = ROCKET_SPEED * -cos(angleRads);
		elapsed = Clock.getElapsedTime().asSeconds();
		Clock.restart();

		//This rotates the rocket when pressing on the left arrow key.
		//The -2 tells the rocket how many degrees to turn every time the page is refreshed.
		//If you want to make it turn faster then increase the number.
		if (leftFlag)
		{
			rocket.setRotation(rocket.getRotation() - (200.0f * elapsed));
		}
		
		//This rotates the rocket when pressing on the right arrow key.
		//Same is true for the +2 here.
		if (rightFlag)
		{
			rocket.setRotation(rocket.getRotation() + (200.0f * elapsed));
		}
	
		//This makes sure that the rocket goes forward using the calculated x and y
		//angles from above.
		//Thrust
		if (upFlag) 
		{
			dx += sin(angleRads) * 200.0f * elapsed;
			dy += -cos(angleRads) * 200.0f * elapsed;
		}

			rocketPosition.x += dx * elapsed;
			rocketPosition.y += dy * elapsed;
		rocket.setPosition(rocketPosition);



		//*********************************************************************

		//***********************UPDATE 2.24.22 TSA ***************************
		// Set screen boundries, If spaceship reaches certain point, wrap spaceship
		// to other side of the screen
		
		if (rocketPosition.x > window.getSize().x)
			rocketPosition.x = 0;
		if (rocketPosition.x < 0) 
			rocketPosition.x = window.getSize().x;
		if (rocketPosition.y < 0) 
			rocketPosition.y = window.getSize().y;
		if (rocketPosition.y > window.getSize().y)
			rocketPosition.y = 0;
		//*****************************************************************


		//********************3/10/2022 Update TSA **************************************************

		//move asteroid
		//asteroid creator
		if (asteroidspawn < 40)
			asteroidspawn++;
		// Set how fast asteroids are created
		if (asteroidspawn >= 40)
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

			//collision with Rocket
			if (asteroids[i].shape.getGlobalBounds().intersects(rocket.getGlobalBounds()))
				asteroids.erase(asteroids.begin() + i);
				
				
		}

		//*******************************************************************************************

		
		//Shooting
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			b1.shape.setPosition(playerCenter);
			b1.currVelocity = aimDirNorm * b1.maxSpeed;

			bullets.push_back(Bullet(b1));
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].shape.move(bullets[i].currVelocity);

			//Out of bounds
			if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
				|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
			{
				bullets.erase(bullets.begin() + i);

				
			}
			else
			{
				//asteroid collision
				for (size_t k = 0; k < asteroids.size(); k++)
				{
					if (bullets[i].shape.getGlobalBounds().intersects(asteroids[k].shape.getGlobalBounds()))
					{
						bullets.erase(bullets.begin() + i);
						asteroids.erase(asteroids.begin() + k);
						break;
					}
				}
			}
		}
		

	




		//The params for window.clear() are just to change the color to a dark grey...
		//Totally useless and can just be left blank if desired.
		window.clear(sf::Color(40, 40, 40));

		//draw player/rocket
		window.draw(rocket);
		//rocket.setPosition(x, y);

		//********************3/10/2022 Update TSA **************************************************
		//draw asteroids
		// uses for loop to constantly spawn asteroids based on how many there are.
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			window.draw(asteroids[i].shape);
		}

		//********************************************************************************************
		for (size_t i = 0; i < bullets.size(); i++)
					{
						window.draw(bullets[i].shape);
					}

		window.display();
	}
	return 0;
}