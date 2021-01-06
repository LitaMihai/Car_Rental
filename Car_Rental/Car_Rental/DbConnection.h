#pragma once

#include <mysql.h>
#include <iostream>

class DbConnection
{
private:
	const char* host = "localhost";
	const char* user = "root";
	const char* pass = "";
	const char* db = "car_rental";
	int port = 3306;
	char* sck = NULL;
	int flags = 0;
	MYSQL* conn;
	MYSQL* connection;

public:
	DbConnection(
		const char* host, const char* user, const char* pass, const char* db,
		int port, char* sck, int flags
	);
	~DbConnection();

	void initConnection();

};

