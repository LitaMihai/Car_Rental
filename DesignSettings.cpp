#include "DesignSettings.h"

void DesignSettings::initWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);

	std::string title = "Car Rental";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 225;
	window_bounds.height = 230;
	windowSettings.antialiasingLevel = 8;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::None, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

	this->window->setPosition(sf::Vector2i(
		this->prevWindow->getPosition().x,
		this->prevWindow->getPosition().y
	));

	if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void DesignSettings::initVariables()
{
}

void DesignSettings::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->background.setFillColor(sf::Color(57, 62, 70, 255));
}

void DesignSettings::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
}

void DesignSettings::initButtons()
{
	this->buttons["BACK"] = new Button(
		0, 100,
		225.f, 25.f,
		&this->font,
		"Back", 20,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 255), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

DesignSettings::DesignSettings(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initWindow(window);
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

DesignSettings::~DesignSettings()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void DesignSettings::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->window->close();
			this->endState();
		}
	}
}

void DesignSettings::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);
		
	if (this->buttons["BACK"]->isPressed()) {
		this->prevWindow->setActive(true);
		this->window->close();
		this->endState();
	}
}

void DesignSettings::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void DesignSettings::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void DesignSettings::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);

	this->renderButtons(target);
	this->window->display();
}
