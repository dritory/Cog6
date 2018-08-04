#pragma once

#include <SFML/Graphics.hpp>
#include "TileSystem\TileSystem.h"
#include "Gui\Gui.h"
#include "FastNoise.h"
#include "GL\Player.h"
#include "GL\RangeHelper.h"
#include "GL\Spawner.h"

class RangeHelper;
class Spawner;
class Game {
public:
	Game();
	~Game();
	void Start();

	const sf::RenderWindow& getWindow();

	EntitySystem& getEntitySystem();
	TileSystem& getTileSystem();
	FastNoise& getNoiseGen();
	Spawner& getSpawner();
	Player& getPlayer();
	RangeHelper& getRangeHelper();


	static Game& instance() {
		static Game game;
		return game;
	}

private:

	Player player;
	EntitySystem *es;
	FastNoise *fastnoise;
	sf::RenderWindow window;
	TileSystem *tileSystem;
	Spawner *spawner;
	RangeHelper *rangehelper;


};

