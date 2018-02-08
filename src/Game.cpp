#include "Game.h"

#include <sol.hpp>
#include "Camera.h"
Game::Game()
{
}


Game::~Game()
{
}

void Game::Start()
{
	window.create(sf::VideoMode(800, 600),
		"Hello SFML", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3));

	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/SegoeUI.ttf");

	sf::Text text;
	text.setFont(font);
	text.setPosition(200, 200);
	text.setString("@");

	sol::state lua;
	lua.set_function("getString", [] { return "Hello from luajit"; });
	auto result = lua.script("return getString()");

	const std::string str = result;

	sf::Text text2;
	text2.setFont(font);
	text2.setPosition(200, 250);
	text2.setString(str);

	tileSystem.load();

	Camera camera(sf::FloatRect(150,150, 800, 600));
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		camera.update();

		window.clear();
		window.draw(text2);
		
		window.setView(camera.view);

		tileSystem.draw(window);
		window.draw(text);

		window.display();
	}

}

const sf::RenderWindow & Game::getWindow()
{
	return this->window;
}
