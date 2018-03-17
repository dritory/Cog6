#include "src/Game.h"
#include <memory>

int main()
{
	Game& game = Game::instance();
	game.Start();
	
	return 0;
}