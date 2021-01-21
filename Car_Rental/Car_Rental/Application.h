#pragma once

#include "State.h"
#include "AccountState.h"
#include "RegistrationState.h"

class Application
{
private:
	//Variables
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

	//Update
	void updateDt();
	void update();

	//Render
	void render();

	//Core
	void run();
};

