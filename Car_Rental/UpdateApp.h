#pragma once

#include "State.h"
#include "Button.h"
#include <Python.h>

class UpdateApp :public State
{
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

	Button *yes, *no;

	// Functions
	void initWindow(sf::RenderWindow* window);
	void initBackground();
	void initVariables();
	void initFonts();
	void initButtons();

	void beginUpdate();

public:

	// Constructor -> Destructor
	UpdateApp(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~UpdateApp();

	// Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

