#pragma once

#include "State.h"
#include "Button.h"

class LogOutConfirmation : public State {
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

	sf::Text areYouSure;
	bool* logout;

	Button* yes, *no;

	sf::Texture* buttonsBackground; // For later
	
	// Functions
	void initWindow(sf::RenderWindow* window);
	void initBackground();
	void initVariables();
	void initFonts();
	void initButtons();

public:

	// Constructor - Destructor
	LogOutConfirmation(sf::RenderWindow* window, std::stack<State*>* states, sf::Texture* buttonsBackground, bool* logout);
	virtual ~LogOutConfirmation();

	// Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};