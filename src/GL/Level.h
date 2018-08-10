
#include "..\PlayState.h"
#include "Spawner.h"

class Level {
public:
	Level();
	
	~Level();
private:
	Game * game;

	Spawner spawner;

};

