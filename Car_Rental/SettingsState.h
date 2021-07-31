#pragma once

#include "State.h"
#include "Button.h"
#include "DesignSettings.h"

class SettingsState : public State
{
private:
	// Variables
	sf::RenderWindow* prevWindow;
	sf::RenderWindow* window;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;

	std::map<std::string, Button*> buttons;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	sf::Text settings;

	sf::Event event;

	sf::Image icon;

	// Functions
	void initWindow(sf::RenderWindow* window);
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();

public:
	// Constructor-Destructor
	SettingsState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~SettingsState();

	// Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

