#include "Game.h"
#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include "EntitySystem/EntitySystem.h"
#include "EntitySystem/Entities/EntityWall.h"
#include "EntitySystem/Entities/EntityMob.h"
#include "EntitySystem/Entities/EntityDummy.h"
#include "Rendering/SpriteBatch.h"
#include "AssetLoader/AssetLoader.h"

#include <sol.hpp>
#include "Camera.h"
#include "GL\Level.h"
#include <cstdlib>
Game::Game()
{
	std::srand(std::time(0));

	int seed = std::rand();
	
	fastnoise = new FastNoise(seed);
	tileSystem = new TileSystem(64, 10);
}


Game::~Game()
{
	delete tileSystem;
	tileSystem = nullptr;

	delete fastnoise;
	fastnoise = nullptr;

}



void Game::Start()
{
	window.create(sf::VideoMode(1200, 800),
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
	text2.setPosition(50, 100);
	text2.setString(str);

	Level level; //current test level

	tileSystem->load();
  
	for (int x = 0; x < 32*32; x += 64)
		for (int z = 0; z < 32*32; z += 64)
		{
				Entity* ent;
			ent = es.Add<EntityMob>();
			ent->SetPosition(sf::Vector3f((float)x, 32, (float)z));
		}
		
	SpriteBatch batcher;
	es.SetBatcher(batcher);

	sf::Clock clock;
	float lastTime = 0;
	int frames = 0;
	
	sf::Clock guiClock;

	bool pressed = false;
	

	Camera camera(sf::FloatRect(150,150, 1200, 800));
	

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
			
			
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}
		
		
		//Updates
		//----------------------------------------//

		window.clear();
		//sets view to cameras view
		window.setView(camera.view);

		
		es.Update();
		camera.update();
		player.Update();
		//--------------------------//



		//Rendering

		//----------------------------------------//
		
		// Draw world
		tileSystem->draw(batcher);
		
		//Draw entity system
		window.draw(es);
		batcher.SetDirty();
		batcher.prepareDraw();
		window.draw(batcher);

		//resets the view so that UI is fixed in the window
		window.setView(window.getDefaultView());
		// Draw UI
		text2.setString(std::to_string(batcher.getQueued()));
		window.draw(text2);
		window.draw(text);

		window.display();

		//--------------------------//

		tileSystem->LateUpdate();
		
	}

}

const sf::RenderWindow & Game::getWindow()
{
	return this->window;
}

EntitySystem & Game::getEntitySystem()
{
	return es;
}

TileSystem & Game::getTileSystem() {
	return *tileSystem;
}

FastNoise & Game::getNoiseGen() {
	return *fastnoise;
}

Player & Game::getPlayer()
{
	return player;
}


