#pragma once
#include "..\Game.h"

class Spawner {
public:
	Spawner();
	~Spawner();


	template <class entity>
	entity * AddToPool() {

		entity * ent = Game::instance().getEntitySystem().Add<entity>();
		mobpool.push_back(ent);
		return ent;
	}
	template <class entity>
	bool RemoveFromPool(entity * ent) {
		mobpool.erase(ent);
	}

	void update(sf::Time elapsed);


private:

	sf::Clock spawnerClock;
	sf::Clock waveClock;

	int waveInterval = 10;//in seconds
	int waveDuration = 5;//in seconds
	int spawnInterval = 500; //in milliseconds

	template <class TYPE>
	//isocoords
	void spawn(int x, int y, int z) {

		for (auto p = unusedMobs.begin(); p != unusedMobs.end(); p++) {
			TYPE* type = dynamic_cast<TYPE*> (*p);
			if (type != nullptr) { //the mob is of the same type

				Game::instance().getEntitySystem().ActivateEntity(*p);
				(*p)->SetPosition(sf::Vector3f(x, y, z));
				(*p)->SetHealthToMax();
				p = unusedMobs.erase(p);
				return;
			}
		}

		TYPE* entity = AddToPool<TYPE>();
		entity->SetPosition(sf::Vector3f(x, y, z));
		entity->SetHealthToMax();
	}

	std::vector<Entity *> unusedMobs;

	std::vector<Entity *> mobpool;
};

