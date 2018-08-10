#include "PlayState.h"



void PlayState::Init()
{


	std::srand(std::time(0));

	int seed = std::rand();
	fastnoise = new FastNoise(seed);
	tileSystem = new TileSystem(128, 10);
	entitysystem = new EntitySystem();
	rangehelper = new RangeHelper(128, 128);
	spawner = new Spawner();
	batcher = new SpriteBatch();
	player = new Player();
	camera = new Camera(sf::FloatRect(150, 150, 1200, 800));

	

	tileSystem->load();
	spawner->load();
	player->load();

	entitysystem->SetBatcher(*batcher);

	gameClock.restart();
}

void PlayState::Unload()
{
	
	delete spawner;
	delete entitysystem;
	delete player;
	delete tileSystem;
	delete fastnoise;
	delete rangehelper;
	delete batcher;
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::HandleEvents(GameEngine * game, sf::Event event)
{
	if ( event.type == sf::Event::Closed ) {
		game->Quit();
	}
}

void PlayState::Update(GameEngine * game)
{
	game->window->setView(camera->view);
	
	accumulator += gameClock.getElapsedTime().asMilliseconds();
	
	while ( accumulator >= dt ) {
		sf::Time elapsed = gameClock.restart();
		player->Update(elapsed);
		entitysystem->Update(elapsed);
		spawner->update(elapsed);
		rangehelper->Update(elapsed);
		
		accumulator -= dt;
	}

	drawn = false;
}

void PlayState::Draw(GameEngine * game)
{
	if ( drawn ) {
		sf::sleep(sf::seconds(0.03f));
	}
	else {

		sf::Time elapsed = fixedClock.restart();
		entitysystem->FixedUpdate(elapsed);
		camera->update(elapsed);
		// Draw world
		tileSystem->draw(*batcher);

		//Draw entity system
		game->window->draw(*entitysystem);
		batcher->SetDirty();
		batcher->prepareDraw();
		game->window->draw(*batcher);
		entitysystem->drawGUI(*(game->window));

		tileSystem->LateUpdate();
		drawn = true;
	}
}

const sf::RenderWindow & PlayState::getWindow()
{
	return *GameEngine::Instance()->window;
}
