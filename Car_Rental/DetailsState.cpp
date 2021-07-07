#include "DetailsState.h"

void DetailsState::initWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);

	std::string title = "Car Rental";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 600;
	window_bounds.height = 400;
	windowSettings.antialiasingLevel = 8;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

	if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void DetailsState::initBackground()
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

void DetailsState::initVariables()
{
	this->carName = "";

	this->body = "";
	this->capacity = 0;
	this->combustible = "";
	this->gearbox = "";
	this->hp = 0;
	this->make = "";
	this->miles = "";
	this->model = "";
	int price = 0;
	this->transmission = "";
	this->year = "";

	this->bodyText.setString("");
	this->capacityText.setString("");
	this->combustibleText.setString("");
	this->gearboxText.setString("");
	this->hpText.setString("");
	this->makeText.setString("");
	this->milesText.setString("");
	this->modelText.setString("");
	this->priceText.setString("");
	this->transmissionText.setString("");
	this->yearText.setString("");
}

void DetailsState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
}

void DetailsState::initText()
{
	this->carDetails = new sf::Text[11];

	std::ifstream i("Resources/Makes/Cars.json");
	json j;
	i >> j;
	i.close();

	for (auto& x : j.items()) {
		std::string modelValue = x.value().find("Model").value();

		if (this->carName.compare(modelValue) == 0) {
			
			this->body = x.value().find("Body").value();
			this->capacity = x.value().find("Capacity").value();
			this->combustible = x.value().find("Combustible").value();
			this->gearbox = x.value().find("Gearbox").value();
			this->hp = x.value().find("Hp").value();
			this->make = x.value().find("Make").value();
			this->miles = x.value().find("Miles").value();
			this->model = modelValue;
			this->price = x.value().find("Price").value();
			this->transmission = x.value().find("Transmission").value();
			this->year = x.value().find("Year").value();

			break;
		}
	}

	float pozX = 10.f, pozY = 10.f;
	for (int it = 0; it < 11; it++) {

		if (it == 6) {
			pozX = 300.f;
			pozY = 10.f;
		}
			

		this->carDetails[it].setFont(this->font);
		this->carDetails[it].setCharacterSize(20);
		this->carDetails[it].setFillColor(sf::Color::White);
		this->carDetails[it].setPosition(pozX, pozY);

		pozY += 50.f;
	}

	this->carDetails[0].setString("Body: " + this->body);

	std::string capacityAux = std::to_string(this->capacity);
	capacityAux.erase(2, 5);

	this->carDetails[1].setString("Capacity: " + capacityAux + " cmc");

	this->carDetails[2].setString("Combustible: " + this->combustible);

	this->carDetails[3].setString("Gearbox: " + this->gearbox);

	this->carDetails[4].setString("Hp: " + std::to_string(this->hp));

	this->carDetails[5].setString("Make: " + this->make);

	this->carDetails[6].setString("Miles: " + this->miles + " Km");

	this->carDetails[7].setString("Model: " + this->model);

	this->carDetails[8].setString("Price/day: " + std::to_string(this->price) + " E");

	this->carDetails[9].setString("Transmission: " + this->transmission);

	this->carDetails[10].setString("Year: " + this->year);
}

void DetailsState::initButtons()
{
	this->close = new Button(
		static_cast<float>(this->window->getSize().x / 2.f - 22.f), 
		static_cast<float>(this->window->getSize().y - 75.f),
		70.f, 45.f,
		&this->font,
		"Close", 35,
		this->buttonsBackground, 20, 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

DetailsState::DetailsState(sf::RenderWindow* window, std::stack<State*>* states, std::string carName, sf::Texture* buttonsBackground) : State(window, states), buttonsBackground(buttonsBackground)
{
	this->initWindow(window);
	this->initVariables();
	this->carName = carName;
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

DetailsState::~DetailsState()
{
	delete this->close;
}

void DetailsState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->endState();
			this->window->close();
		}
	}
}

void DetailsState::updateButtons()
{
	this->close->update(this->mousePosView);

	if (this->close->isPressed()) {
		this->window->close();
		this->endState();
	}
}

void DetailsState::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();

	// std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void DetailsState::renderButtons(sf::RenderTarget* target)
{
	this->close->render(target);
}

void DetailsState::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);

	for(int it = 0; it < 11; it++)
		target->draw(this->carDetails[it]);

	this->renderButtons(target);
	this->window->display();
}
