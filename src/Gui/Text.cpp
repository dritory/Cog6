#include "Text.h"

Text::Text(const sf::String & s,const sf::Font &font, const sf::Vector2f & pos)
{
	text = sf::Text(s, font);
	
	text.setFillColor(sf::Color(255, 255, 255));

	text.setPosition(pos);


	this->sentered = false;
}

Text::Text(const sf::String & s, const sf::Font & font, sf::Vector2f position, bool sentered)
{
	text = sf::Text(s, font);

	text.setFillColor(sf::Color(255, 255, 255));

	text.setPosition(position);
	
	if ( sentered ) {
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	}
	this->sentered = sentered;

}

Text::~Text()
{
}

bool Text::update(sf::Event & e, sf::RenderWindow & window)
{
	return true;
}   

void Text::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text, states);
}
