#include "Game.h"
#include <SFML/Graphics.hpp>
#include <sol.hpp>

Game::Game()
{
}


Game::~Game()
{
}

void Game::Start()
{
	sf::RenderWindow window(sf::VideoMode(800, 600),
		"Hello SFML", sf::Style::Default);

	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/SegoeUI.ttf");

	sf::Text text;
	text.setFont(font);
	text.setPosition(200, 200);
	text.setString("Hello World, hello SFML");

	sol::state lua;
	lua.set_function("getString", [] { return "Hello from luajit"; });
	auto result = lua.script("return getString()");

	const std::string str = result;

	sf::Text text2;
	text2.setFont(font);
	text2.setPosition(200, 250);
	text2.setString(str);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(text);
		window.draw(text2);
		window.display();
	}

}
