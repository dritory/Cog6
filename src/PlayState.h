#pragma once
#include "gamestate.h"
#include "TileSystem\TileSystem.h"
#include "Gui\Gui.h"
#include "FastNoise.h"
#include "GL\Player.h"
#include "GL\RangeHelper.h"
#include "GL\Spawner.h"
#include "Camera.h"

class RangeHelper;
class Spawner;
class TileSystem;
class Player;
class PlayState : public GameState
{
public:


	void Init();
	void Unload();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game, sf::Event event);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static PlayState* Instance() {
		static PlayState instance;
		return &instance;
	}

	const sf::RenderWindow& getWindow();

	Player *player;
	EntitySystem *entitysystem;
	FastNoise *fastnoise;
	TileSystem *tileSystem;
	Spawner *spawner;
	RangeHelper *rangehelper;
	SpriteBatch *batcher;
	Camera *camera;

protected:
	PlayState() { }

private:
	
	sf::Clock gameClock;
	sf::Clock fixedClock;
	bool drawn;
	int accumulator = 0;
	int dt = (int) (1000.0f*(1.0f / 30.0f)); // Modify this to change physics rate. 
};

typedef PlayState Game;
