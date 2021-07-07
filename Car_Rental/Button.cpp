#include "Button.h"

Button::Button(
	float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Texture* buttons_background, int poz_rect_x, int poz_rect_y,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);

	/*this->shape.setTexture(buttons_background);
	this->shape.setTextureRect(sf::IntRect(poz_rect_x, poz_rect_y, width, height));*/

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		static_cast<int>(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f),
		static_cast<int>(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f)
	);
	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->coolDown = 0.f;
}

Button::~Button() {

}

const bool Button::isPressed() const {
	if (this->buttonState == BTN_ACTIVE) 
		return true;
	return false;
}

void Button::move(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));

	this->text.setPosition(
		static_cast<int>(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f),
		static_cast<int>(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f)
	);
}

std::string Button::returnName()
{
	return this->text.getString();
}

void Button::update(const sf::Vector2f mousePos) {
	//Idle
	this->buttonState = BTN_IDLE;
	if(this->coolDown > -5.f)
		this->coolDown -= 1.f;
	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->coolDown < 0) {
			this->buttonState = BTN_ACTIVE;
			this->coolDown = 20.f;
		}
	}

	switch (this->buttonState) {
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void Button::render(sf::RenderTarget* target){
	target->draw(this->shape);
	target->draw(this->text);
}
