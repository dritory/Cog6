#include "Spawner.h"

#include "../EntitySystem/Entities/EntityMob.h"

Spawner::Spawner() {
}


Spawner::~Spawner() {
}

void Spawner::update(sf::Time elapsed) {

	for (auto p = mobpool.begin(); p != mobpool.end(); p++) {
		if (! (*p)->isAlive()) {
			Game::instance().getEntitySystem().DeactivateEntity(*p);
			unusedMobs.push_back(*p);
		}
	}

	sf::Time waveTime = waveClock.getElapsedTime();
	if (waveTime.asSeconds() > waveInterval) {
		sf::Time time = spawnerClock.getElapsedTime();

		if (time.asMilliseconds() > spawnInterval) {

			int z = std::rand() % (Game::instance().getTileSystem().getWidth_world());

			spawn<EntityMob>(0, 32, z);
			spawnerClock.restart();
		}
		if (waveTime.asSeconds() > waveInterval + waveDuration) {
			spawnInterval *= 0.8f;
			waveDuration *= 1.2f;
			waveInterval *= 0.8f;
			waveClock.restart();
		}
	}
}
