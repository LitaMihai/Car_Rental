#pragma once

#include <mysql.h>
#include <iostream>

class DbConnection
{
private:
	const char* host;
	const char* user;
	const char* pass;
	const char* db;
	int port;
	char* sck;
	int flags;
	MYSQL* conn;
	MYSQL* connection;

public:

	//Constructor
	DbConnection(
		const char* host, const char* user, const char* pass, const char* db,
		int port, char* sck, int flags
	);
	
	//Functions
	void initConnection();
	void closeConnection(MYSQL * conn);
	MYSQL* getConn();
};

