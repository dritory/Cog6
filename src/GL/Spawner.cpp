#include "Spawner.h"

#include "../EntitySystem/Entities/EntityMob.h"

Spawner::Spawner() {
}


Spawner::~Spawner() {
}

void Spawner::update(sf::Time elapsed) {

	for (auto p = usedMobs.begin(); p != usedMobs.end();) {
		if (! (*p)->isAlive()) {
			(*p)->Reset();
			Game::instance().getEntitySystem().DeactivateEntity(*p);
			unusedMobs.push_back(*p);
			p = usedMobs.erase(p);
		}
		else
		{
			p++;
		}
	}
	if ( usedMobs.size() < entityLimit && Game::instance().getTileSystem().pathfinder->isValid()) {
		sf::Time waveTime = waveClock.getElapsedTime();
		if ( waveTime.asSeconds() > waveInterval ) {
			sf::Time time = spawnerClock.getElapsedTime();

			if ( time.asMilliseconds() > spawnInterval ) {
				bool spawned = false;
				int tries = 0;
				while ( !spawned && tries < 100) {
					int width = (Game::instance().getTileSystem().getWidth_world());
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
					spawned = spawn<EntityMob>(x, 32, z);
					tries++;
				}
				spawnerClock.restart();
			}
			if ( waveTime.asSeconds() > waveInterval + waveDuration ) {
				spawnInterval *= 0.9f;
				waveDuration *= 1.1f;
				waveInterval *= 0.9f;
				waveClock.restart();
			}
		}
	}




}

void Spawner::load()
{
	usedMobs.clear();
	unusedMobs.clear();
	mobpool.clear();
}
