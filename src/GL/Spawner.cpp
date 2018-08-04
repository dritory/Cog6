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
	if ( usedMobs.size() < entityLimit ) {
		sf::Time waveTime = waveClock.getElapsedTime();
		if ( waveTime.asSeconds() > waveInterval ) {
			sf::Time time = spawnerClock.getElapsedTime();

			if ( time.asMilliseconds() > spawnInterval ) {
				int width = (Game::instance().getTileSystem().getWidth_world());
				int z = std::rand() % width;
				int d = std::rand() % 4;
				switch (d)
				{
				case 0:
					spawn<EntityMob>(0, 32, z);
					break;
				case 1:
					spawn<EntityMob>(z, 32, 0);
					break;
				case 2:
					spawn<EntityMob>(z, 32, width -32);
					break;
				default:
					spawn<EntityMob>(width - 32, 32, z);
					break;
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
