#include "Spawner.h"

Spawner::Spawner() {

}


Spawner::~Spawner() {
}

void Spawner::update(sf::Time elapsed) {

	for (auto p = usedMobs.begin(); p != usedMobs.end();) {
		if (! (*p)->isAlive()) {


			(*p)->getValue();

			(*p)->Reset();
			Game::Instance()->entitysystem->DeactivateEntity(*p);
			unusedMobs.push_back(*p);
			p = usedMobs.erase(p);
		}
		else
		{
			p++;
		}
	}
	if ( usedMobs.size() < entityLimit && Game::Instance()->tileSystem->pathfinder->isValid()) {
		sf::Time waveTime = waveClock.getElapsedTime();

		if ( waveTime.asSeconds() > waveInterval ) {
			sf::Time time = spawnerClock.getElapsedTime();
			
			if ( time.asMilliseconds() > spawnInterval ) {

				
				bool spawned = false;
				int tries = 0;
				while ( !spawned && tries < 100) { //try to spawn

					int width = (Game::Instance()->tileSystem->getWidth_world());
					int r = std::rand() % width;
					int d = std::rand() % 4;
					int x, z;
					switch ( d )
					{
					case 0:
						x = 0;
						z = r;
						break;
					case 1:
						x = r;
						z = 0;
						break;
					case 2:
						x = r;
						z = width - 32;
						break;
					default:
						x = width - 32;
						z = r;
						break;
					}


					int type = rand() % (2);
				

					switch ( type ) {
					case 1:
						spawned = spawn(tank, x, 32, z);
						break;
					case 0:
					default:
						spawned = spawn(fodder, x, 32, z);
						break;
					}

					tries++;
				}
				spawnerClock.restart();
				
			}
			if ( waveTime.asSeconds() > waveInterval + waveDuration ) {
				startNextWave();
			}
		}
	}




}

void Spawner::startNextWave()
{
	spawnInterval *= 0.9f;
	waveDuration *= 1.1f;
	waveInterval *= 0.9f;
	waveClock.restart();
	wave++;

	tank.count = 0;
	fodder.count = 0;
}

void Spawner::load()
{
	usedMobs.clear();
	unusedMobs.clear();
	mobpool.clear();
	wave = 0;
}
