#pragma once

#include "State.h"
#include "AccountState.h"
#include "RegistrationState.h"
#include "DbConnection.h"

class Application
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	DbConnection dataBase;

	std::stack<State*> states;

	sf::Image icon;

	//Initializations
	void initVariables();
	void initWindow();
	void initStates();
	void initDB();

public:
	//Constructor - Destructor
	Application();
	virtual ~Application();

	//Functions
	void endApplication();

	//Update
	void update();

	//Render
	void render();

	//Core
	void run();
};

