#pragma once

#include "State.h"
#include "Button.h"
#include "curl/curl.h"
#include "EmailVerificationState.h"
#include "EmailValidation.h"
#include "ForgotPassCodeState.h"

class ForgotPassState : public State
{
private:
	// Variables

	sf::Event event;

	std::string emailInput;
	sf::Text emailText;
	sf::Text emailLabel;

	sf::Text pleaseEnterYourEmail;
	sf::Text forgotPass;
	sf::Text emailIsNotValid;

	std::map<std::string, Button*> buttons;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	sf::Clock clock;
	sf::Time text_effect_time;
	bool show_cursor;

	int code;

	DbConnection* accountDataBase;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();

	bool emailValid(std::string email);
	bool isRegistrated(std::string email);

	static size_t payload_source(char* ptr, size_t size, size_t nmemb, void* userp);
	int sendEmail(std::string email);

public:
	// Constructor - Destructor
	ForgotPassState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase);
	virtual ~ForgotPassState();

	// Functions
	void updateSFMLEvents();
	void updateCursor();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

