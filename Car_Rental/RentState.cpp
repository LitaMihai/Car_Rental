#include "RentState.h"

void RentState::initWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);

	std::string title = "Car Rental";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 400;
	window_bounds.height = 200;
	windowSettings.antialiasingLevel = 0;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

	if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void RentState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/bg.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
}

void RentState::initVariables()
{
	this->rented.setPosition(45.f, 45.f);
	this->rented.setCharacterSize(30);
	this->rented.setFont(this->font);
	this->rented.setString("I booked the car in the store!");
}

void RentState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
}

void RentState::initButtons()
{
	this->ok = new Button(
		180.f, 120.f, 45.f, 40.f,
		&this->font,
		"OK", 25,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

RentState::RentState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initWindow(window);
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

RentState::~RentState()
{
	delete this->ok;
}

void RentState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->endState();
			this->window->close();
		}	
	}
}

void RentState::updateButtons()
{
	this->ok->update(this->mousePosView);

	if (this->ok->isPressed()) {
		this->window->close();
		this->endState();	
	}
}

void RentState::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void RentState::renderButtons(sf::RenderTarget* target)
{
	this->ok->render(target);
}

void RentState::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);

	target->draw(this->rented);
	this->renderButtons(target);
	this->window->display();
}
