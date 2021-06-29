#include "Application.h"

void Application::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
    this->updateApp = false;

    std::ifstream ifs("./Config/version.ini");

    char* value = nullptr;

    if (ifs.is_open()) 
        std::getline(ifs, this->version);
    else
        std::cout << "Cannot open 'version.ini' file!";

    std::cout << "\n" << version << "\n";
    ifs.close();
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
    this->dataBase.declareConnection("remotemysql.com", "KXi0qciACI", "ZuQeO7OlVy", "KXi0qciACI", 3306, NULL, 0);
    this->dataBase.initConnection();
    if (this->dataBase.isConnected())
        std::cout << "M-am conectat la baza de date!";
}

void Application::needsUpdate()
{
    if (seeIfItNeedsUpdate())
        this->updateApp = true;
    else
        this->updateApp = false;
}

void Application::deletePrevFolder()
{
    if (this->updateApp == false) {
        std::string prevVersion;

        std::ifstream ifs("Config/prev_version.ini");

        if (ifs.is_open())
            ifs >> prevVersion;
        else
            std::cout << "Cannot open 'prev_version.ini' file!";
        ifs.close();

        std::string folderName = "rmdir /Q /S ..\\Car_Rental_v_" + prevVersion;
        char* folder_Name = &folderName[0];

        system(folder_Name);
    }
}

bool Application::seeIfItNeedsUpdate()
{
    if (this->dataBase.isConnected()) {
        MYSQL_RES* result;
        MYSQL_ROW row = NULL;
        int query_rez;
        bool ok = false;

        std::string query = "SELECT `New Update` FROM `Need Update` WHERE `New Update` = '" + this->version + "'"; //the query

        query_rez = mysql_query(this->dataBase.getConnection(), query.c_str()); //send the query

        result = mysql_store_result(this->dataBase.getConnection()); //store the result

        if (result)
            row = mysql_fetch_row(result);
        mysql_free_result(result);

        if (!row) {
            std::cout << "ARE NEVOIE DE UPDATE!";
            return true;
        }
            
        else {
            std::cout << "NU ARE NEVOIE DE UPDATE!";
            return false;
        }
    }
   
    return false;
}

Application::Application()
{
    this->initVariables();
    this->initDB();
    this->needsUpdate();
    this->deletePrevFolder();
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
