#pragma once
#include "./EntityAnimated.h"

class Particle : public EntityAnimated {
public:

	Particle(EntitySystem* system, const EntityId& id);
	~Particle();


	void ToggleGravity(bool gravity);
	void ToggleCollision(bool collision);
protected:

	Animation animation{1,32,32,0,0,0};

	virtual void Load(const std::string& spriteLocation);


	virtual void FixedUpdate(sf::Time elapsed);

	void Reset() override;

	void Update() override;

	std::string GetSpriteLocation() override { return "wall.png"; }

	bool gravity;

	bool collision;
};

