#pragma once
#include "Gui.h"
#include "Button.h"
#include <vector>
#include "GuiObject.h"
#include "Text.h"
class PlayGui : Gui
{
public:
	PlayGui();
	~PlayGui();

	void initialize();

	void update(sf::Event& e, sf::RenderWindow& window);

	void draw(sf::RenderTarget& target);


	void addButton(const sf::String &s, const sf::Vector2f &pos, Button::Callback callback);
	void addButton(Button *button);

	bool isMouseOverGUI();

private:

	std::vector<GuiObject*> objects;

	Text* text;
	sf::Text text1;
	sf::Text text2;
	sf::Text text3;
	Text *text4;
	Text *text5;
	Text *text6;
	Button *buildButton;
	Button *exitBuildButton;
};