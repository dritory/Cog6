#include "EntityAnimated.h"
#include "..\..\PlayState.h"


EntityAnimated::EntityAnimated(EntitySystem * system, const EntityId & id) : Entity(system, id)
{
	frame = 0;
	//sf::Vector2u texsize = getSprite().getTexture()->getSize();
	//if ( framecount <= 0 )
	//	framecount = 1;
	//framewidth = texsize.x / framecount;
	//frameheight = framewidth; //TODO: fix height calculation


}
EntityAnimated::~EntityAnimated()
{
}

sf::Vector2i EntityAnimated::getTilePos()
{
	return Game::Instance()->tileSystem->isoToTileCoord(GetPosition());
}
void EntityAnimated::FixedUpdate(sf::Time elapsed)
{
	sf::Vector3f deltaS = sf::Vector3f(velocity.x * elapsed.asSeconds(), velocity.y * elapsed.asSeconds(), velocity.z * elapsed.asSeconds());
	SetPosition(GetPosition() + (sf::Vector3f)deltaS);
	Entity::FixedUpdate(elapsed);
}
void EntityAnimated::Reset()
{
	velocity = sf::Vector3f(0, 0, 0);
	SetHealthToMax();
}
void EntityAnimated::Update()
{
	if ( currentAnimation.framecount > 1 && currentAnimation.frametime > 0 ) {
		if ( animationClock.getElapsedTime().asMilliseconds() > currentAnimation.frametime ) {
			if ( frame < currentAnimation.framecount ) {

				int diroffset = 0;
				if ( currentAnimation.directional ) {
					diroffset = currentAnimation.frameheight * direction;
				}

				int x = (frame * currentAnimation.framewidth) % getSprite().getTexture()->getSize().x;
				int y = currentAnimation.starty + diroffset + (currentAnimation.startx + frame * currentAnimation.framewidth) / getSprite().getTexture()->getSize().x;

				setTextureRect(sf::IntRect(x, y, currentAnimation.framewidth, currentAnimation.frameheight));

				frame++;
			}
			else {
				if ( currentAnimation.loop ) {
					frame = 0;
				}
			}
			animationClock.restart();
		}
	}

	if ( velocity.x != 0 ) {
		float angle = atan(velocity.z / velocity.x);

		if ( velocity.x < 0 ) {
			angle = angle + 3.1415f;
		}
		if ( angle < 0 ) {
			angle = angle + 2*3.1415f;
		}

		

		if ( angle < 5.890f ) {

			direction = Northeast;
			
		}
		if ( angle <  5.105f ) {

			direction = North;
		}
		if ( angle <  4.320f ) {

			direction = Northwest;
		}
		if ( angle <   3.534f ) {

			direction = West;
		}
		if ( angle < 2.749f ) {


			direction = Southwest;
		}
		if ( angle < 1.963f ) {


			direction = South;
		}
		if ( angle < 1.178f ) {



			direction = Southeast;
		}
		if ( angle < 0.393 ) {

			direction = East;

		}
	}/*
	else if(velocity.z != 0) {
		if ( velocity.z < 0 ) {
			direction = North;
		}
		else {
			direction = South;
		}

	}*/


	Entity::Update();
	lastAnimation = currentAnimation;
}

void EntityAnimated::Load(const std::string & spriteLocation)
{
	Entity::Load(spriteLocation);
	setTextureRect(sf::IntRect(currentAnimation.startx, currentAnimation.starty, currentAnimation.framewidth, currentAnimation.frameheight));
}

void EntityAnimated::pushState(ObjectState & state)
{
	GameObject::pushState(state);
	if ( state.id == getID() ) {
		velocity.x = state.vx;
		velocity.y = state.vy;
		velocity.z = state.vz;
	}
}

void EntityAnimated::playAnimation(const Animation & animation)
{
	if ( animation.framecount > 1 && animation.frametime > 0 ) {
		if ( !(lastAnimation == animation) ) {
			frame = 0;
		}
		currentAnimation = animation;
	}
}

void EntityAnimated::resetAnimation()
{
	frame = 0;
}

void EntityAnimated::SetVelocity(const sf::Vector3f & velocity)
{
	this->velocity = velocity;
}
