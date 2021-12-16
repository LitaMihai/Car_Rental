#include "SimpleHash.h"

unsigned int Hash_t::SHF(std::string input)
{
	unsigned int Init = 128752392;
	unsigned int Magic = 9132867;
	unsigned int Hash = 1;

	for (int i = 0; i < input.length(); i++) {
		Hash = Hash ^ (input[i]);
		Hash = Hash * Magic;
	}

	return Hash;
}

std::string Hash_t::ToHex(unsigned int input)
{
	std::string HexHash;
	std::stringstream hexstream;
	hexstream << std::hex << input;
	HexHash = hexstream.str();
	std::transform(HexHash.begin(), HexHash.end(), HexHash.begin(), ::toupper);

	return HexHash;
}

Hash_t::Hash_t(std::string input)
{
	this->input = input;
	this->hash = ToHex(SHF(input));
}

std::string Hash_t::ReturnHash()
{
	return this->hash;
}


