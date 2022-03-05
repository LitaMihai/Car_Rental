#ifndef EMAILVERIFICATIONSTATE_H
#define EMAILVERIFICATIONSTATE_H

#include "State.h"
#include "Button.h"
#include "SimpleHash.h"
#include "curl/curl.h"
#include <stdlib.h>

struct upload_status {
	size_t bytes_read;
};

static char* payload_text = new char;

static CURL* curl;
static CURLcode res = CURLE_OK;
static struct curl_slist* recipients = NULL;
static struct upload_status upload_ctx = { 0 };

class EmailVerificationState : public State
{
private:
	// Variables

	sf::Event event;

	std::string codeInput;
	sf::Text codeText;
	sf::Text codeLabel;

	sf::Text incorrectCode;

	std::map<std::string, Button*> buttons;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	int code;

	sf::Clock clock;
	sf::Time text_effect_time;
	bool show_cursor;

	std::string emailString;
	std::string password;

	sf::Text email;
	sf::Text anEmailWasSent;
	sf::Text pleaseEnterTheCodeBelow;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();

	bool codeVerif(std::string codeInput);
	bool addAccount(std::string email, std::string password);

	static size_t payload_source(char* ptr, size_t size, size_t nmemb, void* userp);
	int sendEmail(std::string email);

public:
	// Constructor - Destructor
	EmailVerificationState(sf::RenderWindow* window, std::stack<State*>* states, std::string* emailString, std::string* password);
	virtual ~EmailVerificationState();

	// Functions
	void updateSFMLEvents();
	void updateCursor();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

#endif