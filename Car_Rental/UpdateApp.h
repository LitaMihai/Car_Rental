#pragma once

#include "State.h"
#include "Button.h"
#include <Python.h>

class UpdateApp :public State
{
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

	DbConnection *dataBase;
	std::string version;

	sf::Text updateText;
	sf::Text appWillOpen;

	Button *yes, *no;

	// Functions
	void initWindow(sf::RenderWindow* window);
	void initBackground();
	void initVariables();
	void initFonts();
	void initButtons();
	void beginUpdate();
	void readTheNewVersion();

public:

	// Constructor -> Destructor
	UpdateApp(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* DataBase);
	virtual ~UpdateApp();

	// Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

