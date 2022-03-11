#include <SFML/Graphics.hpp>
#include "MainPage.h"

using namespace sf;

void main()
{
	RenderWindow MENU(VideoMode(960, 720), "Main Menu", Style::Default);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	RectangleShape background;
	background.setSize(Vector2f(960, 720));
	Texture Maintexture;
	Maintexture.loadFromFile("Background/A4.jpg");
	background.setTexture(&Maintexture);

	RectangleShape NGbackground;
	NGbackground.setSize(Vector2f(960, 720));
	Texture back_texture;
	back_texture.loadFromFile("Background/A1.jpg");
	NGbackground.setTexture(&back_texture);

	RectangleShape OPbackground;
	OPbackground.setSize(Vector2f(960, 720));
	Texture OPTIONStexture;
	OPTIONStexture.loadFromFile("Background/A3.jpg");
	OPbackground.setTexture(&OPTIONStexture);

	RectangleShape INFObackground;
	INFObackground.setSize(Vector2f(960, 720));
	Texture INFOtexture;
	INFOtexture.loadFromFile("Background/A3.jpg");
	INFObackground.setTexture(&INFOtexture);

	while (MENU.isOpen())
	{
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MENU.close();
			}

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return) {
					RenderWindow New_Game(VideoMode(960, 720), "New Game");
					RenderWindow OPTIONS(VideoMode(960, 720), "OPTIONS");
					RenderWindow INFO(VideoMode(960, 720), "INFO");

					int x = mainMenu.MainMenuPressed();
					if (x == 0)
					{
						while (New_Game.isOpen())
						{
							Event aevent;
							while (New_Game.pollEvent(aevent)) {
								if (aevent.type == Event::Closed)
								{
									New_Game.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										New_Game.close();
									}
								}
							}
							OPTIONS.close();
							INFO.close();
							New_Game.clear();
							New_Game.draw(NGbackground);
							New_Game.display();
						}
					}
					if (x == 1)
					{
						while (OPTIONS.isOpen())
						{
							Event aevent;
							while (OPTIONS.pollEvent(aevent)) {
								if (aevent.type == Event::Closed)
								{
									OPTIONS.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										OPTIONS.close();
									}
								}
							}
							New_Game.close();
							OPTIONS.clear();
							OPTIONS.draw(OPbackground);
							INFO.close();

							OPTIONS.display();
						}
					}
					if (x == 2)
					{
						while (INFO.isOpen())
						{
							Event aevent;
							while (INFO.pollEvent(aevent)) {
								if (aevent.type == Event::Closed)
								{
									INFO.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										INFO.close();
									}
								}
							}
							New_Game.close();
							OPTIONS.clear();
							INFO.clear();
							INFO.draw(INFObackground);
							INFO.display();
						}
					}
					if (x == 3)
						MENU.close();
					break;
				}
			}
		}
		MENU.clear();
		MENU.draw(background);
		mainMenu.draw(MENU);
		MENU.display();
	}
}