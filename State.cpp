#include "State.h"

void State::initDB(){
	database.declareConnection("remotemysql.com", "KXi0qciACI", "ZuQeO7OlVy", "KXi0qciACI", 3306, NULL, 0);
    database.initConnection();
    if (database.isConnected())
        std::cout << "M-am conectat la baza de date!";
}

void State::initFont(){
	if (!font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void State::initBackground(){
	background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!backgroundTexture.loadFromFile("Resources/Images/Background/bg.png"))
		throw "ERROR::ACCOUTSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	background.setTexture(&backgroundTexture);
}

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->quit = false;

	this->initDB();
	this->initBackground();
	this->initFont();
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}

void State::updateMousePositions(sf::RenderWindow* target)
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*target));
}