#include "GameEngine.h"

GameEngine::~GameEngine()
{
	
}
void GameEngine::Init()
{
	m_running = true;
	window = new sf::RenderWindow();

	window->create(sf::VideoMode(1200, 800),
		"Hello SFML", sf::Style::Default);
	window->setFramerateLimit(60);
}

void GameEngine::Unload()
{
	// unload the all states
	while ( !states.empty() ) {
		states.back()->Unload();
		states.pop_back();
	}
	delete window;
}

void GameEngine::ChangeState(GameState * state)
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Unload();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PushState(GameState * state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Unload();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}

void GameEngine::HandleEvents()
{

	sf::Event event;
	while ( window->pollEvent(event) ) {

		states.back()->HandleEvents(this, event);
	}
}

void GameEngine::Update()
{

	window->clear();
	states.back()->Update(this);

	
}

void GameEngine::Draw()
{
	// let the state draw the screen
	states.back()->Draw(this);
	window->display();
}

GameEngine * GameEngine::Instance()
{
	static GameEngine engine;
	return &engine;
}

