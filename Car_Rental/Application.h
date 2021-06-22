#pragma once

#include "State.h"
#include "AccountState.h"
#include "RegistrationState.h"
#include "DbConnection.h"

class Application{

private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	bool updateApp;

	DbConnection dataBase;

	std::string version;

	std::stack<State*> states;

	sf::Image icon;

	//Initializations
	void initVariables();
	void initWindow();
	void initStates();
	void initDB();

	//Functions
	void needsUpdate();
	void deletePrevFolder();
	bool seeIfItNeedsUpdate();

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

