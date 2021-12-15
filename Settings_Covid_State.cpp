#include "Settings_Covid_State.h"

void Settings_Covid_State::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/bg.png"))
		throw "ERROR::ACCOUTSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
}

void Settings_Covid_State::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void Settings_Covid_State::initText()
{
	this->title.setFillColor(sf::Color::White);
	this->title.setCharacterSize(40);
	this->title.setPosition(sf::Vector2f(260, 60));
	this->title.setFont(this->font);
	this->title.setString("Covid-19 Measures");

	this->covidMeasures.setFont(this->font);
	this->covidMeasures.setFillColor(sf::Color::White);
	this->covidMeasures.setCharacterSize(26);
	this->covidMeasures.setPosition(sf::Vector2f(50, 200));
	this->covidMeasures.setString(
								"Stand in the position markings in queues at entrance/exits !\n"
								"Keep physical distance of at least 1 metre !\n"
								"Clean hands frequently with soap and water or hand sanitizer !\n"
								"Wearing a mask is mandatory inside the rental office !\n"
								"\n\n"
								"We disinfect the cars before delivery and after their return from customers !"
								);
}

void Settings_Covid_State::initButtons()
{
	this->close = new Button(
		620.f, 490.f, 100.f, 70.f,
		&this->font,
		"Close", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

Settings_Covid_State::Settings_Covid_State(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

Settings_Covid_State::~Settings_Covid_State()
{
	delete this->close;
}

void Settings_Covid_State::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) 
			this->endState();
	}
}

void Settings_Covid_State::updateButtons()
{
	this->close->update(this->mousePosView);

	if (this->close->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}
}

void Settings_Covid_State::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void Settings_Covid_State::renderText(sf::RenderTarget* target)
{
	target->draw(this->title);
	target->draw(this->covidMeasures);
}

void Settings_Covid_State::renderButtons(sf::RenderTarget* target)
{
	this->close->render(target);
}

void Settings_Covid_State::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);

	this->renderButtons(target);
	this->renderText(target);

	this->window->display();
}
