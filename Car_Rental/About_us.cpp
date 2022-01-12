#include "About_us.h"

void About_us::initBackground()
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

void About_us::initFonts()
{
    if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void About_us::initText()
{
    this->title.setFillColor(sf::Color::White);
	this->title.setCharacterSize(40);
	this->title.setPosition(sf::Vector2f(340, 60));
	this->title.setFont(this->font);
	this->title.setString("About us");

	this->paragraph1.setFillColor(sf::Color::White);
	this->paragraph1.setCharacterSize(26);
	this->paragraph1.setPosition(sf::Vector2f(50, 200));
	this->paragraph1.setFont(this->font);
	this->paragraph1.setString(
								"\t\tIt is just me, the developer!\n"
								"\n\n\n\t\t\t\t\t\tLita Mihai"
								);
}

void About_us::initImage(){
    if(!this->developer.loadFromFile("Resources/Images/Developer/Mihai.png"))
    throw "ERROR::About_us::FAILED_TO_LOAD_DEVELOPER_IMAGE";

    this->developerSprite.setTexture(this->developer);
    this->developerSprite.setPosition(sf::Vector2f(450.f, 140.f));
    this->developerSprite.setScale(0.22f, 0.25f);

}

void About_us::initButtons()
{
    this->close = new Button(
		620.f, 490.f, 100.f, 70.f,
		&this->font,
		"Close", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

About_us::About_us(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    
    this->initBackground();
	this->initFonts();
	this->initText();
    this->initImage();
	this->initButtons();

}

About_us::~About_us()
{
    delete this->close;
}

void About_us::updateSFMLEvents()
{
    while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) 
			this->endState();
	}
}

void About_us::updateButtons()
{
    this->close->update(this->mousePosView);

	if (this->close->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}
}

void About_us::update()
{
    this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void About_us::renderText(sf::RenderTarget* target)
{
    target->draw(this->title);
	target->draw(this->paragraph1);
}

void About_us::renderImage(sf::RenderTarget* target){
    target->draw(this->developerSprite);
}

void About_us::renderButtons(sf::RenderTarget* target)
{
    this->close->render(target);
}

void About_us::render(sf::RenderTarget* target)
{
    target = this->window;
	target->draw(this->background);

	this->renderButtons(target);
	this->renderText(target);
    this->renderImage(target);

	this->window->display();
}