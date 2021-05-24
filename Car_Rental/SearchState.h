#pragma once

#include "iomanip"
#include "State.h"
#include "Button.h"
#include "Json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class SearchState : public State
{
private:
	//Variables
	sf::RenderWindow* prevWindow;
	sf::RenderWindow* window;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;

	std::map<std::string, Button*> buttons;
	std::map<std::string, Button*> make;
	std::map<std::string, Button*> model;

	sf::Event event;

	bool renderLineForModels;
	bool renderTheLastLine;
	
	bool buttonsMoved;

	sf::Texture leftButtonTexture;
	sf::Sprite leftButtonSprite;
	sf::Texture rightButtonTexture;
	sf::Sprite rightButtonSprite;

	sf::Texture firstPhotoTexture;
	sf::Sprite firstPhotoSprite;
	sf::Texture secondPhotoTexture;
	sf::Sprite secondPhotoSprite;

	sf::RectangleShape shape;

	bool seePhoto;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::RectangleShape linie[4];

	sf::Image icon;

	//Functions
	void initWindow(sf::RenderWindow* window);
	void initVariables();
	void initBackground();
	void initLines();
	void initFonts();
	void initButtons();
	void initMake();
	void initModel();

public:
	//Constructor-Destructor
	SearchState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase);
	virtual ~SearchState();

	//Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderLines(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

