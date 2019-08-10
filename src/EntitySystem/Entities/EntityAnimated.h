#pragma once
#include "../Entity.h"


enum Direction {

	South,
	Southwest,
	West,
	Northwest,
	North,
	Northeast,
	East,
	Southeast,
};



struct Animation {
	int framecount = 1;
	int framewidth = 32;
	int frameheight = 32;
	int frametime = 0; //milliseconds
	int startx = 0;
	int starty = 0;
	bool loop = true;
	bool directional = false; //indicates that there are 8 similar animations
	void setFrameTime(int FPS) {
		frametime = (int) (1000 / FPS);
	}
	bool operator== (const Animation &b) {
		if ( framecount == b.framecount &&
			framewidth == b.framewidth &&
			frameheight == b.frameheight &&
			startx == b.startx &&
			starty == b.starty &&
			loop == b.loop &&
			directional == b.directional ) {
			return true;
		}
		return false;
	};
};

class EntityAnimated : public Entity {
public:

	EntityAnimated(EntitySystem* system, const EntityId& id);
	~EntityAnimated();

	virtual void pushState(ObjectState &state);

	void playAnimation(const Animation &animation);

	void resetAnimation();

	void SetVelocity(const sf::Vector3f &velocity);

protected:


	Direction direction = North;

	int frame = 0;


	sf::Vector3f velocity;



	sf::Vector2i getTilePos();

	virtual void FixedUpdate(sf::Time elapsed);

	virtual void Reset();

	virtual void Update() override;

	virtual void Load(const std::string& spriteLocation);

	std::string GetSpriteLocation() override { return "mob.png"; }

private:
	Animation currentAnimation{ 1,32,32,0,0,0 };
	Animation lastAnimation;
	Animation defaultAnimation{ 1,32,32,0,0,0 };

	sf::Clock animationClock;
};

