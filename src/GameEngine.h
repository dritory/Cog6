#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
//Pure abstract class 
class GameState;

class GameEngine {

public:
	~GameEngine();

	void Init();
	void Unload();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	static GameEngine *Instance();

	sf::RenderWindow *window;

private:

	// the stack of states
	std::vector<GameState*> states;

	bool m_running;

};
class GameState
{
public:
	virtual void Init() = 0;
	virtual void Unload() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameEngine* game, sf::Event event) = 0;
	virtual void Update(GameEngine* game) = 0;
	virtual void Draw(GameEngine* game) = 0;

	void ChangeState(GameEngine* game, GameState* state) {
		game->ChangeState(state);
	}

protected:
	GameState() { }
};