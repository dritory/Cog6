#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
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