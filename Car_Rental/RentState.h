#pragma once

#include "State.h"
#include "Button.h"

class RentState : public State {

private:
	// Variables
	sf::RenderWindow* prevWindow;
	sf::RenderWindow* window;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;

	sf::Image icon;

	sf::Event event;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	sf::Text rented;

	Button *ok;

	// Functions
	void initWindow(sf::RenderWindow* window);
	void initBackground();
	void initVariables();
	void initFonts();
	void initButtons();

public:

	// Constructor -> Destructor
	RentState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~RentState();

	// Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};