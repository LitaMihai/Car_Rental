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

	void initVariables();

public:

	//Constructor
	DbConnection();
	virtual ~DbConnection();

	//Functions
	void declareConnection(const char* host, const char* user, const char* pass, const char* db, int port, char* sck, int flags);
	void initConnection();
	void closeConnection(MYSQL * conn);
	bool isConnected();
	MYSQL* getConn();
	MYSQL* getConnection();
};

