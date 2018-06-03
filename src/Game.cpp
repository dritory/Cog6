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

/* cereal
#include <cereal\cereal.hpp>
#include <cereal/archives/binary.hpp>
*/
Game::Game() {
	std::srand(std::time(0));

	int seed = std::rand();

	fastnoise = new FastNoise(seed);
	tileSystem = new TileSystem(128, 10);
	spawner = new Spawner();
}


Game::~Game() {
	delete tileSystem;
	tileSystem = nullptr;

	delete fastnoise;
	fastnoise = nullptr;

}



void Game::Start() {
	window.create(sf::VideoMode(1200, 800),
		"Hello SFML", sf::Style::Default);

	window.setFramerateLimit(60);

	bool loaded = AssetLoader<sf::Font>::GetInstance().LoadAsset("C:/Windows/Fonts/SegoeUI.ttf");
	if (!loaded) {
		std::cout << "Could not load font" << std::endl;
		return;
	}
	sf::Font& font = *AssetLoader<sf::Font>::GetInstance().Get("C:/Windows/Fonts/SegoeUI.ttf");

	sf::Text text;
	text.setFont(font);
	text.setPosition(50, 50);

	sol::state lua;
	lua.set_function("getString", [] { return "Hello from luajit"; });
	auto result = lua.script("return getString()");

	const std::string str = result;

	sf::Text text2;
	text2.setFont(font);
	text2.setPosition(50, 80);
	text2.setString(str);

	sf::Text text3;
	text3.setFont(font);
	text3.setPosition(800, 50);

	sf::Text text4;
	text4.setFont(font);
	text4.setPosition(800, 80);

	Level level; //current test level

	tileSystem->load();



	SpriteBatch batcher;
	es.SetBatcher(batcher);

	sf::Clock fpsclock;
	float lastTime = 0;
	int frames = 0;

	sf::Clock gameClock;
	sf::Clock fixedClock;
	bool pressed = false;


	Camera camera(sf::FloatRect(150, 150, 1200, 800));

	//milliseconds
	int dt = (int) (1000.0f*(1.0f / 30.0f )); // Modify this to change physics rate. 
	int accumulator = 0;



	while (window.isOpen()) {


		

		sf::Event event;
		while (window.pollEvent(event)) {


			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}



		window.clear();
		//sets view to cameras view
		window.setView(camera.view);


		accumulator += gameClock.getElapsedTime().asMilliseconds();
		
		while (accumulator >= dt) {
			
			sf::Time elapsed = fixedClock.restart();

			if (fpsclock.getElapsedTime().asSeconds() >= 0.2f) {
			sf::Time currentTime = fpsclock.restart();
			float fps = frames / currentTime.asSeconds();
			text.setString(std::to_string(fps));
			frames = 0;
		}
		++frames;

			//fixed update calls
			//----------------------------------------//


			player.Update(elapsed);
			
			es.FixedUpdate(elapsed);
			spawner->update(elapsed);
			//--------------------------//


			accumulator -= dt;



		}
		sf::Time elapsed = gameClock.restart();
		//Unfixed update calls, running at fps
		//----------------------------------------//
		
		es.Update(elapsed);
		camera.update(elapsed);

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



		es.drawGUI(window);
		//resets the view so that UI is fixed in the window
		window.setView(window.getDefaultView());
		// Draw UI


		text2.setString(std::to_string(batcher.getQueued()));
		text3.setString("TrMut: " + std::to_string(player.getTM()));
		text4.setString("Power: " + std::to_string(player.getPowerEfficienty()) + "%");



		window.draw(text2);
		window.draw(text);
		window.draw(text3);

		window.draw(text4);
		window.display();

		//--------------------------//

		tileSystem->LateUpdate();

	}

}

const sf::RenderWindow & Game::getWindow() {
	return this->window;
}

EntitySystem & Game::getEntitySystem() {
	return es;
}

TileSystem & Game::getTileSystem() {
	return *tileSystem;
}

FastNoise & Game::getNoiseGen() {
	return *fastnoise;
}

Player & Game::getPlayer() {
	return player;
}

Spawner & Game::getSpawner() {
	return *spawner;
}


