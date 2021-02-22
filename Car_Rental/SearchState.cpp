#include "SearchState.h"

void SearchState::InitWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);

	std::string title = "Car_Rental";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 1600;
	window_bounds.height = 900;
	windowSettings.antialiasingLevel = 0;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);
}

SearchState::SearchState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase) : State(window, states)
{
	InitWindow(window);
}

SearchState::~SearchState()
{
}

void SearchState::updateSFMLEvents()
{
}

void SearchState::updateCursor()
{
}

void SearchState::updateButtons()
{
}

void SearchState::update()
{
}

void SearchState::renderText(sf::RenderTarget* target)
{
}

void SearchState::renderButtons(sf::RenderTarget* target)
{
	
}

void SearchState::render(sf::RenderTarget* target)
{
}
