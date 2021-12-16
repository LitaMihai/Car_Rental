#include "ForgotPassState.h"

void ForgotPassState::initVariables()
{
	this->emailInput = "";
	this->emailText.setString("");
	this->emailLabel.setString("");

	this->pleaseEnterYourEmail.setString("Please enter your email below");
	this->forgotPass.setString("Forgot Password?");
	this->emailIsNotValid.setString("");
}

void ForgotPassState::initBackground()
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

void ForgotPassState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void ForgotPassState::initText()
{
	this->emailLabel.setFont(this->font);
	this->emailLabel.setFillColor(sf::Color::White);
	this->emailLabel.setCharacterSize(40);
	this->emailLabel.setPosition(sf::Vector2f(80, 315));
	this->emailLabel.setString("Email");

	this->pleaseEnterYourEmail.setFont(this->font);
	this->pleaseEnterYourEmail.setFillColor(sf::Color::White);
	this->pleaseEnterYourEmail.setCharacterSize(30);
	this->pleaseEnterYourEmail.setPosition(sf::Vector2f(320, 280));

	this->forgotPass.setFont(this->font);
	this->forgotPass.setFillColor(sf::Color::White);
	this->forgotPass.setCharacterSize(40);
	this->forgotPass.setPosition(sf::Vector2f(280, 40));

	this->emailText.setFont(this->font);
	this->emailText.setFillColor(sf::Color::Black);
	this->emailText.setCharacterSize(28);
	this->emailText.setPosition(sf::Vector2f(255, 323));

	this->emailIsNotValid.setFont(this->font);
	this->emailIsNotValid.setFillColor(sf::Color::Red);
	this->emailIsNotValid.setCharacterSize(32);
	this->emailIsNotValid.setPosition(sf::Vector2f(250, 450));
}

void ForgotPassState::initButtons()
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

	this->buttons["EMAIL"] = new Button(
		250.f, 325.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
}

bool ForgotPassState::emailValid(std::string email)
{
	EmailValidation email1(email);
	return email1.isValid();
}

bool ForgotPassState::isRegistrated(std::string email)
{
	if (this->accountDataBase->isConnected()) {
		MYSQL_RES* result;
		MYSQL_ROW row = NULL;
		int query_rez;
		bool ok = false;

		std::string query = "SELECT `Email` FROM `users` WHERE `Email` = '" + email + "'"; //the query

		query_rez = mysql_query(this->accountDataBase->getConnection(), query.c_str()); //send the query

		result = mysql_store_result(this->accountDataBase->getConnection()); //store the result

		if (result)
			row = mysql_fetch_row(result);
		mysql_free_result(result);

		if (row)
			return true;
		else
			return false;
	}
	else {
		std::cout << "\n\n\nDATABASE NOT CONNECTED - FORGOT_PASS_STATE!\n\n\n";
		return false;
	}
}

size_t ForgotPassState::payload_source(char* ptr, size_t size, size_t nmemb, void* userp)
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

int ForgotPassState::sendEmail(std::string email)
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

ForgotPassState::ForgotPassState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase) : State(window, states), accountDataBase(accountDataBase)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

ForgotPassState::~ForgotPassState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void ForgotPassState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->endState();
			this->window->close();
		}

		if (this->event.type == sf::Event::TextEntered)
			if (std::isprint(this->event.text.unicode))
				this->emailInput += this->event.text.unicode;

		if (this->event.type == sf::Event::KeyPressed) {
			if (this->event.key.code == sf::Keyboard::BackSpace)
				if (!emailInput.empty())
					this->emailInput.pop_back();
		}
	}
}

void ForgotPassState::updateCursor()
{
	this->text_effect_time += this->clock.restart();
	if (this->text_effect_time >= sf::seconds(0.5f)) {
		this->show_cursor = !this->show_cursor;
		this->text_effect_time = sf::Time::Zero;
	}

	this->emailText.setString(this->emailInput + (show_cursor ? '|' : ' '));
}

void ForgotPassState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["CONFIRM"]->isPressed()) {
		// Verifing the email sending the mail etc
		if (emailValid(this->emailInput)) {

			if (isRegistrated(this->emailInput)) {
				// Send email
				this->sendEmail(this->emailInput);
			}

			// Next State
			this->states->push(new ForgotPassCodeState(this->window, this->states, this->accountDataBase, &this->emailInput, &this->code));
		}
		else {
			// Email not valid
			this->emailIsNotValid.setString("Email is not valid!");
		}

	}

	if (this->buttons["CANCEL"]->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}
}

void ForgotPassState::update()
{
	this->updateSFMLEvents();
	this->updateCursor();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void ForgotPassState::renderText(sf::RenderTarget* target)
{
	target->draw(this->emailLabel);
	target->draw(this->emailText);
	target->draw(this->emailIsNotValid);

	target->draw(this->pleaseEnterYourEmail);
	target->draw(this->forgotPass);
}

void ForgotPassState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void ForgotPassState::render(sf::RenderTarget* target)
{
	target->draw(this->background);

	this->renderButtons(target);
	this->renderText(target);

	this->window->display();
}
