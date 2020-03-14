#pragma once
#include "gameEngine.h"
#include "TileSystem\TileSystem.h"
#include "Gui\PlayGui.h"
#include "Gui\PausedGui.h"
#include "FastNoise.h"
#include "GL\Player.h"
#include "GL\RangeHelper.h"
#include "GL\Spawner.h"
#include "Camera.h"
#include <eventbus/EventBus.h>



class RangeHelper;
class Spawner;
class TileSystem;
class Player;
class PlayState : public GameState {
public:


	void Init();
	void Unload();

	void Pause();
	void Resume();

	void Freeze() {
		freezed = true;
	}
	void Unfreeze() {
		freezed = false;
	}
	void ToggleFreeze() {
		freezed = !freezed;
	}

	int getFPS();
	int getFFPS();


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
	PlayGui *gui;
	PausedGui *pausedGui;

	Dexode::EventBus *bus;

protected:
	PlayState() {}

private:

	sf::Clock gameClock;
	sf::Clock fixedClock;

	sf::Clock fclock;
	sf::Clock ffclock;
	bool drawn;
	bool freezed = false;
	bool paused = false;

	int FPS;
	int FFPS;
	int frames;
	int fframes;

	int accumulator = 0;
	int dt = (int)(1000.0f*(1.0f / 30.0f)); // Modify this to change physics rate. 
};


typedef PlayState Game;