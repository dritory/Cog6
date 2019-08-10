#include "GuiObject.h"
#include "../PlayState.h"


GuiObject::GuiObject()
{
}

GuiObject::GuiObject(sf::Vector2f position)
{
	this->position = position;
}

GuiObject::~GuiObject()
{
}



void GuiObject::SetPosition(const sf::Vector2f & position)
{
}

bool GuiObject::inBounds(const sf::Vector2f & pos)
{
	if ( sentered ) {


		return (pos.x > position.x - size.x / 2 &&
			pos.x < position.x + size.x / 2 &&
			pos.y > position.y - size.y / 2 &&
			pos.y < position.y + size.y / 2);
	}
	else {
		return (pos.x > position.x &&
			pos.x < position.x + size.x &&
			pos.y > position.y &&
			pos.y < position.y + size.y);
	}
}

bool GuiObject::inBounds(int x, int y)
{
	return inBounds(sf::Vector2f(x, y));
}

bool GuiObject::inBounds(float x, float y)
{
	return inBounds(sf::Vector2f(x, y));
}

bool GuiObject::inBounds(const sf::Vector2i & position)
{
	return inBounds(sf::Vector2f(position.x, position.y));
}

void GuiObject::update(sf::Event & e, sf::RenderWindow & window)
{
	sf::Vector2f mousepos = Game::Instance()->getWindow().mapPixelToCoords(sf::Mouse::getPosition(Game::Instance()->getWindow()));
	
	if ( e.type == sf::Event::MouseMoved ) {

		if ( inBounds(mousepos) ) {
			state = HOVER;
			hover = true;
		}
		else {
			pressed = false;
			hover = false;
			state = NORMAL;
		}

	}
	if ( e.type == sf::Event::MouseButtonPressed )
	{
		switch ( e.mouseButton.button )
		{
		case sf::Mouse::Left:
		{
			if ( inBounds(mousepos) )
			{
				state = CLICKED;
				pressed = true;
			}
			else
			{
				pressed = false;
			}
		}
		break;
		}
	}

	if ( e.type == sf::Event::MouseButtonReleased )
	{
		switch ( e.mouseButton.button )
		{
		case sf::Mouse::Left:
		{
			pressed = false;

			if ( inBounds(mousepos) )
			{
				state = HOVER;
			}
			else
			{
				state = NORMAL;
			}
		}
		}
	}
	
}

void GuiObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

int GuiObject::getState()
{
	return state;
}
