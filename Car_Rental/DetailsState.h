#pragma once

#include "State.h"
#include "Button.h"
#include "Json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class DetailsState : public State {
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

	std::string carName;

	sf::Text bodyText;
	sf::Text capacityText;
	sf::Text combustibleText;
	sf::Text gearboxText;
	sf::Text hpText;
	sf::Text makeText;
	sf::Text milesText;
	sf::Text modelText;
	sf::Text priceText;
	sf::Text transmissionText;
	sf::Text yearText;

	sf::Text *carDetails;

	std::string body;
	float capacity;
	std::string combustible;
	std::string gearbox;
	int hp;
	std::string make;
	std::string miles;
	std::string model;
	int price;
	std::string transmission;
	std::string year;

	Button* close;

	sf::Texture* buttonsBackground;

	// Functions
	void initWindow(sf::RenderWindow* window);
	void initBackground();
	void initVariables();
	void initFonts();
	void initText();
	void initButtons();

public:

	//Constructor -> Destructor
	DetailsState(sf::RenderWindow* window, std::stack<State*>* states, std::string carName, sf::Texture* buttonsBackground);
	virtual ~DetailsState();

	// Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};