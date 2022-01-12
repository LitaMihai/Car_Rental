#include "EmailVerificationState.h"

void EmailVerificationState::initVariables()
{
	this->codeInput = "";
	this->codeText.setString("");
	this->codeLabel.setString("");

	this->incorrectCode.setString("");

	this->email.setString("");
	this->anEmailWasSent.setString("An email with a code was sent to:");
	this->pleaseEnterTheCodeBelow.setString("Please enter the code below");
}

void EmailVerificationState::initBackground()
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

void EmailVerificationState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void EmailVerificationState::initText()
{
	this->codeLabel.setFont(this->font);
	this->codeLabel.setFillColor(sf::Color::White);
	this->codeLabel.setCharacterSize(40);
	this->codeLabel.setPosition(sf::Vector2f(80, 315));
	this->codeLabel.setString("Code");

	this->incorrectCode.setFont(this->font);
	this->incorrectCode.setFillColor(sf::Color::White);
	this->incorrectCode.setCharacterSize(32);
	this->incorrectCode.setPosition(sf::Vector2f(20, 450));

	this->codeText.setFont(this->font);
	this->codeText.setFillColor(sf::Color::Black);
	this->codeText.setCharacterSize(28);
	this->codeText.setPosition(sf::Vector2f(255, 323));

	this->email.setFont(this->font);
	this->email.setFillColor(sf::Color::White);
	this->email.setCharacterSize(40);
	this->email.setPosition(sf::Vector2f(220, 90));
	this->email.setString(this->emailString);

	this->anEmailWasSent.setFillColor(sf::Color::White);
	this->anEmailWasSent.setCharacterSize(40);
	this->anEmailWasSent.setPosition(sf::Vector2f(150, 40));
	this->anEmailWasSent.setFont(this->font);

	this->pleaseEnterTheCodeBelow.setFillColor(sf::Color::White);
	this->pleaseEnterTheCodeBelow.setCharacterSize(30);
	this->pleaseEnterTheCodeBelow.setPosition(sf::Vector2f(320, 280));
	this->pleaseEnterTheCodeBelow.setFont(this->font);
}

void EmailVerificationState::initButtons()
{
	this->buttons["CANCEL"] = new Button(
		620.f, 490.f, 100.f, 70.f,
		&this->font,
		"Cancel", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CONFIRM"] = new Button(
		50.f, 490.f, 175.f, 70.f,
		&this->font,
		"Confirm", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CODE"] = new Button(
		250.f, 325.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
}

bool EmailVerificationState::codeVerif(std::string codeInput)
{
	if (this->code == atoi(codeInput.c_str())) 
		return true;

	return false;
}

bool EmailVerificationState::addAccount(std::string email, std::string password)
{
	if (this->accountDataBase->isConnected()) {
		MYSQL_RES* result;
		MYSQL_ROW row = NULL;

		Hash_t hashedPassword(password);
		password = hashedPassword.ReturnHash();

		std::string query = "INSERT INTO `users`(`ID`, `Email`, `Password`) VALUES (0, '" + email + "', '" + password + "')"; //the query

		mysql_query(this->accountDataBase->getConnection(), query.c_str()); //send the query

		result = mysql_store_result(this->accountDataBase->getConnection()); //store the result

		if (result)
			row = mysql_fetch_row(result);
		mysql_free_result(result);

		if (!row)
			return true;
		else
			return false;
	}
	else return false;
}

size_t EmailVerificationState::payload_source(char* ptr, size_t size, size_t nmemb, void* userp)
{
	struct upload_status* upload_ctx = (struct upload_status*)userp;
	const char* data;
	size_t room = size * nmemb;

	if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
		return 0;
	}

	data = &payload_text[upload_ctx->bytes_read];

	if (data) {
		size_t len = strlen(data);
		if (room < len)
			len = room;
		memcpy(ptr, data, len);
		upload_ctx->bytes_read += len;

		return len;
	}

	return 0;
}

