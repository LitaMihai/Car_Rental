#include "UpdateApp.h"

void UpdateApp::initWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);
	this->prevWindow->setVisible(false);

	std::string title = "Update?";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 400;
	window_bounds.height = 200;
	windowSettings.antialiasingLevel = 0;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

	if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void UpdateApp::initBackground()
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

void UpdateApp::initVariables()
{
	this->updateText.setCharacterSize(40);
	this->updateText.setFont(this->font);
	this->updateText.setString("Update?");
	this->updateText.setPosition(140.f, 45.f);
	
	this->appWillOpen.setCharacterSize(18);
	this->appWillOpen.setFont(this->font);
	this->appWillOpen.setString("The app will open after the update!");
	this->appWillOpen.setPosition(80.f, 90.f);
}

void UpdateApp::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
}

void UpdateApp::initButtons()
{
	this->yes = new Button(
		300.f, 120.f, 45.f, 40.f,
		&this->font,
		"YES", 25,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->no = new Button(
		50.f, 120.f, 45.f, 40.f,
		&this->font,
		"NO", 25,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void UpdateApp::beginUpdate()
{
	system("chdir Config && start python3.9.5.exe /quiet InstallAllUsers = 1 PrependPath = 1 Include_test = 0");
	system("pip install requests"); // reqests lib for the py script

	Py_Initialize();
	int argc = 6;
	char** argv = new char* [argc];
	for (int i = 0; i < argc; ++i)
		argv[i] = new char[100];

	strcpy(argv[0], "./Config/dropbox.py");
	strcpy(argv[1], "--read");
	strcpy(argv[2], "./Config/links.txt");
	strcpy(argv[3], "--dest");
	strcpy(argv[4], "..");
	strcpy(argv[5], "--unzip");

	wchar_t* program = Py_DecodeLocale(argv[0], NULL);

	wchar_t** _argv = new wchar_t* [argc];
	for (int i = 0; i < argc; ++i)
		_argv[i] = new wchar_t[100];

	for (int i = 0; i < argc; i++) {
		wchar_t* arg = Py_DecodeLocale(argv[i], NULL);
		_argv[i] = arg;
	}

	Py_SetProgramName(program);

	PySys_SetArgv(argc, _argv);

	FILE* file = fopen("./Config/dropbox.py", "rb");

	PyRun_SimpleFile(file, "dropbox.py");

	Py_Finalize();
	fclose(file);

	this->readTheNewVersion();

	this->font.~Font();

	// Start the updated app
	std::string folderName = "chdir .. && chdir && chdir Car_Rental_v_" + this->version + " && start Car_Rental.exe";
	char* folder_Name = &folderName[0];

	system(folder_Name);
}

void UpdateApp::readTheNewVersion()
{
	// Read from the database the new version and store it
	if (this->dataBase->isConnected()) {
		MYSQL_RES* result;
		MYSQL_ROW row = NULL;
		int query_rez;
		bool ok = false;

		std::string query = "SELECT `New Update` FROM `Need Update`"; //the query

		query_rez = mysql_query(this->dataBase->getConnection(), query.c_str()); //send the query

		result = mysql_store_result(this->dataBase->getConnection()); //store the result

		while ((row = mysql_fetch_row(result)) != NULL)
			this->version = row[0];
	}
}

UpdateApp::UpdateApp(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* DataBase) : State(window, states), dataBase(DataBase)
{
	this->initWindow(window);
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

UpdateApp::~UpdateApp()
{
	delete this->yes;
	delete this->no;
}

void UpdateApp::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->endState();
			this->window->close();
		}
	}
}

void UpdateApp::updateButtons()
{
	this->yes->update(this->mousePosView);
	this->no->update(this->mousePosView);

	if (this->no->isPressed()) {
		this->window->close();
		this->endState();
	}

	if (this->yes->isPressed()) {
		this->window->close();
		this->beginUpdate();
		this->endState();
	}
}

void UpdateApp::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void UpdateApp::renderButtons(sf::RenderTarget* target)
{
	this->yes->render(target);
	this->no->render(target);
}

void UpdateApp::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);

	target->draw(this->updateText);
	target->draw(this->appWillOpen);
	this->renderButtons(target);
	this->window->display();
}
