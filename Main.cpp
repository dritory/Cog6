#include "src/Game.h"
#include "src/GameEngine.h"
#include "src//PlayState.h"
int main()
{

	GameEngine *game = GameEngine::Instance();
	game->Init();
	
	game->ChangeState(PlayState::Instance());

	while ( game->Running() ) {

		game->HandleEvents();
		game->Update();
		game->Draw();
	}

	game->Unload();

	return 0;
}