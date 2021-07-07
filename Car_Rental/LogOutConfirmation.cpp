#include "LogOutConfirmation.h"

void LogOutConfirmation::initWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);

	std::string title = "Car Rental";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 400;
	window_bounds.height = 200;
	windowSettings.antialiasingLevel = 8;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

	if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void LogOutConfirmation::initBackground()
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

void LogOutConfirmation::initVariables()
{
	this->areYouSure.setPosition(13.f, 45.f);
	this->areYouSure.setCharacterSize(30);
	this->areYouSure.setFont(this->font);
	this->areYouSure.setString("Are you sure you want to log out?");
}

void LogOutConfirmation::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
}

void LogOutConfirmation::initButtons()
{
	this->yes = new Button(
		100.f, 120.f, 45.f, 40.f,
		&this->font,
		"Yes", 25,
		this->buttonsBackground, 20, 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->no = new Button(
		250.f, 120.f, 45.f, 40.f,
		&this->font,
		"No", 25,
		this->buttonsBackground, 20, 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

LogOutConfirmation::LogOutConfirmation(sf::RenderWindow* window, std::stack<State*>* states, sf::Texture* buttonsBackground, bool* logout) : State(window, states), buttonsBackground(buttonsBackground), logout(logout)
{
	this->initWindow(window);
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

LogOutConfirmation::~LogOutConfirmation()
{
	delete this->yes;
	delete this->no;
}

void LogOutConfirmation::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->prevWindow->setActive(true);
			this->endState();
			this->window->close();
		}
	}
}

void LogOutConfirmation::updateButtons()
{
	this->yes->update(this->mousePosView);
	this->no->update(this->mousePosView);

	if (this->yes->isPressed()) {
		*this->logout = true;
		this->prevWindow->setActive(true);
		this->window->close();
		this->endState();
	}

	if (this->no->isPressed()) {
		*this->logout = false;
		this->prevWindow->setActive(true);
		this->window->close();
		this->endState();
	}
}

void LogOutConfirmation::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void LogOutConfirmation::renderButtons(sf::RenderTarget* target)
{
	this->yes->render(target);
	this->no->render(target);
}

void LogOutConfirmation::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);

	target->draw(this->areYouSure);
	this->renderButtons(target);
	this->window->display();
}
