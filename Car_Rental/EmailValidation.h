#ifndef EMAILVALIDATION_H
#define EMAILVALIDATION_H

#include <iostream>

class EmailValidation {
private:

	bool valid;

	bool isChar(char c);
	bool isDigit(const char c);
	bool is_valid(std::string email);

public:
	EmailValidation(std::string email); // Constructor

	bool isValid();
};

#endif