int EmailVerificationState::sendEmail(std::string email)
{
	srand(time(NULL));

	char securityCode[5];
	this->code = rand() % 9000 + 1000;
	//_itoa(this->code, securityCode, 10);
	sprintf(securityCode, "%d", this->code);

	strcpy(payload_text,
		"To: "
	);
	strcat(payload_text, email.c_str());
	strcat(payload_text,
		"\r\n"
		"From: " "<Car_Rental2021@outlook.com>" "\r\n"
		"Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
		"rfcpedant.example.org>\r\n"
		"Subject: Car Rental account security code\r\n"
		"\r\n\r\n"
		"Security code: "
	);
	strcat(payload_text, securityCode);
	strcat(payload_text,
		"\r\n"
		"\r\n\r\n"
		"If you didn't request this code, you can safely ignore this email. Someone else might have typed your email address by mistake.\r\n"
		"\r\n\r\n"
		"Thanks, \r\n"
		"The Car Rental Staff\r\n"
	);

	curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_USERNAME, "litamihai13@gmail.com");
		curl_easy_setopt(curl, CURLOPT_PASSWORD, "bzntvcvykbxmxsyn");

		curl_easy_setopt(curl, CURLOPT_URL, "smtp.gmail.com:587");

		curl_easy_setopt(curl, CURLOPT_SASL_AUTHZID, "Car Rental's Team");

		curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, "AUTH=PLAIN");

		curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

		curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<Car_Rental2021@outlook.com>");

		recipients = curl_slist_append(recipients, email.c_str());

		curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

		curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
		curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		curl_slist_free_all(recipients);

		curl_easy_cleanup(curl);
	}

	return (int)res;
}

EmailVerificationState::EmailVerificationState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase, std::string* emailString, std::string* password) : State(window, states), emailString(*emailString), password(*password), accountDataBase(accountDataBase)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();

	// Email Verification state
	this->sendEmail(this->emailString);
}

EmailVerificationState::~EmailVerificationState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void EmailVerificationState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->endState();
			this->window->close();
		}
			
		if (this->event.type == sf::Event::TextEntered)
			if (std::isprint(this->event.text.unicode))
				this->codeInput += this->event.text.unicode;

		if (this->event.type == sf::Event::KeyPressed) {
			if (this->event.key.code == sf::Keyboard::BackSpace)
				if (!codeInput.empty())
					this->codeInput.pop_back();
		}
	}
}

void EmailVerificationState::updateCursor()
{
	this->text_effect_time += this->clock.restart();
	if (this->text_effect_time >= sf::seconds(0.5f)) {
		this->show_cursor = !this->show_cursor;
		this->text_effect_time = sf::Time::Zero;
	}

	this->codeText.setString(this->codeInput + (show_cursor ? '|' : ' '));
}

void EmailVerificationState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["CONFIRM"]->isPressed()) {
		if (codeVerif(this->codeInput)) {

			// Adding the account in the database.
			if (this->addAccount(this->emailString, this->password)) 
				std::cout << "Account registrated!";

			else
				std::cout << "Account wasn't registrared!";
			
			this->endState();
			this->states->pop();
			this->states->top()->endState();
		}
		else 
			this->incorrectCode.setString("The code is not correct!!!");
	}

	if (this->buttons["CANCEL"]->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}
}

void EmailVerificationState::update()
{
	this->updateSFMLEvents();
	this->updateCursor();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void EmailVerificationState::renderText(sf::RenderTarget* target)
{
	target->draw(this->codeLabel);

	target->draw(this->email);
	target->draw(this->anEmailWasSent);
	target->draw(this->pleaseEnterTheCodeBelow);

	target->draw(this->codeText);
	target->draw(this->incorrectCode);
}

void EmailVerificationState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void EmailVerificationState::render(sf::RenderTarget* target)
{
	target->draw(this->background);

	this->renderButtons(target);
	this->renderText(target);

	this->window->display();
}
