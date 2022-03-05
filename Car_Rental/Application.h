#ifndef APPLICATION_H
#define APPLICATION_H

#include "AccountState.h"
#include "DbConnection.h"

#include "SearchState.h" // TO BE DELETED

class Application{

private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::ContextSettings windowSettings;
	bool fullscreen;

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