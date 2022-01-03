#ifndef APPLICATION_H
#define APPLICATION_H

#include "State.h"
#include "AccountState.h"
#include "RegistrationState.h"
#include "DbConnection.h"

#include "AccountSettings.h" // TO BE DELETED

class Application{

private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	bool updateApp;

	std::stack<State*> states;

	sf::Image icon;

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
	void update();

	//Render
	void render();

	//Core
	void run();
};

#endif