#include "SettingsState.h"

void SettingsState::initWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);
	this->prevWindow->setVisible(false);

	std::string title = "Car Rental";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 800;
	window_bounds.height = 600;
	windowSettings.antialiasingLevel = 8;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

	if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void SettingsState::initVariables()
{
	int windowX = this->window->getSize().x;
	int windowY = this->window->getSize().y;

	this->settings.setPosition(windowX / 2.f - 75.f, 10.f);
	this->settings.setCharacterSize(50);
	this->settings.setFillColor(sf::Color::White);
	this->settings.setFont(this->font);
	this->settings.setString("Settings");
}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->background.setFillColor(sf::Color(0, 0, 0, 255));
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
}

void SettingsState::initButtons()
{	
	int windowX = this->window->getSize().x;
	int windowY	= this->window->getSize().y;
	int quarterX = windowX / 4;
	int quarterY = windowY / 4;

	this->buttons["DESIGN_SETTINGS"] = new Button(
		// 25, 100,
		quarterX - (225.f / 2), quarterY - (25.f / 2),
		225.f, 50.f,
		&this->font,
		"Design Settings", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ACCOUNT_SETTINGS"] = new Button(
		// 25, 300, 
		quarterX - (225.f / 2), 2 * quarterY - (25.f / 2),
		225.f, 50.f,
		&this->font,
		"Account Settings", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CONTACTS"] = new Button(
		// 25, 500,
		quarterX - (225.f / 2), 3 * quarterY - (25.f / 2),
		225.f, 50.f,
		&this->font,
		"Contacts", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ABOUT_US"] = new Button(
		// 425, 300,
		3 * quarterX - (225.f / 2), quarterY - (25.f / 2),
		225.f, 50.f,
		&this->font,
		"About Us", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["COVID_19"] = new Button(
		// 425, 100,
		3 * quarterX - (225.f / 2), 2 * quarterY - (25.f / 2),
		225.f, 50.f,
		&this->font,
		"Covid-19 Measures", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CLOSE"] = new Button(
		// 425, 500,
		3 * quarterX - (225.f / 2), 3 * quarterY - (25.f / 2),
		225.f, 50.f,
		&this->font,
		"Close", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
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
			this->prevWindow->setVisible(true);
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

	if (this->buttons["CONTACTS"]->isPressed())
		this->states->push(new Contacts(this->window, this->states, &this->font));

	if (this->buttons["COVID_19"]->isPressed())
		this->states->push(new Settings_Covid_State(this->window, this->states));

	if (this->buttons["CLOSE"]->isPressed()) {
		this->prevWindow->setVisible(true);
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
	target->draw(this->settings);
	this->renderButtons(target);

	this->window->display();
}