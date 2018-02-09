#pragma once

#include <SFML/Graphics.hpp>
#include "TileSystem\TileSystem.h"


class Game {
public:
	Game();
	~Game();

	void Start();

	const sf::RenderWindow& getWindow();
private:
	sf::RenderWindow window;
	TileSystem tileSystem;
};

