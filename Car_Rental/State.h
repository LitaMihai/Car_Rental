#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <string.h>
#include <thread>
#include <chrono>
#include <map>

// Global Variables
static DbConnection database;
static sf::Font font;
static sf::Texture backgroundTexture;
static sf::RectangleShape background;

class State
{
protected:
	//Variables
	std::stack<State*>* states;
	sf::RenderWindow* window;
	bool quit;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

private:
	void initDB();
	void initFont();
	void initBackground();

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	void endState();

	virtual void updateMousePositions(sf::RenderWindow* target);
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

#endif