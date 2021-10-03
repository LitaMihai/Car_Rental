#pragma once

#include "State.h"
#include "Button.h"

class Settings_Covid_State : public State
{
private:
	// Variables
	sf::Text title;
	sf::Text covidMeasures;

	sf::Event event;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	Button *close;

	// Functions
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();

public:
	// Constructor - Destructor
	Settings_Covid_State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~Settings_Covid_State();

	// Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

