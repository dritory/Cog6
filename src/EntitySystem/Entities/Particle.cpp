#include "Particle.h"
#include "../../PlayState.h"
Particle::Particle(EntitySystem * system, const EntityId & id) : EntityAnimated(system, id)
{

}

Particle::~Particle()
{
}

void Particle::ToggleGravity(bool gravity)
{
	this->gravity = gravity;
}

void Particle::ToggleCollision(bool collision)
{
	this->collision = collision;
}

void Particle::Load(const std::string & spriteLocation)
{
	playAnimation(animation);
	EntityAnimated::Load(spriteLocation);
}

void Particle::FixedUpdate(sf::Time elapsed)
{
	if ( gravity ) {
		float g = 40.0f;
		if ( collision ) {
			sf::Vector3f pos = GetPosition();
			float lowestPoint = pos.y - (getSprite().getGlobalBounds().height);
			bool collide = !Game::Instance()->tileSystem->canWalkHere(pos.x,
				(lowestPoint), pos.z) || lowestPoint <= 32.0f;
			//bool collide = ;
			if (!collide){
				velocity.y -= g;
			}
			else {
				
				velocity.y = 0;
				velocity.x = 0;
				velocity.z = 0;

				SetPosition(sf::Vector3f((pos.x), 32.0f* (int) (pos.y / 32), pos.z));

			}
		}
		else {
			velocity.y -= g;
		}
	}

	EntityAnimated::FixedUpdate(elapsed);
}

void Particle::Reset()
{
}



void Particle::Update()
{
	EntityAnimated::Update();
}
