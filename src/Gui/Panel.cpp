#include "Panel.h"

Panel::Panel()
{
}

Panel::Panel(const sf::String & s, sf::Font & font, sf::Vector2f position)
{
	objects = std::vector<GuiObject>();
}

Panel::~Panel()
{
	
}


bool Panel::update(sf::Event & e, sf::RenderWindow & window)
{
	for ( GuiObject o : objects )
	{
		if ( !o.update(e, window) ) {
			return false;
		}
	}
	return true;
}

void Panel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for ( GuiObject o : objects ) {
		target.draw(o);
	}
}

bool Panel::isMouseOverGUI()
{
	for ( auto o : objects ) {
		if ( o.isMouseOverGUI() ) {
			return true;
		}
	}
	return false;
}

