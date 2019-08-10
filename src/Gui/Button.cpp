#include "Button.h"
#include "../PlayState.h"
#include "GuiObject.h"
Button::Button()
{
}

Button::Button(const sf::String &s, sf::Font & font, sf::Vector2f position) : GuiObject(position)
{
	
	this->font = font;
	textNormal = sf::Color(255, 255, 255);
	textHover = sf::Color(255, 255, 255);
	textClicked = sf::Color(255, 255, 255);
	bgNormal = sf::Color(255, 255, 255, 100);
	bgHover = sf::Color(200, 200, 200, 100);
	bgClicked = sf::Color(150, 150, 150);
	border = sf::Color(255, 255, 255, 100);


	this->text.setString(s);
	text.setFont(font);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setFillColor(textNormal);

	borderRadius = 5.f;
	borderThickness = 0.f;
	this->size = sf::Vector2f(text.getGlobalBounds().width * 1.5f, text.getGlobalBounds().height * 1.5f);

	button = sf::RectangleShape(size);

	button.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
	button.setPosition(position);

	sf::Vector2f textPosition = sf::Vector2f(button.getPosition().x, button.getPosition().y - button.getGlobalBounds().height / 4);

	text.setPosition(textPosition);

	this->sentered = true;
	
}

Button::~Button()
{
}

void Button::update(sf::Event & e, sf::RenderWindow & window)
{
	GuiObject::update(e, window);
	switch(this->getState()){
	case CLICKED:
		button.setFillColor(bgClicked);
		text.setFillColor(textClicked);
		if ( callback && !isHidden() && !oldHidden) {
			callback();
		}
		break;
	case HOVER:

		text.setFillColor(textHover);
		button.setFillColor(bgHover);

		break;
	case NORMAL:

		text.setFillColor(textNormal);
		button.setFillColor(bgNormal);
		break;
	}
	oldHidden = isHidden();
}

void Button::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(button, states);
	
	target.draw(text, states);
}

void Button::setCallback(Callback callback)
{
	this->callback = std::move(callback);	

}
