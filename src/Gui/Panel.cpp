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


void Panel::update(sf::Event & e, sf::RenderWindow & window)
{
	for ( GuiObject o : objects )
	{
		o.update(e, window);
	}
}

void Panel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for ( GuiObject o : objects ) {
		target.draw(o);
	}
}

