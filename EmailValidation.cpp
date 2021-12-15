#include "EmailValidation.h"

bool EmailValidation::isChar(char c)
{
	return ((c >= 'A' && c <= 'Z') || c >= 'a' && c <= 'z');
}

bool EmailValidation::isDigit(const char c)
{
	return (c >= '0' && c <= '9');
}

bool EmailValidation::is_valid(std::string email)
{
	if (!isChar(email[0]))
		return false;
	
	int At = -1, Dot = -1;

	for (int i = 0; i < email.length(); i++) {
		if (email[i] == ' ')
			return false;

		if (email[i] == '@')
			At = i;

		else if (email[i] == '.')
			Dot = i;
	}

	if (At == -1 || Dot == -1)
		return false;
	
	if (At > Dot)
		return false;

	return !(Dot >= (email.length() - 1));
}

EmailValidation::EmailValidation(std::string email)
{
	this->valid = is_valid(email);
}

bool EmailValidation::isValid()
{
	return this->valid;
}
