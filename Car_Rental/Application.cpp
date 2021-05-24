#include "Application.h"

void Application::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
}

void Application::initWindow()
{
    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    std::ifstream ifs("Config/window.ini");

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }
    else
        std::cout<<"Cannot open 'window.ini' file!";

    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    
    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);

    if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
        throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
    this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void Application::initStates()
{
    this->states.push(new AccountState(this->window, &this->states, &this->dataBase));
}

void Application::initDB()
{
    this->dataBase.declareConnection("localhost", "root", "", "car_rental", 2295, NULL, 0);
    this->dataBase.initConnection();
    if (dataBase.isConnected())
        std::cout << "M-am conectat la baza de date!";
}

Application::Application()
{   
    this->initVariables();
    this->initDB();
    this->initWindow();
    this->initStates();
}

Application::~Application()
{
    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

void Application::endApplication()
{
    std::cout << "Ending Application!" << "\n";
}

void Application::update()
{
    if (!this->states.empty()) {
        this->states.top()->update();

        if (this->states.top()->getQuit()) {
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->endApplication();
        this->window->close();
    }
}

void Application::render()
{
    this->window->clear();

    if (!this->states.empty())
        this->states.top()->render(this->window);
}

void Application::run()
{
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}
