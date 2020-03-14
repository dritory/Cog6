#include "PlayState.h"
#include <yojimbo.h>


void PlayState::Init()
{


	std::srand(std::time(0));

	bus = new Dexode::EventBus();

	int seed = std::rand();
	fastnoise = new FastNoise(seed);
	tileSystem = new TileSystem(100, 10);
	entitysystem = new EntitySystem();
	rangehelper = new RangeHelper(128, 128);
	spawner = new Spawner();
	batcher = new SpriteBatch();
	player = new Player();
	camera = new Camera(sf::FloatRect(150, 150, 1200, 800));
	gui = new PlayGui();
	gui->initialize();

	

	pausedGui = new PausedGui();
	pausedGui->initialize();

	tileSystem->load();
	spawner->load();
	player->load();

	entitysystem->SetBatcher(*batcher);

	gameClock.restart();
	fixedClock.restart();
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
	delete gui;
	delete pausedGui;
	delete bus;
}

void PlayState::Pause()
{
	paused = true;
}

void PlayState::Resume()
{
	paused = false;
}

int PlayState::getFPS()
{
	return FPS;
}

int PlayState::getFFPS()
{
	return FFPS;
}

void PlayState::HandleEvents(GameEngine * game, sf::Event event)
{
	switch ( event.type )
	{
		case sf::Event::Closed:
			game->Quit();
			break;
		case sf::Event::LostFocus:
			Pause();
			break;
		case sf::Event::GainedFocus:
			Resume();
			break;
		default:
			break;
	}

	gui->update(event, *(game->window));


}

void PlayState::Update(GameEngine * game)
{
	game->window->setView(camera->view);

	sf::Time elapsed = gameClock.restart();
	frames++;
	if ( fclock.getElapsedTime().asSeconds() > 1 ) {
		FPS = frames;
		frames = 0;
		fclock.restart();
	}
	
	if ( !paused ) {
		player->Update(elapsed);
		if ( !freezed ) {
			entitysystem->Update(elapsed);
			spawner->update(elapsed);
			rangehelper->Update(elapsed);	
		}
	}

	accumulator += elapsed.asMilliseconds();

	while ( accumulator >= dt ) {
		sf::Time elapsed = fixedClock.restart();
		if (!paused && !freezed) {
			entitysystem->FixedUpdate(elapsed);
		}
		if ( !paused )
			camera->update(elapsed);
		accumulator -= dt;
		fframes++;
		if (ffclock.getElapsedTime().asSeconds() > 1 ) {
			FFPS = fframes;
			fframes = 0;
			ffclock.restart();
		}
	}
	if ( !paused ) {
		entitysystem->CleanupEntities();
	}
}

void PlayState::Draw(GameEngine * game)
{

	sf::Time elapsed = fixedClock.restart();
	
	// Draw world
	tileSystem->draw(*batcher, *(game->window));
	//batcher->QueueObject(&spawner->taint);

	//Draw entity system
	game->window->draw(*entitysystem);
	batcher->SetDirty();
	batcher->prepareDraw();
	game->window->draw(*batcher);
	entitysystem->drawGUI(*(game->window));
	//resets the view to draw the gui
	game->window->setView(game->window->getDefaultView());

	gui->draw(*(game->window));
	if ( paused ) {
		pausedGui->draw(*(game->window));
	}
	if ( !paused )
		tileSystem->LateUpdate();
}

const sf::RenderWindow & PlayState::getWindow()
{
	return *GameEngine::Instance()->window;
}

