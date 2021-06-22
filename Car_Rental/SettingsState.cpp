#include "SettingsState.h"

void SettingsState::initWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);

	std::string title = "Car Rental";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 800;
	window_bounds.height = 600;
	windowSettings.antialiasingLevel = 16;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

	if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void SettingsState::initVariables()
{

}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->background.setFillColor(sf::Color(57, 62, 70, 255));
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
}

void SettingsState::initButtons()
{
	this->buttons["DESIGN_SETTINGS"] = new Button(
		0, 0,
		225.f, 25.f,
		&this->font,
		"Design Settings", 20,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 255), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ACCOUNT_SETTINGS"] = new Button(
		0, 25, 
		225.f, 25.f,
		&this->font,
		"Account Settings", 20,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 255), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ABOUT_US"] = new Button(
		0, 100,
		225.f, 25.f,
		&this->font,
		"About Us", 20,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 255), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

SettingsState::SettingsState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initWindow(window);
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void SettingsState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->prevWindow->setActive(true);
			this->window->close();
			this->endState();
		}
	}
}

void SettingsState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["DESIGN_SETTINGS"]->isPressed())
		this->states->push(new DesignSettings(this->window, this->states));

	if (this->buttons["ABOUT_US"]->isPressed()) {
		this->prevWindow->setActive(true);
		this->window->close();
		this->endState();
	}
}

void SettingsState::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void SettingsState::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);

	this->renderButtons(target);
	this->window->display();
}