#include "Contacts.h"

void Contacts::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->background.setFillColor(sf::Color(0, 0, 0, 255));
}

void Contacts::initText()
{
	this->title.setFillColor(sf::Color::White);
	this->title.setCharacterSize(55);
	this->title.setPosition(sf::Vector2f(310, 60));
	this->title.setFont(*this->font);
	this->title.setString("Contacts");
}

void Contacts::initIcons()
{
	if (!this->fbImageTexture.loadFromFile("Resources/Images/Icon/facebook.png"))
		std::cout << "!FACEBOOK ICON NOT LOADED!";
	this->fbImageTexture.setSmooth(true);

	if (!this->instaImageTexture.loadFromFile("Resources/Images/Icon/instagram.png"))
		std::cout << "!INSTAGRAM ICON NOT LOADED!";
	this->instaImageTexture.setSmooth(true);

	if (!this->wappImageTexture.loadFromFile("Resources/Images/Icon/wapp.png"))
		std::cout << "!WHATSAPP ICON NOT LOADED!";
	this->wappImageTexture.setSmooth(true);

	this->fbImageSprite.setTexture(this->fbImageTexture);
	this->fbImageSprite.setScale(sf::Vector2f(0.1, 0.1));
	this->fbImageSprite.setPosition(sf::Vector2f(100.f, 165.f));

	this->instaImageSprite.setTexture(this->instaImageTexture);
	this->instaImageSprite.setScale(sf::Vector2f(0.05, 0.05));
	this->instaImageSprite.setPosition(sf::Vector2f(100.f, 265.f));

	this->wappImageSprite.setTexture(this->wappImageTexture);
	this->wappImageSprite.setScale(sf::Vector2f(0.13, 0.13));
	this->wappImageSprite.setPosition(sf::Vector2f(100.f, 365.f));
}

void Contacts::initButtons()
{
	this->buttons["CLOSE"] = new Button(
		620.f, 490.f, 100.f, 70.f,
		this->font,
		"Close", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["FACEBOOK"] = new Button(
		250.f, 175.f, 250.f, 30.f,
		this->font,
		"Lita Mihai (Developer)", 30,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["INSTAGRAM"] = new Button(
		250.f, 275.f, 250.f, 30.f,
		this->font,
		"Lita Mihai (Developer)", 30,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["WAPP"] = new Button(
		245.f, 375.f, 450.f, 35.f,
		this->font,
		"0000234523 (Random False Number)", 30,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void Contacts::openLink(std::string link)
{
	// Conversion to wide string
	int len;
	int slength = (int)link.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, link.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, link.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	
	ShellExecute(0, 0, r.c_str(), 0, 0, SW_SHOW);
}

Contacts::Contacts(sf::RenderWindow* window, std::stack<State*>* states, sf::Font* font) : State(window, states), font(font)
{
	this->initBackground();
	this->initText();
	this->initIcons();
	this->initButtons();
}

Contacts::~Contacts()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void Contacts::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->endState();
	}
}

void Contacts::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["CLOSE"]->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}

	if (this->buttons["FACEBOOK"]->isPressed()) {
		this->openLink("https://www.facebook.com/mihailita.mihai/");
	}

	if (this->buttons["INSTAGRAM"]->isPressed()) {
		this->openLink("https://www.instagram.com/mihai._alexandru/");
	}

	if (this->buttons["WAPP"]->isPressed()) {
		this->openLink("https://web.whatsapp.com/");
	}
}

void Contacts::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void Contacts::renderText(sf::RenderTarget* target)
{
	target->draw(this->title);
}

void Contacts::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void Contacts::renderIcons(sf::RenderTarget* target)
{
	target->draw(this->fbImageSprite);
	target->draw(this->instaImageSprite);
	target->draw(this->wappImageSprite);
}

void Contacts::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);

	this->renderButtons(target);
	this->renderText(target);
	this->renderIcons(target);

	this->window->display();
}
