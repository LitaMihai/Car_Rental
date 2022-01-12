#ifndef SIMPLEHASH_H
#define SIMPLEHASH_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

class Hash_t {
private:

	std::string input;
	std::string hash;

	unsigned int SHF(std::string input); // simple hash function
	std::string ToHex(unsigned int input); // to hex

public:
	Hash_t(std::string input); //Constructor

	std::string ReturnHash(); // Return the hashed password
};

#endif