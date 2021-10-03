#pragma once

#include "State.h"
#include "Button.h"
#include <curl/curl.h>
#include <shellapi.h>

class Contacts : public State
{
private:
	// Variables
	sf::Text title;

	sf::Texture fbImageTexture;
	sf::Texture instaImageTexture;
	sf::Texture wappImageTexture;

	sf::Sprite fbImageSprite;
	sf::Sprite instaImageSprite;
	sf::Sprite wappImageSprite;

	std::map<std::string, Button*> buttons;

	sf::Event event;

	sf::RectangleShape background;
	sf::Font* font;

	// Functions
	void initBackground();
	void initText();
	void initIcons();
	void initButtons();
	void openLink(std::string link);

public:
	// Constructor - Destructor
	Contacts(sf::RenderWindow* window, std::stack<State*>* states, sf::Font* font);
	virtual ~Contacts();

	// Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);
	void renderIcons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

