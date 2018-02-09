#include "Game.h"
#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include "EntitySystem/EntitySystem.h"
#include "EntitySystem/Entities/EntityWall.h"
#include "EntitySystem/Entities/EntityDummy.h"
#include "Rendering/SpriteBatch.h"
#include "AssetLoader/AssetLoader.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::Start()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800),
		"Hello SFML", sf::Style::Default);

	window.setFramerateLimit(60);

	bool loaded = AssetLoader<sf::Font>::GetInstance().LoadAsset("C:/Windows/Fonts/SegoeUI.ttf");
	if(!loaded)
	{
		std::cout << "Could not load font" << std::endl;
		return;
	}
	sf::Font& font= *AssetLoader<sf::Font>::GetInstance().Get("C:/Windows/Fonts/SegoeUI.ttf");

	sf::Text text;
	text.setFont(font);
	text.setPosition(50, 50);

	sol::state lua;
	lua.set_function("getString", [] { return "Hello from luajit"; });
	auto result = lua.script("return getString()");

	const std::string str = result;

	sf::Text text2;
	text2.setFont(font);
	text2.setPosition(200, 250);
	text2.setString(str);

	EntitySystem es;

	for (int x = 0; x < 640; x += 32)
		for (int z = 0; z < 640; z += 32)
			for (int y = 0; y < 96; y += 32)
		{
			Entity* ent;
			if (y / 32 >= 1)
			{
				if (rand() % 3 == 0) continue;
				ent = es.Add<EntityWall>();
			}
			else
				ent = es.Add<EntityDummy>();
			ent->SetPosition(sf::Vector3f(x + 700.0f, y, z));
		}

	SpriteBatch batcher;
	es.SetBatcher(batcher);

	sf::Clock clock;
	float lastTime = 0;
	int frames = 0;

	bool pressed = false;
	while (window.isOpen())
	{
		if(clock.getElapsedTime().asSeconds() >= 0.2f)
		{
			float currentTime = clock.restart().asSeconds();
			float fps = frames / currentTime;
			text.setString(std::to_string(fps));
			frames = 0;
		}
		++frames;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		es.Update();

		window.clear();
		window.draw(text);
		window.draw(text2);
		window.draw(es);
		window.draw(batcher);
		batcher.SetDirty();
		window.display();
	}

}
