#pragma once

#include "State.h"
#include "AccountState.h"

class Application
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	//Initializations
	void initVariables();
	void initWindow();
	void initStates();


public:
	//Constructor - Destructor

	Application();
	virtual ~Application();

	//Functions
	void endApplication();

	void updateDt();
	void updateSFMLEvents();
	void update();

	void render();

	void run();
};

